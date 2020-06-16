#ifndef VERTEXMODEL_H
#define VERTEXMODEL_H

#include <QAbstractListModel>
#include <QColor>
#include <QList>
#include <QPointF>

struct Vertex {
    int id;
    QPointF center;
    QColor color{"gray"};
};

class VertexModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        IdRole = Qt::UserRole + 1,
        CenterRole,
        ColorRole
    };

    explicit VertexModel(QObject* parent = nullptr);

    void add(Vertex const& vertex);
    void remove(int id);
    Vertex const* get(int id) const;

    bool removeRows(int row, int count, QModelIndex const& parent = QModelIndex()) override;

    int rowCount(QModelIndex const& parent = QModelIndex()) const override;
    QVariant data(QModelIndex const& index, int role = Qt::DisplayRole) const override;

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<Vertex> vertexes_;
};

#endif // VERTEXMODEL_H
