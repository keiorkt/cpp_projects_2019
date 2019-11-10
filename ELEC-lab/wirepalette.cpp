#include "wirepalette.h"

#include <QEvent>
#include <QPixmap>
#include <QPainter>
#include <QMouseEvent>

WirePalette::WirePalette(QLabel *templateLabel, Impl *hostImpl, QWidget *parent)
    : QLabel(parent),
      isPainting(false),
      hostImpl(hostImpl)
{
    setGeometry(templateLabel->geometry());
    setAutoFillBackground(false);
    setStyleSheet("QLabel { background-color : none; }");
    setVisible(false);
    setMouseTracking(true);
    installEventFilter(this);
}

bool
WirePalette::eventFilter(QObject *, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {

        QMouseEvent *e = static_cast<QMouseEvent*>(event);

        if (rect().contains(e->pos())
                && e->button() == Qt::LeftButton) {

            if (isPainting) {

                // Add this wire to circuit
                // TODO: toggle "isPainting"
                // TODO: add a wire by calling Impl::addWire
                isPainting = !isPainting;
                hostImpl->addWire(startPoint, currentPoint);
                setVisible(false);
                update();

            } else {

                startPoint = currentPoint = e->pos();
                isPainting = true;
                update();

            }

        }

    } else if (event->type() == QEvent::MouseMove && isPainting) {

        QMouseEvent *e = static_cast<QMouseEvent*>(event);
        // TODO: update "currentPoint"s
        currentPoint = e->pos();
        update();

    }

    return false;
}

void
WirePalette::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);

    if (isPainting) {
        QPainter painter(this);
        QColor color = Qt::green;
        color.setAlpha(150);
        QPen pen(color);


        pen.setWidth(10);
        painter.setPen(pen);
        painter.drawPoint(startPoint);

        QLineF line(startPoint, currentPoint);
        pen.setWidth(3);
        painter.setPen(pen);
        painter.drawLine(line);
    }
}
