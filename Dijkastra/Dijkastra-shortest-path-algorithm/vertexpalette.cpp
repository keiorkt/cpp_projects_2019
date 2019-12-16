#include "vertexpalette.h"

#include <QEvent>
#include <QPixmap>
#include <QPainter>
#include <QMouseEvent>

VertexPalette::VertexPalette(QLabel *templateLabel, QWidget *parent)
    : QLabel(parent),
      isPainting(false)
{
    setGeometry(templateLabel->geometry());
    setAutoFillBackground(false);
    setStyleSheet("QLabel { background-color : none; }");
    setVisible(false);
    setMouseTracking(true);
    installEventFilter(this);
}

bool VertexPalette::eventFilter(QObject *, QEvent *event) {
    if (event->type() == QEvent::MouseButtonPress) {

        QMouseEvent *e = static_cast<QMouseEvent*>(event);

        if (rect().contains(e->pos()) && e->button() == Qt::LeftButton) {

            startPoint = e->pos();
            emit this->addVertex(startPoint);
            update();

        }

    }

    return false;
}

void VertexPalette::paintEvent(QPaintEvent *event) {
    QLabel::paintEvent(event);

    if (isPainting) {
        QPainter painter(this);
        QColor color = Qt::gray;
        color.setAlpha(150);
        QPen pen(color);

        pen.setWidth(10);
        painter.setPen(pen);
        painter.drawEllipse(startPoint, 5, 5);
        painter.setFont(QFont("Arial", 10));
        painter.drawText(startPoint, "11");

    }
}
