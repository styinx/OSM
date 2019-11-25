#ifndef OSM_ADJACENCYARRAY_HPP
#define OSM_ADJACENCYARRAY_HPP

#include "structures/Primitives.hpp"

#include "NonCopyable.hpp"
#include "NonMoveable.hpp"

namespace OSM
{
    inline bool compareNodes(const Node& first, const Node& second);
    inline bool compareEdgesSource(const Edge& first, const Edge& second);
    inline bool compareEdgesTarget(const Edge& first, const Edge& second);
    inline bool compareEdgesSourceTarget(const Edge& first, const Edge& second);

    class AdjacencyArray final
        : public NonCopyable
        , public NonMoveable
    {
    private:
        Vector<Node>   m_nodes;
        Vector<Edge>   m_edges;
        Vector<Uint64> m_i_offset;
        Vector<Uint64> m_o_offset;

    public:
        explicit AdjacencyArray();
        AdjacencyArray(const AdjacencyArray& other)     = delete;
        AdjacencyArray(AdjacencyArray&& other) noexcept = delete;
        AdjacencyArray& operator=(const AdjacencyArray& other) = delete;
        AdjacencyArray& operator=(AdjacencyArray&& other) noexcept = delete;
        virtual ~AdjacencyArray()                                  = default;

        void           computeOffsets();
        void           addNode(const Node& node);
        void           addIOEdge(const Edge& edge);
        size_t         nodeCount() const;
        size_t         edgeCount() const;
        Vector<Node>   getNodes() const;
        Vector<Edge>   getEdges() const;
        Vector<Uint64> getIOffsets() const;
        Vector<Uint64> getOOffsets() const;
    };
}  // namespace OSM

#endif  // OSM_ADJACENCYARRAY_HPP
