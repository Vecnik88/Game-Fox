#ifndef DELEGATE_H
#define DELEGATE_H

#include <QtWidgets>
#include <QStyledItemDelegate>
#include <QDrag>
#include <QDebug>

class QDrag;

class Delegate: public QStyledItemDelegate
{
public:
    explicit Delegate(QObject *parent = Q_NULLPTR);

protected:
    void paint(      QPainter             *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex          &index) const;

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex          &index ) const;
};

#endif // DELEGATE_H
