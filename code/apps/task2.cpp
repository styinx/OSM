#include <chrono>
#include <iomanip>
#include <iostream>
#include <osmpbf/filter.h>
#include <osmpbf/inode.h>
#include <osmpbf/irelation.h>
#include <osmpbf/iway.h>
#include <osmpbf/osmfile.h>
#include <osmpbf/primitiveblockinputadaptor.h>

struct Info
{
    unsigned nodes     = 0;
    unsigned ways      = 0;
    unsigned relations = 0;
};

void parseBlock(Info& info, osmpbf::PrimitiveBlockInputAdaptor& pbi)
{
    if(pbi.nodesSize())
    {
        for(osmpbf::INodeStream node = pbi.getNodeStream(); !node.isNull(); node.next())
        {
            info.nodes++;
        }
    }

    if(pbi.waysSize())
    {
        for(osmpbf::IWayStream way = pbi.getWayStream(); !way.isNull(); way.next())
        {
            info.ways++;
        }
    }

    if(pbi.relationsSize())
    {
        for(osmpbf::IRelationStream relation = pbi.getRelationStream(); !relation.isNull();
            relation.next())
        {
            info.relations++;
        }
    }
}

unsigned printInfo(const Info& info)
{
    std::string nodes     = "Nodes: " + std::to_string(info.nodes);
    std::string ways      = "Ways: " + std::to_string(info.ways);
    std::string relations = "Relations: " + std::to_string(info.relations);

    std::cout << std::left << std::setw(30) << nodes << std::setw(30) << ways << std::setw(30)
              << relations << "\n";

    return nodes.size() + ways.size() + relations.size();
}

int main(int argc, char** argv)
{
    using namespace std::chrono;

    if(argc < 2)
    {
        std::cout << "Need in file" << std::endl;
        return -1;
    }

    std::string       inputFileName(argv[1]);
    osmpbf::OSMFileIn inFile(inputFileName, false);

    if(!inFile.open())
    {
        std::cout << "Failed to open " << inputFileName << std::endl;
        return -1;
    }

    Info             info{};
    auto             start = system_clock::now();
    auto             stop  = system_clock::now();
    duration<double> diff  = duration<double>(0);

    osmpbf::PrimitiveBlockInputAdaptor pbi;
    while(inFile.parseNextBlock(pbi))
    {
        if(pbi.isNull())
            continue;
        parseBlock(info, pbi);

        if(diff > std::chrono::duration<double>(1))
        {
            auto duration = duration_cast<seconds>(system_clock::now() - stop).count();
            std::cout << std::right << std::setw(5) << duration << "s: ";
            printInfo(info);

            start = std::chrono::system_clock::now();
        }
        diff = std::chrono::system_clock::now() - start;
    }

    auto duration = duration_cast<seconds>(system_clock::now() - stop).count();
    std::cout << std::right << std::setw(5) << duration << "s: ";
    printInfo(info);

    return 0;
}
