#include <Components/battery.h>

#include <string>

Battery::Battery(const std::string &name, Impl *hostImpl, QWidget *parent, double voltage)
    : CircuitComponent(name, hostImpl, parent)
{
    setImage(Helper::getImagePath("Battery"));
    setV(voltage);
}

std::string
Battery::getType()
{
    return "Battery";
}

void
Battery::displayInfo()
{
    if (needDisplay()) {
        display("V=" + std::to_string(getV())
                          + "\nI=" + std::to_string(getI()));
    } else {
        display("");
    }
}
