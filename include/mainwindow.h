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

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(const QString &type,
                        const QString &path,
                              QWidget *parent = Q_NULLPTR);
    ~MainWindow();

public slots:
    void runGame();
    void runGameClient();
    void runGameServer();
    void stopGame();

private:
    QWidget             *mainMenu;
    QWidget             *gameField;
    Subject             *subject;
    InventoryTable      *table;
    DataBase            *db;
    QPushButton         *menuGame;
};

#endif // MAINWINDOW_H
