#include "gui/UIBridge.hpp"
#include "gui/UIMap.hpp"


namespace OSM
{

    UIBridge::UIBridge(UIMap* map)
        : m_map(map)
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

            m_map->showGraph(m_bounds);
        }
    }

    void UIBridge::onLoad()
    {
        m_map->onLoad();
    }

    void UIBridge::setStart(const QString &latlon)
    {
        m_map->setStart(latlon);
    }

    void UIBridge::setStop(const QString &latlon)
    {
        m_map->setStop(latlon);
    }

}  // namespace OSM
