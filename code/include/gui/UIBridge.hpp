#ifndef OSM_UIBRIDGE_HPP
#define OSM_UIBRIDGE_HPP

#include "gui/mapTypes.hpp"

#include "NonCopyable.hpp"
#include "NonMoveable.hpp"
#include <QtCore/QObject>

namespace OSM
{
    class UIMap;

    class UIBridge final
        : public QObject
        , public NonCopyable
        , public NonMoveable
    {
        Q_OBJECT
    private:
        MapBounds    m_bounds;
        UIMap*       m_map;

    public slots:
        void onLoad();
        void setMapBounds(const float n_lat, const float n_lon, const float s_lat, const float s_lon);
        void setStart(const QString& latlon);
        void setStop(const QString& latlon);

    public:
        explicit UIBridge(UIMap* map);
        virtual ~UIBridge()                            = default;
    };

}  // namespace OSM

#endif  // OSM_UIBRIDGE_HPP
