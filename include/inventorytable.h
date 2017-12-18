#ifndef INVENTORYTABLE_H
#define INVENTORYTABLE_H

#include <QVector>
#include <QDebug>
#include <QtWidgets>
#include <QTableWidget>
#include <QDragEnterEvent>
#include <QtMultimedia/QSound>

#include "include/infocell.h"
#include "include/sourcedata.h"

// содержит игровой инвентарь
class InventoryTable : public QTableWidget
{
    Q_OBJECT
public:
    InventoryTable(const size_t &rowsSrc,
                   const size_t &colsSrc);

    // обновляет таблицу с инвентарем
    void refreshTable();
    // информация о таблице инвентаря
    QVector<InfoCell> cells;
signals:
    // посылает сигнал что необходимо синхронизировать данные,
    // когда игра происходит по сети
    void addMessageToSocket(int     cell,
                            QString type,
                            int     amount);

private:
    size_t cols;
    size_t rows;
    size_t sizeTable;

    QPoint dragStartPosition;
    QRect  highlightedRect;
    void createTable();

private slots:
    void dropEvent(QDropEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
};

#endif // INVENTORYTABLE_H
