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
        , m_changed(m_array->nodeCount(), false)
    {
    }

    void RouteSearch::resetVisited(const Vector<bool>& changed)
    {
        Uint64 id = 0;
        for(const auto& c : changed)
        {
            if(c)
            {
                m_weights[id]   = F32_INF;
                m_distances[id] = 0;
                m_durations[id] = 0;
                m_previous[id]  = U64_INF;
            }
            id++;
        }
        m_visited = Vector<bool>(m_array->nodeCount(), false);
        m_changed = Vector<bool>(m_array->nodeCount(), false);
    }

    PathResult
    RouteSearch::route(const Uint64 from, const Uint64 to, const TransportType type, const bool reset)
    {
        using SearchNode = Pair<Uint64, float>;
        using Clock      = std::chrono::system_clock;
        using MS         = std::chrono::milliseconds;

        const auto comparator = [](const SearchNode& lhs, const SearchNode& rhs) {
            return lhs.second > rhs.second;
        };

        const auto time          = Clock::now();
        const auto alt_speed     = (type & 0x01) ? 5 : ((type & 0x02) ? 15 : 0);
        const auto nodes         = m_array->getNodes();
        const auto node_to       = nodes[to];
        const auto midpoint_node = midpointNode(nodes[from], node_to);
        const auto search_range  = distNodes(nodes[from], node_to);

        m_weights[from]   = 0;
        m_distances[from] = 0;
        m_durations[from] = 0;

        std::priority_queue<SearchNode, Vector<SearchNode>, decltype(comparator)> queue(comparator);
        queue.push({from, m_weights[from]});

        Uint64 node = from;
        while(!queue.empty() && node != to)
        {
            node              = queue.top().first;
            const auto weight = queue.top().second;
            queue.pop();

            // If already visited or the weight is bigger.
            if(weight > m_weights[node] || m_visited[node])
                continue;

            m_visited[node] = true;

            for(const auto& e : m_array->edges(node))
            {
                // Skip roads that are not part of the chosen transportation type.
                if(!(e.mask & type))
                    continue;

                const auto  duration   = e.duration(alt_speed) * 1000;
                const auto  distance   = distNodes(nodes[e.target], node_to) / e.speed / 1000;
                const float new_weight = weight + duration + distance;

                // Check only nodes that are inside the start's and stop's radius.
                if(distNodes(nodes[e.target], midpoint_node, "km") * 1.5 < search_range)
                {
                    if(new_weight < m_weights[e.target])
                    {
                        m_weights[e.target]   = new_weight;
                        m_distances[e.target] = e.distance;
                        m_durations[e.target] = e.duration(alt_speed);
                        m_previous[e.target]  = node;
                        queue.push({e.target, new_weight});

                        m_changed[node]     = true;
                        m_changed[e.target] = true;
                    }
                }
            }
        }

        // Create the route from start to stop.
        PathResult result{};
        auto       p = m_previous[to];
        while(p != U64_INF && p != from)
        {
            result.route.emplace_back(p);
            result.distance += m_distances[p];
            result.duration += m_durations[p];
            p = m_previous[p];
        }

        // Reset all values that were changed during the search.
        if(reset)
        {
            resetVisited(m_changed);
        }

        // Set result values.
        result.start       = from;
        result.stop        = to;
        result.way_found   = !result.route.empty();
        result.calculation = std::chrono::duration_cast<MS>(Clock::now() - time).count();
        return result;
    }

    PathResult
    RouteSearch::biroute(const Uint64 from, const Uint64 to, const TransportType type, const bool reset)
    {
        using SearchNode = Pair<Uint64, float>;
        using Clock      = std::chrono::system_clock;
        using MS         = std::chrono::milliseconds;

        const auto start = Clock::now();

        Vector<bool> forward(m_array->nodeCount(), false);
        Vector<bool> backward(m_array->nodeCount(), false);
        Uint64       target = 0;

        m_weights[from]   = 0;
        m_weights[to]     = 0;
        m_distances[from] = 0;
        m_distances[to]   = 0;
        m_durations[from] = 0;
        m_durations[to]   = 0;

        PathResult result{};
        std::mutex m;

        // Should be run in two separate threads for bidirectional search.
        const auto search = [this, &m, &result, &forward, &backward, &from, &to, &target, &type](
                                const Uint64 start, Vector<bool>& visited) {
            const auto comparator = [](const SearchNode& lhs, const SearchNode& rhs) {
                return lhs.second > rhs.second;
            };

            const auto     nodes         = m_array->getNodes();
            const auto     node_to       = nodes[to];
            const auto     midpoint_node = midpointNode(nodes[from], node_to);
            const auto     search_range  = distNodes(nodes[from], node_to);
            const auto     alt_speed     = (type & 0x01) ? 5 : ((type & 0x02) ? 15 : 0);
            Vector<Uint64> path{};
            Vector<float> weights(m_array->nodeCount(), F32_INF);
            Vector<Uint64> previous(m_array->nodeCount(), U64_INF);

            std::priority_queue<SearchNode, Vector<SearchNode>, decltype(comparator)> queue(comparator);
            queue.push({start, m_weights[start]});

            Uint64 node;
            while(!queue.empty())
            {
                node              = queue.top().first;
                const auto weight = queue.top().second;
                queue.pop();

                // If already visited or the weight is bigger.
                if(weight > weights[node] || visited[node])
                    continue;

                visited[node] = true;

                if(forward[node] && backward[node])
                {
                    m.lock();
                    if(target == U64_INF)
                    {
                        target = node;
                    }
                    m.unlock();
                    break;
                }

                for(const auto& e : m_array->edges(node))
                {
                    // Skip roads that are not part of the chosen transportation type.
                    if(!(e.mask & type))
                        continue;

                    const auto  duration   = e.duration(alt_speed) * 1000;
                    const auto  distance   = distNodes(nodes[e.target], node_to) / e.speed / 1000;
                    const float new_weight = weight + duration + distance;

                    // Check only nodes that are inside the start's and stop's radius.
                    if(distNodes(nodes[e.target], midpoint_node, "km") * 1.5 < search_range)
                    {
                        if(new_weight < weights[e.target])
                        {
                            weights[e.target]   = new_weight;
                            m_distances[e.target] = e.distance;
                            m_durations[e.target] = e.duration(alt_speed);
                            previous[e.target]  = node;
                            queue.push({e.target, new_weight});

                            m_changed[node]     = true;
                            m_changed[e.target] = true;
                        }
                    }
                }
            }

            float distance = 0;
            float duration = 0;
            auto  p        = previous[target];
            while(p != U64_INF && p != start)
            {
                path.emplace_back(p);
                distance += m_distances[p];
                duration += m_durations[p];
                p = previous[p];
            }

            m.lock();
            if(result.route.empty())
            {
               std::reverse(path.begin(), path.end());
                result.route.insert(result.route.end(), path.begin(), path.end());
            }
            else
            {
                result.route.insert(result.route.end(), path.begin(), path.end());
            }
            result.distance += distance;
            result.duration += duration;
            m.unlock();
        };

        std::thread t1(search, from, std::ref(forward));
        std::thread t2(search, to, std::ref(backward));

        t1.join();
        t2.join();

        if(reset)
        {
            resetVisited(m_changed);
        }

        result.start       = from;
        result.stop        = to;
        result.way_found   = !result.route.empty();
        result.calculation = std::chrono::duration_cast<MS>(Clock::now() - start).count();
        return result;
    }

    PathResult
    RouteSearch::route(const Uint64 from, const Uint64 to, const TransportType type, Vector<Node> attractions)
    {
        const auto nodes     = m_array->getNodes();
        const auto node_from = nodes[from];
        const auto node_to   = nodes[to];

        PathResult result{};
        result.start = from;
        result.stop  = to;

        Node start = node_to;
        Node stop  = Node{0, 0, 0, 0, 0};

        while(!attractions.empty())
        {
            stop = closestNode(start, attractions);
            attractions.erase(
                std::remove(attractions.begin(), attractions.end(), stop), attractions.end());

            PathResult temp = route(start.id, stop.id, type);
            if(temp.way_found)
            {
                std::reverse(temp.route.begin(), temp.route.end());
                result.route.insert(result.route.end(), temp.route.begin(), temp.route.end());
                start = stop;
            }
        }

        stop = node_from;

        PathResult last = route(start.id, stop.id, type);
        std::reverse(last.route.begin(), last.route.end());
        result.route.insert(result.route.end(), last.route.begin(), last.route.end());

        return result;
    }

}  // namespace OSM
