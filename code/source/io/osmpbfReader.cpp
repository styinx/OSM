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
        std::regex  r(R".*([0-9]+(\.[0-9+])?).*");
        std::smatch match;
        if(std::regex_search(speed.begin(), speed.end(), match, r))
        {
            // TODO extract speed unit
            return std::abs(std::stoi(match[0]));
        }
        return 1;
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
            Uint64              index = 0;
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
            OrTagFilter highway{new KeyOnlyTagFilter("highway")};
            OrTagFilter max_speed{new KeyOnlyTagFilter("maxspeed")};
            OrTagFilter oneway{new KeyOnlyTagFilter("oneway")};
        } filters{};

        // Start reading.
        std::cout << "Start reading ..." << std::endl;

        std::this_thread::sleep_for(Seconds(1));

        // Read all highway edges and the nodes we need.
        std::cout << "Collect necessary nodes ..." << std::endl;
        const auto collectNodes = [&filters, &array, &nh, weakThis](PrimitiveBlockInputAdaptor& pbi)
        {
            Pair<Uint64, Uint64> local_way_count = {0, 0};

            if(const auto sharedThis = weakThis.lock())
            {
                sharedThis->printInfo(true);

                sharedThis->m_filter_lock.lock();

                filters.highway.assignInputAdaptor(&pbi);

                if(!filters.highway.rebuildCache()) {
                    sharedThis->m_filter_lock.unlock();
                    return;
                }
                sharedThis->m_filter_lock.unlock();

                for(IWayStream way = pbi.getWayStream(); !way.isNull(); way.next())
                {
                    ++local_way_count.second;

                    if(!filters.highway.matches(way))
                        continue;

                    ++local_way_count.first;

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
                            sharedThis->m_edges++;

                            array.addEdge(Edge{nh.id[*previous], nh.id[*current]});
                            array.addEdge(Edge{nh.id[*current], nh.id[*previous]});

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
        const auto getNodes = [&filters, &array, &nh, weakThis](PrimitiveBlockInputAdaptor& pbi)
        {
            Pair<Uint64, Uint64> local_node_count = {0, 0};

            if(const auto sharedThis = weakThis.lock())
            {
                sharedThis->printInfo(true);

                sharedThis->m_filter_lock.lock();

                filters.highway.assignInputAdaptor(&pbi);
//                if(!filters.highway.rebuildCache())
//                {
//                    sharedThis->m_filter_lock.unlock();
//                    return;
//                }
//
//                filters.max_speed.assignInputAdaptor(&pbi);
//                if(!filters.max_speed.rebuildCache())
//                {
//                    sharedThis->m_filter_lock.unlock();
//                    return;
//                }
//
                sharedThis->m_filter_lock.unlock();

                for(INodeStream node = pbi.getNodeStream(); !node.isNull(); node.next())
                {
                    ++local_node_count.second;

                    if(!nh.id.count(node.id()))
                        continue;

                    ++local_node_count.first;

                    if(filters.max_speed.matches(node))
                    {
                        //readMaxSpeed(node.value(filters.max_speed.matchingTag()));
                    }

                    if(filters.oneway.matches(node))
                    {

                    }

                    array.addNode(Node{nh.id[node.id()], node.latd(), node.lond(), 0, 0, 0});
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
