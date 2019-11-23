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

        IOEdge ab{a.id, b.id};
        IOEdge ac{a.id, c.id};
        IOEdge ba{b.id, a.id};
        IOEdge be{b.id, e.id};
        IOEdge ca{c.id, a.id};
        IOEdge cd{c.id, d.id};
        IOEdge dc{d.id, c.id};
        IOEdge de{d.id, e.id};
        IOEdge eb{e.id, b.id};
        IOEdge ed{e.id, d.id};

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
        Pair<float, Vector<Uint64>> res_pair = dijkstra.compute(a.id, e.id);

        Vector<Uint64> optimal_path = {a.id, b.id, e.id};

        ASSERT_EQ(res_pair.first, distNodes(a, e));
        ASSERT_EQ(res_pair.second, optimal_path);
    }
}  // namespace OSMTest
