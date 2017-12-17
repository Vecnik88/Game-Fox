#ifndef SERVER_H
#define SERVER_H

#include <QtCore>
#include <QDebug>
#include <QVector>
#include <QTcpServer>
#include <QTcpSocket>

class ServerTCP : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
    ~Server();

    void createServer();
    bool getServerCreated();
signals:
    void debugLog(QString data);

public slots:
    void slotNewConnection();
    void slotRecvClient();
    void slotListen(size_t port);
    void slotShutdownClientConnection();

private:
    QTcpServer             *tcpServer;
    QMap<int, QTcpSocket*>  accepted;
    quint16                 block;
    QString                 msg;

    void sendToClient(QTcpSocket* pSocket, const QString& str);
    void sendToClients(const QString& str);
    bool serverCreated;
};

#endif // SERVER_H
