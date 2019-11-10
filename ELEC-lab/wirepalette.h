#ifndef WIREPALETTE_H
#define WIREPALETTE_H

#include "impl.h"

#include <QLabel>
#include <QPoint>
#include <QPushButton>

class WirePalette : public QLabel
{
public:
    WirePalette(QLabel *templateLabel,
                Impl *hostImpl,
                QWidget *parent = nullptr);

protected slots:
    bool eventFilter(QObject *, QEvent *event) override;

    void paintEvent(QPaintEvent *event) override;

private:
    bool isPainting;

    QPoint startPoint;

    QPoint currentPoint;

    // To call addWire function
    Impl *hostImpl;
};

#endif // WIREPALETTE_H
