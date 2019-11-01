#ifndef OSM_ADJACENCYARRAY_HPP
#define OSM_ADJACENCYARRAY_HPP

#include "structures/Primitives.hpp"

namespace OSM
{
    inline bool compareNodes(const Node& first, const Node& second);
    inline bool compareEdges(const Edge& first, const Edge& second);

    class AdjacencyArray final
    {
    public:
        Vector<Node>   m_nodes;
        Vector<Edge>   m_edges;
        Vector<Sint64> m_offset;

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
        void     addEdge(const Edge& edge);
        void     computeOffsets();
    };
}  // namespace OSM

#endif  // OSM_ADJACENCYARRAY_HPP
