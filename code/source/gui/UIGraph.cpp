#include "gui/UIGraph.hpp"

#include <QtDebug>

namespace OSM
{

    UIGraph::UIGraph(const AdjacencyArray* array)
        : m_array(array)
    {
    }

    QJsonArray UIGraph::buildNetwork(const std::string street_type)
    {
        QJsonArray  array{};
        const auto  nodes = m_array->getNodes();

        for(const auto& edge : m_array->getEdges())
        {
            if(edge.mask == StreetType[street_type].first)
            {
                array.push_back(QJsonArray({QJsonValue(nodes[edge.source].lat),
                                            QJsonValue(nodes[edge.source].lon),
                                            QJsonValue(nodes[edge.target].lat),
                                            QJsonValue(nodes[edge.target].lon)}));
            }

        }
        return array;
    }

}  // namespace OSM
