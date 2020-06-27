#include "client.h"

#include <QDebug>

#include "graphmodel.h"
#include "edgemodel.h"
#include "vertexmodel.h"

AsyncClient::AsyncClient(const QString &host, unsigned short port, GraphModel &model)
    : Client(host, port, model)
{
    connect(this, &AsyncClient::edgeRemoved, model_.getEdges(), &EdgeModel::remove);
    connect(this, &AsyncClient::vertexRemoved, model_.getEdges(), &EdgeModel::clear);
    connect(this, &AsyncClient::vertexRemoved, model_.getVertexes(), &VertexModel::remove);
}

void AsyncClient::addVertex(const QPointF &center)
{
    auto index = model_.getVertexes()->add(center);
    graph_.addVertex([this, index](auto id, auto error) {
        if (!error) {
            model_.getVertexes()->ok(index, static_cast<int>(id));
        } else {
            qWarning() << error.what();
            model_.getVertexes()->error(index);
        }
    });
}

void AsyncClient::removeVertex(int id)
{
    graph_.removeVertex(static_cast<spf::Id>(id), [this, id](auto error) {
        if (!error) {
            emit vertexRemoved(id);
        } else {
            qWarning() << error.what();
        }
    });
}

void AsyncClient::addEdge(int from, int to, int weight)
{
    auto vfrom = model_.getVertexes()->get(from);
    auto vto = model_.getVertexes()->get(to);
    if (vfrom && vto) {
        QVariantMap mfrom{{"id", vfrom->id}, {"center", vfrom->center}};
        QVariantMap mto{{"id", vto->id}, {"center", vto->center}};
        auto index = model_.getEdges()->add({mfrom, mto, weight});
        graph_.setEdge(static_cast<spf::Id>(from),
                       static_cast<spf::Id>(to), weight,
                       [this, index, from, to, weight](auto error) {
            if (!error) {
                graph_.setEdge(static_cast<spf::Id>(to),
                               static_cast<spf::Id>(from), weight,
                               [this, index](auto error) {
                    if (!error) {
                        model_.getEdges()->ok(index);
                    } else {
                        qWarning() << error.what();
                        model_.getEdges()->error(index);
                    }
                });
            } else {
                qWarning() << error.what();
                model_.getEdges()->error(index);
            }
        });
    } else {
        qDebug() << "no vertex:" << from << to;
    }
}

void AsyncClient::remodeEdge(int from, int to)
{
    graph_.removeEdge(static_cast<spf::Id>(from),
                      static_cast<spf::Id>(to),
                      [this, from, to](auto error) {
        if (!error) {
            graph_.removeEdge(static_cast<spf::Id>(to),
                              static_cast<spf::Id>(from),
                              [this, from, to](auto error) {
                if (!error) {
                    emit edgeRemoved(from, to);
                } else {
                    qWarning() << error.what();
                }
            });
        } else {
            qWarning() << error.what();
        }
    });
}

void SyncClient::addVertex(const QPointF &center)
{
    auto index = model_.getVertexes()->add(center);
    try {
        auto id = static_cast<int>(graph_.addVertex());
        model_.getVertexes()->ok(index, id);
    } catch(std::exception const& e) {
        qWarning() << e.what();
        model_.getVertexes()->error(index);
    }
}

void SyncClient::removeVertex(int id)
{
    try {
        graph_.removeVertex(static_cast<spf::Id>(id));
        model_.getEdges()->clear(id);
        model_.getVertexes()->remove(id);
    } catch (std::exception const& e) {
        qWarning() << e.what();
    }
}

void SyncClient::addEdge(int from, int to, int weight)
{
    auto vfrom = model_.getVertexes()->get(from);
    auto vto = model_.getVertexes()->get(to);
    if (vfrom && vto) {
        QVariantMap mfrom{{"id", vfrom->id}, {"center", vfrom->center}};
        QVariantMap mto{{"id", vto->id}, {"center", vto->center}};
        auto index = model_.getEdges()->add({mfrom, mto, weight});
        try {
            graph_.setEdge(static_cast<spf::Id>(from),
                           static_cast<spf::Id>(to), weight);
            graph_.setEdge(static_cast<spf::Id>(to),
                           static_cast<spf::Id>(from), weight);
            model_.getEdges()->ok(index);
        } catch (std::exception const& e) {
            qWarning() << e.what();
            model_.getEdges()->error(index);
        }
    } else {
        qDebug() << "no vertex:" << from << to;
    }
}

void SyncClient::remodeEdge(int from, int to)
{
    try {
        graph_.removeEdge(static_cast<spf::Id>(from),
                          static_cast<spf::Id>(to));
        graph_.removeEdge(static_cast<spf::Id>(to),
                          static_cast<spf::Id>(from));
        model_.getEdges()->remove(from, to);
    } catch (std::exception const& e) {
        qWarning() << e.what();
    }
}
