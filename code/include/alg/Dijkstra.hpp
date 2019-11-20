#ifndef OSM_DIJKSTRA_HPP
#define OSM_DIJKSTRA_HPP

#include "NonCopyable.hpp"
#include "NonMoveable.hpp"
#include "structures/AdjacencyArray.hpp"

#include <nlohmann/json.hpp>

namespace OSM
{

    class Dijkstra final
        : public NonCopyable
        , public NonMoveable
    {
    private:
    public:
        Dijkstra()          = default;
        virtual ~Dijkstra() = default;

        static Pair<float, Vector<Uint64>>
        compute(const AdjacencyArray& arr, const Uint64 from, const Uint64 to);

        static nlohmann::json
        computeGJSON(const AdjacencyArray& arr, const Uint64 from, const Uint64 to);
    };

}  // namespace OSM

#endif  // OSM_DIJKSTRA_HPP
