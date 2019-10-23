#ifndef OSM_ISERIALIZABLE_HPP
#define OSM_ISERIALIZABLE_HPP

#include "prototypes.hpp"

namespace OSM
{

    class ISerializable
    {
    protected:
        ISerializable() = default;

    public:
        virtual Vector<Byte> serialize() = 0;
    };

} // namespace OSM

#endif //OSM_ISERIALIZABLE_HPP
