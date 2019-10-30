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
    bool operator<(const Node& first, const Node& second)
    {
        return first.id < second.id;
    }

    bool operator<(const Edge& first, const Edge& second)
    {
        return std::tie(first.source, first.target) < std::tie(second.source, second.target);
    }

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

    void AdjacencyArray::addEdge(const Sint64 from, const Sint64 to)
    {
        m_temp_edges.emplace_back(Edge{from, to});

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
        std::cout << "sort nodes ";
        std::sort(m_nodes.begin(), m_nodes.end(), compareNodes);
        std::cout << "end\n";

        std::cout << "sort edges ";
        std::sort(m_temp_edges.begin(), m_temp_edges.end(), compareEdges);
        std::cout << "end\n";

        m_offset.resize(m_edges.size() + 1);
        m_offset[0] = 0;
        Uint64 offset = 1;

        auto node = m_nodes.begin();
        auto it = m_temp_edges.begin();
        while(it != m_temp_edges.end() && node != m_nodes.end())
        {
            if(it->source == node->id)
            {
                m_edges.emplace_back(it->target);
                m_offset[offset]++;
                it++;
            }
            else if(it->source < node->id)
            {
                it++;
            }
            else
            {
                node++;
            }
        }

        node = m_nodes.begin();
        it = m_temp_edges.begin();
        while(it != m_temp_edges.end() && node != m_nodes.end())
        {
            if(it->target == node->id)
            {
                m_edges.emplace_back(it->source);
                m_offset[offset]++;
                it++;
            }
            else if(it->target < node->id)
            {
                it++;
            }
            else
            {
                node++;
            }
        }

        m_temp_edges.clear();
    }
}
