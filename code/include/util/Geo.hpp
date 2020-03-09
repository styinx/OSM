#ifndef OSM_GEO_HPP
#define OSM_GEO_HPP

#include "NonCopyable.hpp"
#include "NonMoveable.hpp"
#include "types.hpp"

#include <QtCore/QString>
namespace OSM
{

    class Geo final
        : public NonCopyable
        , public NonMoveable
    {
    private:
        Geo() = default;

    public:
        virtual ~Geo() = default;

        static Pair<float, float> stringToLatLon(const QString& str);
        static Pair<float, float> midpoint(const float lat1, const float lon1, const float lat2, const float lon2);
        static float dist(const float lat1, const float lon1, const float lat2, const float lon2);
        static float deg2rad(const float deg);
    };

}  // namespace OSM

#endif  // OSM_GEO_HPP
