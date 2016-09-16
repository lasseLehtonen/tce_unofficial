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
    void convert(qint64 src, qint64 dst, qint64 dstBits1, qint64 dstBits2, qint64 dstVectorization, qint64 srcBits1, qint64 srcBits2, qint64 srcVectorization, QString text);

private:
    QString floatToBin(QString f, qint64 e, qint64 m);
    QString floatToFixed(QString f, qint64 e, qint64 m);
    QString bitsToFloat(QString f, qint64 e, qint64 m);
    QString bitsToFixed(QString f, qint64 e, qint64 m);

    QString hexToBin(QString s);
    QString binToHex(QString s);
    qint64 bitsToInt(QString s);
    QString text_;
};

#endif // WORKER_H
