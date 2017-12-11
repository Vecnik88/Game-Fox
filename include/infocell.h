#ifndef INFOCELL_H
#define INFOCELL_H

#include <QString>

class InfoCell
{
public:
    explicit InfoCell();
    ~InfoCell();

    size_t getAmount();
    QString getType();
    void appendAmount(size_t val = 1);
    void removeAmount(size_t val = 1);
    void setParametrs(const QString &srcType,
                      const size_t  &srcAmount);
private:
    QString type;
    size_t  amount;
};

#endif // INFOCELL_H
