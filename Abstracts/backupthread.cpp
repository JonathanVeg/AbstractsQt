#include "backupthread.h"

BackupThread::BackupThread(QObject *parent) :
    QThread(parent)
{
}

void BackupThread::setDatabase(QString bdName, QString driver){
    this->bdName = bdName;

    this->driver = driver;
}

void BackupThread::setTables(QList<QString> tables)
{
    this->tables = tables;
}

QList<QString> BackupThread::getTables()
{
    return tables;
}

void BackupThread::setFilename(QString fileName)
{
    _fileName = fileName;
}

QString BackupThread::fileName(){
    return _fileName;
}

void BackupThread::makeBackup()
{
    bd.start(bdName, "connectionBackup", driver);

    qDebug() << "Backup da tabela" << tables;

    int totalRecords = 0;

    for (int i = 0; i < tables.length(); i++){
        if (bd.search("select count (*) from " + tables[i]))
            totalRecords += bd.loadSimple(0).toInt();
        else
            qDebug() << "[backup] [createBackup] " << tables[i] << "vazia. sql dela: " << "select count (*) from " + tables[i];
    }

    qDebug() << "[backup] [total de registros]" << totalRecords;

    emit totalRecordsBackup(totalRecords); // total de registros

    int jump = 1;

    if (totalRecords > 100)
        jump = totalRecords / 100;

    QString backup = "";

    int current = 0;

    QList<QString> line;

    /// aqui começa a gerar o backup em si
    for (int i = 0; i < tables.length(); i++){

        qDebug() << "[BACKUP] [createBackup] Tabela atual:" << tables[i];

        if (bd.search("select * from " + tables[i])){
            // esse for, pegará a quantidade de linhas da tabela

            backup += "<table>" + tables[i] + "\n";

            int j = 0;

            while (j < bd.loadColumn(0).length()){

                backup += "   <line>\n";

                // aqui ele pega a linha em si

                line = bd.loadLine(j);

                for (int k = 0; k < bd.loadLine(0).length(); k++){

                    backup += "      <field>\n";
                    backup += "         " + encryption.encryption(line[k], "jfinance") + "\n";
                    backup += "      </field>\n";

                }

                backup += "   </line>\n";

                current ++;

                j++;

                if (current % jump == 0)
                    emit currentPositionBackup(current);

            }

            // esse emit é para ter o emit de 100%
            emit currentPositionBackup(current);

            backup += "</table>\n";
        }
    }

    /// aqui ele salva o arquivo do backup
    QFile file(_fileName);
    if (file.open(QIODevice::WriteOnly)){
        QTextStream stream(&file);
        stream << (backup);
    }
    file.close();

    emit finishedBackup();
}
