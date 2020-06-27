#include "vertexmodel.h"

#include <algorithm>

VertexModel::VertexModel(QObject* parent)
    : QAbstractListModel{parent}
{
}

QModelIndex VertexModel::add(QPointF const& center)
{
    auto row = rowCount();
    beginInsertRows(QModelIndex(), row, row);
    vertexes_ << Vertex{row, center, "new"};
    endInsertRows();
    return createIndex(row, 0);
}

void VertexModel::ok(QModelIndex const& index, int id)
{
    auto& v = vertexes_[index.row()];
    v.id = id;
    v.state = "ready";
    emit dataChanged(index, index);
}

void VertexModel::error(QModelIndex const& index)
{
    vertexes_[index.row()].state = "error";
    emit dataChanged(index, index);
}

void VertexModel::remove(int id)
{
    auto it = std::find_if(vertexes_.begin(), vertexes_.end(),
                           [id](auto const& v) {
        return v.id == id;
    });
    if (it != vertexes_.end()) {
        int row = static_cast<int>(std::distance(vertexes_.begin(), it));
        removeRow(row);
    }
}

Vertex* VertexModel::get(int id)
{
    auto it = std::find_if(vertexes_.begin(), vertexes_.end(),
                           [id](auto const& v) {
        return v.id == id;
    });
    if (it != vertexes_.end()) {
        return &*it;
    }
    return nullptr;
}

int VertexModel::rowCount(QModelIndex const&) const
{
    return vertexes_.count();
}

QVariant VertexModel::data(QModelIndex const& index, int role) const
{
    if (index.row() < 0 || index.row() >= vertexes_.count())
        return QVariant();

    const auto& vertex = vertexes_[index.row()];
    if (role == IdRole)
        return vertex.id;
    else if (role == CenterRole)
        return vertex.center;
    else if (role == StateRole)
        return vertex.state;
    return QVariant();
}

QHash<int, QByteArray> VertexModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[CenterRole] = "center";
    roles[StateRole] = "state";
    return roles;
}

bool VertexModel::removeRows(int row, int count, QModelIndex const& parent)
{
    auto begin = vertexes_.begin() + row;
    auto end = begin + count;
    beginRemoveRows(parent, row, row + count - 1);
    vertexes_.erase(begin, end);
    endRemoveRows();
    return true;
}
