#include "gui/UIMap.hpp"

#include "io/MapData.hpp"
#include "gui/UIBridge.hpp"
#include "gui/UIGraph.hpp"
#include "util/Geo.hpp"

namespace OSM
{

    UIMap::UIMap(Window* parent, const AdjacencyArray* array, const MapBounds& bounds)
        : m_parent(parent)
        , m_array(array)
        , m_grid(bounds, array)
        , m_routeSearch(m_array, &m_grid)
    {
        m_page = new WebPage(this);
        setPage(m_page);
        
        m_channel = new QWebChannel(this);
        m_graph = new UIGraph(m_array);

        m_channel->registerObject("UIGraph", m_graph);
        m_channel->registerObject("UIMap", this);
        page()->setWebChannel(m_channel);

        load(QUrl{"qrc:///map_html"});
    }

    Vector<Uint64> UIMap::calculatePath(const QString& from, const QString& to)
    {
        const auto latlon1 = Geo::stringToLatLon(from);
        const auto latlon2 = Geo::stringToLatLon(to);

        auto start = m_grid.getFirstClosest(latlon1.first, latlon1.second);
        auto stop = m_grid.getFirstClosest(latlon2.first, latlon2.second);

        return m_routeSearch.route(start, stop);
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

        page()->runJavaScript("ui_map.showRoute([" + params.left(params.size() - 1) + "]);");
    }

    void UIMap::onLoad()
    {
        const auto bounds = m_grid.getBounds();
        const float vlat = bounds.min_lat + (bounds.max_lat - bounds.min_lat) / 2;
        const float vlon = bounds.min_lon + (bounds.max_lon - bounds.min_lon) / 2;
        const auto diff = std::abs(bounds.max_lon - bounds.min_lon);
        const float auto_zoom = std::max(-15 * diff, -10 * std::log(diff + 12)) + 20;

        page()->runJavaScript("ui_map.setView("
            + QString::number(vlat) + ", "
            + QString::number(vlon) + ", "
            + QString::number(static_cast<int>(std::round(auto_zoom))) +");");
    }

    void UIMap::showGraph(const bool show)
    {
        QString setShow = show ? "true" : "false";
        page()->runJavaScript("ui_map.showGraph(" + setShow + ")");

        m_graph->buildMotorway();

        page()->runJavaScript("ui_graph.show();");
    }

    void UIMap::setStart(const QString &latlon)
    {
        auto pair = Geo::stringToLatLon(latlon);
        m_parent->getPanel()->setStart(pair.first, pair.second);
    }

    void UIMap::setStop(const QString &latlon)
    {
        auto pair = Geo::stringToLatLon(latlon);
        m_parent->getPanel()->setStop(pair.first, pair.second);
    }

}  // namespace OSM
