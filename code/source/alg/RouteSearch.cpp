#include "alg/RouteSearch.hpp"

namespace OSM
{

    RouteSearch::RouteSearch(const AdjacencyArray* array, const Grid* grid)
        : m_array(array)
        , m_grid(grid)
        , m_V(array->nodeCount())
        , m_prev(array->nodeCount(), U64_max)
        , m_dist(array->nodeCount(), U64_max)
        , m_frontier()
        , m_explored()
    {
    }

    Vector<Uint64> RouteSearch::computeDijkstra(const Uint64 from, const Uint64 to)
    {
        Vector<Uint64> path{};
        Uint64         u        = 0;
        const auto     ooffsets = m_array->getOOffsets();
        const auto     ioffsets = m_array->getIOffsets();
        const auto     nodes    = m_array->getNodes();
        const auto     edges    = m_array->getEdges();

        // Init Vertex set from 0 to n (index of the node in the array)
        for(Uint64 i = 0; i < m_array->nodeCount(); ++i)
        {
            m_V[i] = i;
        }

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
                return {path};
            }
            u = m_V[min_index];

            // Check outgoing neighbours of min neighbour
            for(Uint64 i = ooffsets[u]; i < ooffsets[u + 1]; ++i)
            {
                const auto neighbour = edges[i].target;

                if(m_V[neighbour] < U64_max)
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

            // we found a route
            if(u == from)
            {
                while(u < U64_max)
                {
                    path.emplace_back(u);
                    u = m_prev[u];
                }
            }
        }

        return {path};
    }

    Vector<Uint64> RouteSearch::PQ(const Uint64 from, const Uint64 to)
    {
        const auto ooffsets = m_array->getOOffsets();
        const auto ioffsets = m_array->getIOffsets();
        const auto nodes    = m_array->getNodes();
        const auto edges    = m_array->getEdges();

        using Prio = Pair<Uint64, float>;
        struct CMP
        {
            bool operator()(const Prio& l, const Prio& r){ return l.second < r.second; }
        };
        std::priority_queue<Prio, Vector<Prio>, CMP> pq;
        Vector<Uint64> path;

        m_dist = Vector<float>(nodes.size(), U64_max);
        m_prev = Vector<Uint64>(nodes.size(), U64_max);
        m_V = Vector<Uint64>(nodes.size(), U64_max);

        m_dist[from] = 0;

        for(const auto& node : nodes)
        {
            pq.emplace(Prio{node.id, m_dist[node.id]});
        }

        while(!pq.empty())
        {
            const auto t = pq.top();
            auto u = t.first;
            m_V[u] = U64_max;
            pq.pop();

            for(Uint64 i = ooffsets[u]; i < ooffsets[u + 1]; ++i)
            {
                if(m_V[i] != U64_max)
                {
                    const auto neighbour = edges[i].target;

                    const float alternative = m_dist[u] + distNodes(nodes[u], nodes[neighbour]);

                    if(alternative < m_dist[neighbour])
                    {
                        m_dist[neighbour] = alternative;
                        m_prev[neighbour] = u;
                        pq.push(Prio{u, t.second - alternative});
                        m_V[u] = 0;
                    }
                }
            }
        }

        for(const auto& n : m_prev)
        {
            if(n != U64_max)
            {
                path.emplace_back(n);
            }
        }

        return path;
    }

    Vector<Uint64> RouteSearch::UCS(const Uint64 from, const Uint64 to)
    {
        Uint64     node     = from;
        const auto ooffsets = m_array->getOOffsets();
        const auto ioffsets = m_array->getIOffsets();
        const auto nodes    = m_array->getNodes();
        const auto edges    = m_array->getEdges();

        m_frontier.clear();
        m_explored.clear();

        m_frontier.emplace_back(node);

        while(!m_frontier.empty())
        {
            node = m_frontier.front();
            m_frontier.pop_front();

            if(node == to)
            {
                return {m_frontier.begin(), m_frontier.end()};
            }

            m_explored.emplace(node);

            // Check outgoing neighbours of min neighbour
            for(Uint64 i = ooffsets[node]; i < ooffsets[node + 1]; ++i)
            {
                const auto neighbour = edges[i].target;
                if(std::find(m_explored.begin(), m_explored.end(), neighbour) == m_explored.end())
                {
                    m_frontier.emplace_back(neighbour);
                }
            }
        }

        return {};
    }

    std::string RouteSearch::computeGeoJson(const Uint64 from, const Uint64 to)
    {
        std::string path;
        const auto  nodes = m_array->getNodes();

        for(const auto& node : computeDijkstra(from, to))
        {
            path += "[" + std::to_string(nodes[node].lon) + std::to_string(nodes[node].lat) + "]";
        }
        return path;
    }

}  // namespace OSM
