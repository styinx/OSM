#ifndef OSM_ADJACENCYARRAY_HPP
#define OSM_ADJACENCYARRAY_HPP

#include <array>
#include <cstdint>
#include <map>
#include <prototypes.hpp>
#include <set>
#include <unordered_map>
#include <vector>

namespace OSM
{
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
        Sint64   id;
        float    lat;
        float    lon;
        EdgeType type1;
        EdgeType type2;
        EdgeType type3;
        EdgeType type4;

        explicit Node(const Sint64 id, const float lat, const float lon);
    };

    struct Edge
    {
        Sint64 source;
        Sint64 target;
    };

    inline bool operator<(const Node& first, const Node& second);
    inline bool operator<(const Edge& first, const Edge& second);
    inline bool compareNodes(const Node& first, const Node& second);
    inline bool compareEdges(const Edge& first, const Edge& second);

    class AdjacencyArray final
    {
    public:
        Vector<Node>   m_nodes;
        Vector<Sint64> m_edges;
        Vector<Sint64> m_offset;

        Vector<Edge> m_temp_edges;

        Uint64 m_edges_count = 0;

    public:
        explicit AdjacencyArray();
        AdjacencyArray(const AdjacencyArray& other)     = delete;
        AdjacencyArray(AdjacencyArray&& other) noexcept = delete;
        AdjacencyArray& operator=(const AdjacencyArray& other) = delete;
        AdjacencyArray& operator=(AdjacencyArray&& other) noexcept = delete;
        virtual ~AdjacencyArray()                                  = default;

        unsigned nodeCount() const;
        unsigned edgeCount() const;
        void     addNode(const Node& node);
        void     addEdge(const Sint64 from, const Sint64 to);
        void     computeEdges();
    };
}  // namespace OSM

#endif  // OSM_ADJACENCYARRAY_HPP
