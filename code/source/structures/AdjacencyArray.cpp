#include "structures/AdjacencyArray.hpp"

#include <algorithm>

namespace OSM
{

    bool compareNodes(const Node& first, const Node& second)
    {
        return first.id < second.id;
    }

    bool compareEdges(const Edge& first, const Edge& second)
    {
        return first.source < second.source;
    }

    AdjacencyArray::AdjacencyArray() = default;

    void AdjacencyArray::addNode(const Node& node)
    {
        m_nodes.emplace_back(node);
    }

    void AdjacencyArray::addEdge(const Edge& edge)
    {
        m_edges.emplace_back(edge);
    }

    unsigned AdjacencyArray::nodeCount() const
    {
        return m_nodes.size();
    }

    unsigned AdjacencyArray::edgeCount() const
    {
        return m_edges.size();
    }

    void AdjacencyArray::computeOffsets()
    {
        std::sort(m_nodes.begin(), m_nodes.end(), compareNodes);
        std::sort(m_edges.begin(), m_edges.end(), compareEdges);

        auto node = m_nodes.begin();
        auto edge = m_edges.begin();
        Uint64 offset = 1;

        m_offset.resize(m_nodes.size() + 1);
        m_offset[0] = 0;

        while(edge != m_edges.end())
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
    }
}
