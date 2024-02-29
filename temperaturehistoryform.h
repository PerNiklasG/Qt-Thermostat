#ifndef TEMPERATUREHISTORYFORM_H
#define TEMPERATUREHISTORYFORM_H

#include "temperaturestorage.h"

#include <QWidget>
#include <QSortFilterProxyModel>
#include <QStandardItemModel>
#include <QDateTime>
#include <QQmlEngine>
#include <QQmlContext>

namespace Ui {
class temperaturehistoryform;
}

class temperaturehistoryform : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QPointF lastReading READ lastReading WRITE setLastReading NOTIFY newReading)

public:
    explicit temperaturehistoryform(QWidget *parent = nullptr);
    ~temperaturehistoryform();

    QPointF lastReading() const;
    void setLastReading(const QPointF &lastReading);

    void setTemperatureStorage(temperaturestorage *temperaturestorage);

signals:
    void newReading();

private:
    Ui::temperaturehistoryform *ui;

    QStandardItemModel m_tempRecord;
    QSortFilterProxyModel m_tempProxy;

    QPointF m_lastReading;

    temperaturestorage *m_temperatureStorage;

public slots:
    void temperatureUpdate(QDateTime timestamp, float degreesCelsius);
};

#endif // TEMPERATUREHISTORYFORM_H
