#ifndef ASMCODESLOT_H
#define ASMCODESLOT_H

#include <QString>

class AsmCodeSlot
{
public:
    enum class Type {COMMENT, ADDRESS, MOVE, EMPTY};
    struct Code {
        QString functionUnit;
        QString operation;
        QString port;
    };

public:
    AsmCodeSlot();

    Type type() const;

    QString data() const;
    void setData(const QString &data);

    const Code &source() const;

    const Code &destination() const;

private:
    Type type_;
    QString data_;
    Code source_;
    Code destination_;
};

#endif // ASMCODESLOT_H
