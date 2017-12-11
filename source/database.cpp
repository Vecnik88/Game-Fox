#include "include/database.h"

DataBase::DataBase(const QString &nameDB,
                   const QString &srcHostName,
                   const size_t  &amountCells,
                   const QString &typeSrc,
                   const QString &pathSrc,
                         QObject *parent) :
                         QObject (parent)
{
    name = nameDB;
    hostName = srcHostName;
    amountKey = amountCells;
    type = typeSrc;
    path = pathSrc;
}

DataBase::~DataBase()
{

}

// подключает к базе данных
bool DataBase::connectToDataBase()
{
    if (!QFile(name).exists()) {
        if (this->restoreDataBase())
            return true;
    } else {
        if (this->openDataBase())
            return true;
    }
    qDebug() << "<connectToDataBase> problem with connect to database" << endl;
    return false;
}

//восстанавливает базу данных
bool DataBase::restoreDataBase()
{
    if (this->openDataBase()) {
        if (!this->createTable()) {
            qDebug() << "<restoreDataBase> problem with create table" << endl;
            return false;
        } else {
            return true;
        }
    } else {
        qDebug() << "<restoreDataBase> problem with restore database" << endl;
        return false;
    }
    return false;
}

// открывает базу данных, если она существует
bool DataBase::openDataBase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(hostName);
    db.setDatabaseName(name);
    if (db.open())
        return true;

    return false;
}

// закрывает базу данных
void DataBase::closeDataBase()
{
    db.close();
}

bool DataBase::createTable()
{
    const QString createTableSubject = "CREATE TABLE " NAME_TABLE_SUBJECT
                                       " (id INTEGER PRIMARY KEY NOT NULL, "
                                       TABLE_TYPE   " VARCHAR(255),"
                                       TABLE_PATH   " VARCHAR(255))";

    const QString createTableInventory = "CREATE TABLE " NAME_TABLE_INVENTORY
                                         " (id INTEGER PRIMARY KEY NOT NULL, "
                                         TABLE_TYPE     " VARCHAR(255),"
                                         TABLE_AMOUNT   " INTEGER)";
    QSqlQuery query;
    if (!query.exec(createTableSubject) || !query.exec(createTableInventory)) {
            qDebug() << "< createTable > error of create database" << endl;
            qDebug() << query.lastError().text();
            return false;
    }
    QString strF = "INSERT INTO " NAME_TABLE_SUBJECT " (id, " TABLE_TYPE ", " TABLE_PATH ") "
                   "VALUES (%1, '%2', '%3');";
    QString str = strF.arg("1").arg(type).arg(path);
    if (!query.exec(str)) {
        qDebug() << "< createTable > error init database " NAME_TABLE_SUBJECT << endl;
        qDebug() << query.lastError().text();
        return false;
    }
    for (size_t i = 0; i < amountKey; ++i) {
        strF = "INSERT INTO " NAME_TABLE_INVENTORY " (id, " TABLE_TYPE ", " TABLE_AMOUNT ") "
               "VALUES (%1, '%2', %3);";
        str = strF.arg(QString::number(i)).arg(type).arg(QString::number(0));
        if (!query.exec(str)) {
            qDebug() << str << endl;
            qDebug() << "< createTable > error init database " << i << NAME_TABLE_INVENTORY << endl;
            qDebug() << query.lastError().text();
            return false;
        }
    }
    return true;
}

bool DataBase::insertIntoTable(Subject           *subject,
                               QVector<InfoCell> &cells)
{
    QSqlQuery query;
    QString strF = "INSERT or REPLACE INTO " NAME_TABLE_SUBJECT " (id, " TABLE_TYPE ", " TABLE_PATH ") "
                   "VALUES (%1, '%2', '%3');";
    QString str = strF.arg("1").arg(subject->getType()).arg(subject->getPath());
    if (!query.exec(str)) {
        qDebug() << "< insertIntoTable > error insert to database " NAME_TABLE_SUBJECT << endl;
        qDebug() << query.lastError().text();
        return false;
    }
    for (size_t i = 0; i < amountKey; ++i) {
        strF = "INSERT or REPLACE INTO " NAME_TABLE_INVENTORY " (id, " TABLE_TYPE ", " TABLE_AMOUNT ") "
               "VALUES (%1, '%2', %3);";
        str = strF.arg(QString::number(i))
                  .arg(cells[i].getType())
                  .arg(QString::number(cells[i].getAmount()));

        if (!query.exec(str)) {
            qDebug() << str << endl;
            qDebug() << "< insertIntoTable > error insert to database " << i << NAME_TABLE_INVENTORY << endl;
            qDebug() << query.lastError().text();
            return false;
        }
    }
    return true;
}

bool DataBase::getIntoTable(Subject *subject, QVector<InfoCell> &cells)
{
    QSqlQuery query;
    if (!query.exec("SELECT * FROM " NAME_TABLE_SUBJECT ";")) {
        qDebug() << "< getIntoTable > error get into " << NAME_TABLE_SUBJECT;
        qDebug() << query.lastError().text() << endl;
        return false;
    }
    QSqlRecord rec = query.record();
    while (query.next()) {
        QString type = query.value(rec.indexOf(TABLE_TYPE)).toString();
        QString path = query.value(rec.indexOf(TABLE_PATH)).toString();
        subject->setParametrs(type, path);
    }
    query.clear();
    rec.clear();
    if (!query.exec("SELECT * FROM " NAME_TABLE_INVENTORY ";")) {
        qDebug() << "< getIntoTable > error get into " << NAME_TABLE_INVENTORY;
        qDebug() << query.lastError().text() << endl;
        return false;
    }
    rec = query.record();
    while (query.next()) {
        int num = query.value(rec.indexOf("id")).toInt();
        QString type = query.value(rec.indexOf(TABLE_TYPE)).toString();
        size_t amount = query.value(rec.indexOf(TABLE_AMOUNT)).toInt();
        cells[num].setParametrs(type, amount);
    }
    return true;
}

bool DataBase::initParametrs(Subject *subject, QVector<InfoCell> &cells)
{
    return getIntoTable(subject, cells);
}
