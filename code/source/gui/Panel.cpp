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

        m_attraction_slider = new QSlider(Qt::Orientation::Horizontal);

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
        QObject::connect(m_attraction_slider, &QSlider::valueChanged, this, &Panel::setAttractionNumber);
    }

    void Panel::initTop()
    {
        auto grid_wrapper = new QWidget{};
        m_grid            = new QGridLayout{grid_wrapper};

        m_label_start       = new QLabel{"From: "};
        m_label_stop        = new QLabel{"To: "};
        m_label_config_info = new QLabel{"<b>Configuration</b>"};
        m_label_attraction  = new QLabel{"Number of attraction: "};

        auto icon_wrapper = new QWidget();
        auto icon_box     = new QHBoxLayout(icon_wrapper);

        m_start->addAction(QIcon(":/icon_marker_blue"), QLineEdit::TrailingPosition);
        m_start->setPlaceholderText("lat,lon | start");
        m_stop->addAction(QIcon(":/icon_marker_red"), QLineEdit::TrailingPosition);
        m_stop->setPlaceholderText("lat,lon | stop");

        m_attraction_slider->setRange(0, 10);

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

        m_grid->addWidget(m_reset_attraction, row, 0);
        m_grid->addWidget(m_show_attractions, row, 1);

        // m_grid->addWidget(m_street_graph, row++, 1);

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
        m_label_route_type    = new QLabel("Search algorithm");
        m_route_type          = new QComboBox();

        m_route_type->addItems({"Dijkstra", "Bidirectional Dijkstra"});
        m_route_type->setCurrentIndex(1);

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
        m_info_grid->addWidget(m_label_route_type, row, 0);
        m_info_grid->addWidget(m_route_type, row++, 1);

        auto grid_filler2 = new QWidget();
        grid_filler2->setSizePolicy(m_expanding_policy);
        m_grid->addWidget(grid_filler2);

        addWidget(grid_wrapper);
    }

    TransportType Panel::transportation()
    {
        if(m_foot->isChecked())
        {
            return TransportType::FOOT;
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
        float hours = duration;
        if(hours < 1)
        {
            return QString::number(hours * 60, 'f', 2) + " min";
        }
        else
        {
            return QString::number(hours, 'f', 2) + " h";
        }
    }

    QString Panel::distance(const float distance)
    {
        float meters = distance;
        if(meters < 1000)
        {
            return QString::number(meters, 'f', 2) + " m";
        }
        else
        {
            return QString::number(meters / 1000, 'f', 2) + " km";
        }
    }

    void Panel::go()
    {
        auto start = m_start->text();
        auto stop  = m_stop->text();

        auto pathResult = m_parent->getMap()->calculatePath(
            start, stop, transportation(), m_route_type->currentIndex());

        if(pathResult.route.empty() || !pathResult.way_found)
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
                    "No way was found.<br>Make sure that the <b>start</b> and <b>stop</b> location "
                    "are near the road network or choose the <b>pedestrian</b> travel method which "
                    "can reach any node.");
            }
        }
        else
        {
            if(pathResult.uses_default)
            {
                QString which = pathResult.uses_default == 1 ? "the start node" : "end node";

                QMessageBox::information(
                    this,
                    "Warning",
                    "The path search uses a default value for <b>" + which +
                        "</b>.<br>Try to use different nodes that are close to roads or inside the "
                        "map range.");
            }
            else
            {
                using namespace std::chrono;
                auto t = system_clock::now();
                m_parent->getMap()->drawPath(pathResult.route);
                const auto drawing = duration_cast<milliseconds>(system_clock::now() - t).count();

                m_duration_info->setText(duration(pathResult.duration));
                m_distance_info->setText(distance(pathResult.distance));
                m_calculation_info->setText(
                    QString::number(static_cast<float>(pathResult.calculation) / 1000, 'f', 2) + " s (+" +
                    QString::number(static_cast<float>(drawing) / 1000, 'f', 2) + " s drawing)");
            }
        }
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
        const auto val         = static_cast<size_t>(m_attraction_slider->value());
        const auto attractions = m_parent->getMap()->numberOfAttractions();
        if(val > attractions)
        {
            m_attraction_slider->setValue(attractions);
            return;
        }

        if(val == 0)
        {
            m_parent->getMap()->resetAttractions();
        }
        else
        {
            m_parent->getMap()->setAttractions(val);
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

    void Panel::setAttraction(const int size)
    {
        m_attraction_slider->setValue(size);
    }

}  // namespace OSM
