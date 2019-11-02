#ifndef OSM_UIMAP_HPP
#define OSM_UIMAP_HPP

#include <QtWebEngineWidgets/QWebEngineView>

namespace OSM
{

    class UIMap final : public QWebEngineView
    {
    private:


    public:
        UIMap()                     = default;
        UIMap(const UIMap& other)     = delete;
        UIMap(UIMap&& other) noexcept = delete;
        UIMap& operator=(const UIMap& other) = delete;
        UIMap& operator=(UIMap&& other) noexcept = delete;
        virtual ~UIMap()                       = default;
    };

} // namespace OSM

#endif  // OSM_UIMAP_HPP
