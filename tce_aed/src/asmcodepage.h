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
    void beautify(void);

    void insertRowAbove(void);
    void insertRowBelow(void);
    void insertColumnLeft(void);
    void insertColumnRight(void);
    void deleteRows(void);
    void deleteColumns(void);
    void copy(void);
    void cut(void);
    void paste(void);
    void clear(void);
    void undo(void);
    void redo(void);

signals:    
    void modified(void);

public slots:
    void beforeModification(void);
    void on_cellChanged(int row, int col);

private:
    struct CopyItem {
        int row;
        int column;
        QString content;
    };

private:
    void setSpans(void);

    AsmCodeModel* model_;
    AsmCodeCellDelegate* delegate_;
    std::vector<CopyItem> copiedItems_;
    std::vector<AsmCodeModel*> undoStack_;
    std::vector<AsmCodeModel*> redoStack_;
};

#endif // ASMCODEPAGE_H
