#ifndef CLIENTTCP_H
#define CLIENTTCP_H

#include <QObject>
#include <QtNetwork>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client::Client(const QString &ipDestination,
                            const size_t  &portDestination);
    ~ClientTCP();
    QString getData();

public slots:
    void sendToServer(QString);

private slots:
    void recvReady();
    void connected();
    void error(QAbstractSocket::SocketError);

signals:
    void recvMsg();

private:
    QTcpSocket *tcpSocket;
    quint16     block;
    QString     msg;
};

#endif // CLIENTTCP_H
