#include "filemanager.h"
#include <QFileDialog>
#include <QFile>

FileManager::FileManager(QObject *parent) : QObject(parent)
{

}

void FileManager::saveProgram(const QString &contents)
{
    QString filename = QFileDialog::getSaveFileName((QWidget*)this->parent(),
                                                    tr("Guarda el Programa"),
                                                    QString(),
                                                    tr("*.olinki"));
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly)){
        return;
    }

    file.write(contents.toLocal8Bit());
    file.close();
}

void FileManager::loadProgram()
{
    QString filename = QFileDialog::getOpenFileName((QWidget*)this->parent(),
                                                    tr("Abrir Programa"),
                                                    QString(),
                                                    tr("*.olinki"));
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly)){
        return;
    }
    QByteArray data = file.readAll();
    programLoaded(QString(data));
    file.close();
}

