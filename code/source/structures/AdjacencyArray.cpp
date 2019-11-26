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

    bool compareEdgesSourceTarget(const Edge& first, const Edge& second)
    {
        return first.source < second.source || first.target < second.target;
    }

    AdjacencyArray::AdjacencyArray() = default;

    void AdjacencyArray::computeOffsets()
    {
        std::sort(m_nodes.begin(), m_nodes.end(), compareNodes);

        // Outgoing Edges
        m_o_offset.resize(m_nodes.size() + 1);
        m_o_offset[0] = 0;

        // Incoming edges
        m_i_offset.resize(m_nodes.size() + 1);
        m_i_offset[0] = 0;

        Uint64       offset = 0;
        auto         node   = m_nodes.begin();
        auto         edge   = m_edges.begin();
        const auto max_node = m_nodes.size() -1;
        Vector<Edge> filtered_edges;

        // Sort edges by target id and use index instead of id for nodes
        std::sort(m_edges.begin(), m_edges.end(), compareEdgesTarget);
        while(edge != m_edges.end() && node != m_nodes.end())
        {
            while(edge->target < node->id)
            {
                edge++;
            }

            if(edge->target == node->id)
            {
                edge->target = offset;
                edge++;
            }
            else
            {
                node++;
                offset++;
            }
        }

        offset = 1;
        node   = m_nodes.begin();
        edge   = m_edges.begin();

        // Sort the edges by source nodes
        std::sort(m_edges.begin(), m_edges.end(), compareEdgesSource);
        while(edge != m_edges.end() && node != m_nodes.end())
        {
            while(edge->source < node->id)
            {
                edge++;
            }

            if(edge->target > max_node)
            {
                edge++;
                continue;
            }

            if(edge->source == node->id)
            {
                // Assign the index of the node to the edge source
                edge->source = offset - 1;

                // Add edge to the outgoing edges
                m_o_offset[edge->source + 1] += 1;
                // Add ingoing edge to the other node
                m_i_offset[edge->target + 1] += 1;

                filtered_edges.emplace_back(*edge);
                edge++;
            }
            else
            {
                node++;
                offset++;
            }
        }


        m_edges.clear();
        m_edges = filtered_edges;
        filtered_edges.clear();

        // Sum up offsets
        for(Uint64 i = 1; i < m_o_offset.size(); ++i)
        {
            m_o_offset[i] += m_o_offset[i - 1];
            m_i_offset[i] += m_i_offset[i - 1];
        }
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

    Vector<Node> AdjacencyArray::getNodes() const
    {
        return m_nodes;
    }

    Vector<Edge> AdjacencyArray::getEdges() const
    {
        return m_edges;
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
