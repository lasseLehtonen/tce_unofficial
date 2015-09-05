#ifndef ASMCODEPAGE_H
#define ASMCODEPAGE_H

#include <QObject>
#include <QWidget>
#include <QTableView>
#include <QTableWidget>
#include <QStandardItemModel>

#include "asmcodecelldelegate.h"
#include "asmcodemodel.h"

#include <vector>

class AsmCodePage : public QTableView
{
    Q_OBJECT
public:
    explicit AsmCodePage(QWidget* parent);
    virtual ~AsmCodePage();

    void createNew(void);
    bool loadFile(QString fileName);
    bool saveFile(QString fileName);

signals:

public slots:
    void on_cellChanged(int row, int col);

private:
    void initialize(void);

    AsmCodeModel* model_;
    AsmCodeCellDelegate* delegate_;
};

#endif // ASMCODEPAGE_H
