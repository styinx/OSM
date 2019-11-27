#include "gui/UIMap.hpp"

#include "io/MapData.hpp"

namespace OSM
{

    UIMap::UIMap(const OSM::AdjacencyArray* array, const MapBounds& bounds)
        : m_array(array)
        , m_grid(bounds, array)
        , m_routeSearch(m_array, &m_grid)
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
    Uint64 UIMap::townToNode(const QString& town) const
    {
        Uint16 id = MapData::getTownID(town.toStdString());

        Uint64 index = 0;
        for(const auto& node : m_array->getNodes())
        {
            if(node.town == id)
                break;
            ++index;
        }
        return index;
    }

    Uint64 UIMap::coordToNode(const float lat, const float lon) const
    {
        const auto nodes      = m_array->getNodes();
        float      min        = std::numeric_limits<float>::max();
        Uint64     node_index = 0;

        for(const auto& node : m_grid.get(lat, lon))
        {
            auto l_min = dist(lat, lon, nodes[node].lat, nodes[node].lon);
            if(l_min < min)
            {
                min        = l_min;
                node_index = node;
            }
        }
        return node_index;
    }

    Pair<float, float> UIMap::stringToLatLon(const QString& str) const
    {
        QStringList latlon = str.split(",");

        if(latlon.size() == 2)
        {
            return Pair<float, float>{latlon[0].toDouble(nullptr), latlon[1].toDouble(nullptr)};
        }
        return {0, 0};
    }

    Vector<Uint64> UIMap::calculatePath(const QString& from, const QString& to, const int method)
    {
        Uint64 start = 0;
        Uint64 stop = 0;

        auto latlon1 = stringToLatLon(from);
        auto latlon2 = stringToLatLon(to);

        if(latlon1 != Pair<float, float>{0, 0})
        {
            start = coordToNode(latlon1.first, latlon1.second);
        }
        else
        {
            start = townToNode(from);
        }

        if(latlon2 != Pair<float, float>{0, 0})
        {
            stop = coordToNode(latlon2.first, latlon2.second);
        }
        else
        {
            stop = townToNode(to);
        }

        if(method == 0)
        {
            return m_routeSearch.computeDijkstra(start, stop);
        }
        else if(method == 1)
        {
            return m_routeSearch.UCS(start, stop);
        }
    }

    void UIMap::showGraph(const MapBounds& bounds) const
    {
        const auto nodes    = m_array->getNodes();
        const auto edges    = m_array->getEdges();
        const auto ooffsets = m_array->getOOffsets();
        const auto ioffsets = m_array->getIOffsets();

        Uint64 s = 0;

        QString params;
        for(const auto& node : m_grid.get(bounds))
        {
            Uint64 n = 0;
            QString inner;
            for(Uint64 oedge_index = ooffsets[node]; oedge_index < ooffsets[node + 1]; oedge_index++)
            {
                auto edge   = edges[oedge_index];
                auto source = nodes[edge.source];
                auto target = nodes[edge.target];
                inner += "[[" + QString::number(source.lat) + "," + QString::number(source.lon) +
                         "]," + "[" + QString::number(target.lat) + "," +
                         QString::number(target.lon) + "]],";
                n += 1;
            }
            for(Uint64 iedge_index = ioffsets[node]; iedge_index < ioffsets[node + 1]; iedge_index++)
            {
                auto edge   = edges[iedge_index];
                auto source = nodes[edge.source];
                auto target = nodes[edge.target];
                inner += "[[" + QString::number(source.lat) + "," + QString::number(source.lon) +
                         "]," + "[" + QString::number(target.lat) + "," +
                         QString::number(target.lon) + "]],";
                n += 1;
            }
            if(!inner.isEmpty())
            {
                params += "" + inner.left(inner.size() - 1) + ",";
            }
            if(n > 0)
                s += 1;
            if(s > 500)
                break;
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
            params += "[" + QString::number(n.lon) + "," + QString::number(n.lat) + "],";
        }

        qDebug() << params;
        page()->runJavaScript("showRoute([" + params.left(params.size() - 1) + "]);");
    }

}  // namespace OSM
