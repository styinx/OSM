#ifndef OSM_MAPTYPES_HPP
#define OSM_MAPTYPES_HPP

namespace OSM
{

    struct MapBounds
    {
        float sw_lat = 0;
        float sw_lon = 0;
        float ne_lat = 0;
        float ne_lon = 0;

        bool isInBounds(const float lat, const float lon) const
        {
            return lat > sw_lat && lat < ne_lat && lon > sw_lon && lon < ne_lon;
        }
    };

}  // namespace OSM

#endif  // OSM_MAPTYPES_HPP
