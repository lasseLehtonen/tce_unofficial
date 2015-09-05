#ifndef PROJECT_H
#define PROJECT_H

#include <QObject>


class Project : public QObject
{
    Q_OBJECT
public:
    explicit Project(QString& projectFileName, QObject *parent = 0);

    void newProject(void);
    bool loadProject(void);
    bool saveProject(void);

    QString asmCodeFileName() const;

signals:
    void modified(void);

public slots:

private:
    QString projectFolderName_;
    QString projectFileName_;
    QString asmCodeFileName_;
    QString asmDataFileName_;

};

#endif // PROJECT_H
