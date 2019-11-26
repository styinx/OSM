#include "structures/Primitives.hpp"
#include "structures/Grid.hpp"

#include <gtest/gtest.h>

namespace OSMTest
{
    using namespace OSM;

    TEST(DijkstraTest, checkCompute)
    {
        Grid grid{{0, 100, 0, 100}};

        Vector<Node> nodes;
        Node a{0, 1, 0, 0, 0, 0};
        Node b{1, 1, 1, 0, 0, 0};
        Node c{2, 0, 1, 0, 0, 0};
        Node d{3, 0, 2, 0, 0, 0};
        Node e{4, 1, 3, 0, 0, 0};

        nodes.emplace_back(a);
        nodes.emplace_back(b);
        nodes.emplace_back(c);
        nodes.emplace_back(d);
        nodes.emplace_back(e);

        Uint64 i = 0;
        for(const auto& node : nodes)
        {
            grid.set(node.lat, node.lon, i++);
        }

        ASSERT_EQ(grid.get(1, 0), Vector<Uint64>{0});
        ASSERT_EQ(grid.get(1, 1), Vector<Uint64>{1});
        ASSERT_EQ(grid.get(0, 1), Vector<Uint64>{2});
        ASSERT_EQ(grid.get(0, 2), Vector<Uint64>{3});
        ASSERT_EQ(grid.get(1, 3), Vector<Uint64>{4});
    }
}  // namespace OSMTest
