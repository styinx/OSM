#include "gui/Panel.hpp"

#include "gui/UIMap.hpp"
#include "gui/Window.hpp"
#include "io/MapData.hpp"

#include <QHeaderView>
#include <QtWidgets/QMessageBox>

namespace OSM
{

    Panel::Panel(Window* parent)
        : QSplitter(Qt::Orientation::Vertical)
        , m_parent(parent)
    {
        m_start = new QLineEdit();
        m_stop  = new QLineEdit();
        m_go    = new QPushButton("Search");

        m_pedestrian       = new QCheckBox("by foot");
        m_bike             = new QCheckBox("by bike");
        m_car              = new QCheckBox("by car");
        m_public_transport = new QCheckBox("by public transport");

        m_table = new QTableWidget(1, 2);

        m_fill_policy.setHorizontalPolicy(QSizePolicy::Preferred);
        m_fill_policy.setVerticalPolicy(QSizePolicy::Preferred);
        m_fill_policy.setVerticalStretch(1);
        m_fill_policy.setHorizontalStretch(1);

        initTop();
        initBottom();

        QObject::connect(m_go, SIGNAL(clicked()), this, SLOT(go()));
        QObject::connect(m_start, SIGNAL(returnPressed()), this, SLOT(go()));
        QObject::connect(m_stop, SIGNAL(returnPressed()), this, SLOT(go()));
    }

    void Panel::initTop()
    {
        auto grid_wrapper = new QWidget{};
        m_grid            = new QGridLayout{grid_wrapper};

        m_label_start    = new QLabel{"From: "};
        m_label_stop     = new QLabel{"To: "};
        auto grid_filler = new QWidget();

        grid_filler->setSizePolicy(m_fill_policy);

        m_start->setPlaceholderText("starting location");
        m_stop->setPlaceholderText("destination location");

        m_grid->addWidget(m_label_start, 0, 0);
        m_grid->addWidget(m_start, 0, 2);
        m_grid->addWidget(m_label_stop, 1, 0);
        m_grid->addWidget(m_stop, 1, 2);
        m_grid->addWidget(m_go, 2, 0, 1, 3, Qt::AlignRight);
        m_grid->addWidget(m_pedestrian, 3, 0, 1, 1);
        m_grid->addWidget(m_bike, 3, 1, 1, 1);
        m_grid->addWidget(m_car, 4, 0, 1, 1);
        m_grid->addWidget(m_public_transport, 4, 1, 1, 1);
        m_grid->addWidget(grid_filler);

        addWidget(grid_wrapper);
    }

    void Panel::initBottom()
    {
        m_table->setSizePolicy(m_fill_policy);
        m_table->verticalHeader()->hide();
        m_table->horizontalHeader()->hide();

        auto node = std::make_shared<Node>(Node{});

        addNode(node.get());

        addWidget(m_table);
    }

    void Panel::addNode(const Node* node)
    {
        auto lat = new QTableWidgetItem(QString::number(node->lat));
        lat->setFlags(lat->flags() ^ Qt::ItemIsEditable);

        auto lon = new QTableWidgetItem(QString::number(node->lon));
        lon->setFlags(lon->flags() ^ Qt::ItemIsEditable);

        m_table->setItem(m_table->rowCount(), 0, lat);
        m_table->setItem(m_table->rowCount(), 1, lon);
    }

    void addItem()
    {
        auto item = new QTableWidgetItem("test 1");
        item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    }

    void Panel::go()
    {
        auto start = m_start->text();
        auto stop  = m_stop->text();
        if(start.isEmpty() && stop.isEmpty())
        {
            QString towns;
            for(int i = 0; i < 10; ++i)
            {
                towns += QString(MapData::getTown(i).data()) + "\n";
            }

            QMessageBox::information(
                this,
                "Missing parameters",
                "Please provide a start and target location. Here are some:\n" + towns);
            return;
        }

        m_parent->getMap()->drawPath(m_parent->getMap()->calculateDijkstra(start, stop));
    }

}  // namespace OSM
