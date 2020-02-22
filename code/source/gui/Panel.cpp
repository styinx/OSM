#include "gui/Panel.hpp"

#include "gui/Window.hpp"
#include "io/MapData.hpp"

#include <QHeaderView>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QToolBox>

namespace OSM
{

    Panel::Panel(Window* parent)
        : QSplitter(Qt::Orientation::Vertical)
        , m_parent(parent)
    {
        m_min_policy.setVerticalPolicy(QSizePolicy::Minimum);
        m_min_policy.setHorizontalPolicy(QSizePolicy::Minimum);

        m_expanding_policy.setHorizontalPolicy(QSizePolicy::Expanding);
        m_expanding_policy.setVerticalPolicy(QSizePolicy::Expanding);
        m_expanding_policy.setVerticalStretch(1);
        m_expanding_policy.setHorizontalStretch(1);

        m_start = new QLineEdit();
        m_stop  = new QLineEdit();
        m_go    = new QPushButton("Search");

        m_foot             = new QPushButton(QIcon(":/icon_foot"), "");
        m_bike             = new QPushButton(QIcon(":/icon_bike"), "");
        m_car              = new QPushButton(QIcon(":/icon_car"), "");
        m_public_transport = new QPushButton(QIcon(":/icon_public_transport"), "");

        m_street_graph = new QCheckBox("Show street graph");

        m_attraction_slider = new QSlider(Qt::Orientation::Horizontal);

        m_foot->setCheckable(true);
        m_bike->setCheckable(true);
        m_car->setCheckable(true);
        m_public_transport->setCheckable(true);

        m_table = new QTableWidget(0, 3);

        initTop();
        initBottom();

        QObject::connect(m_go, SIGNAL(clicked()), this, SLOT(go()));
        QObject::connect(m_start, SIGNAL(returnPressed()), this, SLOT(go()));
        QObject::connect(m_stop, SIGNAL(returnPressed()), this, SLOT(go()));
        QObject::connect(m_street_graph, SIGNAL(clicked()), this, SLOT(setShowGraph()));
        QObject::connect(m_attraction_slider, SIGNAL(clicked()), this, SLOT(setAttractionRange()));
    }

    void Panel::initTop()
    {
        auto grid_wrapper = new QWidget{};
        m_grid            = new QGridLayout{grid_wrapper};

        m_label_start            = new QLabel{"From: "};
        m_label_stop             = new QLabel{"To: "};
        m_label_attraction       = new QLabel{"Attraction range: "};
        m_label_attraction_start = new QLabel{"1 km"};
        m_label_attraction_stop  = new QLabel{"100 km"};
        auto grid_filler         = new QWidget();
        auto icon_wrapper        = new QWidget();
        auto icon_box            = new QHBoxLayout(icon_wrapper);
        auto range_wrapper       = new QWidget();
        auto range_box           = new QHBoxLayout(range_wrapper);

        grid_filler->setSizePolicy(m_expanding_policy);

        m_start->addAction(QIcon(":/icon_marker"), QLineEdit::TrailingPosition);
        m_start->setPlaceholderText("lat,lon | start");
        m_stop->addAction(QIcon(":/icon_marker"), QLineEdit::TrailingPosition);
        m_stop->setPlaceholderText("lat,lon | stop");

        m_attraction_slider->setRange(1, 100);
        m_attraction_slider->setSizePolicy(m_expanding_policy);

        m_grid->addWidget(m_label_start, 0, 0);
        m_grid->addWidget(m_start, 0, 1, 1, 1, Qt::AlignRight);
        m_grid->addWidget(m_label_stop, 1, 0);
        m_grid->addWidget(m_stop, 1, 1, 1, 1, Qt::AlignRight);

        icon_box->addWidget(m_foot);
        icon_box->addWidget(m_bike);
        icon_box->addWidget(m_car);
        icon_box->addWidget(m_public_transport);
        icon_box->addWidget(m_go);
        m_grid->addWidget(icon_wrapper, 2, 0, 1, 2, Qt::AlignRight);

        range_box->addWidget(m_label_attraction_start);
        range_box->addWidget(m_attraction_slider);
        range_box->addWidget(m_label_attraction_stop);
        // m_grid->addWidget(m_street_graph, 4, 0);
        m_grid->addWidget(m_label_attraction, 4, 0);
        m_grid->addWidget(range_wrapper, 4, 1);

        m_grid->addWidget(grid_filler);

        addWidget(grid_wrapper);
    }

    void Panel::initBottom()
    {
        m_table->setHorizontalHeaderLabels({"Node ID", "Lat", "Lon"});
        m_table->setSizePolicy(m_min_policy);
        m_table->verticalHeader()->hide();

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

        auto path = m_parent->getMap()->calculatePath(start, stop);

        if(path.empty())
        {
            QMessageBox::information(this, "No way found", "No way was found.");
        }

        m_parent->getMap()->drawPath(path);
    }

    void Panel::setShowGraph()
    {
        m_parent->getMap()->showGraph(m_street_graph->isChecked());
    }

    void Panel::setAttractionRange()
    {
        // Trigger the calculation only if at least one second has expired.
        if(std::chrono::duration_cast<Seconds>(Clock::now() - m_timer).count() > 1)
        {
            m_timer = Clock::now();
            // todo do action
        }
    }

    void Panel::setStart(const float lat, const float lon)
    {
        m_start->setText(QString::number(lat) + "," + QString::number(lon));
    }

    void Panel::setStop(const float lat, const float lon)
    {
        m_stop->setText(QString::number(lat) + "," + QString::number(lon));
    }

}  // namespace OSM
