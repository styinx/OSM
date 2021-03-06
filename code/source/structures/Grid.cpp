#include "structures/Grid.hpp"

#include "util/Geo.hpp"

namespace OSM
{

    Grid::Grid(const MapBounds& bounds, const AdjacencyArray* array)
        : m_bounds(bounds)
        , m_array(array)
        , m_lat_range(bounds.max_lat - bounds.min_lat)
        , m_lon_range(bounds.max_lon - bounds.min_lon)
    {
        for(const auto& node : array->getNodes())
        {
            set(node.lat, node.lon, node.id);
        }
    }

    // Private

    Uint16 Grid::nodeToCell(const float lat, const float lon) const
    {
        float x = std::round(((lon - m_bounds.min_lon) / m_lon_range) * m_x);
        float y = std::round(((lat - m_bounds.min_lat) / m_lat_range) * m_y);

        if(x < 0)
            x = 0;
        else if(x > m_x - 1)
            x = m_x - 1;

        if(y < 0)
            y = 0;
        else if(y > m_y - 1)
            y = m_y - 1;

        return static_cast<Uint16>(y * m_y + x);
    }

    Uint64 Grid::findNode(const float lat, const float lon, const float range, const bool first) const
    {
        const auto nodes         = m_array->getNodes();
        const auto cell          = nodeToCell(lat, lon);
        const auto nodes_in_cell = m_cells.at(cell).children;
        float      min           = range;
        Uint64     match         = 0;

        if(nodes_in_cell.empty())
            return U64_INF;

        for(const auto& id : nodes_in_cell)
        {
            const auto node  = nodes[id];
            float      l_min = Geo::dist(lat, lon, node.lat, node.lon);
            if(l_min < min)
            {
                min   = l_min;
                match = node.id;

                if(first)
                    return match;
            }
        }

        return match;
    }

    // Public

    void Grid::set(const Uint16 cell, const Uint64 index)
    {
        m_cells[cell].children.emplace_back(index);
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

        const auto bl    = nodeToCell(bounds.min_lat, bounds.min_lon);
        const auto tr    = nodeToCell(bounds.max_lat, bounds.max_lon);
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

    Uint64
    Grid::getFirstClosest(const float lat, const float lon, float range, const bool search_neighbours) const
    {
        // Cell is not empty, but we did not find a node inside the range.
        // So we repeat with double the range until we find a node.
        auto match = findNode(lat, lon, range, true);
        while(match == 0)
        {
            range *= 2;
            match = findNode(lat, lon, range, true);
        }

        const auto node = m_array->m_nodes[match];

        if(match == U64_INF && search_neighbours)
        {
            // Respective lat and lon range of a cell.
            const auto cell_lat = m_lat_range / m_y;
            const auto cell_lon = m_lat_range / m_x;
            Vector<Pair<float, float>> neighbour_cells{
                {lat - cell_lat, lon - cell_lon},
                {lat - cell_lat, lon},
                {lat - cell_lat, lon + cell_lon},
                {lat, lon - cell_lon},
                {lat, lon + cell_lon},
                {lat + cell_lat, lon - cell_lon},
                {lat + cell_lat, lon + cell_lon},
                {lat + cell_lat, lon}
            };

            for(const auto& n : neighbour_cells)
            {
                match = getFirstClosest(n.first, n.second, range, false);
                if(match > 0 && match < U64_INF)
                    return match;
            }
        }
        return match;
    }

    Uint64 Grid::getBestClosest(const float lat, const float lon) const
    {
        return findNode(lat, lon, F32_INF, false);
    }

}  // namespace OSM
