#ifndef BATTERY_H
#define BATTERY_H

#include "Components/circuitcomponent.h"

class Battery : public CircuitComponent
{
public:
    Battery(const std::string &name, Impl *hostImpl, QWidget *parent = nullptr, double voltage = 1.5);

    std::string getType() override;

protected:
    virtual void displayInfo() override;
};

#endif // BATTERY_H
