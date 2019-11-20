#ifndef OSM_ADJACENCYARRAY_HPP
#define OSM_ADJACENCYARRAY_HPP

#include "structures/Primitives.hpp"

namespace OSM
{
    inline bool compareNodes(const Node& first, const Node& second);
    inline bool compareEdges(const IOEdge& first, const IOEdge& second);

    class AdjacencyArray final
    {
    private:
        Vector<Node>   m_nodes;
        Vector<Uint64> m_edges;
        Vector<Uint64> m_offset;

        // Only for reading and constructing the real structures
        Vector<IOEdge> m_io_edges;

    public:
        explicit AdjacencyArray();
        AdjacencyArray(const AdjacencyArray& other)     = delete;
        AdjacencyArray(AdjacencyArray&& other) noexcept = delete;
        AdjacencyArray& operator=(const AdjacencyArray& other) = delete;
        AdjacencyArray& operator=(AdjacencyArray&& other) noexcept = delete;
        virtual ~AdjacencyArray()                                  = default;

        void   computeOffsets();
        void   addNode(const Node& node);
        void   addIOEdge(const IOEdge& edge);
        size_t nodeCount() const;
        size_t edgeCount() const;
        Vector<Node> getNodes() const;
        Vector<Uint64> getEdges() const;
        Vector<Uint64> getOffsets() const;
    };
}  // namespace OSM

#endif  // OSM_ADJACENCYARRAY_HPP
