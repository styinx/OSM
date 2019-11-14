#ifndef OSM_NONMOVEABLE_HPP
#define OSM_NONMOVEABLE_HPP

namespace OSM
{

    class NonMoveable
    {
    protected:
        NonMoveable() = default;

    public:
        NonMoveable(NonMoveable&& other) noexcept = default;
        NonMoveable& operator=(NonMoveable&& other) noexcept = default;
        virtual ~NonMoveable()                               = default;
    };

}  // namespace OSM

#endif  // OSM_NONMOVEABLE_HPP
