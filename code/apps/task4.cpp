#include "gui/Window.hpp"
#include "io/osmpbfReader.hpp"
#include "structures/AdjacencyArray.hpp"

#include <QApplication>

int main(int argc, char** argv)
{
    auto array  = OSM::AdjacencyArray{};
    auto bounds = OSM::MapBounds();

    if(argc >= 2)
    {
        auto file_name = std::string{argv[1]};
        auto reader    = OSM::osmpbfReader{file_name};
        bounds         = reader.getMapBounds();

        reader.read(array);
    }

    QApplication app(argc, argv);

    auto window = OSM::Window(&array, bounds);
    window.show();

    return app.exec();
}
