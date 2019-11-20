#include "io/MapData.hpp"

namespace OSM
{

    Map<Uint16, std::string> MapData::s_towns = {};

    Uint16 MapData::addTown(const std::string& town)
    {
        if(s_towns.size() == 0xffff)
            return 0;

//        auto pos = std::find(s_towns.begin(), s_towns.end(), town);
//        if(pos != s_towns.end())
//            return std::distance(s_towns.begin(), pos);

        const Uint16 id = s_towns.size();
        s_towns[id] = town;
        return id;
    }

    std::string MapData::getTown(const Uint16 id)
    {
        return s_towns[id];
    }

} // namespace OSM
