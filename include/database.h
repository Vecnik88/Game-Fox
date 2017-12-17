#ifndef DATABASE_H
#define DATABASE_H

#include <QSql>
#include <QFile>
#include <QDate>
#include <QDebug>
#include <QObject>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlDatabase>

#include "include/subject.h"
#include "include/infocell.h"
#include "include/sourcedata.h"

/***********************************
 * представляет базу данных SQLite *
 * *********************************/
class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(const size_t  &amountCells = 0,
                            QObject *parent      = Q_NULLPTR);
    ~DataBase();

    // присоединяется к базе данных
    bool connectToDataBase();
    // присваивает значение объектам, из базы данных
    bool getIntoTable(Subject *subject, QVector<InfoCell> &cells);
    // инициализирует исходные параметры, при старте игры
    bool initParametrs(Subject *subject, QVector<InfoCell> &cells);
    // вставляет данные из объектов в таблицы
    bool insertIntoTable(Subject           *subject,
                         QVector<InfoCell> &cells);
private:
    QSqlDatabase    db;
    QString         name;
    QString         type;
    QString         path;
    QString         hostName;
    size_t          amountKey;

    // методы для настройки базы данных
    bool createTable();
    bool openDataBase();
    void closeDataBase();
    bool restoreDataBase();
};

#endif // DATABASE_H
