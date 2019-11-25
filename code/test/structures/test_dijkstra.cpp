#include "alg/Dijkstra.hpp"

#include <gtest/gtest.h>

namespace OSMTest
{
    using namespace OSM;

    TEST(DijkstraTest, checkCompute)
    {
        //  a  - b -  e
        //   \       /
        //     c - d
        AdjacencyArray array{};

        Node a{0, 1, 0, 0, 0, 0};
        Node b{1, 1, 1, 0, 0, 0};
        Node c{2, 0, 1, 0, 0, 0};
        Node d{3, 0, 2, 0, 0, 0};
        Node e{4, 1, 3, 0, 0, 0};

        array.addNode(a);
        array.addNode(b);
        array.addNode(c);
        array.addNode(d);
        array.addNode(e);

        Edge ab{a.id, b.id};
        Edge ac{a.id, c.id};
        Edge ba{b.id, a.id};
        Edge be{b.id, e.id};
        Edge ca{c.id, a.id};
        Edge cd{c.id, d.id};
        Edge dc{d.id, c.id};
        Edge de{d.id, e.id};
        Edge eb{e.id, b.id};
        Edge ed{e.id, d.id};

        array.addIOEdge(ab);
        array.addIOEdge(ac);
        array.addIOEdge(ba);
        array.addIOEdge(be);
        array.addIOEdge(ca);
        array.addIOEdge(cd);
        array.addIOEdge(dc);
        array.addIOEdge(de);
        array.addIOEdge(eb);
        array.addIOEdge(ed);

        array.computeOffsets();

        Dijkstra dijkstra{&array};
        Vector<Uint64> res = dijkstra.compute(a.id, e.id);

        Vector<Uint64> optimal_path = {a.id, b.id, e.id};

        ASSERT_EQ(res, optimal_path);
    }
}  // namespace OSMTest
