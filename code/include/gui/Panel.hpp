#ifndef OSM_PANEL_HPP
#define OSM_PANEL_HPP

#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableWidget>

namespace OSM
{

    class Panel final : public QSplitter
    {
    private:
        QLineEdit*    m_start;
        QLineEdit*    m_stop;
        QPushButton*  m_go;
        QTableWidget* m_table;

        QWidget*     m_grid_wrapper;
        QGridLayout* m_grid;
        QLabel*      m_label_start;
        QLabel*      m_label_stop;

        void initTop();
        void initBottom();

    public:
        Panel();
        Panel(const Panel& other)     = delete;
        Panel(Panel&& other) noexcept = delete;
        Panel& operator=(const Panel& other) = delete;
        Panel& operator=(Panel&& other) noexcept = delete;
        virtual ~Panel()                         = default;
    };

}  // namespace OSM

#endif  // OSM_PANEL_HPP
