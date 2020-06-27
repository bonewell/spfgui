#include "edgemodel.h"

#include <algorithm>
#include <unordered_map>

EdgeModel::EdgeModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

QModelIndex EdgeModel::add(Edge const& edge)
{
    auto row = rowCount();
    beginInsertRows(QModelIndex(), row, row);
    edges_ << edge;
    endInsertRows();
    return createIndex(row, 0);
}

void EdgeModel::ok(QModelIndex const& index)
{
    edges_[index.row()].state = "ready";
    emit dataChanged(index, index);
}

void EdgeModel::error(QModelIndex const& index)
{
    edges_[index.row()].state = "error";
    emit dataChanged(index, index);
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

bool EdgeModel::exists(int from, int to)
{
    auto it = std::find_if(edges_.begin(), edges_.end(),
                           [from, to] (auto const& e) {
        return (e.from["id"].toInt() == from && e.to["id"].toInt() == to)
                || (e.from["id"].toInt() == to && e.to["id"].toInt() == from);
    });
    return it != edges_.end();
}

void EdgeModel::setPath(std::vector<int> const& path)
{
    std::unordered_multimap<int, int> ids;
    for (size_t i = 1; i < path.size(); ++i) {
        ids.emplace(path[i - 1], path[i]);
        ids.emplace(path[i], path[i - 1]);
    }
    for (auto i = 0; i < edges_.count(); ++i) {
        auto from = ids.equal_range(edges_[i].from["id"].toInt());
        auto to = edges_[i].to["id"].toInt();
        auto found = std::find_if(from.first, from.second, [to](auto const& p) {
            return p.second == to;
        });
        if (found != from.second) {
            edges_[i].state = "path";
            auto index = createIndex(i, 0);
            emit dataChanged(index, index);
        } else if (edges_[i].state == "path") {
            edges_[i].state = "ready";
            auto index = createIndex(i, 0);
            emit dataChanged(index, index);
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
    else if (role == StateRole)
        return vertex.state;
    return QVariant();
}

QHash<int, QByteArray> EdgeModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[FromRole] = "from";
    roles[ToRole] = "to";
    roles[WeightRole] = "weight";
    roles[StateRole] = "state";
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
