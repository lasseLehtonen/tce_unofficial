#include "code.h"
#include <QByteArray>
#include <QRegularExpression>

Code::Code() : type_(TYPE::Empty), padding_(0)
{

}

void Code::code(QString code)
{
    code = code.trimmed();
    code = code.simplified();
    code.replace("  ", " ");
    //qDebug() << "simplified code" << code;

    QRegularExpression portMoveRE("^([a-z][a-z0-9]*)[.]([a-z0-9]+) -> ([a-z][a-z0-9]*)[.]([a-z_0-9]+)$", QRegularExpression::CaseInsensitiveOption);
    QRegularExpression trigMoveRE("^[a-z][a-z0-9]*[.][a-z0-9]* -> [a-z][a-z0-9]*[.][a-z][a-z0-9]*[.][a-z][a-z_0-9]*$", QRegularExpression::CaseInsensitiveOption);
    QRegularExpression guardedPortMoveRE("^[!?][a-z][a-z0-9]*[.][a-z0-9]* [a-z][a-z0-9]*[.][a-z0-9]* -> [a-z][a-z0-9]*[.][a-z_0-9]+$", QRegularExpression::CaseInsensitiveOption);
    QRegularExpression guardedTrigMoveRE("^[!?][a-z][a-z0-9]*[.][a-z0-9]* [a-z][a-z0-9]*[.][a-z0-9]* -> [a-z][a-z0-9]*[.][a-z][a-z0-9]*[.][a-z][a-z_0-9]*$", QRegularExpression::CaseInsensitiveOption);
    QRegularExpression immPortMoveRE("^[1-9][0-9]* -> [a-z][a-z0-9]*[.][a-z_0-9]+$", QRegularExpression::CaseInsensitiveOption);
    QRegularExpression immTrigMoveRE("^[1-9][0-9]* -> [a-z][a-z0-9]*[.][a-z][a-z0-9]*[.][a-z][a-z_0-9]*$", QRegularExpression::CaseInsensitiveOption);
    QRegularExpression guardedImmPortMoveRE("^[!?][a-z][a-z0-9]*[.][a-z0-9]* [1-9][0-9]* -> [a-z][a-z0-9]*[.][a-z_0-9]+$", QRegularExpression::CaseInsensitiveOption);
    QRegularExpression guardedImmTrigMoveRE("^[!?][a-z][a-z0-9]*[.][a-z0-9]* [1-9][0-9]* -> [a-z][a-z0-9]*[.][a-z][a-z0-9]*[.][a-z][a-z_0-9]*$", QRegularExpression::CaseInsensitiveOption);
    QRegularExpression labelRE("^[a-z][a-z_0-9]*:$", QRegularExpression::CaseInsensitiveOption);

    QRegularExpressionMatch match;

    match = portMoveRE.match(code);
    if (match.hasMatch()) {
        type_ = TYPE::PortMove;
        inFu_ = match.captured(1);
        inport_ = match.captured(2);
        outFu_ = match.captured(3);
        outport_ = match.captured(4);
        return;
    }

    qDebug() << "            trigmove match" << trigMoveRE.match(code).hasMatch();
    qDebug() << "guarded     portmove match" << guardedPortMoveRE.match(code).hasMatch();
    qDebug() << "guarded     trigmove match" << guardedTrigMoveRE.match(code).hasMatch();
    qDebug() << "        imm portmove match" << immPortMoveRE.match(code).hasMatch();
    qDebug() << "        imm trigmove match" << immTrigMoveRE.match(code).hasMatch();
    qDebug() << "guarded imm portmove match" << guardedImmPortMoveRE.match(code).hasMatch();
    qDebug() << "guarded imm trigmove match" << guardedImmTrigMoveRE.match(code).hasMatch();
    qDebug() << "               label match" << labelRE.match(code).hasMatch();

    type_ = TYPE::Unkown;
    unkown_ = code;
}

QString Code::asString() const
{
    switch (type_) {
    case TYPE::Comment:
        return comment_;
    case TYPE::Empty:
        return "";
    case TYPE::TriggeringMove:
        return inFu_ + "." + inport_ + QByteArray(padding_, ' ') + " -> " + outFu_ + "." + outport_ + "." + outOperation_;
    case TYPE::PortMove:
        return inFu_ + "." + inport_ + QByteArray(padding_, ' ') + " -> " + outFu_ + "." + outport_;
    case TYPE::GuardedTriggeringMove:
        return guard_ + guardFu_ + "." + guardPort_ + " " + inFu_ + "." + inport_ + QByteArray(padding_, ' ') + " -> " + outFu_ + "." + outport_ + "." + outOperation_;
    case TYPE::GuardedPortMove:
        return guard_ + guardFu_ + "." + guardPort_ + " " + inFu_ + "." + inport_ + QByteArray(padding_, ' ') + " -> " + outFu_ + "." + outport_;
    default:
        return unkown_;
        break;
    }
}

QString Code::type() const
{
    switch (type_) {
    case TYPE::Comment: return "comment";
    case TYPE::Empty: return "empty";
    case TYPE::GuardedPortMove: return "guarded port move";
    case TYPE::GuardedTriggeringMove: return "guarded triggering move";
    case TYPE::PortMove: return "port move";
    case TYPE::TriggeringMove: return "triggering move";
    default: qDebug() << "Code::type() error in codemodel"; return "";
    }
}

quint32 Code::padding() const
{
    switch (type_) {
    case TYPE::Comment:
    case TYPE::Empty:
        return 0;
    case TYPE::TriggeringMove:
        return inFu_.size() + 1 + inport_.size();
    case TYPE::PortMove:
        return inFu_.size() + 1 + inport_.size();
    case TYPE::GuardedTriggeringMove:
        return 1 + guardFu_.size() + 1 + guardPort_.size() + 1 + inFu_.size() + 1 + inport_.size();
    case TYPE::GuardedPortMove:
        return 1 + guardFu_.size() + 1 + guardPort_.size() + 1 + inFu_.size() + 1 + inport_.size();
    default:
        break;
    }
}

void Code::setPadding(quint32 padding)
{
    padding_ = padding;
}

quint32 Code::size() const
{
    return asString().size();
}

