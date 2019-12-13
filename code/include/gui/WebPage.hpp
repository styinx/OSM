#ifndef OSM_WEBPAGE_HPP
#define OSM_WEBPAGE_HPP

#include <QtWebEngineWidgets/QWebEnginePage>

namespace OSM
{

    class WebPage final : public QWebEnginePage
    {
    private:
    public:
        WebPage(QObject* parent = nullptr);
        virtual ~WebPage() = default;

        void javaScriptConsoleMessage(
            JavaScriptConsoleMessageLevel level,
            const QString&                message,
            int                           lineNumber,
            const QString&                sourceID);
    };

}  // namespace OSM

#endif  // OSM_WEBPAGE_HPP
