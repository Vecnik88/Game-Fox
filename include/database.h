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

// имена таблиц в базе данных
#define NAME_TABLE_SUBJECT      "Subject"
#define NAME_TABLE_INVENTORY    "Inventory"

// имена полей в таблицах базы данных
#define TABLE_TYPE              "Type"
#define TABLE_PATH              "Path"
#define TABLE_AMOUNT            "Amount"

// представляет базу данных SQLite
class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(const QString &nameDB,
                      const QString &srcHostName,
                      const size_t  &amountCells,
                      const QString &typeSrc,
                      const QString &pathSrc,
                            QObject *parent = 0);
    ~DataBase();

    bool connectToDataBase();
    bool getIntoTable(Subject *subject, QVector<InfoCell> &cells);
    bool initParametrs(Subject *subject, QVector<InfoCell> &cells);
    bool insertIntoTable(Subject           *subject,
                         QVector<InfoCell> &cells);
private:
    QSqlDatabase    db;
    QString         name;
    QString         hostName;
    QString         type;
    QString         path;
    size_t          amountKey;

    // методы для настройки базы данных
    bool createTable();
    bool openDataBase();
    void closeDataBase();
    bool restoreDataBase();
};

#endif // DATABASE_H
