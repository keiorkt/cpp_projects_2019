#include <QEvent>
#include <QLabel>
#include <QBitmap>
#include <QPixmap>
#include <QPainter>
#include <QMouseEvent>

#include <QDebug>

#include <string>

#include "block.h"

Block::Block(const std::string &name, QWidget *parent)
    : QLabel(parent),
      text(""),
      name(name),
      start({100,100}),
      end({150, 100})
{
    setStyleSheet("border : none");
    setStyleSheet("background-color : none");
    setAutoFillBackground(false);
    setGeometry(QRect(20, 20, 150, 80));
    setVisible(true);
    installEventFilter(this);
}

std::string Block::getName() {
    return name;
}

QPoint Block::getPositive()
{
    return start;
}

QPoint Block::getNegative()
{
    return end;
}


void Block::setPositive(const QPoint &start)
{
    this->start = start;
}

void Block::setNegative(const QPoint &end)
{
    this->end = end;
}

bool Block::eventFilter(QObject *watched, QEvent *event) {
    static QPoint lastPoint;
    static bool isHover = false;

    if (event->type() == QEvent::MouseButtonPress) {

        QMouseEvent *e = static_cast<QMouseEvent*>(event);

        if (rect().contains(e->pos())
                && e->button() == Qt::LeftButton) {
            lastPoint = e->pos();
            isHover = true;
        }

        // call right click action
        if (rect().contains(e->pos())
                && e->button() == Qt::RightButton) {
            rightClickAction();
        }


    } else if (event->type() == QEvent::MouseMove && isHover) {

        QMouseEvent *e = static_cast<QMouseEvent*>(event);

        int dx = e->pos().x() - lastPoint.x();
        int dy = e->pos().y() - lastPoint.y();
        int new_x = x() + dx;
        int new_y = y() + dy;

        move(new_x, new_y);

    } else if (event->type() == QEvent::MouseButtonRelease && isHover) {

        isHover = !isHover;
//        hostImpl->checkConnection();
    }

    return false;
}

void Block::rightClickAction() {
    // delete component
    this->deleteLater();
}

void Block::paintEvent(QPaintEvent *event) {
    // Call paint event of the base class
    QLabel::paintEvent(event);
}

