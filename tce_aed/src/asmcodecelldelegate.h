#ifndef ASMCODECELLDELEGATE_H
#define ASMCODECELLDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>
#include <QModelIndex>
#include <QSize>

class AsmCodeCellDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    AsmCodeCellDelegate(QObject* parent);

    QWidget *createEditor(QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index) const;
    void setEditorData(QWidget * editor, const QModelIndex & index) const;
    void setModelData(QWidget * editor, QAbstractItemModel * model, const QModelIndex & index) const;
    void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;
    void updateEditorGeometry(QWidget * editor, const QStyleOptionViewItem & option, const QModelIndex & index) const;
    QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const;

signals:

public slots:

private:
    QString fontFamily_;
    int fontPointSize_;
    QColor defaultColor_;

};

#endif // ASMCODECELLDELEGATE_H
