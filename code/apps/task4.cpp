#include "io/osmpbfReader.hpp"

#include <iostream>

int main(int argc, char** argv)
{
    using namespace std::chrono;

    if(argc < 2)
    {
        std::cout << "Need in file" << std::endl;
        return -1;
    }

    auto file_name = std::string{argv[1]};
    auto array  = OSM::AdjacencyArray{};
    auto reader = OSM::osmpbfReader{file_name};

    reader.read(array);
    reader.printInfo();
    array.computeOffsets();

    return 0;
}
