#ifndef SUBJECT_H
#define SUBJECT_H

#include <QDrag>
#include <QIcon>
#include <QString>
#include <QFrame>
#include <QtWidgets>
#include <QTableWidget>

#include "include/sourcedata.h"

// описывает игровой предмет
class Subject : public QFrame
{
    Q_OBJECT
public:
    explicit Subject(const QString &typeSrc = "",
                     const QString &pathSrc = "",
                           QWidget *parent  = Q_NULLPTR);
    ~Subject();
    // возвращает тип объекта
    const QString &getType();
    // возвращает количество объектов
    const QString &getPath();
    // устанавливает необходимые параметры
    void setParametrs(const QString &typeSrc,
                      const QString &pathSrc);
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    QString             type;
    QString             path;
    QLabel             *subject;
    QPoint              dragStartPosition;
};

#endif // SUBJECT_H
