#ifndef CLIENTTCP_H
#define CLIENTTCP_H

#include <QObject>
#include <QtNetwork>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(const QString &ipDestination,
                            const size_t  &portDestination,
                                  QObject *parent = Q_NULLPTR);
    ~Client();
    QString getData();

public slots:
    void sendToServer(const QString &msg);

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
