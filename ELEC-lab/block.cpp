#include <QEvent>
#include <QLabel>
#include <QBitmap>
#include <QPixmap>
#include <QPainter>
#include <QMouseEvent>

#include <QDebug>

#include <string>

#include "block.h"

Block::Block(const std::string &name, Impl *hostImpl, QWidget *parent)
    : QLabel(parent),
      imagePath(""),
      text(""),
      name(name),
      hostImpl(hostImpl),
      start({14, 40}),
      end({137, 40})
{
    setStyleSheet("border : none");
    setStyleSheet("background-color : none");
    setAutoFillBackground(false);
    setGeometry(QRect(20, 20, 150, 80));
    setVisible(true);
    installEventFilter(this);
}

QPoint
Block::getPositive()
{
    return start;
}

QPoint
Block::getNegative()
{
    return end;
}

QPoint
Block::getTerminal(int polar)
{
    if (polar == 0) {
        return this->pos() + start;
    } else {
        return this->pos() + end;
    }
}

void
Block::setPositive(const QPoint &start)
{
    this->start = start;
}

void
Block::setNegative(const QPoint &end)
{
    this->end = end;
}

//void
//Block::updateDisplay()
//{
//    displayInfo();
//}

std::string
Block::getName()
{
    return name;
}

bool
Block::eventFilter(QObject *, QEvent *event)
{
    static QPoint lastPoint;
    static bool isHover = false;

    if (event->type() == QEvent::MouseButtonPress) {

        QMouseEvent *e = static_cast<QMouseEvent*>(event);

        if (rect().contains(e->pos())
                && e->button() == Qt::LeftButton) {
            lastPoint = e->pos();
            isHover = true;
        }

        // TODO: If the click position is inside the rectangle area and the right button is clicked,
        // call right click action
        if (rect().contains(e->pos())
                && e->button() == Qt::RightButton) {
            rightClickAction();
        }


    } else if (event->type() == QEvent::MouseMove && isHover) {

        QMouseEvent *e = static_cast<QMouseEvent*>(event);

        int dx = e->pos().x() - lastPoint.x();
        // TODO: get the change of y coordinate "dy"
        int dy = e->pos().y() - lastPoint.y();
        int new_x = x() + dx;
        int new_y = y() + dy; // TODO: get the new y coordinate "new_y"

        move(new_x, new_y);

    } else if (event->type() == QEvent::MouseButtonRelease && isHover) {

        // TODO: toggle "isHover"
        // TODO: check connection by calling Impl::checkConnection
        isHover = !isHover;
        hostImpl->checkConnection();
    }

    return false;
}

void
Block::setImage(std::string path)
{
    this->imagePath = path;
    update();
}

void
Block::display(std::string text)
{
    this->text = text;
    update();
}

bool
Block::needDisplay()
{
    return hostImpl->needDisplay();
}

void
Block::rightClickAction()
{
    // TODO: delete this component by calling Impl::deleteComponent
    hostImpl->deleteComponent(name);
}

void
Block::paintEvent(QPaintEvent *event)
{
    // Call paint event of the base class
    QLabel::paintEvent(event);

    QImage image(imagePath.c_str());
    QPainter p(&image);

    p.setPen(QPen(Qt::red));
    p.setFont(QFont("Arial", 12, QFont::Bold));
    p.drawText(image.rect(), Qt::AlignTop, text.c_str());

    setPixmap(QPixmap::fromImage(image));
    setMask(QPixmap::fromImage(image).mask());
}
