#include "include/mainwindow.h"
#include "include/sourcedata.h"

GameWindow::GameWindow(QWidget *parent):
                       QWidget (parent)
{
    gameInit();

    // соединяем необходимые нам сигналы со слотами
    connect(run, SIGNAL(clicked(bool)), SLOT(slotRunGame()));
    connect(exit, SIGNAL(clicked(bool)), SLOT(close()));
    connect(runClient, SIGNAL(clicked(bool)), SLOT(slotRunGameClient()));
    connect(runServer, SIGNAL(clicked(bool)), SLOT(slotRunGameServer()));
    connect(menuGame, SIGNAL(clicked(bool)), SLOT(slotStopGame()));
}

void GameWindow::slotRunGame()
{
    gameStatus = SIMPLE_GAME;
    startGame();
}

void GameWindow::slotRunGameClient()
{
    gameStatus = CLIENT;
    clientTcpSocket = new QTcpSocket();
    clientTcpSocket->connectToHost(IP_ADDR_LOCAL_HOST, PORT);

    connect(table, SIGNAL(addMessageToSocket(int, QString, int)),
            this, SLOT(slotSendChangeToServer(int, QString, int)));

    connect(clientTcpSocket, SIGNAL(connected()), this, SLOT(slotConnected()));
    connect(clientTcpSocket, SIGNAL(readyRead()), this, SLOT(slotRecvClient()));
    connect(clientTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(slotError(QAbstractSocket::SocketError)));
}

void GameWindow::slotRunGameServer()
{
    gameStatus = SERVER;

    tcpServer = new QTcpServer(this);

    if (!tcpServer->listen(QHostAddress(IP_ADDR_LOCAL_HOST), PORT)) {
        QMessageBox::critical(0,
                              "Server Error",
                              "Unable to start the server:"
                              + tcpServer->errorString());
                tcpServer->close();
                return;
    }

    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));
    connect(table, SIGNAL(addMessageToSocket(int, QString, int)),
            this, SLOT(slotSendChangeToClient(int, QString, int)));

}

void GameWindow::slotStopGame()
{
    gameField->setEnabled(false);
    menuGame->setEnabled(false);
    db->insertIntoTable(subject, table->cells);
    mainMenu->show();
}

void GameWindow::gameInit()
{
    // создает игровое поле
    createGameField();
    // создает игровое меню
    createGameMenu();
    // создает главное меню
    createMainMenu();
    // создает окончательный вид игрового окна
    createGameWindow();
}

void GameWindow::startGame()
{
    table->refreshTable();
    gameField->setEnabled(true);
    menuGame->setEnabled(true);
    mainMenu->hide();
}

// создает главное меню
void GameWindow::createMainMenu()
{
    // создаем виджет главного меню
    mainMenu = new QWidget;
    exit = new QPushButton("Выход");
    run = new QPushButton("Начать 1 игрок");
    runClient = new QPushButton("Сеть - Клиент");
    runServer = new QPushButton("Сеть - Сервер");
    exit->setMaximumSize(200, 50);
    runClient->setMaximumSize(200, 50);
    runServer->setMaximumSize(200, 50);
    run->setMaximumSize(200, 50);
    QHBoxLayout *hbx = new QHBoxLayout;
    hbx->addWidget(run);
    hbx->addWidget(runClient);
    hbx->addWidget(runServer);
    hbx->addWidget(exit);
    mainMenu->setLayout(hbx);
    mainMenu->setMaximumSize(WIDTH, 100);
}

// создает игровое меню
void GameWindow::createGameMenu()
{
    menuGame = new QPushButton("Главное меню");
    menuGame->setEnabled(false);
}

// создает игровое поле
void GameWindow::createGameField()
{
    db = new DataBase(ROWS_TABLE * COLS_TABLE);
    if (!db->connectToDataBase())
        qDebug() << "< MainWindow > error connect to database" << endl;

    table = new InventoryTable(COLS_TABLE, ROWS_TABLE);
    subject = new Subject;

    if (!db->initParametrs(subject, table->cells))
        qDebug() << "< MainWindow > error init parametrs with database" << endl;

    gameField = new QWidget;
    table->verticalHeader()->hide();
    table->horizontalHeader()->hide();
    QGridLayout *grd = new QGridLayout;
    grd->addWidget(table, 0, 0, 2, 2, Qt::AlignHCenter);
    grd->addWidget(subject, 0, 3, 2, 2, Qt::AlignHCenter);
    gameField->setLayout(grd);
    gameField->setEnabled(false);
}

// создает окончательный вид игрового окна
void GameWindow::createGameWindow()
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(mainMenu);
    mainLayout->addWidget(gameField);
    mainLayout->addWidget(menuGame);
    setLayout(mainLayout);
    setGeometry(OFFSET_X, OFFSET_Y, WIDTH, HEIGHT);
}

