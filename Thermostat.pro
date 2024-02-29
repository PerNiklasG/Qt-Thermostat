QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4):

QT += widgets quick quickwidgets sql scxml virtualkeyboard websockets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    hvaccontroller.cpp \
    main.cpp \
    mainwindow.cpp \
    mocktempsensor.cpp \
    temperaturehistoryform.cpp \
    temperaturereading.cpp \
    temperaturesensor.cpp \
    temperaturestorage.cpp \
    wsreporter.cpp

HEADERS += \
    hvaccontroller.h \
    mainwindow.h \
    mocktempsensor.h \
    temperaturehistoryform.h \
    temperaturereading.h \
    temperaturesensor.h \
    temperaturestorage.h \
    wsreporter.h

FORMS += \
    mainwindow.ui \
    temperaturehistoryform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qml.qrc

STATECHARTS += \
    hvaccontrol.scxml
