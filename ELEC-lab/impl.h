#ifndef IMPL_H
#define IMPL_H

#include "circuitgraph.h"

#include <map>
#include <string>
#include <QLabel>
#include <QStatusBar>
#include <QPushButton>

class WirePalette;
class CircuitComponent;

// Implementation class of the circuit

class Impl
{
public:
    Impl(QLabel *backgroundLabel, QPushButton *wireButton, QStatusBar *statusBar);

    void addWire(const QPoint &start, const QPoint &end);

    void addComponent(const std::string &name, double value = 0);

    void deleteComponent(const std::string &name);

    void checkConnection();

    void showWirePalette(bool checked);

    void setDisplay(bool value);

    bool needDisplay();

private:
    std::map<std::string, CircuitComponent*> pool;

    QLabel *backgroundLabel;

    QPushButton *wireButton;

    QStatusBar *statusBar;

    WirePalette *WirePaletteLabel;

    CircuitGraph circuit;

    bool displayInfo;

    void updateInfo();

    void backgroundInit();

    std::string getAvailName(std::string prefix);
};

#endif // IMPL_H
