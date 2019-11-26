#include "io/osmpbfReader.hpp"

#include "structures/Primitives.hpp"

#include <iomanip>
#include <iostream>
#include <osmpbf/include/osmpbf/filter.h>
#include <osmpbf/inode.h>
#include <osmpbf/irelation.h>
#include <osmpbf/iway.h>
#include <osmpbf/osmfile.h>
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

    void osmpbfReader::printInfo()
    {
        std::cout << std::right << std::setw(3) << m_duration << "s"
                  << " | Nodes: " << std::right << std::setw(12) << m_nodes.first << "/"
                  << std::setw(12) << m_nodes.second << " | Ways: " << std::right << std::setw(12)
                  << m_ways << " (Edges: " << std::right << std::setw(12) << m_edges << ")"
                  << " | Relations: " << std::right << std::setw(12) << m_relations << std::endl;
    }

    void osmpbfReader::read(OSM::AdjacencyArray& array)
    {
        using namespace std::chrono;
        using Duration = std::chrono::duration<double>;

        using osmpbf::INodeStream;
        using osmpbf::IRelationStream;
        using osmpbf::IWay;
        using osmpbf::IWayStream;

        auto start  = system_clock::now();
        auto stop   = system_clock::now();
        auto diff   = Duration{0};
        auto second = Duration{1};

        MapData::addTown("null");

        osmpbf::PrimitiveBlockInputAdaptor pbi{};
        osmpbf::OrTagFilter                highwayFilter{
            {new osmpbf::KeyOnlyTagFilter("highway"),
             new osmpbf::KeyOnlyTagFilter("name"),
             new osmpbf::KeyMultiValueTagFilter("place", {"city", "town"})}};

        while(m_osm_file.parseNextBlock(pbi))
        {
            if(diff > second)
            {
                m_duration = duration_cast<seconds>(system_clock::now() - stop).count();
                start      = std::chrono::system_clock::now();

                printInfo();
            }
            diff = std::chrono::system_clock::now() - start;

            if(pbi.isNull())
                continue;

            highwayFilter.assignInputAdaptor(&pbi);

            if(!highwayFilter.rebuildCache())
                continue;

            if(pbi.nodesSize())
            {
                for(INodeStream node = pbi.getNodeStream(); !node.isNull(); node.next())
                {
                    ++m_nodes.second;

                    if(!highwayFilter.matches(node))
                        continue;

                    ++m_nodes.first;

                    bool        hasTown = false;
                    Byte        mask    = 0;
                    Byte        speed   = 1;
                    Uint16      town    = 0;
                    std::string name;

                    for(Uint32 i = 0, s = node.tagsSize(); i < s; ++i)
                    {
                        const auto& key = node.key(i);
                        const auto& val = node.value(i);

                        if(key == "maxspeed")
                        {
                            readMaxSpeed(node.value(i));
                        }
                        else if(key == "oneway")
                        {
                            mask |= NodeTypeMask::ONE_WAY;
                        }
                        else if(key == "name")
                        {
                            name = val;
                        }
                        else if(key == "place")
                        {
                            if(val == "city" || val == "town")
                            {
                                hasTown = true;
                            }
                        }
                    }

                    if(hasTown)
                    {
                        town = MapData::addTown(name);
                    }

                    array.addNode(Node{node.id(), node.latd(), node.lond(), mask, speed, town});
                }
            }

            if(pbi.waysSize())
            {
                for(IWayStream way = pbi.getWayStream(); !way.isNull(); way.next())
                {
                    ++m_ways;
                    IWay::RefIterator previous = nullptr;
                    IWay::RefIterator it       = way.refBegin();
                    for(; it != way.refEnd(); ++it)
                    {
                        if(previous != nullptr)
                        {
                            if(*previous >= 0)
                            {
                                array.addIOEdge(
                                    Edge{static_cast<Uint64>(*previous), static_cast<Uint64>(*it)});
                                m_edges++;
                            }
                        }
                        if(*it >= 0)
                        {
                            previous = it;
                        }
                    }
                }
            }

            if(pbi.relationsSize())
            {
                for(IRelationStream it = pbi.getRelationStream(); !it.isNull(); it.next())
                {
                    ++m_relations;
                }
            }
        }

        printInfo();

        array.computeOffsets();

        printInfo();

        std::cout << "AdjacencyArray:\n"
                  << "Nodes: " << std::setw(12) << array.nodeCount() << "/" << std::setw(12) << m_nodes.second << "\n"
                  << "Edges: " << std::setw(12) << array.edgeCount() << "/" << std::setw(12) << m_edges << std::endl;
    }

    MapBounds osmpbfReader::getMapBounds()
    {
        return {static_cast<float>(m_osm_file.minLatd()),
                static_cast<float>(m_osm_file.maxLatd()),
                static_cast<float>(m_osm_file.minLond()),
                static_cast<float>(m_osm_file.maxLond())};
    }

}  // namespace OSM
