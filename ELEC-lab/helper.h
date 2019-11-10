#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <QPoint>

namespace Helper
{
    std::string getImagePath(std::string type, int status = 0);

    bool isOverlapped(const QPoint &a, const QPoint &b);
};

#endif // HELPER_H
