#include "circuitcomponent.h"

CircuitComponent::CircuitComponent(const std::string &name, Impl *hostImpl, QWidget *parent)
    : Block(name, hostImpl, parent),
      V(0), I(0), R(0)
{}

void
CircuitComponent::setV(double V_)
{
    V = V_;
    displayInfo();
}

void
CircuitComponent::setI(double I_)
{
    I = I_;
    displayInfo();
}

void
CircuitComponent::setR(double R_)
{
    R = R_;
    displayInfo();
}

double
CircuitComponent::getV()
{
    return V;
}

double
CircuitComponent::getI()
{
    return I;
}

double
CircuitComponent::getR()
{
    return R;
}


