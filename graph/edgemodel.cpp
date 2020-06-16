#include "edgemodel.h"

#include <algorithm>

EdgeModel::EdgeModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

void EdgeModel::add(Edge const& edge)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    edges_ << edge;
    endInsertRows();
}

void EdgeModel::remove(int from, int to)
{
    auto it = std::find_if(edges_.begin(), edges_.end(),
                           [from, to] (auto const& e) {
        return e.from["id"].toInt() == from && e.to["id"].toInt() == to;
    });
    if (it != edges_.end()) {
        int row = static_cast<int>(std::distance(edges_.begin(), it));
        removeRow(row);
    }
}

void EdgeModel::clear(int id)
{
    for (auto it = edges_.begin(); it != edges_.end();) {
        if (it = std::find_if(edges_.begin(), edges_.end(),
                [id](auto const& e) {
                    return e.from["id"].toInt() == id || e.to["id"].toInt() == id;
            }); it != edges_.end()) {
                int row = static_cast<int>(std::distance(edges_.begin(), it));
                removeRow(row);
        }
    }
}

int EdgeModel::rowCount(QModelIndex const&) const
{
    return edges_.count();
}

QVariant EdgeModel::data(QModelIndex const& index, int role) const
{
    if (index.row() < 0 || index.row() >= edges_.count())
        return QVariant();

    const auto& vertex = edges_[index.row()];
    if (role == FromRole)
        return vertex.from;
    else if (role == ToRole)
        return vertex.to;
    else if (role == WeightRole)
        return vertex.weight;
    else if (role == ColorRole)
        return vertex.color;
    return QVariant();
}

QHash<int, QByteArray> EdgeModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[FromRole] = "from";
    roles[ToRole] = "to";
    roles[WeightRole] = "weight";
    roles[ColorRole] = "color";
    return roles;
}

bool EdgeModel::removeRows(int row, int count, QModelIndex const& parent)
{
    auto begin = edges_.begin() + row;
    auto end = begin + count;
    beginRemoveRows(parent, row, row + count - 1);
    edges_.erase(begin, end);
    endRemoveRows();
    return true;
}
