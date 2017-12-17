#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QtWidgets>
#include <QtNetwork>
#include <QGridLayout>
#include <QHBoxLayout>

#include "include/subject.h"
#include "include/infocell.h"
#include "include/database.h"
#include "include/inventorytable.h"

enum statusGame {
    CLIENT = 0,
    SERVER,
    SIMPLE_GAME
};

/****************
 * Игровое окно *
 ****************/

class GameWindow : public QWidget
{
    Q_OBJECT
public:
    explicit GameWindow(QWidget *parent = Q_NULLPTR);
    ~GameWindow();

signals:
    // обновляет таблицу с инвентарем
    void newMessageRefreshTable(const size_t  &cell,
                                const QString &type,
                                const size_t  &amount);

    void newGame();

public slots:
    // запускает игру
    void slotRunGame();
    // останавливает игру(сохраняя)
    void slotStopGame();
    // запускает игру как клиент
    void slotRunGameClient();
    // запускает игру как сервер
    void slotRunGameServer();
    // обновляет и переписывает таблицу


    // для сетевого соединения
    // server
    void slotNewConnection();           // определение нового соединения с клиентом
    void slotRecvClient();              // для прочтения данных от клиента
    void slotSendNewGameToClient();
    void slotSendChangeToClient(const int     &cell,
                                const QString &type,
                                const int     &amount);

    // client
    void slotConnected();
    void slotRecvServer();              // для прочтения данных от сервера
    void slotSendNewGameToServer();
    void slotError(QAbstractSocket::SocketError err);
    void slotSendChangeToServer(const int     &cell,
                                const QString &type,
                                const int     &amount);

private:
    DataBase            *db;
    InventoryTable      *table;
    Subject             *subject;
    QWidget             *mainMenu;
    QWidget             *gameField;
    qint8                gameStatus;

    // управляющие кнопки
    QPushButton         *run;
    QPushButton         *exit;
    QPushButton         *menuGame;
    QPushButton         *runClient;
    QPushButton         *runServer;

    // для сетевого соединения
    QTcpServer         *tcpServer;
    QTcpSocket         *clientTcpSocket;
    QTcpSocket         *serverTcpSocket;
    quint16             dataSize;

    // инициализирует/создает игровое поле
    void gameInit();
    void startGame();
    void createMainMenu();
    void createGameMenu();
    void createGameField();
    void createGameWindow();

    void refreshGameField();
};

#endif // MAINWINDOW_H
