#include "asmcodecelldelegate.h"
#include "asmcodemodel.h"

#include <QTextEdit>
#include <QLineEdit>
#include <QPainter>
#include <QStaticText>
#include <QDebug>

AsmCodeCellDelegate::AsmCodeCellDelegate(QObject *parent) :
    QStyledItemDelegate(parent),
    fontFamily_("Courier"),
    fontPointSize_(10),
    defaultColor_("000000")
{

}

QWidget *AsmCodeCellDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QLineEdit* editor = new QLineEdit(parent);

    return editor;
}

void AsmCodeCellDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QLineEdit* edit = static_cast<QLineEdit*>(editor);
    QString data = index.model()->data(index, Qt::EditRole).toString();
    edit->setText(data);
}

void AsmCodeCellDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit* edit = static_cast<QLineEdit*>(editor);
    QString data = edit->text();
    model->setData(index, data, Qt::EditRole);
    AsmCodeModel* asmModel = static_cast<AsmCodeModel*>(model);
    asmModel->dataChange(index);
}

void AsmCodeCellDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStringList list;
    const AsmCodeModel* asmModel = static_cast<const AsmCodeModel*>(index.model());
    switch (asmModel->type(index)) {
    case CodeType::COMMENT:
        list << asmModel->data(index).toString();
        break;
    case CodeType::MOVE:
        list << asmModel->source(index)
             << " -> "
             << asmModel->destination(index);
        break;
    case CodeType::ADDRESS:
        list << asmModel->data(index).toString();
        break;
    case CodeType::EMPTY:
        list << "";
        break;
    default:
        list << "N/A";
        break;
    }


    QPen penText2(defaultColor_);
    QFont newFont(fontFamily_, fontPointSize_, QFont::Bold, false);

    painter->setFont(newFont);
    painter->setPen(penText2);

    QRect area(option.rect.left() + 2, option.rect.top(), option.rect.right(), option.rect.bottom());

    QFontMetrics fm(newFont);
    int textHeight = fm.height();
    int topSpan = (option.rect.height() - textHeight) / 2;
    area.setTop(area.top() + topSpan);

    for(QString& s : list) {
        int textWidth = fm.width(s);
        painter->drawText(area, s);
        area.setLeft(textWidth + area.left());
    }

}

void AsmCodeCellDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

QSize AsmCodeCellDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QString text;

    const AsmCodeModel* asmModel = static_cast<const AsmCodeModel*>(index.model());
    switch (asmModel->type(index)) {
    case CodeType::COMMENT:
        text = asmModel->data(index).toString();
        break;
    case CodeType::MOVE:
        text = asmModel->source(index)
             + " -> "
             + asmModel->destination(index);
        break;
    case CodeType::ADDRESS:
        text = asmModel->data(index).toString();
        break;
    case CodeType::EMPTY:
        text = "";
        break;
    default:
        text = "";
        break;
    }

    QFont font(fontFamily_, fontPointSize_, QFont::Bold, false);

    QFontMetrics fm(font);
    int textWidth = fm.width(text);
    int textHeight = fm.height();

    return QSize(textWidth + 2 + 2, textHeight);
}

