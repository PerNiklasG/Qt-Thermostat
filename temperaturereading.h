#ifndef TEMPERATUREREADING_H
#define TEMPERATUREREADING_H

#include <QDateTime>

class temperaturereading
{
public:
    temperaturereading();
    temperaturereading(const QDateTime &timestamp, float temperature);
    temperaturereading &operator=(const temperaturereading &right) = default;

    ~temperaturereading() = default;

    bool operator==(const temperaturereading &right);
    bool operator<(const temperaturereading &right);

    float temperatureC() const;
    void setTemperatureC(float newTemperatureC);

    QDateTime timestamp() const;
    void setTimestamp(const QDateTime &newTimestamp);

    bool isValid() const;

private:
    float m_temperatureC;
    QDateTime m_timestamp;
};

#endif // TEMPERATUREREADING_H
