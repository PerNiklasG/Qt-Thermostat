#include "hvaccontroller.h"

#include <QDebug>

hvaccontroller::hvaccontroller(QObject *parent)
    : QObject{parent}
{}

void hvaccontroller::setHeatingOn(bool on)
{
    qDebug() << "Heating set to " << on;
}

void hvaccontroller::setCoolingOn(bool on)
{
    qDebug() << "Cooling set to " << on;
}

void hvaccontroller::setFanOn(bool on)
{
    qDebug() << "Fan set to " << on;
}
