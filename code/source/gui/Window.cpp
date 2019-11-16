#include "gui/Window.hpp"

namespace OSM
{

    Window::Window(const AdjacencyArray* array, const MapBounds& bounds)
    {
        m_panel = new Panel();
        m_map = new UIMap(array, bounds);

        m_main_splitter = new QSplitter{Qt::Orientation::Horizontal};

        m_main_splitter->addWidget(m_panel);
        m_main_splitter->addWidget(m_map);

        setCentralWidget(m_main_splitter);
    }

} // namespace OSM
