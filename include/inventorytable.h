#ifndef INVENTORYTABLE_H
#define INVENTORYTABLE_H

#include <QVector>
#include <QDebug>
#include <QTableWidget>
#include <QDragEnterEvent>
#include <QtMultimedia/QSound>
#include <QtWidgets>

#include "include/infocell.h"
#include "include/sourcedata.h"

class InventoryTable : public QTableWidget
{
    Q_OBJECT
public:
    InventoryTable(const size_t &rowsSrc,
                   const size_t &colsSrc);

    QVector<InfoCell> cells;

private:
    size_t cols;
    size_t rows;
    size_t sizeTable;

    QPoint dragStartPosition;
    QRect  highlightedRect;
    void initTable();

private slots:
    void dropEvent(QDropEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
};

#endif // INVENTORYTABLE_H
