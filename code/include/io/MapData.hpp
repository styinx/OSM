#ifndef OSM_MAPDATA_HPP
#define OSM_MAPDATA_HPP

#include <prototypes.hpp>
#include <string>
namespace OSM
{

    class MapData final
    {
    private:
        MapData() = default;

        static Map<Uint16, std::string> s_towns;

    public:
        MapData(const MapData& other)     = delete;
        MapData(MapData&& other) noexcept = delete;
        MapData& operator=(const MapData& other) = delete;
        MapData& operator=(MapData&& other) noexcept = delete;
        virtual ~MapData()                           = default;

        static Uint16 addTown(const std::string& town);
        static std::string getTown(const Uint16 id);
    };

}  // namespace OSM

#endif  // OSM_MAPDATA_HPP
