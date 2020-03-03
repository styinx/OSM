#include "io/osmpbfReader.hpp"

#include "structures/Primitives.hpp"

#include <iomanip>
#include <iostream>
#include <osmpbf/filter.h>
#include <osmpbf/inode.h>
#include <osmpbf/irelation.h>
#include <osmpbf/iway.h>
#include <osmpbf/osmfile.h>
#include <osmpbf/parsehelpers.h>
#include <osmpbf/primitiveblockinputadaptor.h>
#include <regex>

namespace OSM
{
    osmpbfReader::osmpbfReader(const std::string& osm_file)
        : m_osm_file(osm_file, false)
    {
        m_osm_file.open();
    }

    Byte osmpbfReader::readMaxSpeed(const std::string& speed)
    {
        std::string val;
        Byte        index = 0;
        for(char c : speed)
        {
            if(c >= '0' && c <= '9')
            {
                val += c;
                index++;
            }
            else
                break;
        }
        if(val.empty())
            return 0;

        Byte        speed_val = std::stoi(val);
        std::string unit      = speed.substr(index);
        if(!unit.empty())
        {
            if(unit.find("km"))
                return speed_val;
            else if(unit.find("mp"))
                return static_cast<Byte>(std::round((float)speed_val * 1.61F));
        }
        return 0;
    }

    void osmpbfReader::printInfo(const bool timed)
    {
        if(timed)
        {
            m_timer_lock.lock();
            m_diff = Clock::now() - m_start;
            if(m_diff > m_second)
            {
                m_duration = std::chrono::duration_cast<Seconds>(Clock::now() - m_stop).count();
                m_start    = Clock::now();
                m_timer_lock.unlock();
            }
            else
            {
                m_timer_lock.unlock();
                return;
            }
        }

        std::cout << std::right << std::setw(3) << m_duration << "s"
                  << " | Nodes: " << std::right << std::setw(12) << m_nodes.first << "/"
                  << std::setw(12) << m_nodes.second << " | Ways: " << std::right << std::setw(12)
                  << m_ways.first << "/" << std::setw(12) << m_ways.second
                  << " (Edges: " << std::right << std::setw(12) << m_edges << ")" << std::endl;
    }

