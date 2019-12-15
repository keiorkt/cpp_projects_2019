#include "graph.h"
#include <QRect>

//QHash<QString, Vertex> unvisited_vertices;

Graph::Graph() {
    uv.reserve(10000);
}

bool operator>(const Vertex& lhs, const Vertex& rhs) {
    return lhs.getDistance() > rhs.getDistance();
}

// vector and list
void Graph::insertUV(Vertex* v) {
    uv[v->getLabel() % uv.capacity()] = v;
}


void Graph::addEdge(Edge* a) {
    edg[a->getStart()->getLabel()].append(a);
    addEdge(a->getStart(), a->getEnd());
}

void Graph::addEdge(Vertex* a, Vertex* b) {
    for (int i = 0; i < adj.size(); ++i) {
        if (adj[i].front()->getLabel() == a->getLabel()) {
            adj[i].push_back(b);
        }
        else if (adj[i].front()->getLabel() == b->getLabel()) {
            adj[i].push_back(a);
        }
    }
}

void Graph::removeEdge(Edge* a) {
    edg.remove(a->getStart()->getLabel());
    removeEdge(a->getStart(), a->getEnd());
}

void Graph::removeEdge(Vertex* a, Vertex* b) {
    for (int i = 0; i < adj.size(); ++i) {
        if (adj[i].front()->getLabel() == a->getLabel()) {
            adj[i].removeOne(b);
        }
        else if (adj[i].front()->getLabel() == b->getLabel()) {
            adj[i].removeOne(a);
        }
    }
}

void Graph::addVertex(Vertex* a) {
    a->setLabel(getMaxLabel() + 1);
    adj.resize(adj.size() + 1);
    adj[adj.size()-1].push_back(a);
}

void Graph::removeVertex(Vertex* a) {
    for (int i = 0; i < adj.size(); ++i) {
        for (int j = 0; j < adj[i].size(); ++j) {
            if (adj[i][j]->getLabel() == a->getLabel()) {
                adj[i].removeAt(j);
            }
        }
    }

    for (int i = 0; i < adj.size(); ++i) {
        if (adj[i].front()->getLabel() == a->getLabel()) {
          adj.removeAt(i);
          adj.resize(adj.size()-1);
        }
    }
}

int Graph::getMaxLabel() {
    if (adj.empty()) {
        return -1;
    } else {
        return adj.back().front()->getLabel();
    }
}

bool Graph::isOnVertex(QPoint p) {
    for (int i = 0; i < adj.size(); ++i) {
        QPoint vpoint = adj[i].front()->getPositive();
        QRect r = QRect(QPoint(vpoint.x()+5, vpoint.y()+5), QPoint(vpoint.x()-5, vpoint.y()-5));
        if (r.contains(p)) {
            return true;
        }
    }

    return false;
}

Vertex* Graph::onVertex(QPoint p) {
    for (int i = 0; i < adj.size(); ++i) {
        QPoint vpoint = adj[i].front()->getPositive();
        QRect r = QRect(QPoint(vpoint.x()+5, vpoint.y()+5), QPoint(vpoint.x()-5, vpoint.y()-5));
        if (r.contains(p)) {
            return adj[i].front();
        }
    }

    return nullptr;
}

