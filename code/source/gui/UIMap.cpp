#include "gui/UIMap.hpp"

#include "gui/UIBridge.hpp"
#include "gui/UIGraph.hpp"
#include "io/MapData.hpp"
#include "util/Geo.hpp"

namespace OSM
{

    UIMap::UIMap(Window* parent, const AdjacencyArray* array, const MapBounds& bounds)
        : m_parent(parent)
        , m_array(array)
        , m_grid(bounds, array)
        , m_route_search(m_array, &m_grid)
    {
        m_page = new WebPage(this);
        setPage(m_page);

        m_channel = new QWebChannel(this);
        m_graph   = new UIGraph(m_array);

        m_channel->registerObject("UIGraph", m_graph);
        m_channel->registerObject("UIMap", this);
        page()->setWebChannel(m_channel);

        load(QUrl{"qrc:///map_html"});
    }

    Uint64 UIMap::townToNode(const QString& town) const
    {
        const Uint16 town_id = MapData::getTownID(town.toStdString());

        for(const auto& node : m_array->getNodes())
        {
            if(node.town == town_id)
            {
                return node.id;
            }
        }
        return town_id;
    }

    void UIMap::onLoad()
    {
//        const auto preprocess = [this]() {
//            const auto nodes = m_array->getNodes();
//            calculatePath(
//                QString::number((*nodes.begin()).id),
//                QString::number((*nodes.end()).id),
//                TransportType::CAR);
//        };
//
//        std::thread t(preprocess);

        const auto  bounds    = m_grid.getBounds();
        const float vlat      = bounds.min_lat + (bounds.max_lat - bounds.min_lat) / 2;
        const float vlon      = bounds.min_lon + (bounds.max_lon - bounds.min_lon) / 2;
        const auto  diff      = std::abs(bounds.max_lon - bounds.min_lon);
        const float auto_zoom = std::max(-15 * diff, -0.45F * diff - 10) + 20;

        page()->runJavaScript(
            "ui_map.setView(" + QString::number(vlat) + ", " + QString::number(vlon) + ", " +
            QString::number(static_cast<int>(std::round(auto_zoom))) + ");");

//        t.join();
    }

    void UIMap::showGraph(const bool show)
    {
        QString setShow = show ? "true" : "false";
        page()->runJavaScript("ui_map.showGraph(" + setShow + ")");

        m_graph->buildMotorway();

        page()->runJavaScript("ui_graph.show();");
    }

    void UIMap::showNodes(const bool show)
    {
        QString call = "ui_map.showNodes(";

        if(show)
        {
            const auto nodes = m_array->getNodes();
            QString    params;
            for(const auto& node : nodes)
            {
                const auto n = node;
                if(n.mask & NodeTypeMask::TOURISM)
                {
                    params += "[" + QString::number(n.tourism()) + ", " + QString::number(n.lat) +
                              "," + QString::number(n.lon) + ", " + QString::number(n.id) + "],";
                }
            }

            page()->runJavaScript(call + "true, [" + params.left(params.size() - 1) + "]);");
        }
        else
        {
            page()->runJavaScript(call + "false);");
        }
    }

    void UIMap::setStart(const QString& latlon)
    {
        auto pair = Geo::stringToLatLon(latlon);
        m_parent->getPanel()->setStart(pair.first, pair.second);
    }

    void UIMap::setStop(const QString& latlon)
    {
        auto pair = Geo::stringToLatLon(latlon);
        m_parent->getPanel()->setStop(pair.first, pair.second);
    }

    void UIMap::addAttraction(const QString& id)
    {
        const auto node = m_array->getNodes()[id.toInt()];
        if(m_route_attractions.size() == 10)
        {
            m_route_attractions.erase(m_route_attractions.begin());
        }
        m_route_attractions.emplace_back(node);
        m_parent->getPanel()->addAttraction(m_route_attractions.size());
    }

    PathResult UIMap::calculatePath(const QString& from, const QString& to, const TransportType type)
    {
        const auto latlon1 = Geo::stringToLatLon(from);
        const auto latlon2 = Geo::stringToLatLon(to);

        if(!from.contains(',') && latlon1 == latlon2)
        {
            auto start = townToNode(from);
            auto stop  = townToNode(to);

            return m_route_search.route(start, stop, type, m_route_attractions);
        }
        else
        {
            auto start = m_grid.getFirstClosest(latlon1.first, latlon1.second);
            auto stop  = m_grid.getFirstClosest(latlon2.first, latlon2.second);

            return m_route_search.route(start, stop, type, m_route_attractions);
        }
    }

    void UIMap::drawPath(const Vector<Uint64>& path, const Uint8 color) const
    {
        const auto nodes = m_array->getNodes();
        QString    params;

        for(const auto& node : path)
        {
            const auto n = nodes[node];
            params += "[" + QString::number(n.lon) + "," + QString::number(n.lat) + "],";
        }

        page()->runJavaScript(
            "ui_map.showRoute([" + params.left(params.size() - 1) + "], " + QString::number(color) +
            ");");
    }

    void UIMap::drawNodes(const Vector<Uint64>& path) const
    {
        const auto nodes = m_array->getNodes();
        QString    params;

        for(const auto& node : path)
        {
            const auto n = nodes[node];
            params += "[0," + QString::number(n.lat) + "," + QString::number(n.lon) + "],";
        }
        page()->runJavaScript("ui_map.showNodes(true, [" + params.left(params.size() - 1) + "]);");
    }

    void UIMap::resetAttractions()
    {
        m_route_attractions.clear();

        page()->runJavaScript("ui_map.resetAttractions();");
    }

}  // namespace OSM
