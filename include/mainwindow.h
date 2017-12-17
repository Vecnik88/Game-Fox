#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QtWidgets>
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

/****************/
/* Игровое окно */
/* **************/
class GameWindow : public QWidget
{
    Q_OBJECT
public:
    explicit GameWindow(QWidget *parent = Q_NULLPTR);
    ~GameWindow();

public slots:
    // запускает игру
    void runGame();
    // останавливает игру(сохраняя)
    void stopGame();
    // запускает игру как клиент
    void runGameClient();
    // запускает игру как сервер
    void runGameServer();

private:
    DataBase            *db;
    InventoryTable      *table;
    Subject             *subject;
    QWidget             *mainMenu;
    QWidget             *gameField;
    int                  gameStatus;

    QPushButton         *run;
    QPushButton         *exit;
    QPushButton         *menuGame;
    QPushButton         *runClient;
    QPushButton         *runServer;

    // инициализирует/создают игровое поле
    void gameInit();
    void createMainMenu();
    void createGameMenu();
    void createGameField();
    void createGameWindow();
};

#endif // MAINWINDOW_H
