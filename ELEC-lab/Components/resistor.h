#ifndef RESISTANCE_H
#define RESISTANCE_H

#include "Components/circuitcomponent.h"

class Resistor : public CircuitComponent
{
public:
    Resistor(const std::string &name, Impl *hostImpl, QWidget *parent = nullptr, double value = 1000);

    std::string getType() override;

protected:
    virtual void displayInfo() override;
};

#endif // RESISTANCE_H
