#include "client.h"

#include <QDebug>

#include "edgemodel.h"
#include "vertexmodel.h"

void AsyncClient::subscribe()
{
    connect(this, &AsyncClient::edgeRemoved, edges_, &EdgeModel::remove);
    connect(this, &AsyncClient::vertexRemoved, edges_, &EdgeModel::clear);
    connect(this, &AsyncClient::vertexRemoved, vertexes_, &VertexModel::remove);
}

void AsyncClient::addVertex(const QPointF &center)
{
    auto index = vertexes_->add(center);
    graph_.addVertex([this, index](auto id, auto error) {
        if (!error) {
            vertexes_->ok(index, static_cast<int>(id));
        } else {
            qWarning() << error.what();
            vertexes_->error(index);
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
    auto vfrom = vertexes_->get(from);
    auto vto = vertexes_->get(to);
    if (vfrom && vto) {
        QVariantMap mfrom{{"id", vfrom->id}, {"center", vfrom->center}};
        QVariantMap mto{{"id", vto->id}, {"center", vto->center}};
        auto index = edges_->add({mfrom, mto, weight});
        graph_.setEdge(static_cast<spf::Id>(from),
                       static_cast<spf::Id>(to), weight,
                       [this, index, from, to, weight](auto error) {
            if (!error) {
                graph_.setEdge(static_cast<spf::Id>(to),
                               static_cast<spf::Id>(from), weight,
                               [this, index](auto error) {
                    if (!error) {
                        edges_->ok(index);
                    } else {
                        qWarning() << error.what();
                        edges_->error(index);
                    }
                });
            } else {
                qWarning() << error.what();
                edges_->error(index);
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
    auto index = vertexes_->add(center);
    try {
        auto id = static_cast<int>(graph_.addVertex());
        vertexes_->ok(index, id);
    } catch(std::exception const& e) {
        qWarning() << e.what();
        vertexes_->error(index);
    }
}

void SyncClient::removeVertex(int id)
{
    try {
        graph_.removeVertex(static_cast<spf::Id>(id));
        edges_->clear(id);
        vertexes_->remove(id);
    } catch (std::exception const& e) {
        qWarning() << e.what();
    }
}

void SyncClient::addEdge(int from, int to, int weight)
{
    auto vfrom = vertexes_->get(from);
    auto vto = vertexes_->get(to);
    if (vfrom && vto) {
        QVariantMap mfrom{{"id", vfrom->id}, {"center", vfrom->center}};
        QVariantMap mto{{"id", vto->id}, {"center", vto->center}};
        auto index = edges_->add({mfrom, mto, weight});
        try {
            graph_.setEdge(static_cast<spf::Id>(from),
                           static_cast<spf::Id>(to), weight);
            graph_.setEdge(static_cast<spf::Id>(to),
                           static_cast<spf::Id>(from), weight);
            edges_->ok(index);
        } catch (std::exception const& e) {
            qWarning() << e.what();
            edges_->error(index);
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
        edges_->remove(from, to);
    } catch (std::exception const& e) {
        qWarning() << e.what();
    }
}
