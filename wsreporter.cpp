#include "wsreporter.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QWebSocket>

wsreporter::wsreporter(QObject *parent)
    : QObject{parent}
{}

wsreporter::wsreporter(quint16 port, QObject *parent)
{
    m_WsServer = new QWebSocketServer (
        "BigProjectReporter",
        QWebSocketServer::SslMode::NonSecureMode,
        this);

    if(m_WsServer->listen(QHostAddress::Any, port)) {
        qDebug() << "WSReport Listening on port" << port;
        connect(m_WsServer, &QWebSocketServer::newConnection, this, &wsreporter::onNewConnection);
    }
}

wsreporter::~wsreporter()
{
    m_WsServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}

void wsreporter::temperatureUpdate(QDateTime timestamp, float temperature)
{
    QJsonObject jObj;
    jObj.insert("timestamp", timestamp.toString());
    jObj.insert("temperature", temperature);

    QJsonDocument jDoc(jObj);
    QString jText = jDoc.toJson(QJsonDocument::Indented);

    for (auto client : m_clients) {
        client->sendTextMessage(jText);
    }
}

void wsreporter::onNewConnection()
{
    QWebSocket *pSocket = m_WsServer->nextPendingConnection();

    qDebug() << "Client connected:" << pSocket->peerName() << pSocket->origin();

    connect(pSocket, &QWebSocket::disconnected, this, &wsreporter::socketDisconnected);

    m_clients << pSocket;
}

void wsreporter::socketDisconnected()
{
    qDebug() << "Client disconnected";
    QWebSocket *pClient = qobject_cast<QWebSocket *> (sender());
    if(pClient) {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}
