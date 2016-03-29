#include "slot.h"
#include <QDebug>

Slot::Slot(QObject *parent) : QObject(parent)
{
    setWidth(100.f);
}

bool Slot::selected() const
{
    return m_selected;
}

int Slot::row() const
{
    return m_row;
}

int Slot::column() const
{
    return m_column;
}

float Slot::width() const
{
    return m_width;
}

QString Slot::code() const
{
    return model()->code(row(), column());
}

CodeModel *Slot::model() const
{
    return m_model;
}

void Slot::setSelected(bool selected)
{
    if (m_selected == selected)
        return;

    if (selected) {
        qDebug() << "Selecting slot" << row() << column();
        model()->select(row(), column());
    }

    m_selected = selected;
    emit selectedChanged(selected);
}

void Slot::setRow(int row)
{
    if (m_row == row)
        return;

    m_row = row;
    emit rowChanged(row);
}

void Slot::setColumn(int column)
{
    if (m_column == column)
        return;

    m_column = column;
    emit columnChanged(column);
}

void Slot::setWidth(float width)
{
    if (m_width == width)
        return;

    m_width = width;
    emit widthChanged(width);
}

void Slot::setCode(QString code)
{
    if (m_code == code)
        return;

    qDebug() << "Code" << code;
    QString newCode = model()->setCode(row(), column(), code);

    m_code = newCode;
    emit codeChanged(newCode);
}

void Slot::setModel(QObject *model)
{
    CodeModel* m = dynamic_cast<CodeModel*>(model);
    Q_ASSERT(m);

    if (!m || m_model == m)
        return;

    m_model = m;
    emit modelChanged(m);
}

