#ifndef GRAPHMODEL_H
#define GRAPHMODEL_H

#include <QObject>
#include <QString>

#include <memory>

#include "edgemodel.h"
#include "vertexmodel.h"

class Client;

class GraphModel : public QObject
{
    Q_OBJECT

public:
    explicit GraphModel(QObject* parent = nullptr);
    ~GraphModel();

    Q_PROPERTY(QString host MEMBER host_)
    Q_PROPERTY(int port MEMBER port_)
    Q_PROPERTY(bool async MEMBER async_)
    Q_PROPERTY(EdgeModel* edges READ getEdges CONSTANT)
    Q_PROPERTY(VertexModel* vertexes READ getVertexes CONSTANT)

    Q_INVOKABLE void addVertex(QPointF const& center);
    Q_INVOKABLE void removeVertex(int id);
    Q_INVOKABLE void addEdge(int from, int to, int weight);
    Q_INVOKABLE void removeEdge(int from, int to);
    Q_INVOKABLE void calculatePath(int from, int to);
    Q_INVOKABLE bool exists(int from, int id);

    EdgeModel* getEdges() { return &edges_; }
    VertexModel* getVertexes() { return &vertexes_; }

private:
    Client& client();

    EdgeModel edges_;
    VertexModel vertexes_;

    QString host_{"localhost"};
    unsigned short port_{8080};
    bool async_{false};

    std::unique_ptr<Client> client_{nullptr};
};

#endif // GRAPHMODEL_H
