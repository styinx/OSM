#include "structures/AdjacencyArray.hpp"

#include <gtest/gtest.h>

namespace OSMTest
{
    using namespace OSM;

    TEST(AdjacencyArrayTest, checkOffsets)
    {
        AdjacencyArray array{};

        Node a{50, 0.0, 0.0, 0, 0, 0};
        Node b{10, 0.0, 0.0, 0, 0, 0};
        Node c{20, 0.0, 0.0, 0, 0, 0};
        Node d{30, 0.0, 0.0, 0, 0, 0};

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
        const auto ioffsets = array.getIOffsets();

        ASSERT_EQ(nodes[0].id, b.id);
        ASSERT_EQ(nodes[1].id, c.id);
        ASSERT_EQ(nodes[2].id, d.id);
        ASSERT_EQ(nodes[3].id, a.id);

        ASSERT_EQ(edges[0].source, 0U);
        ASSERT_EQ(edges[0].target, 1U);
        ASSERT_EQ(edges[1].source, 0U);
        ASSERT_EQ(edges[1].target, 2U);
        ASSERT_EQ(edges[2].source, 3U);
        ASSERT_EQ(edges[2].target, 0U);
        ASSERT_EQ(edges[3].source, 3U);
        ASSERT_EQ(edges[3].target, 1U);
        ASSERT_EQ(edges[4].source, 3U);
        ASSERT_EQ(edges[4].target, 2U);

        ASSERT_EQ(0U, ooffsets[0]);
        ASSERT_EQ(2U, ooffsets[1]);  // b
        ASSERT_EQ(2U, ooffsets[2]);  // c
        ASSERT_EQ(2U, ooffsets[3]);  // d
        ASSERT_EQ(5U, ooffsets[4]);  // a

        ASSERT_EQ(0U, ioffsets[0]);
        ASSERT_EQ(1U, ioffsets[1]);  // b
        ASSERT_EQ(3U, ioffsets[2]);  // c
        ASSERT_EQ(5U, ioffsets[3]);  // d
        ASSERT_EQ(5U, ioffsets[4]);  // a
    }

}  // namespace OSMTest
