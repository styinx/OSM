#ifndef OSM_GRID_HPP
#define OSM_GRID_HPP

#include "NonCopyable.hpp"
#include "NonMoveable.hpp"
#include "gui/mapTypes.hpp"
#include "prototypes.hpp"

namespace OSM
{

    class Grid final
        : public NonCopyable
        , public NonMoveable
    {
    private:
        struct Cell
        {
            Vector<Uint64> children;
        };

        static const Sint16 m_x = 100;
        static const Sint16 m_y = 100;

        const MapBounds m_bounds;
        const float     m_lat_range;
        const float     m_lon_range;
        Vector<Cell>    m_cells{m_x * m_y};

    public:
        explicit Grid(const MapBounds& bounds);
        virtual ~Grid() = default;

        void             set(const float lat, const float lon, const Uint64 index);
        Vector<Uint64>   get(const Uint16 cell) const;
        Vector<Uint64>   get(const float lat, const float lon) const;
        const MapBounds& getBounds() const;
    };

}  // namespace OSM

#endif  // OSM_GRID_HPP
