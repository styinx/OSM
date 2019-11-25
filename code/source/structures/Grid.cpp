#include "structures/Grid.hpp"

#include <cmath>
#include <iostream>

namespace OSM
{

    Grid::Grid(const MapBounds& bounds)
        : m_bounds(bounds)
        , m_lat_range(bounds.max_lat - bounds.min_lat)
        , m_lon_range(bounds.max_lon - bounds.min_lon)
    {
    }

    void Grid::set(const float lat, const float lon, const Uint64 index)
    {
        auto x    = (lon - m_bounds.min_lon) / m_lon_range * m_x;
        auto y    = (lat - m_bounds.min_lat) / m_lat_range * m_y;
        auto cell = static_cast<Uint16>(y * m_y + x);

        if(cell < m_cells.size())
        {
            m_cells[cell].children.emplace_back(index);
        }
    }

    Vector<Uint64> Grid::get(const Uint16 cell) const
    {
        return m_cells[cell].children;
    }

    Vector<Uint64> Grid::get(const float lat, const float lon) const
    {
        auto x    = (lon - m_bounds.min_lon) / m_lon_range * m_x;
        auto y    = (lat - m_bounds.min_lat) / m_lat_range * m_y;
        auto cell = static_cast<Uint16>(y * m_y + x);

        if(cell < m_cells.size())
        {
            return m_cells[cell].children;
        }

        return {};
    }

    const MapBounds& Grid::getBounds() const
    {
        return m_bounds;
    }

    Vector<Grid::Cell> Grid::getCells() const
    {
        return m_cells;
    }

}  // namespace OSM
