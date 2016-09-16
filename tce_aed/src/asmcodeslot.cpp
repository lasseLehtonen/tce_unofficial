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
    return data_;
}

void AsmCodeSlot::setData(const QString &data)
{
    source_ = "";
    destination_ = "";
    QString temp = data.trimmed();
    if (!data.isEmpty()) {
        if (temp.startsWith('#')) {
            type_ = CodeType::COMMENT;
            data_ = temp;
        } else if (temp == "...") {
            type_ = CodeType::NOP;
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
            } else if (temp.contains('=') ) {
                type_ = CodeType::LIMM;
                data_ = temp;
                source_ = temp;
                destination_ = temp;
                //qDebug() << "Lihapulla:" << temp;
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

