#ifndef OSM_ROUTESEARCH_HPP
#define OSM_ROUTESEARCH_HPP

#include "NonCopyable.hpp"
#include "NonMoveable.hpp"
#include "structures/AdjacencyArray.hpp"
#include "structures/Grid.hpp"

namespace OSM
{

    class RouteSearch final
        : public NonCopyable
        , public NonMoveable
    {
    private:
        const AdjacencyArray* m_array;
        const Grid*           m_grid;

    public:
        explicit RouteSearch(const AdjacencyArray* array, const Grid* grid);
        virtual ~RouteSearch() = default;

        PathResult route(const Uint64 from, const Uint64 to);
    };

}  // namespace OSM

#endif  // OSM_ROUTESEARCH_HPP
