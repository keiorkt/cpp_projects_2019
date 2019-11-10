#ifndef CIRCUITCOMPONENT_H
#define CIRCUITCOMPONENT_H

#include "impl.h"
#include "block.h"
#include "helper.h"

#include <string>
#include <QWidget>

// Circuit component which supports voltage / current measurement

class CircuitComponent : public Block
{
public:
    CircuitComponent(const std::string &name, Impl *hostImpl, QWidget *parent = nullptr);

    double getV();

    double getI();

    double getR();

    virtual void setV(double V_);

    virtual void setI(double I_);

    virtual void setR(double R_);

    virtual std::string getType() = 0;

private:
    double V; // voltage

    double I; // current

    double R; // resistance
};

#endif // CircuitComponent_H