    void osmpbfReader::read(OSM::AdjacencyArray& array)
    {
        using namespace osmpbf;

        // Used to determine the node id.
        struct NodeHeurisitc
        {
            Uint64               index = 0;
            UMap<Sint64, Uint64> id;
        } nh{};

        // Start timer.
        m_start = Clock::now();
        m_stop  = Clock::now();

        // Set default stuff.
        WeakPtr<osmpbfReader> weakThis = shared_from_this();
        MapData::addTown("null");

        // Set filters.
        struct Filters
        {
            KeyOnlyTagFilter highway = KeyOnlyTagFilter("highway");
            KeyOnlyTagFilter speed   = KeyOnlyTagFilter("maxspeed");
            KeyOnlyTagFilter oneway  = KeyOnlyTagFilter("oneway");
        } filters{};

        // Start reading.
        std::cout << "Start reading ..." << std::endl;

        std::this_thread::sleep_for(Seconds(1));

        // Read all highway edges and the nodes we need.
        std::cout << "Collect necessary ways ..." << std::endl;
        const auto collectNodes = [&filters, &array, &nh, weakThis](PrimitiveBlockInputAdaptor& pbi) {
            Pair<Uint64, Uint64> local_way_count = {0, 0};

            if(const auto sharedThis = weakThis.lock())
            {
                sharedThis->printInfo(true);

                // Assign the filters
                sharedThis->m_filter_lock.lock();
                filters.highway.assignInputAdaptor(&pbi);

                if(!filters.highway.rebuildCache())
                {
                    sharedThis->m_filter_lock.unlock();
                    return;
                }
                sharedThis->m_filter_lock.unlock();

                // Read all ways in the block
                for(IWayStream way = pbi.getWayStream(); !way.isNull(); way.next())
                {
                    Byte mask   = 0;
                    Byte speed  = 0;
                    bool oneway = false;

                    // Filter out not matching ways
                    ++local_way_count.second;
                    if(!filters.highway.matches(way))
                        continue;
                    ++local_way_count.first;

                    // Check if the node has a speed key.
                    if(filters.speed.matches(way))
                    {
                        auto sp_idx = filters.speed.matchingTag();
                        if(sp_idx > -1)
                        {
                            speed = readMaxSpeed(way.value(sp_idx));
                        }
                    }

                    // Check if street is oneway
                    if(filters.oneway.matches(way))
                    {
                        oneway = true;
                    }

                    // Determine the type of the highway
                    auto index = filters.highway.matchingTag();
                    if(index > -1 && index < way.tagsSize())
                    {
                        const auto& value = way.value(index);
                        if(StreetType.count(value))
                        {
                            mask |= StreetType[value].first;
                            speed = StreetType[value].second;
                        }
                        else if(speed == 0)
                        {
                            mask |= StreetType["living_street"].first;
                            speed = 50;
                        }
                        else
                        {
                            mask |= StreetType[""].first;
                        }
                    }

                    if(speed == 0)
                    {
                        speed = 50;
                    }
                    if(mask == 0)
                    {
                        mask |= StreetType[""].first;
                    }

                    // Go through all nodes in the edges
                    IWay::RefIterator previous = nullptr;
                    IWay::RefIterator current  = way.refBegin();
                    for(; current != way.refEnd(); ++current)
                    {
                        if(previous != nullptr)
                        {
                            sharedThis->m_node_map_lock.lock();
                            if(!nh.id.count(*previous))
                            {
                                nh.id[*previous] = nh.index++;
                            }
                            if(!nh.id.count(*current))
                            {
                                nh.id[*current] = nh.index++;
                            }

                            Edge e{nh.id[*previous], nh.id[*current], speed, mask, oneway};
                            array.addEdge(e);
                            if(!oneway)
                            {
                                array.addEdge(e.mirror());
                            }
                            sharedThis->m_edges += 2;

                            sharedThis->m_node_map_lock.unlock();
                        }
                        previous = current;
                    }
                }

                sharedThis->m_node_map_lock.lock();
                sharedThis->m_ways.first += local_way_count.first;
                sharedThis->m_ways.second += local_way_count.second;
                sharedThis->m_node_map_lock.unlock();
            }
        };

        osmpbf::parseFileCPPThreads(m_osm_file, collectNodes, m_threads, 1, true);

        m_osm_file.reset();

        // Read all highway edges and the nodes we need.
        std::cout << "Read necessary nodes ..." << std::endl;
        const auto getNodes = [&filters, &array, &nh, weakThis](PrimitiveBlockInputAdaptor& pbi) {
            Pair<Uint64, Uint64> local_node_count = {0, 0};

            if(const auto sharedThis = weakThis.lock())
            {
                sharedThis->printInfo(true);

                for(INodeStream node = pbi.getNodeStream(); !node.isNull(); node.next())
                {
                    // Select the nodes that are part of a highway
                    ++local_node_count.second;
                    if(!nh.id.count(node.id()))
                    {
                        continue;
                    }
                    ++local_node_count.first;

                    bool   isTown = false;
                    Byte   mask   = 0;
                    Uint16 town   = 0;
                    String name;

                    // Check if the node is an attraction or place.
                    for(auto i = 0; i < node.tagsSize(); ++i)
                    {
                        const auto& key = node.key(i);

                        if(key == "attractions" || key == "tourism")
                        {
                            const auto& value = node.value(i);
                            if(AttractionType.count(value))
                            {
                                mask |= AttractionType.at(value);
                            }
                            else
                            {
                                mask |= NodeTypeMask::TOURISM;
                            }
                        }
                        else if(key == "name")
                        {
                            name = node.value(i);
                        }
                        else if(key == "place")
                        {
                            const auto& val = node.value(i);
                            if(val == "city" || val == "town")
                            {
                                isTown = true;
                            }
                        }
                    }

                    if(isTown)
                    {
                        town = MapData::addTown(name);
                        mask |= NodeTypeMask::TOWN;
                    }

                    array.addNode(Node{nh.id[node.id()], node.latd(), node.lond(), mask, town});
                }

                sharedThis->m_node_map_lock.lock();
                sharedThis->m_nodes.first += local_node_count.first;
                sharedThis->m_nodes.second += local_node_count.second;
                sharedThis->m_node_map_lock.unlock();
            }
        };

        osmpbf::parseFileCPPThreads(m_osm_file, getNodes, m_threads, 1, true);

        printInfo();

        std::cout << "Finished reading" << std::endl;
        std::cout << "Compute AdjacencyArray ..." << std::endl;
        array.computeOffsets();

        std::cout << "AdjacencyArray:\n"
                  << "Nodes: " << std::setw(12) << array.nodeCount() << "/" << std::setw(12)
                  << m_nodes.second << "\n"
                  << "Edges: " << std::setw(12) << array.edgeCount() << "/" << std::setw(12)
                  << m_edges << std::endl;
    }

    MapBounds osmpbfReader::getMapBounds()
    {
        return {static_cast<float>(m_osm_file.minLatd()),
                static_cast<float>(m_osm_file.maxLatd()),
                static_cast<float>(m_osm_file.minLond()),
                static_cast<float>(m_osm_file.maxLond())};
    }

}  // namespace OSM
