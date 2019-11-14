#ifndef OSM_DIJKSTRA_HPP
#define OSM_DIJKSTRA_HPP

#include "NonCopyable.hpp"
#include "NonMoveable.hpp"

#include "structures/Graph.hpp"

namespace OSM
{

    class Dijkstra final
        : public NonCopyable
        , public NonMoveable
    {
    private:

    public:
        Dijkstra()                          = default;
        virtual ~Dijkstra()                            = default;

        void compute(const Graph& g);
    };

}  // namespace OSM

#endif  // OSM_DIJKSTRA_HPP
