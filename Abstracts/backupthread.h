#ifndef BACKUPTHREAD_H
#define BACKUPTHREAD_H

#include <QThread>
#include <Abstract/bdtools.h>
#include <Abstract/encryption.h>
#include <QDebug>
#include <QFile>

class BackupThread : public QThread
{
    Q_OBJECT
public:
    explicit BackupThread(QObject *parent = 0);

    void setDatabase(QString bdName, QString driver = "QPSQL");

    void setTables(QList<QString> tables);

    void setFilename(QString _fileName);

    QList<QString> getTables();

    QString fileName();

private:
    QList<QString> tables;

    QString _fileName;

    QString bdName;

    QString driver;

    BDTools bd;

    Encryption encryption;

public slots:
    void makeBackup();

signals:
    void totalRecordsBackup(int);

    void currentPositionBackup(int);

    void finishedBackup();

public slots:

};

#endif // BACKUPTHREAD_H
