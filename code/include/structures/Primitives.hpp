#ifndef OSM_PRIMITIVES_HPP
#define OSM_PRIMITIVES_HPP

#include "prototypes.hpp"

#include <cmath>

namespace OSM
{

    enum class NodeTypeMask : Byte
    {
        _1               = 0x00,
        HIGHWAY          = 0x01,  // is a highway node
        BICYCLE          = 0x02,
        PUBLIC_TRANSPORT = 0x04,  // is a public transport node
        ONE_WAY          = 0x08,  // is a one way highway
        _2               = 0x0F,
        TEXT             = 0x10,  // has a description
        MEDIA            = 0x20,  // has media content
        WEB              = 0x40,  // has web content
        CONTACT          = 0x80,  // has contact content
        _3               = 0xF0
    };

    inline Byte operator|=(Byte value, const NodeTypeMask mask)
    {
        return value |= static_cast<Byte>(mask);
    }

    struct Node
    {
        Uint64 id;
        float  lat;
        float  lon;
        Byte   mask;
        Byte   max_speed;
        Uint16 town;

        Node() = default;

        explicit Node(
            const Sint64 id,
            const double lat,
            const double lon,
            const Byte   mask,
            const Byte   speed,
            const Uint16 town)
            : id(static_cast<Uint64>(id))
            , lat(static_cast<float>(lat))
            , lon(static_cast<float>(lon))
            , mask(mask)
            , max_speed(speed)
            , town(town)
        {
        }

        explicit Node(
            const Uint64 id,
            const double lat,
            const double lon,
            const Byte   mask,
            const Byte   speed,
            const Uint16 town)
            : id(id)
              , lat(static_cast<float>(lat))
              , lon(static_cast<float>(lon))
              , mask(mask)
              , max_speed(speed)
              , town(town)
        {
        }
    };

    inline float deg2rad(const float deg)
    {
        return deg * M_PI / 180;
    }

    inline float dist(const float lat1, const float lon1, const float lat2, const float lon2)
    {
        const auto e_rad    = 6371000;
        const auto lat1_rad = deg2rad(lat1);
        const auto lon1_rad = deg2rad(lon1);
        const auto lat2_rad = deg2rad(lat2);
        const auto lon2_rad = deg2rad(lon2);

        const auto u = sin((lat1_rad - lat2_rad) / 2);
        const auto v = sin((lon1_rad - lon2_rad) / 2);

        return static_cast<float>(2.0F * e_rad * asin(sqrt(pow(u, 2) + cos(lat1_rad) * cos(lat2_rad) * pow(v, 2))));
    }

    inline float distNodes(const Node& n1, const Node& n2)
    {
        return dist(n1.lat, n1.lon, n2.lat, n2.lon);
    }

    struct Edge
    {
        Uint64 source;
        Uint64 target;

        explicit Edge(const Uint64 source, const Uint64 target)
            : source(source)
            , target(target)
        {
        }

        explicit Edge(const Sint64 source, const Sint64 target)
            : source(static_cast<Uint64>(source))
            , target(static_cast<Uint64>(target))
        {
        }
    };

    enum class DummyType : Byte
    {
        wikipedia          = 0x07,
        website            = 0x08,  // web // url // contact:website
        waterway           = 0x09,
        waterway_kilometer = 0x0A,
        video              = 0x0B,
        vending            = 0x0C,
        vehicle            = 0x0D,
        traffic_sign       = 0x0E,
        tourism            = 0x0F,
        surface            = 0x10,
        sport              = 0x10,
        social_facility    = 0x11,
        railway            = 0x12,
        railway_speed      = 0x13,
        phone              = 0x14,  // contact:phone
        parking            = 0x15,
        network            = 0x16,
        name               = 0x17,
        line               = 0x18,  // lines
        image              = 0x19,
        email              = 0x1A,  // contact:email
        evel               = 0x1B,
        description        = 0x1C,
        building           = 0x1D,
        bycicle            = 0x1E,  // cycleway
        amenity            = 0x1F,
        address            = 0x20,  // address city
        access             = 0x21,
        wheelchair         = 0x22,
        tunnel             = 0x23,
        truck              = 0x23,
        tram               = 0x23,
        traffic_signal     = 0x23,
        tracks             = 0x23,
        toilets            = 0x23,
        title              = 0x23,
        route              = 0x23,
        motorcycle         = 0x23,
        maxspeed           = 0x23,
        highway            = 0x23,
    };

}  // namespace OSM

#endif  // OSM_PRIMITIVES_HPP
