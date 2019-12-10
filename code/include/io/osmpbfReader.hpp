#ifndef OSM_OSMPBFREADER_HPP
#define OSM_OSMPBFREADER_HPP

#include "NonCopyable.hpp"
#include "NonMoveable.hpp"
#include "gui/mapTypes.hpp"
#include "io/MapData.hpp"
#include "prototypes.hpp"
#include "structures/AdjacencyArray.hpp"

#include <osmpbf/osmfile.h>

namespace OSM
{

    class osmpbfReader final
        : public NonCopyable
        , public NonMoveable
        , public std::enable_shared_from_this<osmpbfReader>
    {
    private:
        using Clock    = std::chrono::system_clock;
        using Duration = std::chrono::duration<double>;
        using Seconds  = std::chrono::seconds;

        Uint32            m_threads = std::max(std::thread::hardware_concurrency(), 4U);
        osmpbf::OSMFileIn m_osm_file;

        Uint64               m_duration = 0;
        Pair<Uint64, Uint64> m_nodes    = {0, 0};
        Pair<Uint64, Uint64> m_ways     = {0, 0};
        Uint64               m_edges    = 0;

        Clock::time_point m_start  = Clock::now();
        Clock::time_point m_stop   = Clock::now();
        Duration          m_diff   = Duration{0};
        Duration          m_second = Duration{1};

        static Byte readMaxSpeed(const std::string& speed);

    public:
        explicit osmpbfReader(const std::string& osm_file);
        osmpbfReader(const osmpbfReader& other)     = delete;
        osmpbfReader(osmpbfReader&& other) noexcept = delete;
        osmpbfReader& operator=(const osmpbfReader& other) = delete;
        osmpbfReader& operator=(osmpbfReader&& other) noexcept = delete;
        virtual ~osmpbfReader()                                = default;

        void      printInfo(const bool timed = false);
        void      read(OSM::AdjacencyArray& array);
        MapBounds getMapBounds();
    };

}  // namespace OSM

#endif  // OSM_OSMPBFREADER_HPP
