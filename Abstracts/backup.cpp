#include "backup.h"

Backup::Backup()
{
}

Backup::Backup(QString bdName, QString driver){
    setDatabase(bdName, driver);
}

void Backup::connections()
{
    //    connect(backupThread, SIGNAL(totalRecordsBackup(int)), SLOT());
    //    connect(backupThread, SIGNAL(currentPositionBackup(int)), SLOT());
    //    connect(backupThread, SIGNAL(finishedBackup()), SLOT());

    //    connect(restoreThread, SIGNAL(totalRecordsBackup(int)), SLOT());
    //    connect(restoreThread, SIGNAL(currentPositionBackup(int)), SLOT());
    //    connect(restoreThread, SIGNAL(finishedBackup()), SLOT());
}

void Backup::setDatabase(QString bdName, QString driver){
    backupThread->setDatabase(bdName, driver);
    restoreThread->setDatabase(bdName, driver);

    _bdName = bdName;
    _driver = driver;
}

void Backup::setTables(QList<QString> tables)
{
    this->_tables = tables;

    QList<QString> _tables;

    backupThread->setTables(tables);

    for (int i = tables.length() - 1; i >= 0; i++){
        _tables << tables.at(i);
    }

    restoreThread->setTables(_tables);
}

QList<QString> Backup::tables()
{
    return _tables;
}

void Backup::setFileName(QString fileName)
{
    _fileName = fileName;
}

QString Backup::fileName()
{
    return _fileName;
}

QString Backup::bdName()
{
    return _bdName;
}

QString Backup::driver()
{
    return _driver;
}

void Backup::makeBackup()
{
    if (tables().isEmpty())
        return;
}

void Backup::makeRestore()
{
    if (tables().isEmpty())
        return;
}
