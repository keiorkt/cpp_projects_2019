#include "impl.h"
#include "wirepalette.h"

#include <Components/motor.h>
#include <Components/wire.h>
#include <Components/battery.h>
#include <Components/lightbulb.h>
#include <Components/resistor.h>

#include <QDebug>

Impl::Impl(QLabel *backgroundLabel, QPushButton *wireButton, QStatusBar *statusBar)
    : backgroundLabel(backgroundLabel),
      wireButton(wireButton),
      statusBar(statusBar),
      displayInfo(false)
{
    backgroundInit();
}

void
Impl::addWire(const QPoint &start, const QPoint &end)
{
    wireButton->toggle();

    std::string name = getAvailName("Wire");
    Wire *w = new Wire(start, end, name, this, backgroundLabel);
    pool[name] = w;

    checkConnection();
}

void
Impl::addComponent(const std::string &name, double value)
{
    if (name != "battery" && name != "Battery"
            && name != "motor" && name != "Motor"
            && name != "lightbulb" && name != "LightBulb"
            && name != "resistance" && name != "Resistance") {

        return;

    }

    if (name == "battery" || name == "Battery") {
        std::string name = getAvailName("Battery");
        Battery *b = new Battery(name, this, backgroundLabel, value);
        pool[name] = b;
    }

    if (name == "motor" || name == "Motor") {
        // TODO
        std::string name = getAvailName("Motor");
        Motor *m = new Motor(name, this, backgroundLabel);
        pool[name] = m;
    }

    if (name == "lightbulb" || name == "LightBulb") {
        // TODO
        std::string name = getAvailName("LightBulb");
        LightBulb *l = new LightBulb(name, this, backgroundLabel);
        pool[name] = l;
    }

    if (name == "resistance" || name == "Resistance") {
        // TODO
        std::string name = getAvailName("Resistance");
        Resistor *r = new Resistor(name, this, backgroundLabel, value);
        pool[name] = r;
    }

    checkConnection();
}

void
Impl::deleteComponent(const std::string &name)
{
    if (pool.count(name)) {

        pool[name]->deleteLater();
        pool.erase(name);

    }

    checkConnection();
}

void
Impl::checkConnection()
{
    std::string msg = circuit.calculateGraph(pool);
    statusBar->showMessage(msg.c_str());

    updateInfo();
}

void
Impl::showWirePalette(bool checked)
{
    WirePaletteLabel->setVisible(checked);
}

void
Impl::updateInfo()
{
    for (std::pair<std::string, CircuitComponent*> element : pool) {
        element.second->displayInfo();
    }
}

void
Impl::setDisplay(bool value)
{
    displayInfo = value;
    updateInfo();
}

bool
Impl::needDisplay()
{
    return displayInfo;
}

void
Impl::backgroundInit()
{
    // Set the circuit background color to white
    backgroundLabel->setStyleSheet("QLabel { background-color : white; }");
    // Add wire palette label
    WirePaletteLabel = new WirePalette(backgroundLabel, this, backgroundLabel->parentWidget());
}

std::string
Impl::getAvailName(std::string prefix)
{
    int id = 0;
    std::string ret;

    do {

        ret = prefix + std::to_string(id);
        id ++;

    } while (pool.count(ret));

    return ret;
}
