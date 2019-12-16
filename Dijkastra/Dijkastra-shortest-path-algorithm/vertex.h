#ifndef VERTEX_H
#define VERTEX_H

#include <QPoint>
#include "block.h"

class Vertex : public Block {

    Q_OBJECT

public:
    Vertex(const QPoint &start, const std::string &name, QWidget *parent = nullptr);

    int getDistance() const { return this->distance; }

    void setDistance(int d) { distance = d; }

    int getLabel() { return label; }

    void setLabel(int l) { label = l; }

    Vertex* getPreviousV() { return previousV; }

    void setPreviousV(Vertex* v) { previousV = v; }

    QPoint getLocation() { return location; }

signals:
    void onDelete(Vertex*);

protected:
    void paintEvent(QPaintEvent *event) override;
    void rightClickAction() override;

private:
    int distance;

    int label;

    Vertex* previousV;

    QPoint location;

};

bool operator>(const Vertex& lhs, const Vertex& rhs);

#endif // VERTEX_H
