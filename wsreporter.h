#ifndef WSREPORTER_H
#define WSREPORTER_H

#include <QObject>
#include <QWebSocketServer>


class wsreporter : public QObject
{
    Q_OBJECT
public:
    explicit wsreporter(QObject *parent = nullptr);
    explicit wsreporter(quint16 port, QObject *parent = nullptr);
    virtual ~wsreporter();

private:
    QWebSocketServer *m_WsServer;
    QList<QWebSocket *> m_clients;
    quint16 m_port;

public slots:
    void temperatureUpdate(QDateTime timestamp, float temperature);

private slots:
    void onNewConnection();
    void socketDisconnected();
signals:
};

#endif // WSREPORTER_H
