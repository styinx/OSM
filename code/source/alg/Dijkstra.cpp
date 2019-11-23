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
        const auto     offsets = m_array->getOffsets();
        const auto     nodes   = m_array->getNodes();
        const auto     edges   = m_array->getEdges();

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
            for(Uint64 i = offsets[u]; i < offsets[u + 1]; ++i)
            {
                const auto node_id   = edges[i];
                const auto neighbour = std::distance(
                    nodes.begin(), std::find_if(nodes.begin(), nodes.end(), [node_id](const Node& n) {
                        return n.id == node_id;
                    }));

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

        //
        //        auto node = from;
        //        auto cost = 0;
        //        m_frontier.emplace(node);
        //
        //        const auto& offsets = m_array->getOffsets();
        //        const auto& nodes   = m_array->getNodes();
        //
        //        while(true)
        //        {
        //            if(m_frontier.empty())
        //                return {U64_max, {}};
        //
        //            node = m_frontier.front();
        //            m_frontier.pop();
        //
        //            if(node == to)
        //                return {U64_max, {}};
        //
        //            m_explored.emplace(node);
        //
        //            for(Uint64 i = offsets[node]; i < offsets[node + 1]; ++i)
        //            {
        //                if(std::find(m_explored.begin(), m_explored.end(), i) != m_explored.end())
        //                {
        //                    m_frontier.emplace(i);
        //                }
        //            }
        //        }
        //
        //        return {dist_km, path};
    }

    Vector<Uint64> Dijkstra::UCS(Vector<Uint64> goal, int start)
    {
        return {};
        //        Vector<Uint64>                            solution;
        //        std::priority_queue<Pair<Uint64, Uint64>> queue;
        //        Uint64                                    count = 0;
        //
        //        for(Uint64 i = 0; i < goal.size(); i++)
        //        {
        //            solution.push_back(U64_max);
        //        }
        //
        //        queue.push(std::make_pair(0, start));
        //
        //        while(!queue.empty())
        //        {
        //            Pair<Uint64, Uint64> p = queue.top();
        //
        //            queue.pop();
        //            p.first *= -1;
        //
        //            if(find(goal.begin(), goal.end(), p.second) != goal.end())
        //            {
        //                Uint64 index = find(goal.begin(), goal.end(), p.second) - goal.begin();
        //
        //                if(solution[index] == U64_max)
        //                {
        //                    count++;
        //                }
        //
        //                if(solution[index] > p.first)
        //                {
        //                    solution[index] = p.first;
        //                }
        //
        //                queue.pop();
        //
        //                if(count == goal.size())
        //                    return solution;
        //            }
        //
        //            if(visited[p.second] == 0)
        //            {
        //                for(int i = 0; i < graph[p.second].size(); i++)
        //                {
        //                    queue.push(make_pair(
        //                        (p.first + cost[make_pair(p.second, graph[p.second][i])]) * -1,
        //                        graph[p.second][i]));
        //                }
        //            }
        //            visited[p.second] = 1;
        //        }

        //        return solution;
    }

    nlohmann::json Dijkstra::computeGJSON(const Uint64 from, const Uint64 to)
    {
        auto pair = compute(from, to);
        return nlohmann::json();
    }

}  // namespace OSM
