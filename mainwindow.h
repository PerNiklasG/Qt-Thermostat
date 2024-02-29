#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "temperaturesensor.h"
#include "hvaccontrol.h"
#include "hvaccontroller.h"
#include "temperaturestorage.h"
#include "wsreporter.h"

#include <QMainWindow>
#include <QTimer>
#include <QTimerEvent>

class temperaturesensor;
class temperaturestorage;


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(temperaturesensor *tempSensor, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTimer m_updateTimer;
    temperaturesensor *m_tempSensor;
    temperaturestorage *m_tempStorage;

    hvaccontrol  m_hvacSM;
    hvaccontroller m_hvacCtrl;

    wsreporter *m_wsReporter;

private slots:
    void updateDisplay();
    void updateTempDisplay(QDateTime timestamp, float degreesCelsius);

    void on_maxTemperatureSpinBox_valueChanged(int arg1);
    void on_minTemperatureSpinBox_valueChanged(int arg1);
};
#endif // MAINWINDOW_H
