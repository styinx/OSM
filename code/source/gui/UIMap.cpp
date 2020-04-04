#include "gui/UIMap.hpp"

#include "gui/UIBridge.hpp"
#include "gui/UIGraph.hpp"
#include "io/MapData.hpp"
#include "util/Geo.hpp"

#include <iostream>

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

        for(const auto& node : m_array->getNodes())
        {
            const auto n = node;
            if(n.mask & NodeTypeMask::TOURISM)
            {
                m_attr_id.append(QVariant((qlonglong)n.id));
                m_attr_lat.append(QVariant(n.lat));
                m_attr_lon.append(QVariant(n.lon));
                m_attr_tourism.append(QVariant(n.tourism()));
            }
        }
    }

    // Private

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

    void UIMap::runJS(const QString& script) const
    {
        page()->runJavaScript(script);
    }

    // Public

    void UIMap::onLoad()
    {
        const auto  bounds    = m_grid.getBounds();
        const float vlat      = bounds.min_lat + (bounds.max_lat - bounds.min_lat) / 2;
        const float vlon      = bounds.min_lon + (bounds.max_lon - bounds.min_lon) / 2;
        const auto  diff      = std::abs(bounds.max_lon - bounds.min_lon);
        const float auto_zoom = std::max(-15 * diff, -0.50F * diff - 10) + 20;

        runJS(
            "ui_map.setView(" + QString::number(vlat) + ", " + QString::number(vlon) + ", " +
            QString::number(static_cast<int>(std::round(auto_zoom))) + ");");
    }

    void UIMap::showGraph(const bool show)
    {
        QString setShow = show ? "true" : "false";
        runJS("ui_map.showGraph(" + setShow + ")");

        m_graph->buildMotorway();

        runJS("ui_graph.show();");
    }

    void UIMap::showNodes(const bool show)
    {
        runJS(QString("ui_map.showNodes(").append((show) ? "true" : "false").append(")"));
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
        m_route_attractions.push_back(node);
        m_parent->getPanel()->setAttraction(m_route_attractions.size());
    }

    void UIMap::removeAttraction(const QString& id)
    {
        Node t;
        Uint64 number = id.toInt();
        for(const auto& n : m_route_attractions)
        {
            if(n.id == number)
            {
                t = n;
                break;
            }
        }
        if(t.id != 0)
        {
            m_route_attractions.erase(
                std::remove(m_route_attractions.begin(), m_route_attractions.end(), t));
        }
        m_parent->getPanel()->setAttraction(m_route_attractions.size());
    }

    PathResult
    UIMap::calculatePath(const QString& from, const QString& to, const TransportType type, const Byte algorithm)
    {
        const auto latlon1 = Geo::stringToLatLon(from);
        const auto latlon2 = Geo::stringToLatLon(to);
        Uint64     start   = 0;
        Uint64     stop    = 0;

        if(!from.contains(',') && latlon1 == latlon2)
        {
            start = townToNode(from);
            stop  = townToNode(to);
        }
        else
        {
            start = m_grid.getFirstClosest(latlon1.first, latlon1.second);
            stop  = m_grid.getFirstClosest(latlon2.first, latlon2.second);
        }

        if(start == 0 || stop == 0)
        {
            Uint8 which = start == 0 ? 1 : 2;
            return {start, stop, 0, 0, 0, false, which, {}};
        }

        runJS("ui_map.showRoute(false);");

        if(m_route_attractions.empty())
        {
            if(algorithm == 0)
                return m_route_search.route(start, stop, type);

            else if(algorithm == 1)
                return m_route_search.biroute(start, stop, type);
        }
        else
            return m_route_search.route(start, stop, type, m_route_attractions);
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

        runJS(
            "ui_map.showRoute(true, [" + params.left(params.size() - 1) + "], " +
            QString::number(color) + ");");
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
        runJS("ui_map.showNodes(true, [" + params.left(params.size() - 1) + "]);");
    }

    void UIMap::resetAttractions()
    {
        m_route_attractions.clear();

        runJS("ui_map.resetAttractions();");
        runJS("ui_map.showRoute(false);");
    }

    void UIMap::setAttractions(const int val)
    {
        const int diff = val - (int)m_route_attractions.size();

        if(diff > 0)
        {
            runJS("ui_map.addAttractions(" + QString::number(diff) + ");");
            runJS("ui_map.showRoute(false);");
        }
        else if(diff < 0)
        {
            for(int i = 0; i < std::abs(diff); ++i)
            {
                m_route_attractions.pop_back();
            }
            runJS("ui_map.removeAttractions(" + QString::number(std::abs(diff)) + ");");
            runJS("ui_map.showRoute(false);");
        }
    }

    size_t UIMap::numberOfAttractions()
    {
        return m_route_attractions.size();
    }

}  // namespace OSM
