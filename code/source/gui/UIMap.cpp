#include "gui/UIMap.hpp"

#include <QtCore/QFile>

namespace OSM
{

    UIMap::UIMap()
    {
        load(QUrl{"qrc:///map_html"});
    }

} // namespace OSM
