#include "gui/Window.hpp"

namespace OSM
{

    Window::Window(const OSM::AdjacencyArray& array)
    {
        m_panel = new Panel();
        m_map = new UIMap(array);

        m_main_splitter = new QSplitter{Qt::Orientation::Horizontal};

        m_main_splitter->addWidget(m_panel);
        m_main_splitter->addWidget(m_map);

        setCentralWidget(m_main_splitter);
    }

} // namespace OSM
