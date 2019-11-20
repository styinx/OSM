#include "gui/UIMap.hpp"

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

        QString params;
        for(const auto& index : m_grid.get(center.first, center.second))
        {
            const auto node = nodes[index];

            params += "[" + QString::number(node.lat) + "," + QString::number(node.lon) + "],";
        }

        page()->runJavaScript("showGraph([[" + params.left(params.size() - 1) + "]]);");
    }

} // namespace OSM
