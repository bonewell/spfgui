#ifndef VERTEXMODEL_H
#define VERTEXMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QPointF>
#include <QString>

struct Vertex {
    int id;
    QPointF center;
    QString state;
};

class VertexModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        IdRole = Qt::UserRole + 1,
        CenterRole,
        StateRole
    };

    explicit VertexModel(QObject* parent = nullptr);

    QModelIndex add(QPointF const& center);
    void ok(QModelIndex const& index, int id);
    void error(QModelIndex const& index);
    void remove(int id);
    Vertex* get(int id);

    bool removeRows(int row, int count, QModelIndex const& parent = QModelIndex()) override;

    int rowCount(QModelIndex const& parent = QModelIndex()) const override;
    QVariant data(QModelIndex const& index, int role = Qt::DisplayRole) const override;

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<Vertex> vertexes_;
};

#endif // VERTEXMODEL_H
