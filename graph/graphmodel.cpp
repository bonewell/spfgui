#include "graphmodel.h"

#include <QDebug>

GraphModel::GraphModel(QObject* parent)
    : QObject{parent}
{
}

void GraphModel::addVertex(QPointF const& center)
{
    auto index = vertexes_.add(center);
    try {
        auto id = static_cast<int>(graph_.addVertex());
        vertexes_.ok(index, id);
    } catch(std::exception const& e) {
        qWarning() << e.what();
        vertexes_.error(index);
    }
}

void GraphModel::removeVertex(int id)
{
    try {
        graph_.removeVertex(static_cast<spf::Id>(id));
        edges_.clear(id);
        vertexes_.remove(id);
    } catch (std::exception const& e) {
        qWarning() << e.what();
    }
}

void GraphModel::addEdge(int from, int to, int weight)
{
    auto vfrom = vertexes_.get(from);
    auto vto = vertexes_.get(to);
    if (vfrom && vto) {
        QVariantMap mfrom{{"id", vfrom->id}, {"center", vfrom->center}};
        QVariantMap mto{{"id", vto->id}, {"center", vto->center}};
        auto index = edges_.add({mfrom, mto, weight});
        try {
            graph_.setEdge(static_cast<spf::Id>(vfrom->id),
                           static_cast<spf::Id>(vto->id), weight);
            graph_.setEdge(static_cast<spf::Id>(vto->id),
                           static_cast<spf::Id>(vfrom->id), weight);
            edges_.ok(index);
        } catch (std::exception const& e) {
            qWarning() << e.what();
            edges_.error(index);
        }
    } else {
        qDebug() << "no vertex:" << from << to;
    }
}

void GraphModel::removeEdge(int from, int to)
{
    try {
        graph_.removeEdge(static_cast<spf::Id>(from),
                          static_cast<spf::Id>(to));
        graph_.removeEdge(static_cast<spf::Id>(to),
                          static_cast<spf::Id>(from));
        edges_.remove(from, to);
    } catch (std::exception const& e) {
        qWarning() << e.what();
    }
}
