#include "project.h"
#include <QDebug>
#include <QtXml>
#include <QTextStream>

Project::Project(QString& projectFileName, QObject *parent) : QObject(parent),
    projectFileName_(projectFileName)
{
    if(!projectFileName_.endsWith(".tceprj")) {
        projectFileName_ += ".tceprj";
    }
    // Separate full path to folder + file parts.
    // This can be done better ?
    // Doesn't propably work for non-unix systems ?
    int last = projectFileName_.lastIndexOf("/");
    projectFolderName_ = projectFileName_.mid(0, last+1);
    projectFileName_ = projectFileName_.mid(last+1);
}

void Project::newProject()
{
    QString fileBase(projectFileName_.left(projectFileName_.size() - 7));
    asmCodeFileName_ = fileBase + "_code.tceasm";
    asmDataFileName_ = fileBase + "_data.tceasm";
    modified();
}

bool Project::loadProject()
{
    QDomDocument doc("TCEProject");
    QString fileToLoad = projectFolderName_ + projectFileName_;
    qDebug() << "load Project" << fileToLoad;
    QFile file(fileToLoad);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Opening" << fileToLoad << "failed.";
        return false;
    }
    QString err;
    int line;
    int col;
    if (!doc.setContent(&file, &err, &line, &col)) {
        file.close();
        qDebug() << "Loading" << fileToLoad << "failed." << err << "line" << line << "column" << col;
        return false;
    }
    file.close();

    QDomNodeList tagList = doc.elementsByTagName("Project");
    qDebug() << "Tag count" << tagList.count();
    if (tagList.count() == 1) {
        QDomNode node = tagList.at(0);
        QDomElement elem = node.toElement();
        asmCodeFileName_ = elem.attribute("asmCodeFileName");
        asmDataFileName_ = elem.attribute("asmDataFileName");
    }
    else {
        qDebug() << "Error loading project";
    }

    return true;
}

bool Project::saveProject()
{
    QDomDocument doc("TCEProject");

    QDomElement root = doc.createElement("root");
    doc.appendChild(root);

    QDomElement tag = doc.createElement("Project");
    root.appendChild(tag);

    tag.setAttribute("asmCodeFileName", asmCodeFileName_);
    tag.setAttribute("asmDataFileName", asmDataFileName_);

    QString xml = doc.toString();
    QString fileToSave = projectFolderName_ + projectFileName_;
    QFile out(fileToSave);
    if (out.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&out);
        stream << xml;
        out.flush();
        out.close();
        return true;
    } else {
        qDebug() << "Saving" << fileToSave << "failed.";
        return false;
    }
}

QString Project::asmCodeFileName() const
{
    return asmCodeFileName_;
}

