#include "structures/AdjacencyArray.hpp"

#include <algorithm>

namespace OSM
{

    bool compareNodesID(const Node& first, const Node& second)
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
        std::sort(m_nodes.begin(), m_nodes.end(), compareNodesID);

        // Outgoing Edges
        m_o_offset.resize(m_nodes.size() + 1);
        m_o_offset[0] = 0;

        Uint64 offset = 1;
        auto   node   = m_nodes.begin();
        auto   edge   = m_edges.begin();

        // Sort the edges by source nodes
        std::sort(m_edges.begin(), m_edges.end(), compareEdgesSource);
        while(edge != m_edges.end() && node != m_nodes.end())
        {
            while(edge->source < node->id)
            {
                edge++;
            }

            if(edge->source == node->id)
            {
                // Add edge to the outgoing edges
                m_o_offset[node->id + 1] += 1;

                // Update info
                node->mask |= NodeTypeMask::HAS_EDGES;
                edge->distance = distNodes(m_nodes[edge->source], m_nodes[edge->target]);
                edge++;
            }
            else
            {
                node++;
                offset++;
            }
        }

        // Sum up offsets
        for(Uint64 i = 1; i < m_o_offset.size(); ++i)
        {
            m_o_offset[i] += m_o_offset[i - 1];
        }
    }

    void AdjacencyArray::addNode(const Node& node)
    {
        std::lock_guard<std::mutex> guard(m_node_mutex);
        m_nodes.emplace_back(node);
    }

    void AdjacencyArray::addEdge(const Edge& edge)
    {
        std::lock_guard<std::mutex> guard(m_edge_mutex);
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

    Vector<Uint64> AdjacencyArray::getOOffsets() const
    {
        return m_o_offset;
    }

    Vector<Uint64> AdjacencyArray::neighbourIDs(const Uint64 node) const
    {
        Vector<Uint64> neighbours;
        for(Uint64 i = m_o_offset[node]; i < m_o_offset[node + 1]; ++i)
        {
            neighbours.emplace_back(m_edges[i].target);
        }
        return neighbours;
    }

    Vector<Node> AdjacencyArray::neighbours(const Uint64 node) const
    {
        Vector<Node> neighbours;
        for(Uint64 i = m_o_offset[node]; i < m_o_offset[node + 1]; ++i)
        {
            neighbours.emplace_back(m_nodes[m_edges[i].target]);
        }
        return neighbours;
    }
    Vector<Edge> AdjacencyArray::edges(const Uint64 node) const
    {
        Vector<Edge> edges;
        for(Uint64 i = m_o_offset[node]; i < m_o_offset[node + 1]; ++i)
        {
            edges.emplace_back(m_edges[i]);
        }
        return edges;
    }

}  // namespace OSM
