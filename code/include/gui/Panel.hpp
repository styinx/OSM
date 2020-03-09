#ifndef OSM_PANEL_HPP
#define OSM_PANEL_HPP

#include "structures/Primitives.hpp"

#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableWidget>

namespace OSM
{
    class Window;

    class Panel final : public QSplitter
    {
        Q_OBJECT

    private:
        Window* m_parent;

        QSizePolicy m_min_policy;
        QSizePolicy m_expanding_policy;

        QGridLayout* m_grid;
        QLineEdit*   m_start;
        QLineEdit*   m_stop;
        QPushButton* m_go;
        QPushButton* m_car;
        QPushButton* m_bike;
        QPushButton* m_foot;
        QPushButton* m_public_transport;
        QPushButton* m_reset_attraction;
        QCheckBox*   m_street_graph;
        QCheckBox*   m_show_attractions;
        QSlider*     m_attraction_slider;
        QLabel*      m_label_config_info;
        QLabel*      m_label_start;
        QLabel*      m_label_stop;
        QLabel*      m_label_attraction;

        QGridLayout* m_info_grid;
        QLabel*      m_label_route_info;
        QLabel*      m_label_distance_info;
        QLabel*      m_distance_info;
        QLabel*      m_label_duration_info;
        QLabel*      m_duration_info;
        QLabel*      m_label_calculation;
        QLabel*      m_calculation_info;

        void           initTop();
        void           initBottom();
        TransportType  transportation();
        static QString duration(const float duration);
        static QString distance(const float distance);

    public slots:
        void go();
        void setShowGraph();
        void setShowAttractions();
        void resetAttractions();
        void setAttractionNumber(int);

    signals:
        void goPressed();

    public:
        explicit Panel(Window* parent);
        Panel(const Panel& other)     = delete;
        Panel(Panel&& other) noexcept = delete;
        Panel& operator=(const Panel& other) = delete;
        Panel& operator=(Panel&& other) noexcept = delete;
        virtual ~Panel()                         = default;

        void setStart(const float lat, const float lon);
        void setStop(const float lat, const float lon);
        void addAttraction(const int size);
    };

}  // namespace OSM

#endif  // OSM_PANEL_HPP
