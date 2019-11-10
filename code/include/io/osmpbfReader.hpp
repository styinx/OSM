#ifndef OSM_OSMPBFREADER_HPP
#define OSM_OSMPBFREADER_HPP

#include "prototypes.hpp"
#include "structures/AdjacencyArray.hpp"

#include <osmpbf/osmfile.h>

namespace OSM
{

    class osmpbfReader final
    {
    private:
        osmpbf::OSMFileIn m_osm_file;

        Uint64 m_duration  = 0;
        Uint64 m_nodes     = 0;
        Uint64 m_ways      = 0;
        Uint64 m_relations = 0;

    public:
        explicit osmpbfReader(const std::string& osm_file);
        osmpbfReader(const osmpbfReader& other)     = delete;
        osmpbfReader(osmpbfReader&& other) noexcept = delete;
        osmpbfReader& operator=(const osmpbfReader& other) = delete;
        osmpbfReader& operator=(osmpbfReader&& other) noexcept = delete;
        virtual ~osmpbfReader()                                = default;

        void printInfo();
        void read(OSM::AdjacencyArray& array);
    };

}  // namespace OSM

#endif  // OSM_OSMPBFREADER_HPP
