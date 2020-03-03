#include "alg/RouteSearch.hpp"

namespace OSM
{

    RouteSearch::RouteSearch(const AdjacencyArray* array, const Grid* grid)
        : m_array(array)
        , m_grid(grid)
        , m_weights(m_array->nodeCount(), F32_INF)
        , m_distances(m_array->nodeCount(), F32_INF)
        , m_durations(m_array->nodeCount(), F32_INF)
        , m_previous(m_array->nodeCount(), U64_INF)
        , m_visited(m_array->nodeCount(), false)
    {
    }

    PathResult
    RouteSearch::route(const Uint64 from, const Uint64 to, const TransportType type, const Vector<Node>& attractions)
    {
        using SearchNode   = Pair<Uint64, float>;
        using Clock        = std::chrono::system_clock;
        using Milliseconds = std::chrono::milliseconds;

        const auto start = Clock::now();

        const auto comparator = [](const SearchNode& lhs, const SearchNode& rhs) {
            return lhs.second > rhs.second;
        };

        const auto nodes        = m_array->getNodes();
        const auto node_from    = nodes[from];
        const auto node_to      = nodes[to];
        const auto from_to_dist = Geo::dist(node_from.lat, node_from.lon, node_to.lat, node_to.lon);

        std::priority_queue<SearchNode, Vector<SearchNode>, decltype(comparator)> queue(comparator);
        m_weights   = Vector<float>(m_array->nodeCount(), F32_INF);
        m_distances = Vector<float>(m_array->nodeCount(), F32_INF);
        m_durations = Vector<float>(m_array->nodeCount(), F32_INF);
        m_visited   = Vector<bool>(m_array->nodeCount(), false);
        m_previous  = Vector<Uint64>(m_array->nodeCount(), U64_INF);

        m_weights[from]   = 0;
        m_distances[from] = 0;
        m_durations[from] = 0;
        queue.push({from, m_weights[from]});

        for(Uint64 i = 0; i < nodes.size(); ++i)
        {
            const auto& other = nodes[i];
            m_weights[i]      = Geo::dist(node_from.lat, node_from.lon, other.lat, other.lon);
        }

        while(!queue.empty())
        {
            const auto node   = queue.top().first;
            const auto weight = queue.top().second;
            queue.pop();

            if(weight > m_weights[node] || m_visited[node])
                continue;

            m_visited[node] = true;

            for(const auto& e : m_array->edges(node))
            {
                // Skip roads that are not part of the chosen transportation type.
                if(!(e.mask & type))
                    continue;

                Uint64 neighbour        = e.target;
                float  neighbour_weight = e.weight();
                float  new_weight       = weight + neighbour_weight;

                if(new_weight < m_weights[neighbour])
                {
                    m_weights[neighbour]   = new_weight;
                    m_distances[neighbour] = e.distance;
                    m_durations[neighbour] = e.duration();
                    m_previous[neighbour]  = node;
                    queue.push({neighbour, m_weights[neighbour]});
                }
            }
        }

        Vector<Uint64> path;
        float          distance = 0;
        float          duration = 0;
        auto           p        = m_previous[to];
        while(p != U64_INF && p != from)
        {
            path.emplace_back(p);
            distance += m_distances[p];
            duration += m_durations[p];
            p = m_previous[p];
        }

        const Uint64 calculation =
            std::chrono::duration_cast<Milliseconds>(Clock::now() - start).count();
        return {from, to, distance, duration, path, calculation};
    }

}  // namespace OSM
