#include "gui/UIMap.hpp"

#include <QtCore/QFile>
#include <QtWidgets/QMessageBox>
#include <iostream>

namespace OSM
{

    UIMap::UIMap(const OSM::AdjacencyArray* array)
        : m_array(array)
    {
        m_channel = new QWebChannel(this);
        m_bridge = new UIBridge(this);

        m_channel->registerObject("UIBridge", m_bridge);
        page()->setWebChannel(m_channel);

        load(QUrl{"qrc:///map_html"});
    }

    void UIMap::drawEdges(const MapBounds& bounds) const
    {
        Vector<Vector<std::pair<float, float>>> nodes;
        page()->runJavaScript("showGraph([]);");
    }

} // namespace OSM
