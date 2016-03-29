#ifndef SLOT_H
#define SLOT_H

#include <QObject>
#include "codemodel.h"

class Slot : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool selected READ selected WRITE setSelected NOTIFY selectedChanged)
    Q_PROPERTY(int row READ row WRITE setRow NOTIFY rowChanged)
    Q_PROPERTY(int column READ column WRITE setColumn NOTIFY columnChanged)
    Q_PROPERTY(float width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(QString code READ code WRITE setCode NOTIFY codeChanged)
    Q_PROPERTY(QObject* model READ model WRITE setModel NOTIFY modelChanged)

    bool m_selected;
    int m_row;
    int m_column;
    float m_width;
    QString m_code;
    CodeModel* m_model;

public:
    explicit Slot(QObject *parent = 0);

    bool selected() const;
    int row() const;
    int column() const;
    float width() const;
    QString code() const;
    CodeModel* model() const;

signals:

    void selectedChanged(bool selected);
    void rowChanged(int row);
    void columnChanged(int column);
    void widthChanged(float width);
    void codeChanged(QString code);
    void modelChanged(QObject* model);

public slots:
    void setSelected(bool selected);
    void setRow(int row);
    void setColumn(int column);
    void setWidth(float width);
    void setCode(QString code);
    void setModel(QObject* model);
};

#endif // SLOT_H
