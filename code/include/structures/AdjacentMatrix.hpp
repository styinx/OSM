#ifndef OSM_ADJACENTMATRIX_HPP
#define OSM_ADJACENTMATRIX_HPP

#include <cstdint>
#include <array>
#include <set>
#include <unordered_map>
#include <vector>

namespace OSM
{
    using ID = std::int64_t;

    struct Node
    {
        ID id;
        std::vector<int> edges;
    };

    struct Edge
    {

    };

    class AdjacentMatrix final
    {
    private:
        std::vector<ID> m_nodes;
        std::vector<ID> m_edges;

    public:
        AdjacentMatrix()                                = default;
        AdjacentMatrix(const AdjacentMatrix& other)     = default;
        AdjacentMatrix(AdjacentMatrix&& other) noexcept = default;
        AdjacentMatrix& operator=(const AdjacentMatrix& other) = default;
        AdjacentMatrix& operator=(AdjacentMatrix&& other) noexcept = default;
        virtual ~AdjacentMatrix()                                  = default;

        unsigned nodeCount() const;
        unsigned edgeCount() const;
        AdjacentMatrix& addNode(const ID node);
        AdjacentMatrix& addEdge(const ID source, const ID target);
    };
}  // namespace OSM

#endif  // OSM_ADJACENTMATRIX_HPP
