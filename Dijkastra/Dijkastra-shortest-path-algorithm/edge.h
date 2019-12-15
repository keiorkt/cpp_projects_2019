#ifndef EDGE_H
#define EDGE_H

#include <QPoint>
#include "block.h"
#include "vertex.h"

class Edge : public Block {

public:
    Edge(const QPoint &start, const QPoint &end,
             const std::string &name, QWidget *parent = nullptr);

    int getWeight() { return weight; }

    void setWeight(int w) { weight = w > 0 ? w : 1; }

    Vertex* getStart() { return start; }

    Vertex* getEnd() { return end; }

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int weight;

    Vertex* start{nullptr};

    Vertex* end{nullptr};
};

#endif // EDGE_H
