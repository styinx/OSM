#ifndef OSM_MAPTYPES_HPP
#define OSM_MAPTYPES_HPP

#include "prototypes.hpp"

namespace OSM
{

    struct MapBounds
    {
        float min_lat = 0;
        float max_lat = 0;
        float min_lon = 0;
        float max_lon = 0;

        bool isInBounds(const float lat, const float lon) const
        {
            return lat <= max_lat && lat >= min_lat && lon >= min_lon && lon <= max_lon;
        }

        Pair<float, float> center() const
        {
            return {
                min_lat + (max_lat - min_lat) / 2,
                min_lon + (max_lon - min_lon) / 2
            };
        }
    };

}  // namespace OSM

#endif  // OSM_MAPTYPES_HPP
