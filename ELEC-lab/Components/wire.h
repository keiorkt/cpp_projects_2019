#ifndef WIRE_H
#define WIRE_H

#include "Components/circuitcomponent.h"

#include <QPoint>

class Wire : public CircuitComponent
{
public:
    Wire(const QPoint &start, const QPoint &end,
         const std::string &name, Impl *hostImpl, QWidget *parent = nullptr);

    std::string getType() override;

protected:
    virtual void displayInfo() override;

    void paintEvent(QPaintEvent *event) override;
};

#endif // WIRE_H
