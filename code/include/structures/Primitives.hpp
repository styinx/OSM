#ifndef OSM_PRIMITIVES_HPP
#define OSM_PRIMITIVES_HPP

#include "prototypes.hpp"

namespace OSM
{
    
    enum class NodeType : Byte
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

    struct Node
    {
        Sint64   id;
        float    lat;
        float    lon;
        NodeType type1;
        NodeType type2;
        NodeType type3;
        NodeType type4;

        explicit Node(const Sint64 id, const double lat, const double lon);
    };

    struct Edge
    {
        Sint64 source;
        Sint64 target;
    };

}  // namespace OSM

#endif  // OSM_PRIMITIVES_HPP
