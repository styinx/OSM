#ifndef OSM_ADJACENCYARRAY_HPP
#define OSM_ADJACENCYARRAY_HPP

#include "structures/Primitives.hpp"

namespace OSM
{
    inline bool compareNodes(const IONode& first, const IONode& second);
    inline bool compareEdges(const IOEdge& first, const IOEdge& second);

    class AdjacencyArray final
    {
    private:
        Vector<Node>   m_nodes;
        Vector<Uint64> m_edges;
        Vector<Uint64> m_offset;

        // Only for reading and constructing the real structures
        Vector<IONode> m_io_nodes;
        Vector<IOEdge> m_io_edges;

        template<typename R>
        R offsetCheck(Vector<R> container, Uint64 index) const
        {
            if(container.size() > 0 && index < container.size() - 1)
            {
                return container[index];
            }
            return R{};
        }

    public:
        explicit AdjacencyArray();
        AdjacencyArray(const AdjacencyArray& other)     = delete;
        AdjacencyArray(AdjacencyArray&& other) noexcept = delete;
        AdjacencyArray& operator=(const AdjacencyArray& other) = delete;
        AdjacencyArray& operator=(AdjacencyArray&& other) noexcept = delete;
        virtual ~AdjacencyArray()                                  = default;

        void   computeOffsets();
        void   addIONode(const IONode& node);
        void   addIOEdge(const IOEdge& edge);
        size_t nodeCount() const;
        size_t edgeCount() const;
        Node   getNode(const Uint64 index) const;
        Uint64   getEdge(const Uint64 index) const;
        Uint64 getOffset(const Uint64 index) const;
    };
}  // namespace OSM

#endif  // OSM_ADJACENCYARRAY_HPP
