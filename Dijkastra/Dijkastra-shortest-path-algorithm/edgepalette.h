#ifndef EDGEPALETTE_H
#define EDGEPALETTE_H

#include <QLabel>
#include <QPoint>
#include <QPushButton>
#include "graph.h"
#include "vertex.h"

class EdgePalette : public QLabel {
    Q_OBJECT

public:
    EdgePalette(QLabel *templateLabel, Graph* graph,
            QWidget *parent = nullptr);

signals:
    void addEdge(QPoint, QPoint, Vertex*, Vertex*);

protected slots:
    bool eventFilter(QObject *, QEvent *event) override;

    void paintEvent(QPaintEvent *event) override;

private:
    Graph* graph;

    bool isPainting;

    QPoint startPoint;

    QPoint currentPoint;

    Vertex* startVertex;

    Vertex* endVertex;

    bool onVertex(QPoint);
};


#endif // EDGEPALETTE_H
