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
        auto bound = std::min(m_array->nodeCount(), 200UL);

        for(Uint64 i = 0; i < bound; ++i)
        {
//            if(bounds.isInBounds(node.lat, node.lon) && nodes.size() < 1000)
//            {
                Vector<std::pair<float, float>> nodeList;
                for(Uint64 j = m_array->getOffset(i); j < m_array->getOffset(i + 1) - 1; ++j)
                {
                    nodeList.emplace_back(
                        std::pair<float, float>{m_array->getNode(j).lat, m_array->getNode(j).lon});
                }
                if(nodeList.size() > 0)
                {
                    nodes.emplace_back(nodeList);
                }
//            }
        }

        QString paramString = "";
        for(const auto& n : nodes)
        {
            QString inner;
            for(const auto& nl : n)
            {
                inner += "[" + QString::number(nl.first) + ", " + QString::number(nl.second) + "],";
            }
            if(n.size() > 0)
            {
                paramString += "[" + inner.left(inner.length() - 1) + "],";
            }
        }

        qDebug() << paramString;

        page()->runJavaScript("showGraph([" + paramString.left(paramString.length() - 1) + "]);");
    }

} // namespace OSM
