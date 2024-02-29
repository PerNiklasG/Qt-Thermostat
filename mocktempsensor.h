#ifndef MOCKTEMPSENSOR_H
#define MOCKTEMPSENSOR_H

#include "temperaturesensor.h"

#include <QScxmlStateMachine>
#include <QTimer>

class mocktempsensor : public temperaturesensor
{
public:
    explicit mocktempsensor(QObject *parent = nullptr);

    const QScxmlStateMachine *sm() const;
    void setSm(const QScxmlStateMachine *sm);

private:
    QTimer m_sendTempTimer;
    float m_lastTemp;

    const QScxmlStateMachine *m_sm;
};

#endif // MOCKTEMPSENSOR_H
