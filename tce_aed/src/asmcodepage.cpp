#include "asmcodepage.h"
#include <QDebug>
#include <QFile>

AsmCodePage::AsmCodePage(QWidget *parent) : QTableView(parent)
{
    delegate_ = new AsmCodeCellDelegate(this);
    model_ = new AsmCodeModel(0, 0, this);

    setModel(model_);
    setItemDelegate(delegate_);
    this->setAlternatingRowColors(true);
    QWidget::connect(model_, SIGNAL(cellChanged(int, int)), this, SLOT(on_cellChanged(int, int)));
}

AsmCodePage::~AsmCodePage()
{

}

void AsmCodePage::createNew()
{
    model_->insertRows(0, 5);
    model_->insertColumns(0, 2);
    model_->setData(model_->index(0, 0), "CODE;");
    model_->setData(model_->index(2, 0), ":procedure main;");
    model_->setData(model_->index(3, 0), "main:");
    model_->beautify();
    renameColumns();
}

bool AsmCodePage::loadFile(QString fileName)
{
    qDebug() << "Loading " << fileName;
    int rows = 0;
    int columns = 2;
    QFile in(fileName);

    if (!in.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "couldn't open file" << fileName;
        return false;
    }
    model_->insertRows(0, 2);
    model_->insertColumns(0, 2);

    QTextStream stream(&in);
    QString line;
    while (!stream.atEnd()) {
        line = stream.readLine();
        if (rows >= model_->rowCount()) {
            model_->insertRows(rows, 1);
        }

        if (line.isEmpty()) {
            // Empty
        } else if (line.startsWith("#")) {
            model_->setData(model_->index(rows, 0), line);
        } else if (line.startsWith(" ")) {
            int idx = 0;
            int col = 0;
            while (line.mid(idx).contains(",")) {                
                int comma = line.mid(idx).indexOf(",");
                col++;
                if (col >= columns - 1) {
                    model_->insertColumns(columns - 1, 1);
                    columns++;
                }
                QString s = line.mid(idx, comma).trimmed();
                if (!s.contains("...")) {
                    model_->setData(model_->index(rows, col), s);
                }
                idx += comma + 1;
            }
            if (line.mid(idx).contains(";")) {
                int len = line.mid(idx).size();
                QString s = line.mid(idx, len-1).trimmed();
                if (!s.contains("...")) {
                    model_->setData(model_->index(rows, col + 1), s);
                }
            }
        } else {
            model_->setData(model_->index(rows, 0), line);
        }

        rows++;
    }
    beautify();
    renameColumns();


    return true;
}

bool AsmCodePage::saveFile(QString fileName)
{
    QFile out(fileName);
    if (!out.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Opening file" << fileName << "failed";
        return false;
    }

    QTextStream stream(&out);

    beautify();
    std::vector<int> sourceLengths = model_->sourceLengths();


    for (int row = 0; row < model_->rowCount(); ++row) {
        if (model_->type(model_->index(row, 0)) == CodeType::COMMENT) {
            stream << model_->data(model_->index(row, 0)).toString() << "\n";
            continue;
        }
        if (model_->type(model_->index(row, 0)) == CodeType::ADDRESS) {
            stream << model_->data(model_->index(row, 0)).toString() << "\n";
            continue;
        }

        bool codeLine = false;
        for (int col = 1; col < model_->columnCount(); ++col) {
            if (model_->type(model_->index(row, col)) == CodeType::MOVE) {
                codeLine = true;
                break;
            }
        }

        if (codeLine) {
            stream << "    ";
            for (int col = 1; col < model_->columnCount(); ++col) {
                if (model_->type(model_->index(row, col)) == CodeType::MOVE) {
                    QModelIndex idx =  model_->index(row, col);
                    QString temp = model_->source(idx)
                        + " -> "
                        + model_->destination(idx);
                    stream << temp.leftJustified(model_->columnLength(col));
                } else if (model_->type(model_->index(row, col)) == CodeType::EMPTY) {
                    stream << QString("...") .leftJustified(model_->columnLength(col));
                } else {
                    qDebug() << "Error(1) in saving??";
                }
                if (col == model_->columnCount() - 1) {
                    stream << " ;\n";
                } else {
                    stream << " , ";
                }
            }
        } else {
            stream << "\n";
        }
    }

    out.flush();
    out.close();
    return true;
}

void AsmCodePage::beautify()
{
    model_->beautify();
    model_->dataChanged(model_->index(0, 0), model_->index(model_->rowCount(), model_->columnCount()));
    setSpans();
    resizeColumnsToContents();
    resizeRowsToContents();
    modified();
}

void AsmCodePage::insertRowAbove()
{
    int minIdx = -1;
    QModelIndexList list = this->selectionModel()->selectedIndexes();
    for (auto& index : list) {
        if(minIdx < 0 || index.row() < minIdx) {
            minIdx = index.row();
        }
    }
    if (minIdx != -1) {
        model_->insertRows(minIdx, 1);
        modified();
    } else {
        model_->insertRows(0, 1);
        modified();
    }
}

