#ifndef SUBJECT_H
#define SUBJECT_H

#include <QIcon>
#include <QString>
#include <QTableWidget>

/*
 * Класс "Предмет", описывает тип предмета и исходник изображения
*/
class Subject : public QTableWidget
{
public:
    explicit Subject(const QString &typeSrc = "",
                     const QString &pathSrc = "");
    ~Subject();

    const QString &getType();
    const QString &getPath();

    void setParametrs(const QString &typeSrc,
                      const QString &pathSrc);
private:
    QString             type;
    QString             path;
    QTableWidgetItem   *item;
};

#endif // SUBJECT_H
