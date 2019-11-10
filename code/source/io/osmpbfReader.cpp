#include "io/osmpbfReader.hpp"

#include "structures/Primitives.hpp"

#include <iomanip>
#include <iostream>
#include <osmpbf/inode.h>
#include <osmpbf/irelation.h>
#include <osmpbf/iway.h>
#include <osmpbf/osmfile.h>
#include <osmpbf/primitiveblockinputadaptor.h>

namespace OSM
{
    osmpbfReader::osmpbfReader(const std::string& osm_file)
        : m_osm_file(osm_file, false)
    {
        m_osm_file.open();
    }

    void osmpbfReader::printInfo()
    {
        std::cout << std::right << std::setw(3) << m_duration << "s"
                  << " | Nodes: " << std::right << std::setw(15) << m_nodes
                  << " | Ways: " << std::right << std::setw(15) << m_ways
                  << " | Relations: " << std::right << std::setw(15) << m_relations << "\n";
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

        osmpbf::PrimitiveBlockInputAdaptor pbi{};

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

            if(pbi.nodesSize())
            {
                for(INodeStream node = pbi.getNodeStream(); !node.isNull(); node.next())
                {
                    ++m_nodes;
                    if(node.id() >= 0)
                    {
                        array.addNode(OSM::Node{node.id(), node.latd(), node.lond()});
                    }
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
                                array.addEdge(OSM::Edge{*previous, *it});
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
    }

}  // namespace OSM
