#include "temperaturereading.h"

temperaturereading::temperaturereading() :
    m_temperatureC(0.0),
    m_timestamp(QDateTime())
{}

temperaturereading::temperaturereading(const QDateTime &timestamp, float temperature)
    : m_temperatureC(temperature),
    m_timestamp(timestamp)
{

}

bool temperaturereading::operator==(const temperaturereading &right)
{
    return((right.m_timestamp == m_timestamp) &&
            (right.m_temperatureC == m_temperatureC));
}

bool temperaturereading::operator<(const temperaturereading &right)
{
    return (m_timestamp.toMSecsSinceEpoch() < right.m_timestamp.toMSecsSinceEpoch());
}

float temperaturereading::temperatureC() const
{
    return m_temperatureC;
}

void temperaturereading::setTemperatureC(float newTemperatureC)
{
    m_temperatureC = newTemperatureC;
}

QDateTime temperaturereading::timestamp() const
{
    return m_timestamp;
}

void temperaturereading::setTimestamp(const QDateTime &newTimestamp)
{
    m_timestamp = newTimestamp;
}

bool temperaturereading::isValid() const
{
    return m_timestamp.isValid();
}
