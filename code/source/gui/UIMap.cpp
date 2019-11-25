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

    Vector<Uint64> UIMap::calculateDijkstra(const QString& from, const QString& to)
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

        return {};
    }

    void UIMap::showGraph(const MapBounds& bounds) const
    {
        const auto nodes   = m_array->getNodes();
        const auto edges   = m_array->getEdges();
        const auto ooffsets = m_array->getOOffsets();
        const auto ioffsets = m_array->getIOffsets();
        //        const auto center  = bounds.center();

        Uint64 n = 0;

        QString params;
        for(Uint64 node = 0; node < nodes.size() && n < 2000; ++node)
        {
            QString inner;
            auto source = nodes[node];
//            for(Uint64 neighbour = ooffsets[node]; neighbour < ooffsets[node + 1]; neighbour++)
//            {
//                auto target = nodes[edges[neighbour].target];
//                inner += "[[" + QString::number(source.lat) + "," +
//                         QString::number(source.lon) + "]," + "[" +
//                         QString::number(target.lat) + "," + QString::number(target.lon) + "]],";
//                n += 1;
//
//            }
            for(Uint64 neighbour = ioffsets[node]; neighbour < ioffsets[node + 1]; neighbour++)
            {
                auto target = nodes[edges[neighbour].source];
                inner += "[[" + QString::number(source.lat) + "," +
                         QString::number(source.lon) + "]," + "[" +
                         QString::number(target.lat) + "," + QString::number(target.lon) + "]],";
            }
            if(!inner.isEmpty())
            {
                params += "" + inner.left(inner.size() - 1) + ",";
            }
        }
        page()->runJavaScript("showGraph([" + params.left(params.size() - 1) + "]);");
    }

    void UIMap::drawPath(const Vector<Uint64>& path) const
    {
        const auto nodes = m_array->getNodes();
        QString    params;

        for(const auto& node : path)
        {
            const auto n = nodes[node];
            params += "[" + QString::number(n.lat) + "," + QString::number(n.lat) + "],";
        }

        page()->runJavaScript("showGraph([" + params.left(params.size() - 1) + "]);");
    }

}  // namespace OSM
