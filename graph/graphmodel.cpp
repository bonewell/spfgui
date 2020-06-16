#include "graphmodel.h"

#include <QDebug>

GraphModel::GraphModel(QObject* parent)
    : QObject{parent}
{
}

void GraphModel::addVertex(const QPointF &p)
{
    static int id = 0;
    vertexes_.add({++id, p});
}

void GraphModel::removeVertex(int id)
{
    edges_.clear(id);
    vertexes_.remove(id);
}

void GraphModel::addEdge(int from, int to, int weight)
{
    auto vfrom = vertexes_.get(from);
    auto vto = vertexes_.get(to);
    if (vfrom && vto) {
        QVariantMap mfrom{{"id", vfrom->id}, {"center", vfrom->center}};
        QVariantMap mto{{"id", vto->id}, {"center", vto->center}};
        edges_.add({mfrom, mto, weight});
    } else {
        qDebug() << "no vertex:" << from << to;
    }
}

void GraphModel::removeEdge(int from, int to)
{
    edges_.remove(from, to);
}
