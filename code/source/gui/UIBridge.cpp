#include "gui/UIBridge.hpp"
#include "gui/UIMap.hpp"


namespace OSM
{

    UIBridge::UIBridge(const UIMap* map)
        : m_map(map)
    {

    }

    void UIBridge::dummy()
    {

    }

    void
    UIBridge::setMapBounds(const float n_lat, const float n_lon, const float s_lat, const float s_lon)
    {
        if(m_bounds.ne_lat != n_lat || m_bounds.ne_lon != n_lon || m_bounds.sw_lat != s_lat ||
           m_bounds.sw_lon != s_lon)
        {
            m_bounds.ne_lat = n_lat;
            m_bounds.ne_lon = n_lon;
            m_bounds.sw_lat = s_lat;
            m_bounds.sw_lon = s_lon;

            m_map->drawEdges(m_bounds);
        }
    }

}  // namespace OSM
