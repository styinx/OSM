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
        if(m_bounds.min_lat != n_lat || m_bounds.max_lon != n_lon || m_bounds.max_lat != s_lat ||
           m_bounds.min_lon != s_lon)
        {
            m_bounds.min_lat = n_lat;
            m_bounds.max_lon = n_lon;
            m_bounds.max_lat = s_lat;
            m_bounds.min_lon = s_lon;

            m_map->drawEdges(m_bounds);
        }
    }

}  // namespace OSM
