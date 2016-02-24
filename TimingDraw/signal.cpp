#include "signal.h"
#include <QDebug>

Signal::Signal(QObject *parent) : QObject(parent)
{

}

QString Signal::type(int x, int y)
{
    qDebug() << "Looking for " << x << y;
    QString retval = "hi";
    for (int Y = y; Y >= 0; --Y) {
        std::pair<int, int> p(x, Y);
        if (type_.find(p) != type_.end() ) {
            qDebug() << "found";
            retval = type_[p];
            break;
        }
    }
    qDebug() << x << y << " => " << retval;
    return retval;
}

void Signal::addType(int x, int y, QString type)
{
    qDebug() << x << y << " <= " << type;
    std::pair<int, int> p(x, y);
    type_[p] = type;
}

QString Signal::value(int x, int y)
{
    std::pair<int, int> p(x, y);
    if (value_.find(p) != value_.end())
        return value_[p];
    return "";
}

void Signal::addValue(int x, int y, QString value)
{
    std::pair<int, int> p(x, y);
    value_[p] = value;
}

