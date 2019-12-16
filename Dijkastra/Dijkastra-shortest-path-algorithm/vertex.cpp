#include "vertex.h"

#include <cmath>
#include <QBitmap>
#include <QPainter>
#include <QString>

Vertex::Vertex(const QPoint &start, const std::string &name, QWidget *parent)
    : Block(name, parent), location(start)
{
    QPoint lefttop;

    lefttop.setX(std::max(0, std::min(start.x(), start.x()) - 10));
    lefttop.setY(std::max(0, std::min(start.y(), start.y()) - 10));

    int width = abs(start.x() - start.x()) + 20;
    int height = abs(start.y() - start.y()) + 20;

    setGeometry(QRect(lefttop.x(), lefttop.y(), width, height));
    setPositive(start - lefttop);

    update();
}

void Vertex::rightClickAction() {
    emit onDelete(this);
    this->deleteLater();
}

void Vertex::paintEvent(QPaintEvent *event) {
    // Call paint event of the base class
    QLabel::paintEvent(event);
    QPixmap image(size());

    image.fill(Qt::transparent);

    QPainter painter(&image);
    QColor color = Qt::gray;
    color.setAlpha(150);
    QPen pen(color);

    pen.setWidth(10);
    painter.setPen(pen);

    QString text = "";

    QPoint textLoc = getPositive();
    textLoc.setX(textLoc.x() - (text.length() == 1 ? 3 : 5));
    textLoc.setY(textLoc.y() + 4);

    painter.drawEllipse(getPositive(), 5, 5);

    QPen blackPen(Qt::black);
    painter.setPen(blackPen);
    painter.setFont(QFont("Arial", 10));
    painter.drawText(textLoc, text);

    setPixmap(image);
    setMask(image.mask());
}
