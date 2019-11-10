#ifndef OSM_ADJACENCYARRAY_HPP
#define OSM_ADJACENCYARRAY_HPP

#include "structures/Primitives.hpp"

namespace OSM
{
    inline bool compareNodes(const Node& first, const Node& second);
    inline bool compareEdges(const Edge& first, const Edge& second);

    class AdjacencyArray final
    {
    private:
        Vector<Node>   m_nodes;
        Vector<Edge>   m_edges;
        Vector<Uint64> m_offset;

    public:
        explicit AdjacencyArray();
        AdjacencyArray(const AdjacencyArray& other)     = delete;
        AdjacencyArray(AdjacencyArray&& other) noexcept = delete;
        AdjacencyArray& operator=(const AdjacencyArray& other) = delete;
        AdjacencyArray& operator=(AdjacencyArray&& other) noexcept = delete;
        virtual ~AdjacencyArray()                                  = default;

        void   computeOffsets();
        void   addNode(const Node& node);
        void   addEdge(const Edge& edge);
        size_t nodeCount() const;
        size_t edgeCount() const;
        Node   getNode(const Uint64 index) const;
        Edge   getEdge(const Uint64 index) const;
        Sint64 getOffset(const Uint64 index) const;
    };
}  // namespace OSM

#endif  // OSM_ADJACENCYARRAY_HPP
