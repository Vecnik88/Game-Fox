#include "include/servertcp.h"

serverTCP::serverTCP(const size_t &port) : QObject(parent)
{
    tcpServer = new QTcpServer;
    if (tcpServer->listen(QHostAddress::Any, port)) {
        qDebug() << "<serverTCP> listen error" << endl;
        return;
    }
    connect(tcpServer, SIGNAL(newConnection()), SLOT(newConnect()));
}

serverTCP::~serverTCP()
{
    tcpServer->close();
    delete tcpServer;
}

serverTCP::sendToClients(const QString &msg)
{
    for (auto &socket : accepted)
        sendToClient(socket, msg);
}

serverTCP::newConnect()
{
    QTcpSocket *tcpSocket = tcpServer->nextPendingConnection();
    sendToClient(tcpSocket, "[Connected true]");
    accepted.push_back(tcpSocket);

    connect(tcpSocket, SIGNAL(disconnected()), tcpSocket, deleteLater());
    connect(tcpSocket, SIGNAL(readyRead()), tcpSocket, SLOT(recvReady()));
}

void serverTCP::recvClient()
{
    QTcpSocket *tcpSocket = (QTcpSocket *)sender();
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_5_9);
    block = 0;
    msg = "";

    while(1) {
        if (!block) {
            if (tcpSocket->bytesAvailable() < sizeof(quint16)) {
                qDebug() << "<recvClient> error read bytes" << endl;
                break;
            }
            in >> block;
        }
        if (tcpSocket->bytesAvailable() < block)
            break;
    }
    QTime time;
    QString str;
    in >> time >> str;
    msg += time.toString() + " " + str + "\n";
    block = 0;
    msgClients.push_back(msg);
    emit recvClientDone();
}

void serverTCP::sendToClient(QTcpSocket *tcpSocket, const QString &msg)
{
    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_9);
    out << quint16(0) << QTime::currentTime() << msg;
    tcpSocket->write(buffer);
}

QString serverTCP::msgClient()
{
    return msgClients().pop_back();
}
