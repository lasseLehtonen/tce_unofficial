#include "asmcodeslot.h"
#include <QDebug>

AsmCodeSlot::AsmCodeSlot() :
    type_(AsmCodeSlot::Type::EMPTY)
{

}

AsmCodeSlot::Type AsmCodeSlot::type() const
{
    return type_;
}

QString AsmCodeSlot::data() const
{
    switch (type_) {
    case Type::EMPTY:
    case Type::COMMENT:
    case Type::ADDRESS:
    case Type::MOVE:
    default:
        return data_;
    }
}

void AsmCodeSlot::setData(const QString &data)
{
    QString temp = data.trimmed();
    if (!data.isEmpty()) {
        if (temp.startsWith('#')) {
            type_ = Type::COMMENT;
            data_ = temp;
        } else {
            int idx = temp.indexOf("->", 0);
            if (idx != -1) {
                type_ = Type::MOVE;
                QString lhs = temp.left(idx).trimmed();
                QString rhs = temp.right(temp.size() - idx - 2).trimmed();
                source_.operation = lhs;
                destination_.operation = rhs;
                data_ = lhs + " -> " + rhs;
            } else {
                type_ = Type::ADDRESS;
                data_ = temp;
            }
        }
    } else {
        type_ = Type::EMPTY;
        data_ = "";
    }
}

const AsmCodeSlot::Code& AsmCodeSlot::source() const
{
    return source_;
}

const AsmCodeSlot::Code &AsmCodeSlot::destination() const
{
    return destination_;
}

