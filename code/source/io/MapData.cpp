#include "io/MapData.hpp"

namespace OSM
{

    Map<Uint16, std::string> MapData::s_towns = {};

    Uint16 MapData::addTown(const std::string& town)
    {
        if(s_towns.size() == 0xffff)
            return 0;

        const auto result = std::find_if(
            s_towns.begin(), s_towns.end(), [town](const auto& t) { return t.second == town; });

        if(result != s_towns.end())
            return std::distance(s_towns.begin(), result);

        const Uint16 id = s_towns.size();
        s_towns[id]     = town;
        return id;
    }

    std::string MapData::getTown(const Uint16 id)
    {
        return s_towns[id];
    }

    Uint16 MapData::getTownID(const std::string& town)
    {
        for(const auto& pair : s_towns)
        {
            if(pair.second == town)
                return pair.first;
        }
        return 0;
    }

    Map<Uint16, std::string> MapData::getTowns()
    {
        return s_towns;
    }

}  // namespace OSM
