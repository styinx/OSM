#include "structures/AdjacencyArray.hpp"

#include <algorithm>

namespace OSM
{

    bool compareNodes(const Node& first, const Node& second)
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
        std::sort(m_nodes.begin(), m_nodes.end(), compareNodes);
        std::sort(m_io_edges.begin(), m_io_edges.end(), compareEdges);

        auto node = m_nodes.begin();
        auto edge = m_io_edges.begin();
        Uint64 offset = 1;

        m_offset.resize(m_nodes.size() + 1);
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

        while(offset < m_offset.size())
        {
            m_offset[offset + 1] += m_offset[offset];
            offset++;
        }

        // Replace IOEdge with Uint64
        edge = m_io_edges.begin();
        while(edge != m_io_edges.end())
        {
            m_edges.emplace_back((*edge).target);
            edge++;
        }
        m_io_edges.clear();
    }

    void AdjacencyArray::addNode(const Node& node)
    {
        m_nodes.emplace_back(node);
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
