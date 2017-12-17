#include "include/inventorytable.h"

InventoryTable::InventoryTable(const size_t &rowsSrc,
                               const size_t &colsSrc):
                               QTableWidget(rowsSrc, colsSrc)
{
    rows = rowsSrc;
    cols = colsSrc;
    sizeTable = rows * cols;
    cells.resize(sizeTable);
    createTable();
}

void InventoryTable::initTable()
{
    for (size_t col = 0; col < cols; ++col) {
        for (size_t row = 0; row < rows; ++row) {
            QTableWidgetItem *item = new QTableWidgetItem(QString(""));
            size_t cell = col * rows + row;
            if (cells[cell].getAmount()) {
                item->setIcon(QIcon(QPixmap(PATH_IMAGE)));
                item->setText(QString::number(cells[cell].getAmount()));
            }

            item->setTextAlignment(Qt::AlignBottom | Qt::AlignRight);
            this->setItem(col, row, item);
        }
    }
}

void InventoryTable::createTable()
{
    // формируем таблицу
    setFixedSize(300, 300);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setDragDropMode(QAbstractItemView::DragDrop);
    horizontalHeader()->hide();
    verticalHeader()->hide();
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    verticalHeader()->setDefaultSectionSize(120);
    horizontalHeader()->setDefaultSectionSize(120);
    setDragEnabled(true);
    setAcceptDrops(true);
    setDragDropOverwriteMode(true);
    setDragDropMode(QAbstractItemView::DragDrop);
    setDefaultDropAction(Qt::MoveAction);
    setDropIndicatorShown(true);
    setDragDropOverwriteMode(true);
    setIconSize(QSize(70, 70));

    for (size_t i = 0; i < sizeTable; ++i) {
        setColumnWidth(i, 100);
        setRowHeight(i, 100);
    }
}


void InventoryTable::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        event->acceptProposedAction();
    } else {
        event->accept();
    }
}

void InventoryTable::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        QByteArray buffer = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&buffer, QIODevice::ReadOnly);

        int amount;
        QPixmap pixmap;
        QPoint oldPosition;
        QString type;
        size_t currentCell = rowAt(event->pos().y()) * cols + columnAt(event->pos().x());

        dataStream >> pixmap >> amount >> type >> oldPosition;

        QTableWidgetItem *item = new QTableWidgetItem();
        item->setIcon(QIcon(QPixmap(pixmap)));
        if (itemAt(oldPosition)) { // если перемещаем внутри таблицы
            itemAt(oldPosition)->setSelected(false);
            size_t oldCell = itemAt(oldPosition)->row() * rows + itemAt(oldPosition)->column();
            if (oldCell == currentCell)
                return;

            cells[currentCell].appendAmount(cells[oldCell].getAmount());
            cells[oldCell].clear();
            item->setText(QString::number(cells[currentCell].getAmount()));
            delete itemAt(oldPosition);
        }
        else { // если добавляем новый
                cells[currentCell].appendAmount();
                item->setText(QString::number(cells[currentCell].getAmount()));
        }
        item->setTextAlignment(Qt::AlignBottom | Qt::AlignRight);
        setItem(rowAt(event->pos().y()), columnAt(event->pos().x()), item);
        event->acceptProposedAction();
        event->accept();
    }
    else {
        event->accept();
    }
}

void InventoryTable::mousePressEvent(QMouseEvent *event)
{
    if (itemAt(event->pos())) {
        QTableWidgetItem *item = itemAt(event->pos());
        size_t currentCell = item->row() * rows + item->column();
        item->setSelected(true);
        if (event->button() == Qt::LeftButton) {
            QPixmap pixmap = item->icon().pixmap(QSize(100,100));
            int amount;
            QByteArray itemData;
            QDataStream dataStream(&itemData, QIODevice::WriteOnly);
            QString subjectType = cells[currentCell].getType();
            amount = cells[currentCell].getAmount();
            if (!amount) { // если ячейка пуста
                item->setSelected(false);
                return;
            }

            dataStream << pixmap << amount << subjectType << event->pos();
            QMimeData *mimeData = new QMimeData;
            mimeData->setData("application/x-dnditemdata", itemData);
            QDrag *drag = new QDrag(this);
            drag->setMimeData(mimeData);
            drag->setPixmap(pixmap);
            drag->setHotSpot(event->pos() - QPoint(item->column() * 100, item->row() * 100));
            drag->exec(Qt::CopyAction);
        }
        else if (event->button() == Qt::RightButton) {
            if (cells[currentCell].getAmount())
                QSound::play(SOUND_FOX);

            if (cells[currentCell].getAmount() > 1) {
                cells[currentCell].removeAmount();
                item->setText(QString::number(cells[currentCell].getAmount()));
            }
            else {
                cells[currentCell].clear();
                item->setSelected(false);
                delete item;
            }
        }
    }
}

void InventoryTable::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")){
        event->acceptProposedAction();
        QAbstractItemView *d = reinterpret_cast<QAbstractItemView*>(this);
        QModelIndex index = indexAt(event->pos());
        highlightedRect = d->visualRect(index);

        viewport()->update();
    }
    else {
        event->accept();
    }
}

void InventoryTable::paintEvent(QPaintEvent *event)
{
    QTableWidget::paintEvent(event);
    QPainter painter(this->viewport());
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::blue);
    painter.drawRect(highlightedRect);
}
