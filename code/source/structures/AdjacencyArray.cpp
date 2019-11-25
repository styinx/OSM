#include "structures/AdjacencyArray.hpp"

#include <algorithm>

namespace OSM
{

    bool compareNodes(const Node& first, const Node& second)
    {
        return first.id < second.id;
    }

    bool compareEdgesSource(const Edge& first, const Edge& second)
    {
        return first.source < second.source;
    }

    bool compareEdgesTarget(const Edge& first, const Edge& second)
    {
        return first.target < second.target;
    }

    AdjacencyArray::AdjacencyArray() = default;

    void AdjacencyArray::computeOffsets()
    {
        std::sort(m_nodes.begin(), m_nodes.end(), compareNodes);
        std::sort(m_edges.begin(), m_edges.end(), compareEdgesSource);

        // Outgoing Edges
        m_o_offset.resize(m_nodes.size() + 1);
        m_o_offset[0] = 0;

        // Incoming edges
        m_i_offset.resize(m_nodes.size() + 1);
        m_i_offset[0] = 0;

        Uint64 offset = 1;
        auto   node   = m_nodes.begin();
        auto   edge   = m_edges.begin();

        // Create outgoing offsets
        while(edge != m_edges.end() && node != m_nodes.end())
        {
            if(edge->source == node->id)
            {
                m_o_offset[offset] += 1;
                m_o_edges.emplace_back(offset - 1);

                // Collect nodes we need to create incoming edges
                m_i_edges.emplace_back(std::distance(m_edges.begin(), edge));

                edge++;
            }
            else
            {
                node++;
                m_o_offset[offset + 1] += m_o_offset[offset];
                offset++;
            }
        }

        // Creates offsets for nodes that do not have outgoing edges.
        while(offset < m_o_offset.size())
        {
            m_o_offset[offset + 1] += m_o_offset[offset];
            offset++;
        }

        std::sort(m_edges.begin(), m_edges.end(), compareEdgesTarget);

        offset = 1;
        node   = m_nodes.begin();
        Uint64 edge_index = 0;

        // Create incoming offsets
        for(auto& edge : m_i_edges)
        {
            if(m_edges[edge].target == node->id)
            {
                m_i_offset[offset] += 1;
                m_i_edges[edge_index++] = offset - 1;
            }
            else
            {
                node++;
                m_i_offset[offset + 1] += m_i_offset[offset];
                offset++;
            }
        }

        // Creates offsets for nodes that do not have ingoing edges.
        while(offset < m_i_offset.size())
        {
            m_i_offset[offset + 1] += m_i_offset[offset];
            offset++;
        }

        m_edges.clear();
    }

    void AdjacencyArray::addNode(const Node& node)
    {
        m_nodes.emplace_back(node);
    }

    void AdjacencyArray::addIOEdge(const Edge& edge)
    {
        m_edges.emplace_back(edge);
    }

    size_t AdjacencyArray::nodeCount() const
    {
        return m_nodes.size();
    }

    size_t AdjacencyArray::edgeCount() const
    {
        return m_edges.size();
    }

    size_t AdjacencyArray::iEdgeCount() const
    {
        return m_i_edges.size();
    }

    size_t AdjacencyArray::oEdgeCount() const
    {
        return m_o_edges.size();
    }

    Vector<Node> AdjacencyArray::getNodes() const
    {
        return m_nodes;
    }

    Vector<Edge> AdjacencyArray::getEdges() const
    {
        return m_edges;
    }

    Vector<Uint64> AdjacencyArray::getIEdges() const
    {
        return m_i_edges;
    }

    Vector<Uint64> AdjacencyArray::getOEdges() const
    {
        return m_o_edges;
    }

    Vector<Uint64> AdjacencyArray::getIOffsets() const
    {
        return m_i_offset;
    }

    Vector<Uint64> AdjacencyArray::getOOffsets() const
    {
        return m_o_offset;
    }
}  // namespace OSM
