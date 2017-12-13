#include "include/clienttcp.h"

Client::Client(const QString &ipDestination,
                     const size_t  &portDestination) : QObject()
{
    tcpSocket = new QTcpSocket;
    tcpSocket->connectToHost(ipDestination, portDestination);

    connect(tcpSocket, SIGNAL(recvReady()), SLOT(recvReady()));
    connect(tcpSocket, SIGNAL(connected()), SLOT(connected()));
}

Client::~Client()
{
    delete tcpSocket;
}

void Client::recvReady()
{
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_5_9);

    msg = "";
    block = 0;

    while (true) {
        if (!block) {
            if (tcpSocket->bytesAvailable() < sizeof(quint16)) {
                break;
            }
            in >> block;
        }

        if (tcpSocket->bytesAvailable() < block) {
            break;
        }

        QTime time;
        QString str;
        in >> time >> str;
        msg += time.toString() + " " + str + '\n';
        block = 0;
    }
    emit recvMsg();
}

void Client::connected()
{ }

void Client::error(QAbstractSocket::SocketError err)
{
    qDebug() << err << tcpSocket->errorString() << endl;
}

void Client::sendToServer(const QString &msg)
{
    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_9);
    out << quint16(0) << QTime::currentTime() << msg;
    out.device()->seek(0);
    out << quint16(buffer.size() - sizeof(quint16));
    tcpSocket->write(buffer);
}

QString Client::getData()
{
    return data;
}
