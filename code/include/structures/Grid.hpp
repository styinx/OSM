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

        const MapBounds m_bounds;
        Vector<Cell>    m_cells{10000};

    public:
        explicit Grid(const MapBounds& bounds);
        virtual ~Grid() = default;

        void           set(const float lat, const float lon, const Uint64 index);
        Vector<Uint64> get(const Uint16 cell) const;
        Vector<Uint64> get(const float lat, const float lon) const;
    };

}  // namespace OSM

#endif  // OSM_GRID_HPP
