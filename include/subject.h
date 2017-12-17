#ifndef SUBJECT_H
#define SUBJECT_H

#include <QIcon>
#include <QString>
#include <QTableWidget>
#include <QFrame>
#include <QtWidgets>
#include <QDrag>

#include "include/sourcedata.h"

/*******************************************
 * Класс "Предмет", описывает тип предмета *
 * и путь где лежит исходное изображение   *
 *******************************************/
class Subject : public QFrame
{
    Q_OBJECT
public:
    explicit Subject(const QString &typeSrc = "",
                     const QString &pathSrc = "",
                           QWidget *parent = 0);
    ~Subject();

    const QString &getType();
    const QString &getPath();

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
