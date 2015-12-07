#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>

class FileManager : public QObject
{
    Q_OBJECT
public:
    explicit FileManager(QObject *parent = 0);

signals:
    void programLoaded(const QString &file);

public slots:
    Q_INVOKABLE void saveProgram(const QString &contents);
    Q_INVOKABLE void loadProgram();
};

#endif // FILEMANAGER_H
