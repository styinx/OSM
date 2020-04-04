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
        const float DURATION_FACTOR = 100;
        const float DISTANCE_FACTOR = 1000;
        const float DISTANCE_RANGE  = 1000;
        const AdjacencyArray* m_array;
        const Grid*           m_grid;

        Vector<float>  m_weights;
        Vector<float>  m_distances;
        Vector<float>  m_durations;
        Vector<Uint64> m_previous;
        Vector<bool>   m_visited;
        Vector<bool>   m_changed;

        void resetVisited(const Vector<bool>& changed);

    public:
        explicit RouteSearch(const AdjacencyArray* array, const Grid* grid);
        virtual ~RouteSearch() = default;

        PathResult
        route(const Uint64 from, const Uint64 to, const TransportType type, const bool reset = true);
        PathResult
        biroute(const Uint64 from, const Uint64 to, const TransportType type, const bool reset = true);
        PathResult
        route(const Uint64 from, const Uint64 to, const TransportType type, Vector<Node> attractions);
    };

}  // namespace OSM

#endif  // OSM_ROUTESEARCH_HPP
