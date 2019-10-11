#ifndef OSM_STD_HPP
#define OSM_STD_HPP

#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace osm::chzorn
{

    using String = std::string;

    template<typename ValueType>
    using Vector = std::vector<ValueType>;

    template<typename KeyType, typename ValueType>
    using Map = std::map<KeyType, ValueType>;

    template<typename KeyType, typename ValueType>
    using UMap = std::map<KeyType, ValueType>;

    template<typename ValueType>
    using SharedPtr = std::shared_ptr<ValueType>;

    template<typename ValueType>
    using UniquePtr = std::unique_ptr<ValueType>;

}

#endif  // OSM_STD_HPP
