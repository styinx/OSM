#include "structures/Primitives.hpp"

namespace OSM
{

    Node::Node(const Sint64 id, const double lat, const double lon)
        : id(id)
        , lat(static_cast<float>(lat))
        , lon(static_cast<float>(lon))
    {
    }

}  // namespace OSM
