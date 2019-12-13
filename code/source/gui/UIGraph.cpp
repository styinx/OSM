#include "gui/UIGraph.hpp"

namespace OSM
{

    UIGraph::UIGraph(const AdjacencyArray* array)
        : m_array(array)
    {
        buildNetwork(EdgeTypeMask::MOTORWAY);
    }

    void UIGraph::buildNetwork(const EdgeTypeMask street_type)
    {
        const auto nodes = m_array->getNodes();

        for(const auto& edge : m_array->getEdges())
        {
            if(edge.mask & street_type)
            {
                m_motorway.insert(QString::number(edge.source), QString::number(edge.target));
            }
        }
    }

} // namespace OSM
