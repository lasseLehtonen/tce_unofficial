#ifndef CODE_H
#define CODE_H

#include <QString>
#include <QDebug>

class Code
{
public:
    Code();

    void code(QString code);
    QString asString() const;
    quint32 padding() const;
    void setPadding(quint32 padding);
    quint32 size() const;

private:
    enum class TYPE {Comment, TriggeringMove, PortMove, Empty, GuardedPortMove, GuardedTriggeringMove};
    TYPE type_;
    QString guard_;
    QString guardFu_;
    QString guardPort_;
    QString inFu_;
    QString inport_;
    QString comment_;
    QString outFu_;
    QString outport_;
    QString outOperation_;
    quint32 padding_;
};

#endif // CODE_H
