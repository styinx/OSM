#ifndef OSM_UIMAP_HPP
#define OSM_UIMAP_HPP

#include "alg/RouteSearch.hpp"
#include "gui/mapTypes.hpp"
#include "structures/AdjacencyArray.hpp"
#include "structures/Grid.hpp"

#include <QtWebChannel/QWebChannel>
#include <QtWebEngineWidgets/QWebEngineView>

namespace OSM
{
    class Window;
    class UIBridge;

    class UIMap final : public QWebEngineView
    {
    private:
        QWebChannel*          m_channel;
        UIBridge*             m_bridge;
        const AdjacencyArray* m_array;

        Grid        m_grid;
        RouteSearch m_routeSearch;

        Uint64 townToNode(const QString& town) const;
        Uint64 coordToNode(const float lat, const float lon) const;

    public:
        explicit UIMap(Window* parent, const OSM::AdjacencyArray* array, const MapBounds& bounds);
        UIMap(const UIMap& other)     = delete;
        UIMap(UIMap&& other) noexcept = delete;
        UIMap& operator=(const UIMap& other) = delete;
        UIMap& operator=(UIMap&& other) noexcept = delete;
        virtual ~UIMap()                         = default;

        Vector<Uint64> calculatePath(const QString& from, const QString& to, const int method);
        void           setGraph(const MapBounds& bounds) const;
        void           drawPath(const Vector<Uint64>& path) const;

        UIBridge* getBridge() const;
        void      showGraph(const bool show);
        void onLoad();
    };

}  // namespace OSM

#endif  // OSM_UIMAP_HPP
