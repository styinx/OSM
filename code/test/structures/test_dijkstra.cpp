#include "alg/Dijkstra.hpp"

#include <gtest/gtest.h>

namespace OSMTest
{
    using namespace OSM;

    TEST(DijkstraTest, checkCompute)
    {

        AdjacencyArray array{};

        array.addNode(Node{0, 0, 0, 0, 0, 0});
        array.addNode(Node{1, 0, 0, 0, 0, 0});
        array.addNode(Node{2, 0, 0, 0, 0, 0});
        array.addNode(Node{4, 0, 0, 0, 0, 0});
        array.addNode(Node{5, 0, 0, 0, 0, 0});

        array.addIOEdge(IOEdge{0UL, 1UL});
        array.addIOEdge(IOEdge{1UL, 2UL});
        array.addIOEdge(IOEdge{2UL, 4UL});
        array.addIOEdge(IOEdge{3UL, 5UL});

        array.computeOffsets();

        Pair<float, Vector<Uint64>> res_pair = Dijkstra::compute(array, 0UL, 1UL);

        Vector<Uint64> optimal_path = {0UL, 1UL};

        ASSERT_EQ(res_pair.second, optimal_path);
    }
}  // namespace OSMTest