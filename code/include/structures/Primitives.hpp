#ifndef OSM_PRIMITIVES_HPP
#define OSM_PRIMITIVES_HPP

#include "types.hpp"
#include "util/Geo.hpp"

#include <cmath>

namespace OSM
{

    const static auto U64_INF = std::numeric_limits<Uint64>::max();
    const static auto F32_INF = std::numeric_limits<float>::max();

    enum class TransportType : Byte
    {
        FOOT             = 0x01,
        BICYCLE          = 0x02,
        CAR              = 0x04,
        PUBLIC_TRANSPORT = 0x08,
        ANY              = 0x0F
    };

    enum class NodeTypeMask : Byte
    {
        HAS_EDGES           = 0x01,
        TOWN                = 0x02,
        TOURISM             = 0x04,
        TOURISM_ATTRACTION  = 0x08,
        TOURISM_INFORMATION = 0x0F,
        TOURISM_CULTURE     = 0x10,
        TOURISM_SLEEPING    = 0x20,
        TOURISM_UNKNOWN     = 0x40
    };

    enum class EdgeTypeMask : Byte
    {
        // Access type
        FOOT             = 0x01,
        BICYCLE          = 0x02,
        CAR              = 0x04,
        PUBLIC_TRANSPORT = 0x08,

        // Street usage
        LIVING_STREET     = 0x17,
        SERVICE_STREET    = 0x24,
        PEDESTRIAN_STREET = 0x37,
        TRACK_STREET      = 0x43,
        BUS_STREET        = 0x5C,
        ESCAPE_STREET     = 0x64,
        RACEWAY_STREET    = 0x70,

        // Street types
        MOTORWAY     = 0x84,
        TRUNK        = 0x94,
        PRIMARY      = 0xA4,
        SECONDARY    = 0xB6,
        TERTIARY     = 0xC7,
        UNCLASSIFIED = 0xD7,
        RESIDENTIAL  = 0xE7,
    };

    static Map<std::string, Pair<Byte, Byte>> StreetType = {
        {"living_street", {0x17, 30}},  {"service", {0x27, 30}},
        {"driveway", {0x17, 15}},       {"road", {0x27, 30}},
        {"pedestrian", {0x37, 5}},      {"track", {0x47, 20}},
        {"footway", {0x43, 5}},         {"corridor", {0x43, 5}},
        {"sidewalk", {0x43, 5}},        {"path", {0x43, 5}},
        {"steps", {0x43, 5}},           {"cycleway", {0x43, 15}},
        {"bridleway", {0x43, 15}},      {"construction", {0x43, 5}},
        {"proposed", {0x43, 5}},        {"bus_guideway", {0x57, 50}},
        {"escape", {0x67, 10}},         {"raceway", {0x70, 255}},

        {"motorway_link", {0xF4, 110}}, {"trunk_link", {0xF4, 110}},
        {"primary_link", {0xF6, 90}},   {"secondary_link", {0xF7, 90}},
        {"tertiary_link", {0xF7, 60}},

        {"motorway", {0x84, 120}},      {"trunk", {0x94, 120}},
        {"primary", {0xA6, 100}},       {"secondary", {0xB7, 100}},
        {"tertiary", {0xC7, 70}},       {"unclassified", {0xD7, 70}},
        {"residential", {0xE7, 30}},    {"", {0x17, 30}},
    };

    static Map<std::string, Byte> AttractionType = {
        {"attraction", 0x0C},
        {"picnic_site", 0x0C},
        {"theme_site", 0x0C},
        {"theme_park", 0x0C},
        {"viewpoint", 0x0C},
        {"zoo", 0x0C},

        {"information", 0x13},

        {"aquarium", 0x14},
        {"artwork", 0x14},
        {"gallery", 0x14},
        {"museum", 0x14},

        {"alpine_hut", 0x24},
        {"appartment", 0x24},
        {"camp_pitch", 0x24},
        {"camp_site", 0x24},
        {"caravan_site", 0x24},
        {"chalet", 0x24},
        {"guest_house", 0x24},
        {"hotel", 0x24},
        {"hostel", 0x24},
        {"motel", 0x24},
        {"wilderness_hut", 0x24},

        {"yes", 0x44},
        {"", 0x44},
    };

    template<typename E>
    inline bool operator&(const Byte value, const E mask)
    {
        return value & static_cast<typename std::underlying_type<E>::type>(mask);
    }

    template<typename E>
    inline bool operator&(const E mask, const Byte value)
    {
        return value & static_cast<typename std::underlying_type<E>::type>(mask);
    }

