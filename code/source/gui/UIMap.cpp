#include "gui/UIMap.hpp"

#include "io/MapData.hpp"
#include "gui/UIBridge.hpp"
#include "util/Geo.hpp"

namespace OSM
{

    UIMap::UIMap(Window* parent, const OSM::AdjacencyArray* array, const MapBounds& bounds)
        : m_array(array)
        , m_grid(bounds, array)
        , m_routeSearch(m_array, &m_grid)
    {
        m_channel = new QWebChannel(this);
        m_bridge  = new UIBridge(parent, this);

        m_channel->registerObject("UIBridge", m_bridge);
        page()->setWebChannel(m_channel);

        load(QUrl{"qrc:///map_html"});
    }

    Vector<Uint64> UIMap::calculatePath(const QString& from, const QString& to, const int method)
    {
        const auto latlon1 = Geo::stringToLatLon(from);
        const auto latlon2 = Geo::stringToLatLon(to);

        auto start = m_grid.getFirstClosest(latlon1.first, latlon1.second);
        auto stop = m_grid.getFirstClosest(latlon2.first, latlon2.second);

        if(method == 0)
            return m_routeSearch.computeDijkstra(start, stop);
        else if(method == 1)
            return m_routeSearch.UCS(start, stop);
        return m_routeSearch.PQ(start, stop);
    }

    void UIMap::setGraph() const
    {
        const auto nodes    = m_array->getNodes();
        const auto edges    = m_array->getEdges();
        const auto ooffsets = m_array->getOOffsets();
        const auto ioffsets = m_array->getIOffsets();

        Uint64 s = 0;

        QString params;
        for(Uint64 node = 0; node < 1000; ++node)
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
            if(!inner.isEmpty())
            {
                params += "" + inner.left(inner.size() - 1) + ",";
            }
            if(n > 0)
                s += 1;
        }
        page()->runJavaScript("bridge.setGraph([" + params.left(params.size() - 1) + "]);");
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

        page()->runJavaScript("bridge.showRoute([" + params.left(params.size() - 1) + "]);");
    }

    UIBridge* UIMap::getBridge() const
    {
        return m_bridge;
    }

    void UIMap::showGraph(const bool show)
    {
        QString setShow = show ? "true" : "false";
        page()->runJavaScript("bridge.showGraph(" + setShow + ")");
    }

    void UIMap::onLoad()
    {
        const auto bounds = m_grid.getBounds();
        const float vlat = bounds.min_lat + (bounds.max_lat - bounds.min_lat) / 2;
        const float vlon = bounds.min_lon + (bounds.max_lon - bounds.min_lon) / 2;
        page()->runJavaScript("bridge.setView(" + QString::number(vlat) + ", " + QString::number(vlon) + ");");
        setGraph();
    }

}  // namespace OSM
