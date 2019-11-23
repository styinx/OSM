#ifndef OSM_UIMAP_HPP
#define OSM_UIMAP_HPP

#include "alg/Dijkstra.hpp"
#include "gui/UIBridge.hpp"
#include "gui/mapTypes.hpp"
#include "structures/AdjacencyArray.hpp"
#include "structures/Grid.hpp"

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

        Grid     m_grid;
        Dijkstra m_dijkstra;

    public:
        explicit UIMap(const OSM::AdjacencyArray* array, const MapBounds& bounds);
        UIMap(const UIMap& other)     = delete;
        UIMap(UIMap&& other) noexcept = delete;
        UIMap& operator=(const UIMap& other) = delete;
        UIMap& operator=(UIMap&& other) noexcept = delete;
        virtual ~UIMap()                         = default;

        Pair<float, Vector<Uint64>> calculateDistance(const QString& from, const QString& to);
        void                        drawEdges(const MapBounds& bounds) const;
    };

}  // namespace OSM

#endif  // OSM_UIMAP_HPP
