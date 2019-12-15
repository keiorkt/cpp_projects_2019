#ifndef GRAPH_H
#define GRAPH_H

#include <QHash>
#include <QString>
#include <QVector>
#include <QList>
#include <queue>
#include "vertex.h"
#include "edge.h"

class Graph {

public:
    Graph();

    ~Graph();

    std::priority_queue<Vertex, std::vector<Vertex>, std::less<Vertex> > p_queue;

    int getMaxLabel();

    void addEdge(Edge* a);

    void removeEdge(Edge* a);

    void removeVertex(Vertex* a);

    void addVertex(Vertex* a);

    void setSource(Vertex* s) { source = s; }

    void insertUV(Vertex* v);

    QList<Vertex*> getAllVertex();

    bool isOnVertex(QPoint);

    Vertex* onVertex(QPoint p);

private:
    QVector<QList<Vertex*> > adj; // data structure to store adjacecncy list

    QMap<int, QList<Edge*> > edg; // data structure to store weights

    Vertex* source;

    Vertex* current_vertex;

    void addEdge(Vertex* a, Vertex* b);

    void removeEdge(Vertex* a, Vertex* b);

    QHash<int, Vertex*> uv;

};

#endif // GRAPH_H
