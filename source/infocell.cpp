#include "include/infocell.h"

InfoCell::InfoCell(): type(""), amount(0)
{

}

InfoCell::~InfoCell()
{

}

void InfoCell::setParametrs(const QString &srcType,
                            const size_t  &srcAmount)
{
    type = srcType;
    amount = srcAmount;
}

void InfoCell::appendAmount(size_t val)
{
    amount += val;
}

void InfoCell::removeAmount(size_t val)
{
    amount -= val;
}

size_t InfoCell::getAmount()
{
    return amount;
}

QString InfoCell::getType()
{
    return type;
}

void InfoCell::clear()
{
    amount = 0;
    type = "";
}
