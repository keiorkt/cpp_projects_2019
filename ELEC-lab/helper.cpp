#include "helper.h"

std::string
Helper::getImagePath(std::string type, int status)
{
    if (type == "Battery" || type == "battery") {
        if (status == 0) {
            return ":/resources/image/Battery/" + std::to_string(status) + ".png";
        }
    }

    if (type == "LightBulb" || type == "lightbulb") {
        if (status >= 0 && status <= 3) {
            return ":/resources/image/LightBulb/" + std::to_string(status) + ".png";
        }
    }

    if (type == "Motor" || type == "motor") {
        if (status >= 0 && status <= 2) {
            return ":/resources/image/Motor/" + std::to_string(status) + ".png";
        }
    }

    if (type == "Resistance" || type == "resistance") {
        if (status == 0) {
            return ":/resources/image/Resistance/" + std::to_string(status) + ".png";
        }
    }

    return "";
}

bool
Helper::isOverlapped(const QPoint &a, const QPoint &b)
{
    int thres = 10;
    int dist = (a.x() - b.x()) * (a.x() - b.x())
            + (a.y() - b.y()) * (a.y() - b.y());

    return dist < thres * thres;
}
