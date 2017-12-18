#ifndef INFOCELL_H
#define INFOCELL_H

#include <QString>

// описывает ячейку таблицы
class InfoCell
{
public:
    explicit InfoCell();
    ~InfoCell();

    // возвращает количество элементов
    size_t getAmount();
    // возвращает тип объекта
    QString getType();
    // очищает объект
    void clear();
    // добавляет указанное количество к текущему(по умолчанию +1)
    void appendAmount(size_t val = 1);
    // отнимает указанное количество от текущего(по умолчанию -1)
    void removeAmount(size_t val = 1);
    // устанавливает параметры для объекта
    void setParametrs(const QString &srcType,
                      const size_t  &srcAmount);
private:
    QString type;
    size_t  amount;
};

#endif // INFOCELL_H
