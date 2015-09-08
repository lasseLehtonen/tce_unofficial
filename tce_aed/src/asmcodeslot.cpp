#include "asmcodeslot.h"

#include <QDebug>

AsmCodeSlot::AsmCodeSlot() :
    type_(CodeType::EMPTY)
{

}

CodeType AsmCodeSlot::type() const
{
    return type_;
}

QString AsmCodeSlot::data() const
{
    switch (type_) {
    case CodeType::EMPTY:
    case CodeType::COMMENT:
    case CodeType::ADDRESS:
    case CodeType::MOVE:
    default:
        return data_;
    }
}

void AsmCodeSlot::setData(const QString &data)
{
    QString temp = data.trimmed();
    if (!data.isEmpty()) {
        if (temp.startsWith('#')) {
            type_ = CodeType::COMMENT;
            data_ = temp;
        } else {
            int idx = temp.indexOf("->", 0);
            if (idx != -1) {
                type_ = CodeType::MOVE;
                QString lhs = temp.left(idx).trimmed();
                QString rhs = temp.right(temp.size() - idx - 2).trimmed();
                source_ = lhs;
                destination_ = rhs;
                data_ = lhs + " -> " + rhs;
            } else {
                type_ = CodeType::ADDRESS;
                data_ = temp;
            }
        }
    } else {
        type_ = CodeType::EMPTY;
        data_ = "";
    }
}

const QString& AsmCodeSlot::source() const
{
    return source_;
}

const QString &AsmCodeSlot::destination() const
{
    return destination_;
}

