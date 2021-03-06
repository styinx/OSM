#ifndef OSM_MAPDATA_HPP
#define OSM_MAPDATA_HPP

#include <mutex>
#include <string>
#include <types.hpp>

namespace OSM
{

    class MapData final
    {
    private:
        MapData() = default;

        static Map<Uint16, std::string> s_towns;
        static std::mutex s_map_mutex;

    public:
        MapData(const MapData& other)     = delete;
        MapData(MapData&& other) noexcept = delete;
        MapData& operator=(const MapData& other) = delete;
        MapData& operator=(MapData&& other) noexcept = delete;
        virtual ~MapData()                           = default;

        static Uint16 addTown(const std::string& town);
        static std::string getTown(const Uint16 id);
        static Uint16 getTownID(const std::string& town);
        static Map<Uint16, std::string> getTowns();
    };

}  // namespace OSM

#endif  // OSM_MAPDATA_HPP
