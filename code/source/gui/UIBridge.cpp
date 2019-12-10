#include "gui/UIBridge.hpp"

#include "gui/UIMap.hpp"
#include "util/Geo.hpp"

namespace OSM
{

    UIBridge::UIBridge(Window* window, UIMap* map)
        : m_window(window)
        , m_map(map)
    {

    }

    void
    UIBridge::setMapBounds(const float n_lat, const float n_lon, const float s_lat, const float s_lon)
    {
        if(m_bounds.min_lat != n_lat || m_bounds.max_lon != n_lon || m_bounds.max_lat != s_lat ||
           m_bounds.min_lon != s_lon)
        {
            m_bounds.min_lat = s_lat;
            m_bounds.max_lat = n_lat;
            m_bounds.max_lon = n_lon;
            m_bounds.min_lon = s_lon;

            m_map->setGraph(m_bounds);
        }
    }

    void UIBridge::onLoad()
    {
        m_map->onLoad();
    }

    void UIBridge::setStart(const QString &latlon)
    {
        auto pair = Geo::stringToLatLon(latlon);
        m_window->getPanel()->setStart(pair.first, pair.second);
    }

    void UIBridge::setStop(const QString &latlon)
    {
        auto pair = Geo::stringToLatLon(latlon);
        m_window->getPanel()->setStop(pair.first, pair.second);
    }

}  // namespace OSM
