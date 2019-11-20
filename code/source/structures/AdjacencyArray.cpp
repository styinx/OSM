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
        while(edge != m_io_edges.end() && node != m_nodes.end())
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

        // Fill offsets if edges at the end do not have edges
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

    Vector<Node> AdjacencyArray::getNodes() const
    {
        return m_nodes;
    }
    Vector<Uint64> AdjacencyArray::getEdges() const
    {
        return m_edges;
    }
    Vector<Uint64> AdjacencyArray::getOffsets() const
    {
        return m_offset;
    }
}
