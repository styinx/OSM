#include "structures/AdjacencyArray.hpp"

#include <gtest/gtest.h>

namespace OSMTest
{
    using namespace OSM;

    TEST(AdjacencyArrayTest, checkOffsets)
    {
        AdjacencyArray array{};

        Node a{0, 0.0, 0.0, 0, 0, 0};
        Node b{1, 0.0, 0.0, 0, 0, 0};
        Node c{2, 0.0, 0.0, 0, 0, 0};
        Node d{3, 0.0, 0.0, 0, 0, 0};

        IOEdge ab{a.id, b.id};
        IOEdge ac{a.id, c.id};
        IOEdge ad{a.id, d.id};

        IOEdge bc{b.id, c.id};
        IOEdge bd{b.id, d.id};

        array.addNode(a);
        array.addNode(b);
        array.addNode(c);
        array.addNode(d);

        array.addIOEdge(ab);
        array.addIOEdge(ac);
        array.addIOEdge(ad);

        array.addIOEdge(bc);
        array.addIOEdge(bd);

        array.computeOffsets();

        const auto nodes   = array.getNodes();
        const auto edges   = array.getEdges();
        const auto offsets = array.getOffsets();

        ASSERT_EQ(0U, offsets[0]);
        ASSERT_EQ(3U, offsets[1]);  // a
        ASSERT_EQ(5U, offsets[2]);  // b
        ASSERT_EQ(5U, offsets[3]);  // c
        ASSERT_EQ(5U, offsets[4]);  // d
    }

}  // namespace OSMTest
