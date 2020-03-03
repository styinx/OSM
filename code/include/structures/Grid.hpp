#ifndef OSM_GRID_HPP
#define OSM_GRID_HPP

#include "NonCopyable.hpp"
#include "NonMoveable.hpp"
#include "structures/AdjacencyArray.hpp"
#include "types.hpp"

namespace OSM
{

    class Grid final
        : public NonCopyable
        , public NonMoveable
    {
    public:
        struct Cell
        {
            Vector<Uint64> children;
        };

    private:
        static const Uint16 m_x = 100;
        static const Uint16 m_y = 100;

        const MapBounds       m_bounds;
        const AdjacencyArray* m_array;
        const float           m_lat_range;
        const float           m_lon_range;
        Vector<Cell>          m_cells{m_x * m_y};

        Uint16 nodeToCell(const float lat, const float lon) const;

    public:
        explicit Grid(const MapBounds& bounds, const AdjacencyArray* array);
        virtual ~Grid() = default;

        void             set(const Uint16 cell, const Uint64 index);
        void             set(const float lat, const float lon, const Uint64 index);
        Vector<Uint64>   get(const Uint16 cell) const;
        Vector<Uint64>   get(const float lat, const float lon) const;
        Vector<Uint64>   get(const MapBounds& bounds) const;
        const MapBounds& getBounds() const;
        Vector<Cell>     getCells() const;
        Uint64           getFirstClosest(const float lat, const float lon, const float range = 500) const;
    };

}  // namespace OSM

#endif  // OSM_GRID_HPP
