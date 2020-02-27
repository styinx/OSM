#include "alg/RouteSearch.hpp"

namespace OSM
{

    RouteSearch::RouteSearch(const AdjacencyArray* array, const Grid* grid)
        : m_array(array)
        , m_grid(grid)
    {
    }

    PathResult RouteSearch::route(const Uint64 from, const Uint64 to)
    {
        using SearchNode = Pair<Uint64, float>;

        const auto edges   = m_array->getNodes();

        Vector<float>  weights(m_array->nodeCount(), F32_INF);
        Vector<Uint64> previous(m_array->nodeCount(), U64_INF);
        Vector<bool> visited(m_array->nodeCount(), false);
        Vector<Edge> edges_visited;
        std::priority_queue<SearchNode, Vector<SearchNode>, std::greater<>> queue;

        weights[from] = 0;
        queue.push({from, weights[from]});

        while(!queue.empty())
        {
            const auto node   = queue.top().first;
            const auto weight = queue.top().second;
            queue.pop();

            if(weight > weights[node] || visited[node])
                continue;

            visited[node] = true;

            for(const auto& e : m_array->edges(node))
            {
                Uint64 neighbour          = e.target;
                float  neighbour_weight   = e.weight();
                float  new_weight         = weight + neighbour_weight;

                if(new_weight < weights[neighbour])
                {
                    edges_visited.emplace_back(e);
                    weights[neighbour]  = new_weight;
                    previous[neighbour] = node;
                    queue.push({neighbour, weights[neighbour]});
                }
            }
        }

        float distance = 0;
        float duration = 0;
        for(const auto& edge : edges_visited)
        {
            distance += edge.distance;
            duration += edge.weight();
        }

        Vector<Uint64> path;
        auto p = previous[to];
        while(p != U64_INF && p != from)
        {
            path.emplace_back(p);
            p = previous[p];
        }

        return {from, to, distance, duration, path};
    }

}  // namespace OSM
