#include "gui/Panel.hpp"

#include <QHeaderView>

namespace OSM
{

    Panel::Panel()
        : QSplitter(Qt::Orientation::Vertical)
    {
        m_start = new QLineEdit();
        m_stop  = new QLineEdit();
        m_go    = new QPushButton("Search");
        m_table = new QTableWidget(1, 2);

        m_fill_policy.setHorizontalPolicy(QSizePolicy::Preferred);
        m_fill_policy.setVerticalPolicy(QSizePolicy::Preferred);
        m_fill_policy.setVerticalStretch(1);
        m_fill_policy.setHorizontalStretch(1);

        initTop();
        initBottom();
    }

    void Panel::initTop()
    {
        auto grid_wrapper = new QWidget{};
        m_grid = new QGridLayout{grid_wrapper};

        m_label_start = new QLabel{"From: "};
        m_label_stop = new QLabel{"To: "};
        auto grid_filler = new QWidget();

        grid_filler->setSizePolicy(m_fill_policy);

        m_start->setPlaceholderText("starting location");
        m_stop->setPlaceholderText("destination location");

        m_grid->addWidget(m_label_start, 0, 0);
        m_grid->addWidget(m_start, 0, 2);
        m_grid->addWidget(m_label_stop, 1, 0);
        m_grid->addWidget(m_stop, 1, 2);
        m_grid->addWidget(m_go, 2, 0, 1, 3, Qt::AlignRight);
        m_grid->addWidget(grid_filler);

        addWidget(grid_wrapper);
    }

    void Panel::initBottom()
    {
        m_table->setSizePolicy(m_fill_policy);
        m_table->verticalHeader()->hide();
        m_table->horizontalHeader()->hide();

        m_table->setItem(0, 0, new QTableWidgetItem("test 1"));
        m_table->setItem(0, 1, new QTableWidgetItem("test 2"));

        addWidget(m_table);
    }

}  // namespace OSM
