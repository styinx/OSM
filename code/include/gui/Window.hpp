#ifndef OSM_WINDOW_HPP
#define OSM_WINDOW_HPP

#include "gui/Panel.hpp"
#include "gui/UIMap.hpp"
#include "structures/AdjacencyArray.hpp"

#include <QtWidgets/QMainWindow>

namespace OSM
{

    class Window final : public QMainWindow
    {
    private:
        Panel* m_panel;
        UIMap* m_map;

        QSplitter* m_main_splitter;

    public:
        explicit Window(const AdjacencyArray* array);
        Window(const Window& other)     = delete;
        Window(Window&& other) noexcept = delete;
        Window& operator=(const Window& other) = delete;
        Window& operator=(Window&& other) noexcept = delete;
        virtual ~Window()                          = default;
    };

}  // namespace OSM

#endif  // OSM_WINDOW_HPP
