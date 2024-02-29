#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H

#include <QDateTime>
#include <QObject>

class temperaturesensor : public QObject
{
    Q_OBJECT
public:
    explicit temperaturesensor(QObject *parent = nullptr);

signals:
    void newTemperature(QDateTime timestamp, float degreesCelsius);

public slots:

private slots:

private:
    float m_tempSensor;

};

#endif // TEMPERATURESENSOR_H