void AsmCodePage::insertRowBelow()
{
    int maxIdx = -1;
    QModelIndexList list = this->selectionModel()->selectedIndexes();
    for (auto& index : list) {
        if(maxIdx < 0 || index.row() > maxIdx) {
            maxIdx = index.row();
        }
    }
    if(maxIdx != -1) {
        model_->insertRows(maxIdx + 1, 1);
        modified();
    } else {
        model_->insertRows(0, 1);
        modified();
    }
}

void AsmCodePage::insertColumnLeft()
{
    int minIdx = -1;
    QModelIndexList list = this->selectionModel()->selectedIndexes();
    for (auto& index : list) {
        if(minIdx < 0 || index.column() < minIdx) {
            minIdx = index.column();
        }
    }
    if (minIdx != -1) {
        model_->insertColumns(minIdx, 1);
        modified();
    }
    setSpans();
    renameColumns();
    modified();
}

void AsmCodePage::insertColumnRight()
{
    int maxIdx = -1;
    QModelIndexList list = this->selectionModel()->selectedIndexes();
    for (auto& index : list) {
        if(maxIdx < 0 || index.column() > maxIdx) {
            maxIdx = index.column();
        }
    }
    if (maxIdx != -1) {
        model_->insertColumns(maxIdx + 1, 1);
        modified();
    }
    setSpans();
    renameColumns();
    modified();
}

void AsmCodePage::deleteRows()
{
    int min = -1;
    int max = -1;
    QModelIndexList list = this->selectionModel()->selectedIndexes();
    for (auto& index : list) {
        if (min == -1 || index.row() < min) {
            min = index.row();
        }
        if (max == -1 || index.row() > max) {
            max = index.row();
        }
    }
    if (min != -1 && max != -1) {
        model_->removeRows(min, max-min+1);
    }

    modified();
}

void AsmCodePage::deleteColumns()
{
    int min = -1;
    int max = -1;
    QModelIndexList list = this->selectionModel()->selectedIndexes();
    for (auto& index : list) {
        if (min == -1 || index.column() < min) {
            min = index.column();
        }
        if (max == -1 || index.column() > max) {
            max = index.column();
        }
    }

    if (min != -1 && max != -1) {
        model_->removeColumns(min, max-min+1);
    }

    setSpans();
    modified();
    renameColumns();
}

void AsmCodePage::copy()
{
    int minRow = -1;
    int minCol = -1;
    copiedItems_.clear();
    QModelIndexList list = this->selectionModel()->selectedIndexes();
    for (auto& index : list) {
        if (minRow == -1 || index.row() < minRow) {
            minRow = index.row();
        }
        if (minCol == -1 || index.column() < minCol) {
            minCol = index.column();
        }
    }
    for (auto& index : list) {
        CopyItem temp;
        temp.row = index.row() - minRow;
        temp.column = index.column() - minCol;
        temp.content = index.data().toString();
        copiedItems_.push_back(temp);
    }
}

void AsmCodePage::paste()
{
    int minRow = -1;
    int minCol = -1;
    QModelIndexList list = this->selectionModel()->selectedIndexes();
    for (auto& index : list) {
        if (minRow == -1 || index.row() < minRow) {
            minRow = index.row();
        }
        if (minCol == -1 || index.column() < minCol) {
            minCol = index.column();
        }
    }
    for (auto& item : copiedItems_) {
        while (item.row + minRow >= model_->rowCount()) {
            model_->insertRow(model_->rowCount());
        }
        while (item.column + minCol >= model_->columnCount()) {
            model_->insertColumn(model_->columnCount());
        }
        auto index = model_->index(item.row + minRow, item.column + minCol);
        model_->setData(index, item.content);
    }
    beautify();
    modified();
}


void AsmCodePage::on_cellChanged(int row, int col)
{
    if (col == 0) {
        setSpans();
    }
    if (row == model_->rowCount() - 1) {
        model_->insertRow(row + 1);
    }
    this->resizeColumnToContents(col);
    modified();
}

void AsmCodePage::renameColumns()
{
    model_->setHeaderData(0, Qt::Orientation::Horizontal, "");
    for(int c = 1; c < model_->columnCount(); ++c) {
        model_->setHeaderData(c, Qt::Orientation::Horizontal, "Bus " + QString::number(c));
    }

}

void AsmCodePage::setSpans()
{
    for (int row = 0; row < model_->rowCount(); ++row) {
        if (model_->type(model_->index(row, 0)) == CodeType::ADDRESS
            || model_->type(model_->index(row, 0)) == CodeType::COMMENT) {
            setSpan(row, 0, 1, model_->columnCount());
        } else {
            if(columnSpan(row, 0) > 1) {
                setSpan(row, 0, 1, 1);
            }
        }
    }
}

