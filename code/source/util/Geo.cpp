#include "util/Geo.hpp"

#include <QtCore/QStringList>
#include <cmath>

namespace OSM
{

    Pair<float, float> Geo::stringToLatLon(const QString& str)
    {
        QStringList latlon = str.split(",");

        if(latlon.size() == 2)
        {
            return Pair<float, float>{latlon[0].toDouble(nullptr), latlon[1].toDouble(nullptr)};
        }
        return {0, 0};
    }

    float Geo::deg2rad(const float deg)
    {
        return deg * M_PI / 180;
    }

    float Geo::dist(const float lat1, const float lon1, const float lat2, const float lon2)
    {
        const auto e_rad    = 6371000;
        const auto lat1_rad = deg2rad(lat1);
        const auto lon1_rad = deg2rad(lon1);
        const auto lat2_rad = deg2rad(lat2);
        const auto lon2_rad = deg2rad(lon2);

        const auto u = sin((lat1_rad - lat2_rad) / 2);
        const auto v = sin((lon1_rad - lon2_rad) / 2);

        return static_cast<float>(
            2.0F * e_rad * asin(sqrt(pow(u, 2) + cos(lat1_rad) * cos(lat2_rad) * pow(v, 2))));
    }

} // namespace OSM
