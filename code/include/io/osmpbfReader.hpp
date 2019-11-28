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
    {
    private:
        osmpbf::OSMFileIn m_osm_file;

        Uint64               m_duration  = 0;
        Pair<Uint64, Uint64> m_nodes     = {0, 0};
        Pair<Uint64, Uint64> m_ways      = {0, 0};
        Uint64               m_edges     = 0;
        Uint64               m_relations = 0;

        static Byte readMaxSpeed(const std::string& speed);

    public:
        explicit osmpbfReader(const std::string& osm_file);
        osmpbfReader(const osmpbfReader& other)     = delete;
        osmpbfReader(osmpbfReader&& other) noexcept = delete;
        osmpbfReader& operator=(const osmpbfReader& other) = delete;
        osmpbfReader& operator=(osmpbfReader&& other) noexcept = delete;
        virtual ~osmpbfReader()                                = default;

        void      printInfo();
        void      read(OSM::AdjacencyArray& array);
        MapBounds getMapBounds();
    };

}  // namespace OSM

#endif  // OSM_OSMPBFREADER_HPP
