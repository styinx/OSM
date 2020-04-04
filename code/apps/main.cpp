#include "gui/Window.hpp"
#include "io/osmpbfReader.hpp"
#include "structures/AdjacencyArray.hpp"

#include <QApplication>
#include <iostream>

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
#ifndef NDEBUG
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtInfoMsg:
        fprintf(stderr, "Info: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        abort();
    }
#endif
}

int main(int argc, char** argv)
{
    auto array = OSM::AdjacencyArray{};
    auto bounds = OSM::MapBounds();

    if(argc >= 2)
    {
        auto file_name = std::string{argv[1]};
        auto reader    = std::make_shared<OSM::osmpbfReader>(file_name);
        bounds = reader->getMapBounds();

        reader->read(array);
    }
    else
    {
        std::cout << "Missing map file. Please specify a *.pbf file.\n"
                  << "Usage: ./OSM <relative path to the *.pbf file>\n";
        return 0;
    }

    qInstallMessageHandler(myMessageOutput);
    QApplication app(argc, argv);

    auto window = OSM::Window(&array, bounds);
    window.show();

    return app.exec();
}
