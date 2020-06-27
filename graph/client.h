#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>

#include "spf/graph.h"
#include "spf/web_socket_rpc.h"

class GraphModel;

class Client : public QObject {
    Q_OBJECT
public:
    Client(QString const& host, unsigned short port, GraphModel& model)
        : service_{new spf::WebSocketRpc{host.toStdString(), port}},
          graph_{*service_}, model_{model} {}

    virtual ~Client() = default;
    virtual void addVertex(QPointF const& center) = 0;
    virtual void removeVertex(int id) = 0;
    virtual void addEdge(int from, int to, int weight) = 0;
    virtual void remodeEdge(int from, int to) = 0;

protected:
    std::unique_ptr<spf::WebSocketRpc> service_;
    spf::Graph graph_;
    GraphModel& model_;
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
    AsyncClient(QString const& host, unsigned short port, GraphModel& model);
    void addVertex(QPointF const& center) override;
    void removeVertex(int id) override;
    void addEdge(int from, int to, int weight) override;
    void remodeEdge(int from, int to) override;

signals:
    void vertexRemoved(int id);
    void edgeRemoved(int from, int to);
};
#endif // CLIENT_H
