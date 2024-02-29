#include "mainwindow.h"
#include "mocktempsensor.h"
#include "ui_mainwindow.h"

#include <QDateTime>
#include <QThread>
#include <QTimer>

MainWindow::MainWindow(temperaturesensor *tempSensor, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_tempSensor(tempSensor),
    m_tempStorage(new temperaturestorage)
{
    m_wsReporter = new wsreporter(8091, this);

    connect(m_tempSensor,
            &temperaturesensor::newTemperature,
            m_wsReporter,
            &wsreporter::temperatureUpdate);

    this->setAttribute(Qt::WA_QuitOnClose);

    ui->setupUi(this);

    ui->heatingInd->setEnabled(false);
    ui->coolingInd->setEnabled(false);
    ui->fanInd->setEnabled(false);

    m_hvacSM.moveToThread(new QThread);

    m_hvacSM.connectToState("Heating", ui->heatingInd, &QLabel::setEnabled);
    m_hvacSM.connectToState("Cooling", ui->coolingInd, &QLabel::setEnabled);
    m_hvacSM.connectToState("FanOn", ui->fanInd, &QLabel::setEnabled);

    m_hvacSM.connectToState("Heating", &m_hvacCtrl, &hvaccontroller::setHeatingOn);
    m_hvacSM.connectToState("Cooling", &m_hvacCtrl, &hvaccontroller::setCoolingOn);
    m_hvacSM.connectToState("FanOn", &m_hvacCtrl, &hvaccontroller::setFanOn);

    /*
    connect(&m_hvacSM, &QScxmlStateMachine::reachedStableState, [this]() {
        qDebug() << "Stable States: " << m_hvacSM.activeStateNames(false);
    });
    */
    m_hvacSM.start();

    auto mockTemp = dynamic_cast<mocktempsensor *>(m_tempSensor);
    if(mockTemp){
        mockTemp->setSm(&m_hvacSM);
    }

    m_tempStorage->openStorage("history");
    ui->historyForm->setTemperatureStorage(m_tempStorage);

    connect(m_tempSensor, &temperaturesensor::newTemperature, this, &MainWindow::updateTempDisplay);
    connect(m_tempSensor, &temperaturesensor::newTemperature, ui->historyForm, &temperaturehistoryform::temperatureUpdate);
    connect(m_tempSensor, &temperaturesensor::newTemperature,
            [this](QDateTime timestamp, float temperature) {
        m_tempStorage->addReading(temperaturereading(timestamp,temperature));
    });

    m_updateTimer.setSingleShot(false);
    connect(&m_updateTimer, &QTimer::timeout, this, &MainWindow::updateDisplay);
    m_updateTimer.start(1000);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateDisplay()
{
    QDateTime now = QDateTime::currentDateTime();
    ui->currentDateTime->setText(now.toString());
}

void MainWindow::updateTempDisplay(QDateTime timestamp, float degreesCelsius)
{
    ui->temperatureLabel->setText(QString("%1 C").arg(degreesCelsius));

    auto activeStates = m_hvacSM.activeStateNames(false);
    qDebug() << QString("[%1, %2] : %3 - %4").arg(ui->minTemperatureSpinBox->value())
                    .arg(ui->maxTemperatureSpinBox->value())
                    .arg(degreesCelsius)
                    .arg(activeStates.join(":"));

    QString transition;
    if (degreesCelsius > ui->maxTemperatureSpinBox->value()) {
        transition = "TooHot";
    } else if (degreesCelsius < ui->minTemperatureSpinBox->value()) {
        transition = "TooCold";
    } else {
        transition = "TargetReached";
    }
    m_hvacSM.submitEvent(transition);
    //        qDebug() << "Sent" << transition;
}

void MainWindow::on_maxTemperatureSpinBox_valueChanged(int arg1)
{
    if(ui->minTemperatureSpinBox->value() > (arg1 - 3)) {
        ui->minTemperatureSpinBox->setValue(arg1 - 3);
    }
}

void MainWindow::on_minTemperatureSpinBox_valueChanged(int arg1)
{
    if(ui->maxTemperatureSpinBox->value() < (arg1 + 3)) {
        ui->maxTemperatureSpinBox->setValue(arg1 + 3);
    }
}
