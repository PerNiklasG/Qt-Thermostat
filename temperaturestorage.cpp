#include "temperaturestorage.h"

#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QSqlTableModel>
#include <QSqlRecord>

temperaturestorage::temperaturestorage() {}

temperaturestorage::~temperaturestorage()
{

}

void temperaturestorage::addReading(const temperaturereading &reading)
{
    QSqlQuery query(m_db);
    query.prepare("insert into TemperatureHistory values (:timestamp, :temperature);");
    query.bindValue(":timestamp", reading.timestamp());
    query.bindValue(":temperature", reading.temperatureC());
    query.exec();

    m_temperatureModel->setQuery("select * from TemperatureHistory order by timestamp desc;", m_db);
}

QList<temperaturereading> temperaturestorage::getAllReadings() const
{
    QList<temperaturereading> ret;
    QSqlTableModel model(nullptr, m_db);
    model.setTable("TemperatureHistory");
    model.select();

    for(int row = 0; row < model.rowCount(); ++row) {
        auto rec = model.record(row);
        ret << temperaturereading(rec.value("timestamp").toDateTime(),
                                   rec.value("temperature").toFloat());
    }
    return ret;
}

QList<temperaturereading> temperaturestorage::getLastNReadings(int n) const
{
    QList<temperaturereading> ret;

    auto qStr = QString("select * from TemperatureHistory order by timestamp desc limit %1;").arg(n);

    QSqlQuery query(qStr, m_db);
    query.exec();
    while (query.next()) {
        ret << temperaturereading(query.value("timestamp").toDateTime(),
                                   query.value("temperature").toFloat());
    }

    return ret;
}

temperaturereading temperaturestorage::getLastReading() const
{
    auto data = getLastNReadings(1);
    return data.value(0, temperaturereading());
}

void temperaturestorage::clearAllReadings()
{
    QSqlQuery query("delete from TemperatureHistory where 1;", m_db);
    query.exec();

    m_temperatureModel->query().executedQuery();
}

int temperaturestorage::numberOfReadings() const
{
    QSqlQuery query("select count(timestamp) from TemperatureHistory;", m_db);
    query.exec();
    query.next();

    return query.value(1).toInt();
}

bool temperaturestorage::openStorage(const QString &id)
{
    QString dbName = QString("ReadingStore_%1").arg(id);
    QString dbFileName = QString("%1.sqlite").arg(dbName);

    m_db = QSqlDatabase::addDatabase("QSQLITE", dbName);
    m_db.setDatabaseName(dbFileName);

    bool result = m_db.open();
    if(result)
    {
        QSqlQuery query(m_db);
        result = query.exec("create table if not exists TemperatureHistory ("
                            " timestamp datetime primary key, "
                            " temperature float"
                            ");"
                            );

        m_temperatureModel = new QSqlQueryModel;
        m_temperatureModel->setQuery("select * from TemperatureHistory order by timestamp desc;", m_db);

    }

    if(!result) {
        qDebug() << "!!! Databse Error: " << m_db.lastError();
    }

    return result;
}

void temperaturestorage::closeStorage()
{
    m_db.close();
}

QString temperaturestorage::id() const
{
    return m_id;
}

QSqlQueryModel *temperaturestorage::temperatureModel() const
{
    return m_temperatureModel;
}
