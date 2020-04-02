#ifndef OSM_UIMAP_HPP
#define OSM_UIMAP_HPP

#include "alg/RouteSearch.hpp"
#include "gui/WebPage.hpp"
#include "structures/AdjacencyArray.hpp"
#include "structures/Grid.hpp"

#include <QtWebChannel/QWebChannel>
#include <QtWebEngineWidgets/QWebEngineView>

namespace OSM
{
    class Window;
    class UIGraph;

    class UIMap final
        : public QWebEngineView
        , public NonCopyable
        , public NonMoveable
    {
        Q_OBJECT
        Q_PROPERTY(int zoom MEMBER m_zoom)
        Q_PROPERTY(QVariantList attr_id MEMBER m_attr_id)
        Q_PROPERTY(QVariantList attr_lat MEMBER m_attr_lat)
        Q_PROPERTY(QVariantList attr_lon MEMBER m_attr_lon)
        Q_PROPERTY(QVariantList attr_tourism MEMBER m_attr_tourism)
    private:
        Window*               m_parent;
        WebPage*              m_page;
        QWebChannel*          m_channel;
        const AdjacencyArray* m_array;
        UIGraph*              m_graph;

        int          m_zoom = 0;
        Grid         m_grid;
        RouteSearch  m_route_search;
        Vector<Node> m_route_attractions{};
        QVariantList m_attr_id{};
        QVariantList m_attr_lat{};
        QVariantList m_attr_lon{};
        QVariantList m_attr_tourism{};

        Uint64 townToNode(const QString& town) const;
        void   runJS(const QString& script) const;

    public slots:
        void onLoad();
        void showGraph(const bool show);
        void showNodes(const bool show);
        void setStart(const QString& latlon);
        void setStop(const QString& latlon);
        void addAttraction(const QString& id);
        void removeAttraction(const QString& id);

    public:
        explicit UIMap(Window* parent, const OSM::AdjacencyArray* array, const MapBounds& bounds);
        virtual ~UIMap() = default;

        PathResult
               calculatePath(const QString& from, const QString& to, const TransportType type, const Byte algorithm);
        void   drawPath(const Vector<Uint64>& path, const Uint8 color = 0) const;
        void   drawNodes(const Vector<Uint64>& path) const;
        void   resetAttractions();
        void   setAttractions(const int val);
        size_t numberOfAttractions();
    };

}  // namespace OSM

#endif  // OSM_UIMAP_HPP
