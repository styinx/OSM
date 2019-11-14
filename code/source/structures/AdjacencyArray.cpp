#include "structures/AdjacencyArray.hpp"

#include <algorithm>

namespace OSM
{

    bool compareNodes(const IONode& first, const IONode& second)
    {
        return first.id < second.id;
    }

    bool compareEdges(const IOEdge& first, const IOEdge& second)
    {
        return first.source < second.source;
    }

    AdjacencyArray::AdjacencyArray() = default;

    void AdjacencyArray::computeOffsets()
    {
        std::sort(m_io_nodes.begin(), m_io_nodes.end(), compareNodes);
        std::sort(m_io_edges.begin(), m_io_edges.end(), compareEdges);

        auto node = m_io_nodes.begin();
        auto edge = m_io_edges.begin();
        Uint64 offset = 1;

        m_offset.resize(m_io_nodes.size() + 1);
        m_offset[0] = 0;

        // Compute offsets of the edges
        while(edge != m_io_edges.end())
        {
            if(node->id == edge->source)
            {
                m_offset[offset] += 1;
                edge++;
            }
            else
            {
                node++;
                m_offset[offset + 1] += m_offset[offset];
                offset++;
            }
        }

        // Replace IONode with Node
        node = m_io_nodes.begin();
        while(node != m_io_nodes.end())
        {
            m_nodes.emplace_back(Node{(*node).lat, (*node).lon});
            node++;
        }
        m_io_nodes.clear();

        // Replace IOEdge with Uint64
        edge = m_io_edges.begin();
        while(edge != m_io_edges.end())
        {
            m_edges.emplace_back((*edge).target);
            edge++;
        }
        m_io_edges.clear();
    }

    void AdjacencyArray::addIONode(const IONode& node)
    {
        m_io_nodes.emplace_back(node);
    }

    void AdjacencyArray::addIOEdge(const IOEdge& edge)
    {
        m_io_edges.emplace_back(edge);
    }

    size_t AdjacencyArray::nodeCount() const
    {
        return m_nodes.size();
    }

    size_t AdjacencyArray::edgeCount() const
    {
        return m_edges.size();
    }

    Node AdjacencyArray::getNode(const Uint64 index) const
    {
        return offsetCheck(m_nodes, index);
    }

    Uint64 AdjacencyArray::getEdge(const Uint64 index) const
    {
        return offsetCheck(m_edges, index);
    }

    Uint64 AdjacencyArray::getOffset(const Uint64 index) const
    {
        return offsetCheck(m_offset, index);
    }
}
