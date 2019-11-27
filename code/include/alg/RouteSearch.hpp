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
        const Uint64          U64_max = std::numeric_limits<Uint64>::max();
        const AdjacencyArray* m_array;
        const Grid*           m_grid;
        Vector<Uint64>        m_V;
        Vector<Uint64>        m_prev;
        Vector<float>         m_dist;

        Deque<Uint64> m_frontier;
        Set<Uint64>   m_explored;

    public:
        explicit RouteSearch(const AdjacencyArray* array, const Grid* grid);
        virtual ~RouteSearch() = default;

        Vector<Uint64> computeDijkstra(const Uint64 from, const Uint64 to);
        Vector<Uint64> UCS(const Uint64 from, const Uint64 to);
        std::string    computeGeoJson(const Uint64 from, const Uint64 to);
    };

}  // namespace OSM

#endif  // OSM_ROUTESEARCH_HPP
