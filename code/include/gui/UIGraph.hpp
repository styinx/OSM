#ifndef OSM_UIGRAPH_HPP
#define OSM_UIGRAPH_HPP

#include "NonCopyable.hpp"
#include "NonMoveable.hpp"
#include "structures/AdjacencyArray.hpp"

#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QObject>

namespace OSM
{

    class UIGraph final
        : public QObject
        , public NonCopyable
        , public NonMoveable
    {
        Q_OBJECT
        Q_PROPERTY(QJsonArray motorway MEMBER m_motorway)
    private:
        const AdjacencyArray* m_array;
        QJsonArray m_motorway;

    public slots:
        QJsonArray buildNetwork(const std::string street_type);

    public:
        explicit UIGraph(const AdjacencyArray* array);
        virtual ~UIGraph() = default;

        void buildMotorway() {m_motorway = buildNetwork("motorway");}
    };

}  // namespace OSM

#endif  // OSM_UIGRAPH_HPP
