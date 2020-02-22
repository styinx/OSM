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
        using Clock    = std::chrono::system_clock;
        using Seconds    = std::chrono::seconds;

        enum class TransportType : Byte
        {
            Pedestrian      = 0,
            Bicycle         = 1,
            Car             = 2,
            PublicTransport = 3,
            Any             = 4
        };

        Window* m_parent;

        QSizePolicy m_min_policy;
        QSizePolicy m_expanding_policy;

        QLineEdit*   m_start;
        QLineEdit*   m_stop;
        QPushButton* m_go;

        QPushButton* m_car;
        QPushButton* m_bike;
        QPushButton* m_foot;
        QPushButton* m_public_transport;
        QCheckBox* m_street_graph;
        QSlider* m_attraction_slider;

        QTableWidget* m_table;

        QGridLayout* m_grid;
        QLabel*      m_label_start;
        QLabel*      m_label_stop;
        QLabel*      m_label_attraction;
        QLabel*      m_label_attraction_start;
        QLabel*      m_label_attraction_stop;

        Clock::time_point m_timer = Clock::now();

        void initTop();
        void initBottom();

    public slots:
        void go();
        void setShowGraph();
        void setAttractionRange();

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
        void setStart(const float lat, const float lon);
        void setStop(const float lat, const float lon);
    };

}  // namespace OSM

#endif  // OSM_PANEL_HPP
