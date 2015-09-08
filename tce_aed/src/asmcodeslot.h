#ifndef ASMCODESLOT_H
#define ASMCODESLOT_H

#include "common.h"
#include <QString>

class AsmCodeSlot
{
public:

public:
    AsmCodeSlot();

    CodeType type() const;

    QString data() const;
    void setData(const QString &data);

    const QString &source() const;

    const QString &destination() const;

private:

    CodeType type_;
    QString data_;
    QString source_;
    QString destination_;
};

#endif // ASMCODESLOT_H
