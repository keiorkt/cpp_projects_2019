#ifndef EDGE_H
#define EDGE_H

#include <QPoint>
#include "block.h"
#include "vertex.h"

class Edge : public Block {

    Q_OBJECT

public:
    Edge(const QPoint &start, const QPoint &end, const int weight, Vertex* startV,
         Vertex* endV, const std::string &name, QWidget *parent = nullptr);

    int getWeight() { return weight; }

    void setWeight(int w) { weight = w > 0 ? w : 1; }

    Vertex* getStart() { return start; }

    Vertex* getEnd() { return end; }

signals:
    void onDelete(Edge*);

protected:
    void paintEvent(QPaintEvent *event) override;
    void rightClickAction() override;

private:
    int weight;

    Vertex* start;

    Vertex* end;
};

#endif // EDGE_H
