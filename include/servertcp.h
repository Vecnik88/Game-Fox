#ifndef SERVERTCP_H
#define SERVERTCP_H

#include <QVector>
#include <QtNetwork>

class serverTCP : public QObject
{
    Q_OBJECT

public:
    explicit Server(const size_t &, QObject *parent = Q_NULLPTR);
    ~Server();
    QString msgClient();

public slots:
    void sendToClients(const QString &);

signals:
    void recvClientDone();

private slots:
    void newConnect();
    void recvClient();

private:
    void sendToClient(      QTcpSocket *,
                      const QString    &);

    QTcpServer              *tcpServer;
    quint16                  block;
    QString                  msg;
    QVector<QTcpSocket *>    accepted;
    QVector<QString>         msgClients;
};

#endif // SERVERTCP_H
