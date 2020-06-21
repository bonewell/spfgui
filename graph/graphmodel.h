#ifndef GRAPHMODEL_H
#define GRAPHMODEL_H

#include <QObject>

#include "spf/graph.h"
#include "spf/web_socket_rpc.h"

#include "edgemodel.h"
#include "vertexmodel.h"

class GraphModel : public QObject
{
    Q_OBJECT

public:
    explicit GraphModel(QObject* parent = nullptr);

    Q_PROPERTY(EdgeModel* edges READ getEdges CONSTANT)
    Q_PROPERTY(VertexModel* vertexes READ getVertexes CONSTANT)

    Q_INVOKABLE void addVertex(QPointF const& center);
    Q_INVOKABLE void removeVertex(int id);
    Q_INVOKABLE void addEdge(int from, int to, int weight);
    Q_INVOKABLE void removeEdge(int from, int to);

private:
    EdgeModel* getEdges() { return &edges_; }
    VertexModel* getVertexes() { return &vertexes_; }

    EdgeModel edges_;
    VertexModel vertexes_;

    spf::WebSocketRpc service_{"localhost", 8080};
    spf::Graph graph_{service_};
};

#endif // GRAPHMODEL_H
