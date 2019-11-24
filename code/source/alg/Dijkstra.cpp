#include "alg/Dijkstra.hpp"

#include <numeric>

namespace OSM
{

    Dijkstra::Dijkstra(const AdjacencyArray* array)
        : m_array(array)
        , m_V(array->nodeCount())
        , m_prev(array->nodeCount(), U64_max)
        , m_dist(array->nodeCount(), U64_max)
        , m_frontier()
        , m_explored()
    {
        // Init Vertex set from 0 to n (index of the node in the array)
        for(Uint64 i = 0; i < array->nodeCount(); ++i)
        {
            m_V[i] = i;
        }
    }

    Pair<float, Vector<Uint64>> Dijkstra::compute(const Uint64 from, const Uint64 to)
    {
        Vector<Uint64> path{};
        Uint64         u       = 0;
        float          dist_m  = -1;
        const auto     ooffsets = m_array->getOOffsets();
        const auto     ioffsets = m_array->getIOffsets();
        const auto     nodes   = m_array->getNodes();

        m_dist = Vector<float>(nodes.size(), U64_max);
        m_prev = Vector<Uint64>(nodes.size(), U64_max);

        m_dist[to] = 0;

        while(!m_V.empty())
        {
            // Find node with min dist that is still in V
            auto min       = U64_max;
            auto min_index = 0;
            for(Uint64 index = 0; index < m_dist.size(); ++index)
            {
                if(m_V[index] < U64_max)
                {
                    auto l_min = m_dist[index];
                    if(l_min < min)
                    {
                        min       = l_min;
                        min_index = index;
                    }
                }
            }
            if(min == U64_max)
            {
                return {dist_m, path};
            }
            u = m_V[min_index];

            // Check neighbours of min neighbour
            for(Uint64 i = ooffsets[u]; i < ooffsets[u + 1]; ++i)
            {
                const auto neighbour = i;

                if(m_V[i] < U64_max)
                {
                    const float alternative = m_dist[u] + distNodes(nodes[u], nodes[neighbour]);

                    if(alternative < m_dist[neighbour])
                    {
                        m_dist[neighbour] = alternative;
                        m_prev[neighbour] = u;
                    }
                }
            }

            // Remove u from V
            m_V[u] = U64_max;

            if(u == from)
            {
                dist_m = m_dist[u];
                while(u < U64_max)
                {
                    path.emplace_back(u);
                    u = m_prev[u];
                }
            }
        }

        return {dist_m, path};
    }

    std::string Dijkstra::computeGeoJson(const Uint64 from, const Uint64 to)
    {
        auto pair = compute(from, to);


    }

}  // namespace OSM
