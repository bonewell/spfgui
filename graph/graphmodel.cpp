#include "graphmodel.h"

#include <QDebug>

#include "client.h"

GraphModel::GraphModel(QObject* parent) : QObject{parent} {}

GraphModel::~GraphModel() = default;

Client& GraphModel::client()
{
    // thread-unsafe
    if (!client_) {
        if (async_) {
            client_ = std::make_unique<AsyncClient>(host_, port_, *this);
        } else {
            client_ = std::make_unique<SyncClient>(host_, port_, *this);
        }
    }
    return *client_;
}

void GraphModel::addVertex(QPointF const& center)
{
    client().addVertex(center);
}

void GraphModel::removeVertex(int id)
{
    client().removeVertex(id);
}

void GraphModel::addEdge(int from, int to, int weight)
{
    client().addEdge(from, to, weight);
}

void GraphModel::removeEdge(int from, int to)
{
    client().remodeEdge(from, to);
}

void GraphModel::calculatePath(int from, int to)
{
    client().calculatePath(from, to);
}

bool GraphModel::exists(int from, int id)
{
    return edges_.exists(from, id);
}
