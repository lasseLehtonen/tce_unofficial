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

void Worker::convert(qint64 src, qint64 dst,
                     qint64 dstBits1, qint64 dstBits2, qint64 dstVectorization,
                     qint64 srcBits1, qint64 srcBits2, qint64 srcVectorization,
                     QString text)
{
    qDebug() << src << dst << dstBits1 << dstBits2 << dstVectorization << text;


    int splice;


    QStringList ls = text.split(QRegExp("\\s"),QString::SkipEmptyParts);
    QStringList result;

    if (src == 0 && dst == 0) {
        for (auto s : ls) {
            result << floatToBin(s, dstBits1, dstBits2);
        }
    }

    if (src == 0 && dst == 1) {
        for (auto s : ls) {
            result << binToHex(floatToBin(s, dstBits1, dstBits2));
        }
    }

    if (src == 0 && dst == 2) {
        for (auto s : ls) {
            result << floatToFixed(s, dstBits1, dstBits2);
        }
    }

    if (src == 1 && dst == 0) {
        for (auto s : ls) {
            splice = s.size() / srcVectorization;

            for (int i = 0; i < srcVectorization; ++i)
                result << bitsToFloat(s.mid(i*splice, splice), srcBits1, srcBits2);
        }
    }

    if (src == 2 && dst == 0) {
        for (auto s : ls) {
            s = hexToBin(s);
            splice = s.size() / srcVectorization;

            for (int i = 0; i < srcVectorization; ++i)
                result << bitsToFloat(s.mid(i*splice, splice), srcBits1, srcBits2);
        }
    }

    if (src == 3 && dst == 0) {
        for (auto s : ls) {
            result << bitsToFixed(s, srcBits1, srcBits2);
        }
    }



    QString retval;
    int cnt = 0;
    for (auto s : result) {
        retval += s; cnt++;
        if (cnt >= dstVectorization) {
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

QString Worker::bitsToFloat(QString f, qint64 e, qint64 m)
{
    if (f.size() != 1+e+m) {
        qDebug() << "String size doesn't match the amount of bits in exponent and mantissa"
                 << f << 1+e+m;
        return "FAIL";
    }

    double sign = f.at(0) == '0' ? 1 : -1;

    if (bitsToInt(f.right(e+m)) == 0) {
        return "0";
    }

    qint64 exp = bitsToInt(f.mid(1, e)) - (exp2(e-1)-1);
    double man = bitsToInt("1" + f.right(m)) * (1/exp2(m));

    qDebug() << sign << exp << man;

    while(exp < 0) {
        man /= 2;
        exp++;
    }
    while(exp > 0) {
        man *= 2;
        exp--;
    }

    return QString::number(sign * man);
}

QString Worker::bitsToFixed(QString f, qint64 e, qint64 m)
{

}

QString Worker::hexToBin(QString s)
{
    QString result;
    for(auto c : s) {
        switch (c.toLatin1()) {
        case '0': result += "0000"; break;
        case '1': result += "0001"; break;
        case '2': result += "0010"; break;
        case '3': result += "0011"; break;
        case '4': result += "0100"; break;
        case '5': result += "0101"; break;
        case '6': result += "0110"; break;
        case '7': result += "0111"; break;
        case '8': result += "1000"; break;
        case '9': result += "1001"; break;
        case 'A':
        case 'a': result += "1010"; break;
        case 'B':
        case 'b': result += "1011"; break;
        case 'C':
        case 'c': result += "1100"; break;
        case 'D':
        case 'd': result += "1101"; break;
        case 'E':
        case 'e': result += "1110"; break;
        case 'F':
        case 'f': result += "1111"; break;
        default: qDebug() << "Error in hexToBin conversion"; result += "xxxx";
        }
    }
    return result;
}

QString Worker::binToHex(QString s)
{
    qDebug() << "binToHex:" << s << "of" << s.size();
    QString retval;
    int len = s.size();
    for (int i = 0; i < len; i+=4) {
        QString c = s.mid(i, 4);
        qDebug() << "what is" << c;
        if (c == "0000") retval += "0";
        if (c == "0001") retval += "1";
        if (c == "0010") retval += "2";
        if (c == "0011") retval += "3";
        if (c == "0100") retval += "4";
        if (c == "0101") retval += "5";
        if (c == "0110") retval += "6";
        if (c == "0111") retval += "7";
        if (c == "1000") retval += "8";
        if (c == "1001") retval += "9";
        if (c == "1010") retval += "A";
        if (c == "1011") retval += "B";
        if (c == "1100") retval += "C";
        if (c == "1101") retval += "D";
        if (c == "1110") retval += "E";
        if (c == "1111") retval += "F";
    }
    return retval;
}



qint64 Worker::bitsToInt(QString s)
{
    qint64 retval = 0;
    qint64 exp = 1;

    for (int i = s.size()-1; i >= 0; --i) {
        if (s.at(i) == '1') {
            retval += exp;
        }
        exp <<= 1;
    }
    return retval;
}

