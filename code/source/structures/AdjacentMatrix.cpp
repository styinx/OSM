#include "structures/AdjacentMatrix.hpp"

#include <algorithm>
#include <iostream>

namespace OSM
{
    AdjacentMatrix& AdjacentMatrix::addNode(const ID node)
    {
        m_nodes.emplace_back(node);
        return *this;
    }

    AdjacentMatrix& AdjacentMatrix::addEdge(const ID source, const ID target)
    {

        return *this;
    }

    unsigned AdjacentMatrix::nodeCount() const
    {
        return m_nodes.size();
    }

    unsigned AdjacentMatrix::edgeCount() const
    {
        return m_edges.size();
    }
}
