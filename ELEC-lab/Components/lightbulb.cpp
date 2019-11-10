#include <Components/lightbulb.h>

#include <string>

LightBulb::LightBulb(const std::string &name, Impl *hostImpl, QWidget *parent)
    : CircuitComponent(name, hostImpl, parent)
{
    setImage(Helper::getImagePath("LightBulb"));
    setR(10);
}

std::string
LightBulb::getType()
{
    return "LightBulb";
}

void
LightBulb::setI(double I_)
{
    CircuitComponent::setI(I_);

    // TODO: set the image of the lightbulb for other illumination level
    if (I_ < 0.1) {
        setImage(Helper::getImagePath("LightBulb", 0));
    }
    else if (I_ < 0.5) {
        setImage(Helper::getImagePath("LightBulb", 1));
    }
    else if (I_ < 1) {
        setImage(Helper::getImagePath("LightBulb", 2));
    }
    else {
        setImage(Helper::getImagePath("LightBulb", 3));
    }

}

void
LightBulb::displayInfo()
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
