#ifndef OSM_ADJACENCYARRAY_HPP
#define OSM_ADJACENCYARRAY_HPP

#include <array>
#include <cstdint>
#include <map>
#include <set>
#include <unordered_map>
#include <vector>

namespace OSM
{
    using ID = std::int64_t;

    struct Node
    {
        ID     id;
//        double lat;
//        double lon;

        explicit Node(const ID id, const double lat, double lon);
    };

    struct Edge
    {
        ID target;
    };

    class AdjacencyArray final
    {
    private:
        std::vector<Node> m_nodes;
        std::vector<Edge> m_edges;

    public:
        explicit AdjacencyArray();
        AdjacencyArray(const AdjacencyArray& other)     = delete;
        AdjacencyArray(AdjacencyArray&& other) noexcept = delete;
        AdjacencyArray& operator=(const AdjacencyArray& other) = delete;
        AdjacencyArray& operator=(AdjacencyArray&& other) noexcept = delete;
        virtual ~AdjacencyArray()                                  = default;

        unsigned        nodeCount() const;
        unsigned        edgeCount() const;
        AdjacencyArray& addNode(const Node& node);
        AdjacencyArray& addEdge(const Edge& edge);
    };
}  // namespace OSM

#endif  // OSM_ADJACENCYARRAY_HPP
