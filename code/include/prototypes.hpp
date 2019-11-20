#ifndef OSM_PROTOTYPES_HPP
#define OSM_PROTOTYPES_HPP

#include <functional>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <thread>
#include <unordered_map>
#include <vector>

namespace OSM
{

    // primitive types
    using Byte   = std::uint8_t;
    using Uint8  = std::uint8_t;
    using Sint8  = std::int8_t;
    using Uint16 = std::uint16_t;
    using Sint16 = std::int16_t;
    using Uint32 = std::uint32_t;
    using Sint32 = std::int32_t;
    using Uint64 = std::uint64_t;
    using Sint64 = std::int64_t;

    // complex types
    using Thread  = std::thread;
    using String  = std::string;
    using WString = std::wstring;
    // using Any = std::any;

    // collection types
    template<typename T, std::size_t Size>
    using Array = std::array<T, Size>;
    template<typename T>
    using Vector = std::vector<T>;
    template<typename T>
    using List = std::list<T>;
    template<typename T>
    using Set = std::set<T>;
    template<typename K, typename V>
    using Pair = std::pair<K, V>;
    template<typename T>
    using Queue = std::queue<T>;
    template<typename K, typename V>
    using Map = std::map<K, V>;
    template<typename K, typename V>
    using UMap = std::unordered_map<K, V>;

    // pointer types
    template<typename T>
    using UniquePtr = std::unique_ptr<T>;
    template<typename T>
    using SharedPtr = std::shared_ptr<T>;
    template<typename T>
    using WeakPtr = std::weak_ptr<T>;

    // function types
    template<typename Func>
    using Function = std::function<Func>;

}  // namespace OSM

#endif  // OSM_PROTOTYPES_HPP
