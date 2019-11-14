#ifndef OSM_UIMAP_HPP
#define OSM_UIMAP_HPP

#include "gui/UIBridge.hpp"
#include "gui/mapTypes.hpp"
#include "structures/AdjacencyArray.hpp"

#include <QtWebChannel/QWebChannel>
#include <QtWebEngineWidgets/QWebEngineView>

namespace OSM
{

    class UIMap final : public QWebEngineView
    {
    private:
        QWebChannel*          m_channel;
        UIBridge*             m_bridge;
        const AdjacencyArray* m_array;

    public:
        explicit UIMap(const OSM::AdjacencyArray* array);
        UIMap(const UIMap& other)     = delete;
        UIMap(UIMap&& other) noexcept = delete;
        UIMap& operator=(const UIMap& other) = delete;
        UIMap& operator=(UIMap&& other) noexcept = delete;
        virtual ~UIMap()                         = default;

        void drawEdges(const MapBounds& bounds) const;
    };

}  // namespace OSM

#endif  // OSM_UIMAP_HPP
