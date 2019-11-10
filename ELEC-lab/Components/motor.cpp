#include <Components/motor.h>

#include <cmath>
#include <string>

Motor::Motor(const std::string &name, Impl *hostImpl, QWidget *parent)
    : CircuitComponent(name, hostImpl, parent)
{
    setImage(Helper::getImagePath("Motor"));
    setR(10);
    motorTimer.setParent(this);
    connect(&motorTimer, &QTimer::timeout, [=](){
        this->rotate();
    });
}

std::string
Motor::getType()
{
    return "Motor";
}

void
Motor::setI(double I_)
{
    if (fabs(I_ - getI()) > 1e-6) {

        CircuitComponent::setI(I_);

        if (I_ < 1) {
            if (motorTimer.isActive()) {
                motorTimer.stop();
            }
        } else {
            // TODO: if the timer is not active, start the timer
            int interval = std::max(int(1000 - I_ * 400), 10);
            // TODO: set the timer interval by calling QTimer::setInterval
            if (!motorTimer.isActive()) {
                motorTimer.setInterval(interval);
                motorTimer.start();
                rotate();
            }
        }

    }
}

void
Motor::displayInfo()
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

void
Motor::rotate()
{
    static int currentFrame = 0;
    currentFrame = (currentFrame + 1) % 3;
    setImage(Helper::getImagePath("Motor", currentFrame));
}
