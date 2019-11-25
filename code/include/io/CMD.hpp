#ifndef OSM_CMD_HPP
#define OSM_CMD_HPP

#include "prototypes.hpp"

#include "NonCopyable.hpp"
#include "NonMoveable.hpp"

namespace OSM
{

    class CMD final
        : public NonCopyable
        , public NonMoveable
    {
    private:
        static Vector<std::string> s_arguments;

        CMD() = default;

    public:
        virtual ~CMD()                       = default;
    };

}  // namespace OSM

#endif  // OSM_CMD_HPP
