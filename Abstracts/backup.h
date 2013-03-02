#ifndef BACKUP_H
#define BACKUP_H

#include <QObject>
#include <Abstract/backupthread.h>
#include <Abstract/restorethread.h>

class Backup : public QObject
{
    Q_OBJECT
public:
    explicit Backup();
    explicit Backup(QString bdName, QString driver);

    void setDatabase(QString bdName, QString driver);

    void setTables(QList<QString> tables);

    QList<QString> tables();

    void setFileName(QString fileName);

    inline QString fileName();
    inline QString bdName();
    inline QString driver();

    void makeBackup();
    void makeRestore();

private:
    void connections();

private:
    QList<QString> _tables;
    QString _fileName;

    QString _bdName;
    QString _driver;

    BackupThread *backupThread;
    RestoreThread *restoreThread;

signals:

public slots:

};

#endif // BACKUP_H
