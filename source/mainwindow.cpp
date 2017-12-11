#include "include/mainwindow.h"

#define WIDTH           600
#define HEIGHT          400
#define OFFSET_X        100
#define OFFSET_Y        100
#define DATABASE_NAME   "/home/anton/qt_project/red/database/gameFox"
#define ROWS_TABLE      3
#define COLS_TABLE      3

MainWindow::MainWindow(const QString &type,
                       const QString &path,
                             QWidget *parent) :
                             QWidget (parent)
{
    // проверяем базу данных
    db = new DataBase(DATABASE_NAME,
                      "SQLHOST",
                      ROWS_TABLE*COLS_TABLE,
                      type,
                      path);
    if (!db->connectToDataBase())
        qDebug() << "< MainWindow > error connect to database" << endl;

    table = new InventoryTable(COLS_TABLE, ROWS_TABLE);
    subject = new Subject;
    subject->verticalHeader()->hide();
    subject->horizontalHeader()->hide();

    if (!db->initParametrs(subject, table->cells))
        qDebug() << "< MainWindow > error init parametrs with database" << endl;

    menuGame = new QPushButton("Главное меню");
    menuGame->setEnabled(false);

    // создаем виджет главного меню
    mainMenu = new QWidget;
    QPushButton *exit = new QPushButton("Выход");
    QPushButton *run = new QPushButton("Начать 1 игрок");
    QPushButton *runClient = new QPushButton("Игра по сети(Клиент)");
    QPushButton *runServer = new QPushButton("Игра по сети(Сервер)");
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

    // создаем игровое поле
    gameField = new QWidget;
    table->verticalHeader()->hide();
    table->horizontalHeader()->hide();
    QGridLayout *grd = new QGridLayout;
    grd->addWidget(table, 0, 0, 2, 2, Qt::AlignHCenter);
    grd->addWidget(subject, 0, 3, 2, 2, Qt::AlignHCenter);
    gameField->setLayout(grd);
    gameField->setEnabled(false);

    // создаем окончательный вид сцены
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(mainMenu);
    mainLayout->addWidget(gameField);
    mainLayout->addWidget(menuGame);
    this->setLayout(mainLayout);
    this->setGeometry(OFFSET_X, OFFSET_Y, WIDTH, HEIGHT);

    // соединяем необходимые нам сигналы со слотами
    connect(run, SIGNAL(clicked(bool)), SLOT(runGame()));
    connect(exit, SIGNAL(clicked(bool)), SLOT(close()));
    connect(runClient, SIGNAL(clicked(bool)), SLOT(runGameClient()));
    connect(runServer, SIGNAL(clicked(bool)), SLOT(runGameServer()));
    connect(menuGame, SIGNAL(clicked(bool)), SLOT(stopGame()));
}

void MainWindow::runGame()
{
    table->clear();
    gameField->setEnabled(true);
    menuGame->setEnabled(true);
    mainMenu->hide();
}

void MainWindow::runGameClient()
{

}

void MainWindow::runGameServer()
{

}

void MainWindow::stopGame()
{
    gameField->setEnabled(false);
    menuGame->setEnabled(false);
    mainMenu->show();
}

MainWindow::~MainWindow()
{
    delete table;
    delete mainMenu;
    delete gameField;
    delete subject;
    delete table;
    delete db;
    delete menuGame;
}
