#include "structures/AdjacencyArray.hpp"

#include <algorithm>
#include <iostream>

namespace OSM
{
    Node::Node(const OSM::Sint64 id, const float lat, const float lon)
        : id(id)
        , lat(lat)
        , lon(lon)
    {

    }

    bool operator<(const Edge& first, const Edge& second)
    {
        return std::tie(first.source, first.target) < std::tie(second.source, second.target);
    }

    AdjacencyArray::AdjacencyArray() = default;

    void AdjacencyArray::addNode(const Node& node)
    {
        m_nodes.emplace_back(node);
    }

    void AdjacencyArray::addEdge(const Sint64 from, const Sint64 to)
    {
        m_temp_edges.emplace(Edge{from, to});
        m_temp_edges.emplace(Edge{to, from});

        m_edges_count += 1;
    }

    unsigned AdjacencyArray::nodeCount() const
    {
        return m_nodes.size();
    }

    unsigned AdjacencyArray::edgeCount() const
    {
        return m_edges_count;
    }

    void AdjacencyArray::computeEdges()
    {
        Sint64 offset = 0;
        m_offset.emplace_back(offset);

        Uint64 node_index = 0;
        Sint64 node_val = m_nodes[0].id;

        auto it = m_temp_edges.begin();
        while(it != m_temp_edges.end())
        {
            m_edges.emplace_back(it->target);
            if(it->source == node_val)
            {
                ++offset;
            }
            else
            {
                node_val = m_nodes[++node_index].id;
                m_offset.emplace_back(offset++);
            }
            it = m_temp_edges.erase(it);
        }
    }
}
