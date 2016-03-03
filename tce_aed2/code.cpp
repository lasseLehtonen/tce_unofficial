#include "code.h"
#include <QByteArray>

Code::Code() : type_(TYPE::Empty), padding_(0)
{

}

void Code::code(QString code)
{
    code = code.trimmed();
    outOperation_ = "";
    if (code.isEmpty()) {
        type_ = TYPE::Empty;
        return;
    }

    if (!code.contains("->")) {
        type_ = TYPE::Comment;
        comment_ = code;
        return;
    }

    int index = code.indexOf("->");
    if (index < 0) {
        qDebug() << "Error finding '->'";
        return;
    }

    if ((index == 0) || (code.size()-(index+2) < 1)) {
        type_ = TYPE::Comment;
        comment_ = code;
        return;
    }

    QString left = code.left(index).trimmed();
    QString right = code.right(code.size()-(index+2)).trimmed();

    qDebug() << left << "->" << right;
    bool isComment = false;

    bool guarded = false;
    if (left.startsWith('!') || left.startsWith('?')) {
        guarded = true;
        guard_ = left.at(0);
        left = left.right(left.size()-1).trimmed();
        index = left.indexOf(".");
    }

    if (guarded && index > 0) {
        guardFu_ = left.left(index);
        left = left.right(left.size()-1-index).trimmed();
        index = left.indexOf(" ");
    } else {
        isComment = guarded;
        guarded = false;
    }

    if (guarded && index > 0) {
        guardPort_ = left.left(index);
        left = left.right(left.size()-1-index).trimmed();
    } else {
        isComment = guarded;
        guarded = false;
    }

    if (!isComment) {
        index = left.indexOf(".");
        if (index > 0 && left.size() > index + 1) {
            inFu_ = left.left(index);
            inport_ = left.right(left.size()-1-index);
        } else {
            isComment = true;
        }
    }

    if (!isComment) {
        index = right.indexOf(".");
        if (index > 0) {
            outFu_ = right.left(index);
            right = right.right(right.size()-1-index);
        } else {
            isComment = true;
        }
    }

    if (!isComment) {
        index = right.indexOf(".");
        if (index > 0) {
            outport_ = right.left(index);
            outOperation_ = right.right(right.size()-1-index);
        } else {
            outport_ = right;
        }
    }


    if (isComment) {
        type_ = TYPE::Comment;
        comment_ = code;
        return;
    }

    if (guarded) {
        if(outOperation_.size() == 0) {
            type_ = TYPE::GuardedPortMove;
        } else {
            type_ = TYPE::GuardedTriggeringMove;
        }
        return;
    } else {
        if(outOperation_.size() == 0) {
            type_ = TYPE::PortMove;
        } else {
            type_ = TYPE::TriggeringMove;
        }
        return;
    }
    //qDebug() << guard_ << guardFu_ << guardPort_ << inFu_ << inport_ << outFu_ << outport_ << outOperation_;
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
        break;
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

