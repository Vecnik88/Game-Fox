#include "include/mainwindow.h"
#include "include/sourcedata.h"

GameWindow::GameWindow(QWidget *parent):
                       QWidget (parent)
{
    gameInit();

    // соединяем необходимые нам сигналы со слотами
    connect(run, SIGNAL(clicked(bool)), SLOT(runGame()));
    connect(exit, SIGNAL(clicked(bool)), SLOT(close()));
    connect(runClient, SIGNAL(clicked(bool)), SLOT(runGameClient()));
    connect(runServer, SIGNAL(clicked(bool)), SLOT(runGameServer()));
    connect(menuGame, SIGNAL(clicked(bool)), SLOT(stopGame()));
}

void GameWindow::runGame()
{
    gameStatus = SIMPLE_GAME;
    table->initTable();
    gameField->setEnabled(true);
    menuGame->setEnabled(true);
    mainMenu->hide();
}

void GameWindow::runGameClient()
{
    gameStatus = CLIENT;
}

void GameWindow::runGameServer()
{
    gameStatus = SERVER;
}

void GameWindow::stopGame()
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

// создает главное меню
void GameWindow::createMainMenu()
{
    // создаем виджет главного меню
    mainMenu = new QWidget;
    exit = new QPushButton("Выход");
    run = new QPushButton("Начать 1 игрок");
    runClient = new QPushButton("Игра по сети(Клиент)");
    runServer = new QPushButton("Игра по сети(Сервер)");
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
    menuGame = new QPushButton("Главное меню(Игра сохранится)");
    menuGame->setEnabled(false);
}

// создает игровое поле
void GameWindow::createGameField()
{
    db = new DataBase(ROWS_TABLE * COLS_TABLE);
    if (!db->connectToDataBase())
        qDebug() << "< MainWindow > error connect to database" << endl;

    table = new InventoryTable(COLS_TABLE, ROWS_TABLE);
    qDebug() << "debug 8" << endl;
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

GameWindow::~GameWindow()
{
    delete table;
    delete mainMenu;
    delete gameField;
    delete subject;
    delete table;
    delete db;
    delete menuGame;
}
