#ifndef OSM_DIJKSTRA_HPP
#define OSM_DIJKSTRA_HPP

#include "NonCopyable.hpp"
#include "NonMoveable.hpp"
#include "structures/AdjacencyArray.hpp"

namespace OSM
{

    class Dijkstra final
        : public NonCopyable
        , public NonMoveable
    {
    private:
        const Uint64          U64_max = std::numeric_limits<Uint64>::max();
        const AdjacencyArray* m_array;
        Vector<Uint64>        m_V;
        Vector<Uint64>        m_prev;
        Vector<float>         m_dist;

        Queue<Uint64> m_frontier;
        Set<Uint64>   m_explored;

    public:
        explicit Dijkstra(const AdjacencyArray* array);
        virtual ~Dijkstra() = default;

        Vector<Uint64> compute(const Uint64 from, const Uint64 to);
        std::string computeGeoJson(const Uint64 from, const Uint64 to);
    };

}  // namespace OSM

#endif  // OSM_DIJKSTRA_HPP
