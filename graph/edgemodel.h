#ifndef EDGEMODEL_H
#define EDGEMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QPointF>
#include <QString>
#include <QVariantMap>

#include <vector>

struct Vertex;

struct Edge {
    QVariantMap from;
    QVariantMap to;
    int weight;
    QString state{"new"};
};

class EdgeModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        FromRole = Qt::UserRole + 1,
        ToRole,
        WeightRole,
        StateRole
    };

    explicit EdgeModel(QObject* parent = nullptr);

    QModelIndex add(Edge const& edge);
    void ok(QModelIndex const& index);
    void error(QModelIndex const& index);
    void remove(int from, int to);
    void clear(int id);
    bool exists(int from, int to);
    void setPath(std::vector<int> const& path);

    bool removeRows(int row, int count, QModelIndex const& parent = QModelIndex()) override;

    int rowCount(QModelIndex const& parent = QModelIndex()) const override;
    QVariant data(QModelIndex const& index, int role = Qt::DisplayRole) const override;

protected:
    QHash<int, QByteArray> roleNames() const override;
private:
    QList<Edge> edges_;
};

#endif // EDGEMODEL_H