    template<typename E>
    inline bool operator&(const E mask1, const E mask2)
    {
        return static_cast<typename std::underlying_type<E>::type>(mask1) &
               static_cast<typename std::underlying_type<E>::type>(mask2);
    }

    template<typename E>
    inline bool operator|(const Byte value, const E mask)
    {
        return value | static_cast<typename std::underlying_type<E>::type>(mask);
    }

    template<typename E>
    inline bool operator|(const E mask1, const E mask2)
    {
        return static_cast<typename std::underlying_type<E>::type>(mask1) |
               static_cast<typename std::underlying_type<E>::type>(mask2);
    }

    template<typename E>
    inline Byte operator|=(Byte& value, const E mask)
    {
        return value |= static_cast<typename std::underlying_type<E>::type>(mask);
    }

    template<typename E>
    inline Byte operator&=(Byte& value, const E mask)
    {
        return value &= static_cast<typename std::underlying_type<E>::type>(mask);
    }

    struct Node
    {
        Uint64 id   = 0;
        float  lat  = 0;
        float  lon  = 0;
        Uint16 town = 0;
        Byte   mask = 0;
        // 40 bits padding

        explicit Node(const Uint64 id, const double lat, const double lon, const Byte mask, const Uint16 town)
            : id(id)
            , lat(static_cast<float>(lat))
            , lon(static_cast<float>(lon))
            , town(town)
            , mask(mask)
        {
        }

        bool operator<(const Node& other) const
        {
            return id < other.id;
        }

        bool operator==(const Node& other) const
        {
            return id == other.id;
        }

        Byte tourism() const
        {
            if(mask & NodeTypeMask::TOURISM)
            {
                if(mask & NodeTypeMask::TOURISM_ATTRACTION)
                {
                    return 1;
                }
                else if(mask & NodeTypeMask::TOURISM_INFORMATION)
                {
                    return 2;
                }
                else if(mask & NodeTypeMask::TOURISM_CULTURE)
                {
                    return 3;
                }
                else if(mask & NodeTypeMask::TOURISM_SLEEPING)
                {
                    return 4;
                }
                else if(mask & NodeTypeMask::TOURISM_UNKNOWN)
                {
                    return 0;
                }
                return 0;
            }
            return 255;
        }
    };

    struct Edge
    {
        Uint64 source   = 0;
        Uint64 target   = 0;
        float  distance = 0;
        Byte   speed    = 0;
        Byte   mask     = 0;
        Byte   tourism  = 0;
        bool   oneway   = false;
        // 0 bits padding

        explicit Edge(
            const Uint64 source,
            const Uint64 target,
            const Byte   speed   = 0,
            const Byte   mask    = 0,
            const Byte   tourism = 0,
            const bool   oneway  = false)
            : source(source)
            , target(target)
            , speed(speed)
            , mask(mask)
            , tourism(tourism)
            , oneway(oneway)
        {
        }

        Edge mirror()
        {
            Edge e   = *this;
            e.source = this->target;
            e.target = this->source;
            return e;
        }

        float duration(const Uint8 alt_speed = 0) const
        {
            if(alt_speed > 0)
            {
                return distance / 1000 / static_cast<float>(alt_speed);
            }
            return distance / 1000 / static_cast<float>(speed);
        }

        /*
         * Distance: m
         * Speed: km/h
         * Weight: s
         */
        float weight() const
        {
            return distance / (static_cast<float>(speed * speed));
        }
    };

    struct PathResult
    {
        Uint64         start    = 0;
        Uint64         stop     = 0;
        float          distance = 0;
        float          duration = 0;
        Vector<Uint64> route;
        Uint64         calculation = 0;
        bool           way_found   = false;
    };

    inline float distNodes(const Node& n1, const Node& n2, const String& unit = "m")
    {
        if(unit == "m")
            return Geo::dist(n1.lat, n1.lon, n2.lat, n2.lon);
        else
            return Geo::dist(n1.lat, n1.lon, n2.lat, n2.lon) / 1000;
    }

    inline Node midpointNode(const Node& n1, const Node& n2)
    {
        const auto result = Geo::midpoint(n1.lat, n1.lon, n2.lat, n2.lon);
        return Node{0, result.first, result.second, 0, 0};
    }

    template<typename C>
    inline Node closestNode(const Node& n, const C& container)
    {
        auto  index = *container.end();
        float min   = F32_INF;

        for(const auto& el : container)
        {
            const auto l_min = distNodes(n, el);
            if(l_min < min)
            {
                index = el;
                min   = l_min;
            }
        }
        return index;
    }

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
            return {min_lat + (max_lat - min_lat) / 2, min_lon + (max_lon - min_lon) / 2};
        }
    };

}  // namespace OSM

#endif  // OSM_PRIMITIVES_HPP
