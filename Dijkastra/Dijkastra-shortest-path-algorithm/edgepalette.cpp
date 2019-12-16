#include "edgepalette.h"
#include "vertex.h"

#include <QEvent>
#include <QPixmap>
#include <QPainter>
#include <QMouseEvent>


EdgePalette::EdgePalette(QLabel *templateLabel, Graph* graph, QWidget *parent)
    : QLabel(parent),
      isPainting(false)
{
    setGeometry(templateLabel->geometry());
    setAutoFillBackground(false);
    setStyleSheet("QLabel { background-color : none; }");
    setVisible(false);
    setMouseTracking(true);
    installEventFilter(this);
    this->graph = graph;

}

bool EdgePalette::eventFilter(QObject *, QEvent *event) {
    if (event->type() == QEvent::MouseButtonPress) {

        QMouseEvent *e = static_cast<QMouseEvent*>(event);

        if (rect().contains(e->pos()) && e->button() == Qt::LeftButton && graph->isOnVertex(e->pos())) {

            if (isPainting) {
                // Add this wire to circuit
                isPainting = !isPainting;
                emit addEdge(startPoint, currentPoint, startVertex, endVertex);
                update();
            } else {
                startPoint = currentPoint = e->pos();
                startVertex = endVertex = graph->onVertex(startPoint);
                isPainting = true;
                update();
            }
        }

    } else if (event->type() == QEvent::MouseMove && isPainting) {
        QMouseEvent *e = static_cast<QMouseEvent*>(event);
        currentPoint = e->pos();
        endVertex = graph->onVertex(currentPoint);
        update();
    }

    return false;
}

void EdgePalette::paintEvent(QPaintEvent *event) {
    QLabel::paintEvent(event);

    if (isPainting) {
        QPainter painter(this);
        QColor color = Qt::black;
        color.setAlpha(150);
        QPen pen(color);

        pen.setWidth(3);
        painter.setPen(pen);
        painter.drawPoint(startPoint);

        QLineF line(startPoint, currentPoint);
        pen.setWidth(3);
        painter.setPen(pen);
        painter.drawLine(line);
    }
}
