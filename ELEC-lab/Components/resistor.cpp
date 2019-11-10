#include <Components/resistor.h>

#include <string>

#include <QDebug>

Resistor::Resistor(const std::string &name, Impl *hostImpl, QWidget *parent, double value)
    : CircuitComponent(name, hostImpl, parent)
{
    setImage(Helper::getImagePath("Resistance"));
    setR(value);
}

std::string
Resistor::getType()
{
    return "Resistance";
}

void
Resistor::displayInfo()
{
    // TODO: display V, I and R
    if (needDisplay()) {
        display("V=" + std::to_string(getV())
                     + "\nI=" + std::to_string(getI())
                     + "\nR=" + std::to_string(getR()));
    } else {
        display("");
    }
}
