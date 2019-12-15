#ifndef VERTEX_H
#define VERTEX_H

#include <QPoint>
#include "block.h"

class Vertex : public Block {

public:
    Vertex(const QPoint &start, const std::string &name, QWidget *parent = nullptr);

    int getDistance() const { return this->distance; }

    void setDistance(int d) { distance = d; }

    int getLabel() { return label; }

    void setLabel(int l) { label = l; }

    Vertex* getPreviousV() { return previousV; }

    void setPreviousV(Vertex* v) { previousV = v; }

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int distance;

    int label;

    Vertex* previousV;
};

bool operator>(const Vertex& lhs, const Vertex& rhs);

#endif // VERTEX_H
