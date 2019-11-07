#include "gui/Window.hpp"
#include "io/osmpbfReader.hpp"

#include <QApplication>
#include <QtCore/QResource>
#include <iostream>

int main(int argc, char** argv)
{
    //    if(argc < 2)
    //    {
    //        std::cout << "Need in file" << std::endl;
    //        return -1;
    //    }
    //
    //    auto file_name = std::string{argv[1]};
    //    auto array  = OSM::AdjacencyArray{};
    //    auto reader = OSM::osmpbfReader{file_name};
    //
    //    reader.read(array);
    //    reader.printInfo();
    //    array.computeOffsets();

    QApplication app(argc, argv);
    QResource::registerResource("../../resources.rcc");

    auto window = OSM::Window();
    window.show();

    return app.exec();
}
