#ifndef OSM_ADJACENCYARRAY_HPP
#define OSM_ADJACENCYARRAY_HPP

#include "NonCopyable.hpp"
#include "NonMoveable.hpp"
#include "structures/Primitives.hpp"

#include <mutex>

namespace OSM
{
    inline bool compareNodesID(const Node& first, const Node& second);
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
        Vector<Uint64> m_o_offset;

        std::mutex m_node_mutex;
        std::mutex m_edge_mutex;

    public:
        explicit AdjacencyArray();
        AdjacencyArray(const AdjacencyArray& other)     = delete;
        AdjacencyArray(AdjacencyArray&& other) noexcept = delete;
        AdjacencyArray& operator=(const AdjacencyArray& other) = delete;
        AdjacencyArray& operator=(AdjacencyArray&& other) noexcept = delete;
        virtual ~AdjacencyArray()                                  = default;

        void           computeOffsets();
        void           addNode(const Node& node);
        void           addEdge(const Edge& edge);
        size_t         nodeCount() const;
        size_t         edgeCount() const;
        Vector<Node>   getNodes() const;
        Vector<Edge>   getEdges() const;
        Vector<Uint64> getOOffsets() const;
        Vector<Uint64> neighbourIDs(const Uint64 node) const;
        Vector<Node> neighbours(const Uint64 node) const;
        Vector<Edge> edges(const Uint64 node) const;
    };
}  // namespace OSM

#endif  // OSM_ADJACENCYARRAY_HPP
