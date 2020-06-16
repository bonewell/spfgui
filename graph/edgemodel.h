#ifndef EDGEMODEL_H
#define EDGEMODEL_H

#include <QAbstractListModel>
#include <QColor>
#include <QList>
#include <QPointF>
#include <QVariantMap>

struct Vertex;

struct Edge {
    QVariantMap from;
    QVariantMap to;
    int weight;
    QColor color{"gray"};
};

class EdgeModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        FromRole = Qt::UserRole + 1,
        ToRole,
        WeightRole,
        ColorRole
    };

    explicit EdgeModel(QObject* parent = nullptr);

    void add(Edge const& edge);
    void remove(int from, int to);
    void clear(int id);

    bool removeRows(int row, int count, QModelIndex const& parent = QModelIndex()) override;

    int rowCount(QModelIndex const& parent = QModelIndex()) const override;
    QVariant data(QModelIndex const& index, int role = Qt::DisplayRole) const override;

protected:
    QHash<int, QByteArray> roleNames() const override;
private:
    QList<Edge> edges_;
};

#endif // EDGEMODEL_H
