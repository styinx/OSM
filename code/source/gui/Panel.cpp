#include "gui/Panel.hpp"

namespace OSM
{

    Panel::Panel()
        : QSplitter(Qt::Orientation::Vertical)
    {
        m_start = new QLineEdit();
        m_stop  = new QLineEdit();
        m_go    = new QPushButton("Search");
        m_table = new QTableWidget(0, 2);

        initTop();
        initBottom();
    }

    void Panel::initTop()
    {
        m_grid_wrapper = new QWidget{};
        m_grid = new QGridLayout{m_grid_wrapper};

        m_label_start = new QLabel{"From: "};
        m_label_stop = new QLabel{"To: "};

        m_start->setPlaceholderText("starting location");
        m_stop->setPlaceholderText("destination location");

        m_grid->addWidget(m_label_start, 0, 0);
        m_grid->addWidget(m_start, 0, 1);
        m_grid->addWidget(m_label_stop, 1, 0);
        m_grid->addWidget(m_stop, 1, 1);
        m_grid->addWidget(m_go, 2, 0, 1, 2, Qt::AlignRight);

        addWidget(m_grid_wrapper);
    }

    void Panel::initBottom()
    {
        m_table->setVerticalHeaderLabels({"1", "2"});

        QTableWidgetItem* item = new QTableWidgetItem("test");
        m_table->setItem(1, 1, item);

        addWidget(m_table);
    }

}  // namespace OSM
