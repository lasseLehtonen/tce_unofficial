#ifndef SIGNAL_H
#define SIGNAL_H

#include <QObject>
#include <QString>
#include <map>
#include <utility>

class Signal : public QObject
{
    Q_OBJECT
public:
    explicit Signal(QObject *parent = 0);

signals:

public slots:
    QString type(int x, int y);
    void addType(int x, int y, QString type);
    QString value(int x, int y);
    void addValue(int x, int y, QString value);

private:
    std::map<std::pair<int, int>, QString> type_;
    std::map<std::pair<int, int>, QString> value_;
};

#endif // SIGNAL_H
