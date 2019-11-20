#include "alg/Dijkstra.hpp"

#include <numeric>

namespace OSM
{

    Pair<float, Vector<Uint64>>
    Dijkstra::compute(const AdjacencyArray& arr, const Uint64 from, const Uint64 to)
    {
        const Uint64 U64_max = std::numeric_limits<Uint64>::max();

        Uint64 n       = from;
        float  dist_km = 0;

        Vector<Uint64> V{arr.nodeCount()};
        std::iota(V.begin(), V.end(), 0);
        Vector<Uint64> path{arr.nodeCount(), U64_max};
        Vector<Uint64> dV{arr.nodeCount(), U64_max};

        path.emplace_back(n);

        while(!V.empty() || n == to)
        {
            // Check min distance for all neighbours
            float  n_dist_min = std::numeric_limits<float>::max();
            Uint64 n_min      = 0;
            for(Uint64 i = arr.getOffsets()[n]; i < arr.getOffsets()[n + 1]; ++i)
            {
                const float d = dist(arr.getNodes()[n], arr.getNodes()[i]);
                if(d < n_dist_min)
                {
                    n_dist_min = d;
                    n_min      = i;
                }
            }

            // Remove min neighbour from Q
            V[n_min] = U64_max;

            // Check neighbours of min neighbour
            for(Uint64 i = arr.getOffsets()[n_min]; i < arr.getOffsets()[n_min + 1]; ++i)
            {
                if(V[i] < U64_max)
                {
                    Uint64 alternative = dV[n_min] + dist(arr.getNodes()[n_min], arr.getNodes()[i]);

                    if(alternative < dV[i])
                    {
                        dV[i]   = alternative;
                        path[i] = n_min;
                    }
                    break;
                }
            }

            n = n_min;
        }
        return {dist_km, path};
    }

    nlohmann::json Dijkstra::computeGJSON(const AdjacencyArray& arr, const Uint64 from, const Uint64 to)
    {
        auto pair = compute(arr, from, to);
        return nlohmann::json();
    }

}  // namespace OSM
