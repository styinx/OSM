#ifndef OSM_UIBRIDGE_HPP
#define OSM_UIBRIDGE_HPP

#include "gui/mapTypes.hpp"

#include <QtCore/QObject>

namespace OSM
{
    class UIMap;

    class UIBridge final : public QObject
    {
        Q_OBJECT
    private:
        MapBounds    m_bounds;
        const UIMap* m_map;

    public slots:
        void dummy();
        void setMapBounds(const float n_lat, const float n_lon, const float s_lat, const float s_lon);

    public:
        explicit UIBridge(const UIMap* map);
        UIBridge(const UIBridge& other)     = delete;
        UIBridge(UIBridge&& other) noexcept = delete;
        UIBridge& operator=(const UIBridge& other) = delete;
        UIBridge& operator=(UIBridge&& other) noexcept = delete;
        virtual ~UIBridge()                            = default;
    };

}  // namespace OSM

#endif  // OSM_UIBRIDGE_HPP