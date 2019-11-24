#include "gui/UIMap.hpp"

#include "io/MapData.hpp"

namespace OSM
{

    UIMap::UIMap(const OSM::AdjacencyArray* array, const MapBounds& bounds)
        : m_array(array)
        , m_grid(bounds)
        , m_dijkstra(m_array)
    {
        m_channel = new QWebChannel(this);
        m_bridge  = new UIBridge(this);

        m_channel->registerObject("UIBridge", m_bridge);
        page()->setWebChannel(m_channel);

        load(QUrl{"qrc:///map_html"});

        int i = 0;
        for(const auto& node : array->getNodes())
        {
            m_grid.set(node.lat, node.lon, i++);
        }
    }

    Pair<float, Vector<Uint64>> UIMap::calculateDistance(const QString& from, const QString& to)
    {
        const auto  max       = std::numeric_limits<Uint64>::max();
        Uint64      from_town = max;
        Uint64      from_node = max;
        Uint64      to_town   = max;
        Uint64      to_node   = max;
        std::string from_name = from.toStdString();
        std::string to_name   = to.toStdString();

        for(const auto& o : MapData::getTowns())
        {
            if(o.second == from_name)
            {
                from_town = o.first;
            }
            else if(o.second == to_name)
            {
                to_town = o.first;
            }

            if(from_town != max && to_town != max)
            {
                int index = 0;
                for(const auto& node : m_array->getNodes())
                {
                    if(node.town == from_town)
                    {
                        from_node = index;
                    }
                    else if(node.town == to_town)
                    {
                        to_node = index;
                    }

                    if(from_node != max && to_node != max)
                    {
                        return m_dijkstra.compute(from_node, to_node);
                    }

                    ++index;
                }
                break;
            }
        }

        return {-1, {}};
    }

    void UIMap::drawEdges(const MapBounds& bounds) const
    {
        const auto nodes   = m_array->getNodes();
        const auto edges   = m_array->getEdges();
        const auto offsets = m_array->getOOffsets();
        const auto center  = bounds.center();

        QString params;
        for(const auto& index : m_grid.get(center.first, center.second))
        {
            QString inner;
            for(Uint64 n = offsets[index]; n < offsets[index + 1]; ++n)
            {
                auto node = nodes[edges[n].source];
                inner += "[" + QString::number(node.lat) + "," + QString::number(node.lon) + "],";
            }
            params += "[" + inner.left(inner.size() - 1) + "],";
        }

        qDebug() << params;
        page()->runJavaScript("showGraph([" + params.left(params.size() - 1) + "]);");
    }

    void UIMap::drawPath(const Vector<Uint64>& path) const
    {
        const auto nodes = m_array->getNodes();
        QString params;

        for(const auto& node : path)
        {
            const auto n = nodes[node];
            params += "[" + QString::number(n.lat) + "," + QString::number(n.lat) + "],";
        }

        page()->runJavaScript("showGraph([" + params.left(params.size() - 1) + "]);");
    }

}  // namespace OSM
