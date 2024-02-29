#include "temperaturehistoryform.h"
#include "ui_temperaturehistoryform.h"

#include <QList>
#include <QVariant>
#include <QQmlEngine>
#include <QQmlContext>

temperaturehistoryform::temperaturehistoryform(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::temperaturehistoryform)
{
    ui->setupUi(this);

    m_tempRecord.setHorizontalHeaderLabels(QStringList({"Date & Time", "Temperature"}));

    ui->tableView->setModel(&m_tempProxy);

    ui->quickWidget->resize(QSize(640, 480));
    ui->quickWidget->engine()->rootContext()->setContextProperty("temperatureData", this);
    ui->quickWidget->setSource(QUrl("qrc:/temperaturechart.qml"));
    ui->quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
}

temperaturehistoryform::~temperaturehistoryform()
{
    delete ui;
}

QPointF temperaturehistoryform::lastReading() const
{
    return m_lastReading;
}

void temperaturehistoryform::setLastReading(const QPointF &lastReading)
{
    m_lastReading = lastReading;
    emit newReading();
}

void temperaturehistoryform::setTemperatureStorage(temperaturestorage *temperaturestorage)
{
    m_temperatureStorage = temperaturestorage;
    m_tempProxy.setSourceModel(m_temperatureStorage->temperatureModel());
}

void temperaturehistoryform::temperatureUpdate(QDateTime timestamp, float degreesCelsius)
{
    auto time = new QStandardItem;
    auto temp = new QStandardItem;

    time->setData(timestamp, Qt::DisplayRole);
    temp->setData(degreesCelsius, Qt::DisplayRole);

    QList<QStandardItem *> row;
    row << time << temp;

    m_tempRecord.appendRow(row);

    double xVal = timestamp.toSecsSinceEpoch();
    setLastReading(QPointF(xVal, degreesCelsius));
}
