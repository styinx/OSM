#ifndef OSM_ADJACENCYARRAY_HPP
#define OSM_ADJACENCYARRAY_HPP

#include <ISerializable.hpp>
#include <array>
#include <cstdint>
#include <map>
#include <prototypes.hpp>
#include <set>
#include <unordered_map>
#include <vector>

namespace OSM
{
    using ID = std::int64_t;

    enum class EdgeType : Byte
    {
        NONE            = 0x00,
        PEDESTRIAN      = 0x01,
        BIKE            = 0x02,
        PEDESTRIAN_BIKE = 0x03,
        CAR             = 0x04,
        PEDESTRIAN_CAR  = 0x05,  // unlikely
        BIKE_CAR        = 0x06,
        ANY             = 0x07
    };

    struct Node
    {
//        ID       id;
//        double   lat;
//        double   lon;
//        EdgeType type;

        explicit Node(const ID id, const double lat, double lon);
    };

    struct Edge
    {
        ID target;
    };

    class AdjacencyArray final : public ISerializable
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

        Vector<Byte> serialize() override;
    };
}  // namespace OSM

#endif  // OSM_ADJACENCYARRAY_HPP
