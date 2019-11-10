#include "gui/Window.hpp"
#include "io/osmpbfReader.hpp"

#include <QApplication>
#include <structures/AdjacencyArray.hpp>

int main(int argc, char** argv)
{
    auto array = OSM::AdjacencyArray{};

    if(argc >= 2)
    {
        auto file_name = std::string{argv[1]};
        auto reader    = OSM::osmpbfReader{file_name};

        reader.read(array);
        reader.printInfo();
        array.computeOffsets();
    }

    QApplication app(argc, argv);

    auto window = OSM::Window(array);
    window.show();

    return app.exec();
}
