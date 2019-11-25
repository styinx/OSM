#include "structures/AdjacencyArray.hpp"

#include <gtest/gtest.h>

namespace OSMTest
{
    using namespace OSM;

    TEST(AdjacencyArrayTest, checkOffsets)
    {
        AdjacencyArray array{};

        Node a{5, 0.0, 0.0, 0, 0, 0};
        Node b{1, 0.0, 0.0, 0, 0, 0};
        Node c{2, 0.0, 0.0, 0, 0, 0};
        Node d{3, 0.0, 0.0, 0, 0, 0};

        Edge ab{a.id, b.id};
        Edge ac{a.id, c.id};
        Edge ad{a.id, d.id};

        Edge bc{b.id, c.id};
        Edge bd{b.id, d.id};

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
        const auto ooffsets = array.getOOffsets();
        const auto ioffsets = array.getOOffsets();

        ASSERT_EQ(0U, ooffsets[0]);
        ASSERT_EQ(3U, ooffsets[1]);  // a
        ASSERT_EQ(5U, ooffsets[2]);  // b
        ASSERT_EQ(5U, ooffsets[3]);  // c
        ASSERT_EQ(5U, ooffsets[4]);  // d

        ASSERT_EQ(0U, ioffsets[0]);
        ASSERT_EQ(0U, ioffsets[1]);  // a
        ASSERT_EQ(1U, ioffsets[2]);  // b
        ASSERT_EQ(3U, ioffsets[3]);  // c
        ASSERT_EQ(5U, ioffsets[4]);  // d
    }

}  // namespace OSMTest
