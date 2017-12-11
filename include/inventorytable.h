#ifndef INVENTORYTABLE_H
#define INVENTORYTABLE_H

#include <QVector>
#include <QDebug>
#include <QTableWidget>
#include <QDragEnterEvent>
#include <QtMultimedia/QSound>

#include "include/infocell.h"
#include "include/delegate.h"

#define SOUND_FOX "/home/anton/qt_project/red/sound/fox.wav"

class InventoryTable : public QTableWidget
{
public:
    InventoryTable(const size_t &rowsSrc,
                   const size_t &colsSrc);

    void appendSubject(const size_t row,
                       const size_t col);
    void removeSubject(QTableWidgetItem *item);

    QVector<InfoCell> cells;

private:
    size_t cols;
    size_t rows;

private slots:
    void removeInventory(QTableWidgetItem *item);
    void dropEvent(QDropEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void mouseReleaseEvent(QMouseEvent* event);
};

#endif // INVENTORYTABLE_H
