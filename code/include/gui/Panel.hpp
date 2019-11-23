#ifndef OSM_PANEL_HPP
#define OSM_PANEL_HPP

#include "structures/Primitives.hpp"

#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableWidget>

namespace OSM
{
    class Window;

    class Panel final : public QSplitter
    {
        Q_OBJECT

    private:
        Window*       m_parent;
        QLineEdit*    m_start;
        QLineEdit*    m_stop;
        QPushButton*  m_go;
        QTableWidget* m_table;

        QGridLayout* m_grid;
        QLabel*      m_label_start;
        QLabel*      m_label_stop;

        QSizePolicy m_fill_policy;

        void initTop();
        void initBottom();

    public slots:
        void go();

    signals:
        void goPressed();

    public:
        explicit Panel(Window* parent);
        Panel(const Panel& other)     = delete;
        Panel(Panel&& other) noexcept = delete;
        Panel& operator=(const Panel& other) = delete;
        Panel& operator=(Panel&& other) noexcept = delete;
        virtual ~Panel()                         = default;

        void addNode(const Node* node);
    };

}  // namespace OSM

#endif  // OSM_PANEL_HPP
