#ifndef OSM_ADJACENTMATRIX_HPP
#define OSM_ADJACENTMATRIX_HPP

#include <vector>
#include <cstdint>

using ID = std::uint64_t;

namespace OSM
{
    class AdjacentMatrix final
    {
    private:
        std::vector<ID> m_nodes;
        std::vector<int> m_edges;

    public:
        AdjacentMatrix()                                = default;
        AdjacentMatrix(const AdjacentMatrix& other)     = default;
        AdjacentMatrix(AdjacentMatrix&& other) noexcept = default;
        AdjacentMatrix& operator=(const AdjacentMatrix& other) = default;
        AdjacentMatrix& operator=(AdjacentMatrix&& other) noexcept = default;
        virtual ~AdjacentMatrix()                                  = default;
    };
}

#endif //OSM_ADJACENTMATRIX_HPP
