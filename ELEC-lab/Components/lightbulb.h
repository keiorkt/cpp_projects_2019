#ifndef LIGHTBULB_H
#define LIGHTBULB_H

#include "Components/circuitcomponent.h"

class LightBulb : public CircuitComponent
{
public:
    LightBulb(const std::string &name, Impl *hostImpl, QWidget *parent = nullptr);

    std::string getType() override;

    void setI(double I_) override;

protected:
    virtual void displayInfo() override;
};

#endif // LightBulb_H
