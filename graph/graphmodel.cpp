#include "graphmodel.h"

#include <QDebug>

#include "spf/graph.h"

#include "client.h"

GraphModel::GraphModel(QObject* parent) : QObject{parent} {}

Client& GraphModel::client()
{
    if (async_) {
        static AsyncClient am{service_};
        am.setVertexModel(&vertexes_);
        am.setEdgeModel(&edges_);
        am.subscribe();
        return am;
    } else {
        static SyncClient sm{service_};
        sm.setVertexModel(&vertexes_);
        sm.setEdgeModel(&edges_);
        return sm;
    }
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
