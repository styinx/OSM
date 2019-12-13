#ifndef OSM_UIGRAPH_HPP
#define OSM_UIGRAPH_HPP

#include "NonCopyable.hpp"
#include "NonMoveable.hpp"
#include "structures/AdjacencyArray.hpp"

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
        Q_PROPERTY(QJsonObject motorway MEMBER m_motorway)
    private:
        const AdjacencyArray* m_array;
        QJsonObject m_motorway;

    public slots:
        void buildNetwork(const EdgeTypeMask street_type);

    public:
        explicit UIGraph(const AdjacencyArray* array);
        virtual ~UIGraph() = default;
    };

}  // namespace OSM

#endif  // OSM_UIGRAPH_HPP
