#include "mocktempsensor.h"

#include <QRandomGenerator>

mocktempsensor::mocktempsensor(QObject *parent)
    : temperaturesensor{parent},
    m_sm(nullptr)
{
    m_lastTemp = 17.5;
    m_sendTempTimer.setInterval(1000);
    m_sendTempTimer.setSingleShot(false);

    connect(&m_sendTempTimer, &QTimer::timeout, this, [this] () {
        QDateTime now = QDateTime::currentDateTime();
        float change = 0.0;

        auto states = (m_sm != nullptr) ? m_sm->activeStateNames(false) : QStringList();

        if (states.contains("Heating")) {
            change = 0.4;
        }
        else if(states.contains("Cooling")) {
            change = -0.4;
        }
        else {
            float delta = states.contains("Fan") ? (float) 0.01 : (float) 0.04;
            int rd = ((QRandomGenerator::global()->generate() % 100)-51);
            change = static_cast<float>(rd);
            qDebug() << "Random: " << rd;
            change *= delta;
            qDebug() << "Change: " << change;
        }

        m_lastTemp += change;
        emit newTemperature(now, m_lastTemp);
    });

    m_sendTempTimer.start();
}

const QScxmlStateMachine *mocktempsensor::sm() const
{
    return m_sm;
}

void mocktempsensor::setSm(const QScxmlStateMachine *sm)
{
    m_sm = sm;
}
