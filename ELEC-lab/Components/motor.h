#ifndef Motor_H
#define Motor_H

#include "Components/circuitcomponent.h"

#include <QTimer>

class Motor : public CircuitComponent
{
public:
    Motor(const std::string &name, Impl *hostImpl, QWidget *parent = nullptr);

    std::string getType() override;

    void setI(double I_) override;

protected:
    virtual void displayInfo() override;

private:
    void rotate();

    QTimer motorTimer;
};

#endif // Motor_H
