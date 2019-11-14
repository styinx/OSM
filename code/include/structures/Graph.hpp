#ifndef OSM_GRAPH_HPP
#define OSM_GRAPH_HPP

#include "NonCopyable.hpp"
#include "NonMoveable.hpp"
#include "structures/AdjacencyArray.hpp"

namespace OSM
{

    class Graph
        : public NonCopyable
        , public NonMoveable
    {
    private:

    public:
        Graph(const AdjacencyArray& array);
        virtual ~Graph() = default;
    };

}  // namespace OSM

#endif  // OSM_GRAPH_HPP
