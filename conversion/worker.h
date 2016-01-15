#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QFile>

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = 0);

signals:
    void textUpdated(QString text);
    void converted(QString text);
    void sourceError();

public slots:
    void droppedText(QString dt);
    void convert(qint64 src, qint64 dst, qint64 bits1, qint64 bits2, qint64 bits3, QString text);

private:
    QString floatToBin(QString f, qint64 e, qint64 m);
    QString floatToFixed(QString f, qint64 e, qint64 m);
    QString text_;
};

#endif // WORKER_H
