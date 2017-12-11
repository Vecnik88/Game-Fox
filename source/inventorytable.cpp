#include "include/inventorytable.h"

InventoryTable::InventoryTable(const size_t &rowsSrc,
                               const size_t &colsSrc):
                               QTableWidget(rowsSrc, colsSrc)
{
    rows = rowsSrc;
    cols = colsSrc;
    cells.resize(rows * cols);

    // формируем таблицу
    setMaximumSize(300, 300);
    setMinimumWidth(300);
    setMinimumHeight(300);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setDragDropMode(QAbstractItemView::DragDrop);
    setColumnWidth(0, 100);
    setColumnWidth(1, 100);
    setColumnWidth(2, 100);
    setRowHeight(0, 100);
    setRowHeight(1, 100);
    setRowHeight(2, 100);
    setIconSize(QSize(92, 92));
    setDragDropOverwriteMode(true);
    setDropIndicatorShown(true);

    connect(this, &InventoryTable::itemClicked, this, &InventoryTable::removeInventory);
}
// добавляет предмет в таблицу
void InventoryTable::appendSubject(const size_t row, const size_t col)
{
    size_t cell = row * cols + col;
    cells[cell].appendAmount();

    for (int i = 0; i < rows*cols; ++i) {
        qDebug() << i << " " << cells[i].getAmount() << " " << cells[i].getType() << endl;
    }
}
// удаляет предмет из таблицы
void InventoryTable::removeSubject(QTableWidgetItem *item)
{
    size_t cell = item->row() * cols + item->column();
    qDebug() << "cell = " << cell << endl;
    if (!cells[cell].getAmount())
        return;

    cells[cell].removeAmount();
    QSound::play(SOUND_FOX);
    if (!cells[cell].getAmount())
        item->setIcon(QIcon());
}

void InventoryTable::removeInventory(QTableWidgetItem *item)
{
    this->removeSubject(item);
}

void InventoryTable::dragEnterEvent(QDragEnterEvent *event)
{
    QTableWidget::dragEnterEvent(event);
}

void InventoryTable::mouseReleaseEvent(QMouseEvent *event)
{
    event->
}

void InventoryTable::dragMoveEvent(QDragMoveEvent *event)
{
    QTableWidget::dragMoveEvent(event);
}

void InventoryTable::dragLeaveEvent(QDragLeaveEvent *event)
{
    QTableWidget::dragLeaveEvent(event);
}

void InventoryTable::dropEvent(QDropEvent *event)
{
    QPoint position = event->pos();
    size_t row = this->rowAt(position.y());
    size_t col = this->columnAt(position.x());
    this->appendSubject(row, col);
    //qDebug() << (row * cols + col) << endl;

    QTableWidget::dropEvent(event);
}
