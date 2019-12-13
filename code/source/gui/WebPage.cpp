#include "gui/WebPage.hpp"

namespace OSM
{

    WebPage::WebPage(QObject* parent)
        : QWebEnginePage(parent)
    {
    }

    void WebPage::javaScriptConsoleMessage(
        QWebEnginePage::JavaScriptConsoleMessageLevel level,
        const QString&                                message,
        int                                           lineNumber,
        const QString&                                sourceID)
    {
        qDebug() << lineNumber << ": " << message;
    }

} // namespace OSM
