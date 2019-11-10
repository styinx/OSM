#include "gui/UIMap.hpp"

#include <QtCore/QFile>
#include <iostream>

namespace OSM
{

    UIMap::UIMap(const OSM::AdjacencyArray& array)
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
        auto node = m_array.getNode(0);
        Vector<std::pair<float, float>> nodes;
        for(Uint64 i = 0; i < m_array.nodeCount(); ++i)
        {
            node = m_array.getNode(i);
            if(bounds.isInBounds(node.lat, node.lon) && nodes.size() < 1000)
            {
                for(Uint64 j = m_array.getOffset(i); j < m_array.getOffset(i + 1) - 1; ++j)
                {
                    nodes.emplace_back(
                        std::pair<float, float>{m_array.getNode(j).lat, m_array.getNode(j).lon});
                }
            }
        }

        QString paramString = "";
        for(const auto& n : nodes)
        {
            paramString += "[" + QString::number(n.first) + ", " + QString::number(n.second) + "],";
        }

        page()->runJavaScript("showGraph([" + paramString.left(paramString.length() - 1) + "]);");
    }

} // namespace OSM
