#ifndef TEMPERATURESTORAGE_H
#define TEMPERATURESTORAGE_H

#include "temperaturereading.h"

#include <QSqlDatabase>
#include <QSqlQueryModel>


class temperaturestorage
{
public:
    temperaturestorage();
    ~temperaturestorage();

    void addReading(const temperaturereading &reading);
    QList<temperaturereading> getAllReadings() const;
    QList<temperaturereading> getLastNReadings(int n) const;
    temperaturereading getLastReading() const;

    void clearAllReadings();
    int numberOfReadings() const;

    bool openStorage(const QString &id = "readings");
    void closeStorage();

    QString id() const;

    QSqlQueryModel *temperatureModel() const;

private:
    QSqlDatabase m_db;
    QString m_id;

    QSqlQueryModel *m_temperatureModel;
};

#endif // TEMPERATURESTORAGE_H
