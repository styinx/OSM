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

    Uint16 Grid::nodeToCell(const float lat, const float lon) const
    {
        float x    = ((lon - m_bounds.min_lon) / m_lon_range) * m_x;
        float y    = ((lat - m_bounds.min_lat) / m_lat_range) * m_y;

        if(x < 0)
            x = 0;
        else if(x > m_x - 1)
            x = m_x - 1;

        if(y < 0)
            y = 0;
        else if(y > m_y -1)
            y = m_y - 1;

        return static_cast<Uint16>(y * m_y + x);
    }

    void Grid::set(const float lat, const float lon, const Uint64 index)
    {
        auto i = nodeToCell(lat, lon);
        m_cells[i].children.emplace_back(index);
    }

    Vector<Uint64> Grid::get(const Uint16 cell) const
    {
        return m_cells[cell].children;
    }

    Vector<Uint64> Grid::get(const float lat, const float lon) const
    {
        return m_cells[nodeToCell(lat, lon)].children;
    }

    Vector<Uint64> Grid::get(const MapBounds& bounds) const
    {
        Vector<Uint64> nodes;

        const auto bl = nodeToCell(bounds.min_lat, bounds.min_lon);
        const auto tr = nodeToCell(bounds.max_lat, bounds.max_lon);
        const auto x_min = bl % m_y;
        const auto x_max = tr % m_y;
        const auto y_min = bl / m_y;
        const auto y_max = tr / m_y;

        for(Uint16 y = y_min; y <= y_max; ++y)
        {
            for(Uint16 x = x_min; x <= x_max; ++x)
            {
                const auto new_nodes = get(y * m_y + x);
                nodes.insert(nodes.end(), new_nodes.begin(), new_nodes.end());
            }
        }

        return nodes;
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
