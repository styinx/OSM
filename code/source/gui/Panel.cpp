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
        m_expanding_policy.setHorizontalStretch(1);
        m_expanding_policy.setVerticalStretch(1);

        m_start            = new QLineEdit();
        m_stop             = new QLineEdit();
        m_go               = new QPushButton("Search");
        m_reset_attraction = new QPushButton("Reset");

        m_foot             = new QPushButton(QIcon(":/icon_foot"), "");
        m_bike             = new QPushButton(QIcon(":/icon_bike"), "");
        m_car              = new QPushButton(QIcon(":/icon_car"), "");
        m_public_transport = new QPushButton(QIcon(":/icon_public_transport"), "");

        m_street_graph     = new QCheckBox("Show street graph");
        m_show_attractions = new QCheckBox("Show attractions");

        m_attraction_slider          = new QSlider(Qt::Orientation::Horizontal);
        m_attraction_slider_distance = new QSlider(Qt::Orientation::Horizontal);

        m_foot->setCheckable(true);
        m_bike->setCheckable(true);
        m_car->setCheckable(true);
        m_car->setChecked(true);
        m_public_transport->setCheckable(false);

        initTop();
        initBottom();

        QObject::connect(m_go, SIGNAL(clicked()), this, SLOT(go()));
        QObject::connect(m_start, SIGNAL(returnPressed()), this, SLOT(go()));
        QObject::connect(m_stop, SIGNAL(returnPressed()), this, SLOT(go()));
        QObject::connect(m_street_graph, SIGNAL(clicked()), this, SLOT(setShowGraph()));
        QObject::connect(m_show_attractions, SIGNAL(clicked()), this, SLOT(setShowAttractions()));
        QObject::connect(m_reset_attraction, SIGNAL(clicked()), this, SLOT(resetAttractions()));
        QObject::connect(
            m_attraction_slider, SIGNAL(valueChanged(int)), this, SLOT(setAttractionNumber(int)));
        QObject::connect(
            m_attraction_slider_distance, SIGNAL(valueChanged(int)), this, SLOT(setAttractionRange(int)));
    }

    void Panel::initTop()
    {
        auto grid_wrapper = new QWidget{};
        m_grid            = new QGridLayout{grid_wrapper};

        m_label_start               = new QLabel{"From: "};
        m_label_stop                = new QLabel{"To: "};
        m_label_show_attraction     = new QLabel{"Show tourism: "};
        m_label_config_info         = new QLabel{"<b>Configuration</b>"};
        m_label_attraction          = new QLabel{"Number of attraction: "};
        m_label_attraction_distance = new QLabel{"Attraction range: "};
        m_label_attraction_start    = new QLabel{"1 km"};
        m_label_attraction_stop     = new QLabel{"10 km"};

        auto icon_wrapper           = new QWidget();
        auto icon_box               = new QHBoxLayout(icon_wrapper);
        auto range_wrapper          = new QWidget();
        auto range_box              = new QHBoxLayout(range_wrapper);

        m_start->addAction(QIcon(":/icon_marker_blue"), QLineEdit::TrailingPosition);
        m_start->setPlaceholderText("lat,lon | start");
        m_stop->addAction(QIcon(":/icon_marker_red"), QLineEdit::TrailingPosition);
        m_stop->setPlaceholderText("lat,lon | stop");

        m_attraction_slider->setRange(0, 10);
        m_attraction_slider_distance->setRange(1, 10);

        int row = 0;

        m_grid->addWidget(m_label_start, row, 0);
        m_grid->addWidget(m_start, row++, 1, 1, 1, Qt::AlignRight);
        m_grid->addWidget(m_label_stop, row, 0);
        m_grid->addWidget(m_stop, row++, 1, 1, 1, Qt::AlignRight);

        icon_box->addWidget(m_foot);
        icon_box->addWidget(m_bike);
        icon_box->addWidget(m_car);
        icon_box->addWidget(m_public_transport);
        icon_box->addWidget(m_go);
        m_grid->addWidget(icon_wrapper, row++, 0, 1, 2, Qt::AlignRight);

        auto grid_filler1 = new QWidget();
        grid_filler1->setSizePolicy(m_expanding_policy);
        m_grid->addWidget(grid_filler1);

        row++;

        m_grid->addWidget(m_label_config_info, row++, 0, 1, 2, Qt::AlignCenter);
        m_grid->addWidget(m_label_attraction, row, 0);
        m_grid->addWidget(m_attraction_slider, row++, 1);

        range_box->addWidget(m_label_attraction_start);
        range_box->addWidget(m_attraction_slider_distance);
        range_box->addWidget(m_label_attraction_stop);
        m_grid->addWidget(m_label_attraction_distance, row, 0);
        m_grid->addWidget(range_wrapper, row++, 1);
        m_grid->addWidget(m_reset_attraction, row, 1);
        m_grid->addWidget(m_label_show_attraction, row++, 0);
        m_grid->addWidget(m_show_attractions, row++, 1);

        //m_grid->addWidget(m_street_graph, row++, 1);

        auto grid_filler2 = new QWidget();
        grid_filler2->setSizePolicy(m_expanding_policy);
        m_grid->addWidget(grid_filler2);

        addWidget(grid_wrapper);
    }

    void Panel::initBottom()
    {
        auto grid_wrapper = new QWidget{};
        m_info_grid       = new QGridLayout{grid_wrapper};

        m_label_route_info    = new QLabel("<b>Route information</b>");
        m_label_distance_info = new QLabel("Estimated distance: ");
        m_distance_info       = new QLabel("0.0 km");
        m_label_duration_info = new QLabel("Estiated duration: ");
        m_duration_info       = new QLabel("0.0 h");
        m_label_calculation   = new QLabel("Calculation:");
        m_calculation_info    = new QLabel("0.0 s");

        auto grid_filler1 = new QWidget();
        grid_filler1->setSizePolicy(m_expanding_policy);
        m_grid->addWidget(grid_filler1);

        int row = 1;

        m_info_grid->addWidget(m_label_route_info, row++, 0, 1, 2, Qt::AlignCenter);
        m_info_grid->addWidget(m_label_distance_info, row, 0);
        m_info_grid->addWidget(m_distance_info, row++, 1);
        m_info_grid->addWidget(m_label_duration_info, row, 0);
        m_info_grid->addWidget(m_duration_info, row++, 1);
        m_info_grid->addWidget(m_label_calculation, row, 0);
        m_info_grid->addWidget(m_calculation_info, row++, 1);

        auto grid_filler2 = new QWidget();
        grid_filler2->setSizePolicy(m_expanding_policy);
        m_grid->addWidget(grid_filler2);

        addWidget(grid_wrapper);
    }

    TransportType Panel::transportation()
    {
        if(m_foot->isChecked())
        {
            return TransportType::PEDESTRIAN;
        }
        else if(m_bike->isChecked())
        {
            return TransportType::BICYCLE;
        }
        else if(m_car->isChecked())
        {
            return TransportType::CAR;
        }
        else if(m_public_transport->isChecked())
        {
            return TransportType::PUBLIC_TRANSPORT;
        }
        return TransportType::ANY;
    }

    QString Panel::duration(const float duration)
    {
        float minutes = duration;
        if(minutes < 60)
        {
            return QString::number(minutes, 'g', 2) + " min";
        }
        else
        {
            return QString::number(minutes / 60, 'g', 2) + " h";
        }
    }

    QString Panel::distance(const float distance)
    {
        float meters = distance;
        if(meters < 1000)
        {
            return QString::number(meters, 'g', 2) + " m";
        }
        else
        {
            return QString::number(meters / 1000, 'g', 2) + " km";
        }
    }

    void Panel::go()
    {
        auto start = m_start->text();
        auto stop  = m_stop->text();

        //        if(start.isEmpty() && stop.isEmpty())
        //        {
        //            QString towns;
        //            for(int i = 0; i < 10; ++i)
        //            {
        //                towns += QString(MapData::getTown(i).data()) + "\n";
        //            }
        //
        //            QMessageBox::information(
        //                this,
        //                "Missing parameters",
        //                "Please provide a start and target location.\n Here are some:\n" + towns);
        //            return;
        //        }

        auto pathResult = m_parent->getMap()->calculatePath(start, stop, transportation());

        if(pathResult.route.empty())
        {
            if(pathResult.start == pathResult.stop)
            {
                QMessageBox::information(this, "No way found", "Start and Stop are the same.");
            }
            else
            {
                QMessageBox::information(
                    this,
                    "No way found",
                    "No way was found.\nMake sure that the start and stop point are connected to "
                    "the road network.");
            }
        }
        else
        {
            if(pathResult.start == 0 || pathResult.stop == 0)
            {
                QMessageBox::information(
                    this,
                    "Warning",
                    "The path search uses most likely a default value for one of your nodes.");
            }
        }

        m_parent->getMap()->drawPath(pathResult.route);

        m_duration_info->setText(duration(pathResult.duration));
        m_distance_info->setText(distance(pathResult.distance));
        m_calculation_info->setText(QString::number(pathResult.calculation / 1000, 'g', 4) + " s");
    }

    void Panel::setShowGraph()
    {
        m_parent->getMap()->showGraph(m_street_graph->isChecked());
    }

    void Panel::setShowAttractions()
    {
        m_parent->getMap()->showNodes(m_show_attractions->isChecked());
    }

    void Panel::resetAttractions()
    {
        m_parent->getMap()->resetAttractions();
        m_attraction_slider->setValue(0);
    }

    void Panel::setAttractionNumber(int)
    {
        // Trigger the calculation only if at least three seconds have expired.
        if(std::chrono::duration_cast<Seconds>(Clock::now() - m_timer).count() > 3)
        {
            m_timer = Clock::now();
            // todo do action
        }
    }

    void Panel::setAttractionRange(int)
    {
        // Trigger the calculation only if at least three seconds have expired.
        if(std::chrono::duration_cast<Seconds>(Clock::now() - m_timer).count() > 3)
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

    void Panel::addAttraction(const int size)
    {
        m_attraction_slider->setValue(size);
    }

}  // namespace OSM
