#include "worker.h"

Worker::Worker(QObject *parent) : QObject(parent)
{
}

void Worker::droppedText(QString dt)
{
    dt = dt.trimmed();
    if(!dt.startsWith("file://")) {
        qDebug() << "Dropped type not supported";
    }

    if(dt.startsWith("file://")) {
        dt = dt.right(dt.size() - 7);
    }

    QFile fin(dt);
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Opening file" << dt << "failed";
        return;
    }

    text_ = fin.readAll();
    emit textUpdated(text_);

}

void Worker::convert(qint64 src, qint64 dst, qint64 bits1, qint64 bits2, qint64 bits3, QString text)
{
    qDebug() << src << dst << bits1 << bits2 << bits3 << text;

    QStringList ls = text.split(QRegExp("\\s"),QString::SkipEmptyParts);
    QStringList result;

    switch (src) {
    case 0: {
        if ( dst == 0) {
            for (auto s : ls) {
                result << floatToBin(s, bits1, bits2);
            }
        } else {
            for (auto s : ls) {
                result << floatToFixed(s, bits1, bits2);
            }
        }
        break;
    }
    case 1: {
        break;
    }
    case 2: {
        break;
    }
    default: {
        qDebug() << "error: Default reached";
        return;
    }
    }

    QString retval;
    int cnt = 0;
    for (auto s : result) {
        retval += s; cnt++;
        if (cnt >= bits3) {
            retval += "\r\n";
            cnt = 0;
        }
    }

    emit converted(retval);
}

QString Worker::floatToBin(QString f, qint64 e, qint64 m)
{
    bool ok;
    double d = f.toDouble(&ok);

    if (!ok) {
        qDebug() << "Failure::floatToBin";
        emit sourceError();
        return QByteArray(1+e+m, '0');
    }

    qDebug() << "Converting" << d;

    QString retval;

    if (d < 0 ) {
        retval += "1";
        d *= -1;
    } else {
        retval += "0";
    }

    int expMod = 0;
    while( !(d<1.0) ) {
        d /= 2;
        expMod++;
    }

    quint64 b = static_cast<quint64>(d * exp2(m+1));

    QString frac;
    QString exp;

    for (quint64 i = 0; i < m+1; ++i) {
        quint64 mask = static_cast<quint64>(1) << i;
        if (b & mask) {
            frac.push_front("1");
        } else {
            frac.push_front("0");
        }
    }
    qDebug()  << "frac" << frac << frac.size();

    int firstOne = frac.indexOf("1");
    if (firstOne == -1) {
        // zero
        qDebug() << "Returning " << 1+e+m;
        return QByteArray(1+e+m, '0');
    }

    frac = frac.right(frac.size() - firstOne -1);
    if (frac.size() < m) {
        frac += QByteArray(m-frac.size(), '0');
    }

    qint64 expi = exp2(e-1)-2 - firstOne + expMod;
    for (quint64 i = 0; i < e; ++i) {
        quint64 mask = static_cast<quint64>(1) << i;
        if (expi & mask) {
            exp.push_front("1");
        } else {
            exp.push_front("0");
        }
    }
    qDebug() << "exp" << (firstOne) << exp2(e-1) << expMod << expi << "=" << exp << exp.size();

    retval += exp + frac;

    return retval;
}

QString Worker::floatToFixed(QString f, qint64 e, qint64 m)
{
    bool ok;
    double d = f.toDouble(&ok);

    if (!ok) {
        qDebug() << "Failure::floatToFixed";
        emit sourceError();
        return QByteArray(1+e+m, '0');
    }

    qDebug() << "Converting" << d;

    QString retval;

    if (d < 0 ) {
        retval += "1";
        d *= -1;
        for (int i = e-1; i >= -m; --i) {
            if (d < exp2(i)) {
                retval += "1";
            } else {
                retval += "0";
                d -= exp2(i);
            }
        }
    } else {
        retval += "0";

        for (int i = e-1; i >= -m; --i) {
            if (d < exp2(i)) {
                retval += "0";
            } else {
                retval += "1";
                d -= exp2(i);
            }
        }

    }
    return retval;
}

