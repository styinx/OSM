#ifndef OSM_NONCOPYABLE_HPP
#define OSM_NONCOPYABLE_HPP

namespace OSM
{

    class NonCopyable
    {
    protected:
        NonCopyable()                             = default;

    public:
        NonCopyable(const NonCopyable& other)     = delete;
        NonCopyable& operator=(const NonCopyable& other) = delete;
        virtual ~NonCopyable()                               = default;
    };

} // namespace OSM

#endif  // OSM_NONCOPYABLE_HPP
