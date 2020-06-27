#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>

#include "spf/graph.h"
#include "spf/web_socket_rpc.h"

class EdgeModel;
class VertexModel;

class Client : public QObject {
    Q_OBJECT
public:
    Client(spf::WebSocketRpc& service) : graph_{service} {}
    virtual ~Client() = default;
    virtual void addVertex(QPointF const& center) = 0;
    virtual void removeVertex(int id) = 0;
    virtual void addEdge(int from, int to, int weight) = 0;
    virtual void remodeEdge(int from, int to) = 0;

    void setEdgeModel(EdgeModel* edges) { edges_ = edges; }
    void setVertexModel(VertexModel* vertexes) { vertexes_ = vertexes; }

protected:
    spf::Graph graph_;
    EdgeModel* edges_{nullptr};
    VertexModel* vertexes_{nullptr};
};

class SyncClient : public Client {
    Q_OBJECT
public:
    using Client::Client;
    void addVertex(QPointF const& center) override;
    void removeVertex(int id) override;
    void addEdge(int from, int to, int weight) override;
    void remodeEdge(int from, int to) override;
};

class AsyncClient : public Client {
    Q_OBJECT
public:
    using Client::Client;
    void subscribe();
    void addVertex(QPointF const& center) override;
    void removeVertex(int id) override;
    void addEdge(int from, int to, int weight) override;
    void remodeEdge(int from, int to) override;

signals:
    void vertexRemoved(int id);
    void edgeRemoved(int from, int to);
};
#endif // CLIENT_H