void GameWindow::refreshGameField()
{
    table->refreshTable();
}

GameWindow::~GameWindow()
{
    delete db;
    delete run;
    delete exit;
    delete table;
    delete subject;
    delete menuGame;
    delete mainMenu;
    delete gameField;
    delete runClient;
    delete runServer;
    delete tcpServer;
    delete clientTcpSocket;
    delete serverTcpSocket;
}

void GameWindow::slotNewConnection()
{
    qDebug() << "New connection to server" << endl;
    serverTcpSocket = tcpServer->nextPendingConnection();
    startGame();

    connect(serverTcpSocket, SIGNAL(disconnected()), serverTcpSocket, SLOT(deleteLater()));
    connect(serverTcpSocket, SIGNAL(readyRead()), this, SLOT(slotRecvServer()));
}

void GameWindow::slotRecvClient()
{
    qDebug() << "slotRecvClient" << endl;
    QDataStream in(clientTcpSocket);
    qDebug() << "1" << endl;
    in.setVersion(QDataStream::Qt_5_9);
    while(1) {
        qDebug() << "2" << endl;
        if (!dataSize) {
            if (clientTcpSocket->bytesAvailable() < sizeof(quint16)) {
                qDebug() << "3" << endl;
                    break;
                }
                in >> dataSize;
                qDebug() << "datasize = " << endl;
            }
        qDebug() << "4" << endl;
        qDebug() << "byte = " << serverTcpSocket->bytesAvailable() << endl;
            /*if (clientTcpSocket->bytesAvailable() < dataSize) {
                break;
            }*/
            QString action;

            in >> action;
            qDebug() << "action = " << action << endl;
            if (action == "change") {
                int cell;
                int amount;
                QString type;
                in >> cell >> type >> amount;
                table->cells[cell].setParametrs(type, amount);
                refreshGameField();
            }
            else if (action == "game") {
                startGame();
            }
            dataSize = 0;
    }
}

void GameWindow::slotSendChangeToClient(const int     &cell,
                                        const QString &type,
                                        const int     &amount)
{
    qDebug() << "slotSendChangeToClient" << endl;
    QString action = "change";
    QByteArray  buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_9);
    out << quint16(0) << action << cell << type << amount;
    qDebug() << action << cell << type << amount << endl;
    out.device()->seek(0);
    out << quint16(buffer.size() - sizeof(quint16));
    serverTcpSocket->write(buffer);
}

void GameWindow::slotRecvServer()
{
    qDebug() << "slotRecvServer" << endl;
    QDataStream in(serverTcpSocket);
    in.setVersion(QDataStream::Qt_5_9);
    while (1) {
        if (!dataSize) {
            if (serverTcpSocket->bytesAvailable() < sizeof(quint16)) {
                break;
            }
                in >> dataSize;
            }
        qDebug() << "byte = " << serverTcpSocket->bytesAvailable() << endl;
            if (serverTcpSocket->bytesAvailable() < dataSize) {
                break;
            }
            QString action;

            in >> action;
            if (action == "change"){
                QString type;
                int amount;
                int cell;
               in >> type >> amount >> cell;
               table->cells[cell].setParametrs(type, amount);
               refreshGameField();
            }
            else if (action == "game"){
                startGame();
            }
            dataSize = 0;
    }
}

void GameWindow::slotError(QAbstractSocket::SocketError err)
{
    QString strError =
                "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                             "The host was not found." :
                             err == QAbstractSocket::RemoteHostClosedError ?
                             "The remote host is closed." :
                             err == QAbstractSocket::ConnectionRefusedError ?
                             "The connection was refused." :
                             QString(clientTcpSocket->errorString()));
        qDebug() << strError;
}

void GameWindow::slotSendChangeToServer(const int &cell, const QString &type, const int &amount)
{
    qDebug() << "slotSendChangeToServer" << endl;
    QString action = "change";
    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_9);
    out << quint16(0) << action << cell << type << amount;
    out.device()->seek(0);
    qDebug() << action << cell << type << amount << endl;
    out << quint16(buffer.size() - sizeof(quint16));
    clientTcpSocket->write(buffer);
}

void GameWindow::slotSendNewGameToServer()
{
    qDebug() << "slotSendNewGameToServer" << endl;
    QString action = "game";
    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_9);
    out << quint16(0) << action;
    out.device()->seek(0);
    out << quint16(buffer.size() - sizeof(quint16));
    clientTcpSocket->write(buffer);
}

void GameWindow::slotConnected()
{
    qDebug() << "Connections to host" << endl;
    startGame();
}


void GameWindow::slotSendNewGameToClient()
{
    qDebug() << "slotSendNewGameToClient" << endl;
    QString action = "game";
    QByteArray  buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_9);
    out << quint16(0) << action;
    out.device()->seek(0);
    out << quint16(buffer.size() - sizeof(quint16));
    serverTcpSocket->write(buffer);
}
