#ifndef OSM_PRIMITIVES_HPP
#define OSM_PRIMITIVES_HPP

#include "prototypes.hpp"
#include "util/Geo.hpp"

#include <cmath>

namespace OSM
{

    static Map<std::string, Pair<Byte, Byte>> StreetType = {
        {"living_street", {0x16, 30}},  {"service", {0x20, 10}},
        {"pedestrian", {0x33, 5}},      {"track", {0x40, 255}},
        {"bus_guideway", {0x58, 50}},   {"escape", {0x64, 10}},
        {"raceway", {0x70, 255}},

        {"motorway_link", {0xF4, 120}}, {"trunk_link", {0xF4, 120}},
        {"primary_link", {0xF4, 100}},  {"secondary_link", {0xF4, 100}},
        {"tertiary_link", {0xF4, 70}},

        {"motorway", {0x84, 120}},      {"trunk", {0x94, 120}},
        {"primary", {0xA4, 100}},       {"secondary", {0xB4, 100}},
        {"tertiary", {0xC6, 70}},       {"unclassified", {0xD7, 70}},
        {"residential", {0xE7, 50}},
    };

    enum class NodeTypeMask : Byte
    {
        HAS_EDGES = 0x01,
    };

    enum class EdgeTypeMask : Byte
    {
        // Access type
        FOOT             = 0x01,
        BICYCLE          = 0x02,
        CAR              = 0x04,
        PUBLIC_TRANSPORT = 0x08,

        // Street usage
        LIVING_STREET     = 0x16,
        SERVICE_STREET    = 0x20,
        PEDESTRIAN_STREET = 0x33,
        TRACK_STREET      = 0x40,
        BUS_STREET        = 0x58,
        ESCAPE_STREET     = 0x64,
        RACEWAY_STREET    = 0x70,

        // Street types
        MOTORWAY     = 0x84,
        TRUNK        = 0x94,
        PRIMARY      = 0xA4,
        SECONDARY    = 0xB4,
        TERTIARY     = 0xC6,
        UNCLASSIFIED = 0xD7,
        RESIDENTIAL  = 0xE7,
    };

    struct Node
    {
        Uint64 id    = 0;
        float  lat   = 0;
        float  lon   = 0;
        Uint16 town  = 0;
        Byte   mask  = 0;
        Byte   speed = 0;

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
            , town(town)
            , mask(mask)
            , speed(speed)
        {
        }
    };

    struct Edge
    {
        Uint64 source   = 0;
        Uint64 target   = 0;
        float  distance = 0;
        Byte   speed    = 0;
        Byte   mask     = 0;
        bool   oneway   = false;

        explicit Edge(
            const Uint64 source,
            const Uint64 target,
            const Byte   speed  = 0,
            const Byte   mask   = 0,
            const bool   oneway = false)
            : source(source)
            , target(target)
            , speed(speed)
            , mask(mask)
            , oneway(oneway)
        {
        }

        Edge& swap()
        {
            std::swap(source, target);
            return *this;
        }

        float weight() const
        {
            return distance / (float)speed;
        }
    };

    inline Byte operator|=(Byte value, const NodeTypeMask mask)
    {
        return value |= static_cast<Byte>(mask);
    }

    inline Byte operator&=(Byte value, const NodeTypeMask mask)
    {
        return value &= static_cast<Byte>(mask);
    }

    inline bool operator&(Byte value, const EdgeTypeMask mask)
    {
        return value & static_cast<Byte>(mask);
    }

    inline Byte operator|=(Byte value, const EdgeTypeMask mask)
    {
        return value |= static_cast<Byte>(mask);
    }

    inline Byte operator&=(Byte value, const EdgeTypeMask mask)
    {
        return value &= static_cast<Byte>(mask);
    }

    inline float distNodes(const Node& n1, const Node& n2)
    {
        return Geo::dist(n1.lat, n1.lon, n2.lat, n2.lon);
    }

}  // namespace OSM

#endif  // OSM_PRIMITIVES_HPP
