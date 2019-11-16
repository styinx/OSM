#include "gui/UIMap.hpp"

#include <iostream>

namespace OSM
{

    UIMap::UIMap(const OSM::AdjacencyArray* array, const MapBounds& bounds)
        : m_array(array)
        , m_grid(bounds)
    {
        m_channel = new QWebChannel(this);
        m_bridge = new UIBridge(this);

        m_channel->registerObject("UIBridge", m_bridge);
        page()->setWebChannel(m_channel);

        load(QUrl{"qrc:///map_html"});

        int i = 0;
        for(const auto& node : array->getNodes())
        {
            m_grid.set(node.lat, node.lon, i++);
        }
    }

    void UIMap::drawEdges(const MapBounds& bounds) const
    {
        auto nodes = m_array->getNodes();
        auto center = bounds.center();
        Vector<Uint64> cell = m_grid.get(center.first, center.second);

        QString params;
        int n = 0;
        for(const auto& index : cell)
        {
            const auto node = nodes[index];

            if(n < 10000)
            {
                params += "[" + QString::number(node.lat) + "," + QString::number(node.lon) + "],";
                n++;
            }
        }

        page()->runJavaScript("showGraph([[" + params.left(params.size() - 1) + "]]);");
    }

} // namespace OSM
