#include "structures/AdjacencyArray.hpp"

#include <algorithm>
#include <iostream>

namespace OSM
{
    Node::Node(const OSM::ID id, const double lat, double lon)
//        : id(id)
//        , lat(lat)
//        , lon(lon)
    {

    }

    AdjacencyArray::AdjacencyArray() = default;

    AdjacencyArray& AdjacencyArray::addNode(const Node& node)
    {
        m_nodes.emplace_back(node);
        return *this;
    }

    AdjacencyArray& AdjacencyArray::addEdge(const Edge& target)
    {
        m_edges.emplace_back(target);
        return *this;
    }

    unsigned AdjacencyArray::nodeCount() const
    {
        return m_nodes.size();
    }

    unsigned AdjacencyArray::edgeCount() const
    {
        return m_edges.size();
    }

    Vector<Byte> AdjacencyArray::serialize()
    {
        return OSM::Vector<Byte>();
    }
}
