#include "structures/Grid.hpp"

namespace OSM
{

    Grid::Grid(const MapBounds& bounds)
        : m_bounds(bounds)
    {
    }

    void Grid::set(const float lat, const float lon, const Uint64 index)
    {
        auto x    = (lat - m_bounds.min_lat) * 10000 / 10000;
        auto y    = (lon - m_bounds.min_lon) * 10000 / 10000;
        auto cell = static_cast<Uint16>(y * 100 + x);

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
        auto x    = (lat - m_bounds.min_lat) * 10000 / 10000;
        auto y    = (lon - m_bounds.min_lon) * 10000 / 10000;
        auto cell = static_cast<Uint16>(y * 100 + x);

        if(cell < m_cells.size())
            return m_cells[cell].children;

        return {};
    }

}  // namespace OSM
