#include "include/subject.h"

Subject::Subject(const QString &typeSrc,
                 const QString &pathSrc):
                       QTableWidget(1, 1)
{
    type = typeSrc;
    path = pathSrc;
    item = new QTableWidgetItem();

    // формируем внешний вид виджета
    setFixedSize(100, 100);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setDragEnabled(true);
    setColumnWidth(0, 100);
    setRowHeight(0, 100);
    setIconSize(QSize(92, 92));
    setDragDropOverwriteMode(true);
    setDropIndicatorShown(true);
    Delegate *delegate = new Delegate();
    setItemDelegate(delegate);
}

Subject::~Subject()
{
    delete item;
}

const QString &Subject::getPath()
{
    return path;
}

const QString &Subject::getType()
{
    return type;
}

void Subject::setParametrs(const QString &typeSrc,
                           const QString &pathSrc)
{
    path = pathSrc;
    type = typeSrc;
    item->setIcon(QIcon(QPixmap(path)));
    setItem(0, 0, item);
}



