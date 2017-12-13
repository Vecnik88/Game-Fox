#include "include/inventorytable.h"

InventoryTable::InventoryTable(const size_t &rowsSrc,
                               const size_t &colsSrc):
                               QTableWidget(rowsSrc, colsSrc)
{
    rows = rowsSrc;
    cols = colsSrc;
    cells.resize(rows * cols);

    // формируем таблицу
    setFixedSize(300, 300);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setDragDropMode(QAbstractItemView::DragDrop);

    for (size_t i = 0; i < cols; ++i) {
        setColumnWidth(i, 100);
        setRowHeight(i, 100);
    }
    setIconSize(QSize(92, 92));
    setDragDropOverwriteMode(true);
    setDropIndicatorShown(true);
    Delegate *delegate = new Delegate();
    setItemDelegate(delegate);
    connect(this, &InventoryTable::itemClicked, this, &InventoryTable::removeInventory);
}
// добавляет предмет в таблицу
void InventoryTable::appendSubject(const size_t row, const size_t col)
{
    size_t cell = row * cols + col;
    cells[cell].appendAmount();

    for (size_t i = 0; i < rows*cols; ++i) {
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
    QTableWidget::dropEvent(event);
    QPoint position = event->pos();
    QString str = this->indexAt(position).data().toString();
    qDebug() << "str = " << str << endl;
    size_t row = this->rowAt(position.y());
    size_t col = this->columnAt(position.x());
    this->appendSubject(row, col);
    //qDebug() << (row * cols + col) << endl;


}
