#include "gui/UIMap.hpp"

#include "io/MapData.hpp"
#include "gui/Window.hpp"

namespace OSM
{

    UIMap::UIMap(Window* parent, const OSM::AdjacencyArray* array, const MapBounds& bounds)
        : m_parent(parent)
        , m_array(array)
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
//        Uint64 e = 0;
//        QString params;
//        for(Uint64 ei = 0; ei < edges.size(); ++ei)
//        {
//            params += "[[" + QString::number(nodes[edges[ei].source].lat) + ","
//                + QString::number(nodes[edges[ei].source].lon) + "]," +
//                "[" + QString::number(nodes[edges[ei].target].lat) + ","
//                + QString::number(nodes[edges[ei].target].lon) + "]],";
//            if(e++ > 100)
//                break;
//        }
        qDebug() << params;
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

    void UIMap::setShowGraph(const bool show)
    {
        QString setShow = show ? "true" : "false";
        page()->runJavaScript("setShowGraph(" + setShow + ")");
    }

    void UIMap::onLoad()
    {
        const auto bounds = m_grid.getBounds();
        const float vlat = bounds.min_lat + (bounds.max_lat - bounds.min_lat) / 2;
        const float vlon = bounds.min_lon + (bounds.max_lon - bounds.min_lon) / 2;
        page()->runJavaScript("setView(" + QString::number(vlat) + ", " + QString::number(vlon) + ");");
    }

    void UIMap::setStart(const QString &latlon)
    {
        auto pair = stringToLatLon(latlon);
        m_parent->getPanel()->setStart(pair.first, pair.second);
    }

    void UIMap::setStop(const QString &latlon)
    {
        auto pair = stringToLatLon(latlon);
        m_parent->getPanel()->setStop(pair.first, pair.second);
    }

}  // namespace OSM
