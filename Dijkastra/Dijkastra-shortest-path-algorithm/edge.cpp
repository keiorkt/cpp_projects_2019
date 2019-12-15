#include "edge.h"

#include <cmath>
#include <QBitmap>
#include <QPainter>

Edge::Edge(const QPoint &start, const QPoint &end,
           const std::string &name, QWidget *parent)
    : Block(name, parent)
{
    QPoint lefttop;

    lefttop.setX(std::max(0, std::min(start.x(), end.x()) - 10));
    lefttop.setY(std::max(0, std::min(start.y(), end.y()) - 10));

    int width = abs(start.x() - end.x()) + 20;
    int height = abs(start.y() - end.y()) + 20;

    setGeometry(QRect(lefttop.x(), lefttop.y(), width, height));
    setPositive(start - lefttop);
    setNegative(end - lefttop);

    update();
}

void Edge::paintEvent(QPaintEvent *event) {
    // Call paint event of the base class
    QLabel::paintEvent(event);
    QPixmap image(size());

    image.fill(Qt::transparent);

    QPainter painter(&image);
    QColor color = Qt::black;
    color.setAlpha(150);
    QPen pen(color);

    pen.setWidth(3);
    painter.setPen(pen);
    painter.drawPoint(getPositive());
    painter.drawPoint(getNegative());

    QLineF line(getPositive(), getNegative());
    pen.setWidth(3);
    painter.setPen(pen);
    painter.drawLine(line);

    setPixmap(image);
    setMask(image.mask());
}
