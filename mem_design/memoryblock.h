#ifndef MEMORYBLOCK_H
#define MEMORYBLOCK_H

#include <QString>

class MemoryBlock
{
public:
    MemoryBlock();
    MemoryBlock(QString component, QString instance);

private:
    QString name_;
    QString instance_;
    QString component_;
    qint32 width_;
    qint32 depth_;
};

#endif // MEMORYBLOCK_H
