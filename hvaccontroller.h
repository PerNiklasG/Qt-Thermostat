#ifndef HVACCONTROLLER_H
#define HVACCONTROLLER_H

#include <QObject>

class hvaccontroller : public QObject
{
    Q_OBJECT
public:
    explicit hvaccontroller(QObject *parent = nullptr);

public slots:
    void setHeatingOn(bool on);
    void setCoolingOn(bool on);
    void setFanOn(bool on);

signals:
};

#endif // HVACCONTROLLER_H
