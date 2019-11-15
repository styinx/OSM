#ifndef OSM_RTREE_HPP
#define OSM_RTREE_HPP

#include <prototypes.hpp>
namespace OSM
{

    template<typename T>
    class RTree final
    {
    private:
        struct Node
        {
            T index;

            SharedPtr<Node>         parent;
            Vector<SharedPtr<Node>> children;
        };

        SharedPtr<Node> head;

    public:
        RTree()                       = default;
        RTree(const RTree& other)     = default;
        RTree(RTree&& other) noexcept = default;
        RTree& operator=(const RTree& other) = default;
        RTree& operator=(RTree&& other) noexcept = default;
        virtual ~RTree()                         = default;
    };

}  // namespace OSM

#endif  // OSM_RTREE_HPP
