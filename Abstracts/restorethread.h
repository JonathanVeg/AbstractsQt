#ifndef RESTORETHREAD_H
#define RESTORETHREAD_H

#include <QThread>
#include <Abstract/bdtools.h>
#include <Abstract/encryption.h>
#include <QDebug>
#include <QFile>

class RestoreThread : public QThread
{
    Q_OBJECT
public:
    explicit RestoreThread(QObject *parent = 0);

    explicit RestoreThread(QString bdName, QString driver = "QPLSQL");

    void setDatabase(QString bdName, QString driver = "QPSQL");

    void setFileName(QString fileName);

    void setTables(QList<QString> tables);

private:
    QString bdName;

    QString driver;

    QString fileName;

    QList<QString> tables;

    BDTools bd;

    Encryption encryption;

public slots:
    void makeRestore();

signals:
    void totalRecordsRestore(int);
    void currentPositionRestore(int);
    void finishedRestore();

public slots:

};

#endif // RESTORETHREAD_H
