#include "gui/Window.hpp"
#include "io/osmpbfReader.hpp"
#include "structures/AdjacencyArray.hpp"

#include <QApplication>

int main(int argc, char** argv)
{
    auto array = OSM::AdjacencyArray{};

    if(argc >= 2)
    {
        auto file_name = std::string{argv[1]};
        auto reader    = OSM::osmpbfReader{file_name};

        reader.read(array);
        reader.printInfo();
    }

    QApplication app(argc, argv);

    auto window = OSM::Window(&array);
    window.show();

    return app.exec();
}
