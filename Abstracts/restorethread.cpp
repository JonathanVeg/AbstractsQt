#include "restorethread.h"

RestoreThread::RestoreThread(QObject *parent) :
    QThread(parent)
{
}

RestoreThread::RestoreThread(QString bdName, QString driver){
    this->bdName = bdName;
    this->driver = driver;
}

void RestoreThread::setDatabase(QString bdName, QString driver)
{
    this->bdName = bdName;

    this->driver = driver;
}

void RestoreThread::setFileName(QString fileName)
{
    this->fileName = fileName;
}

void RestoreThread::setTables(QList<QString> tables)
{
    this->tables = tables;
}

void RestoreThread::makeRestore(){
    bd.start(bdName, "connectionRestore", driver);

    // primeiro ele irá limpar o banco.

    QString sql;
    foreach (QString table, tables){
        sql = QString("delete from %1").arg(table);

        if (! bd.exec(sql))
            qDebug() << QString("[RestoreThread] [makeRestore] Tabela \"%1\" não pode ser esvaziada").arg(table);
    }

    // agora ele restaura os dados do arquivo

    QString table;

    // por que não jogar direto em values a string? campos como anotação tem mais de uma linha, logo, como ele le linha a linha, ia dar errado.
    QString value; // valor para jogar em values e add a tabela.

    QList<QString> values; // valores para adição

    int current = 0;
    int totalReg = 0;

    QFile fileCount(fileName);
    if (fileCount.open(QIODevice::ReadOnly)){
        QTextStream inCount(&fileCount);

        QString line;

        do{
            line = inCount.readLine();

            if (line.count("</line>") > 0){
                totalReg ++;
            }

        }while (! line.isNull());

        emit totalRecordsRestore(totalReg);
    }

    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly)){
        QTextStream in(&file);

        QString line;
        do {

            // linha em questao do arquivo
            line = in.readLine();

            if (line.count("<table>") > 0){
                // inicio de uma tabela especifica.

                line.replace("<table>", "");

                table = line;

            }else if (line.count("</field>") > 0){
                // final de um campo especifico

                values << value;

                value.clear();

            }else if (line.count("</line>") > 0){
                // final de uma linha (aqui ele deve inserir a linha já preparada)

                current++;

                emit currentPositionRestore(current);

                bd.insert(table, values);

                values.clear();
            }else if (line.count("         ") > 0){
                // ve se tem os 9 espaços iniciais (caracteristica da linha de valor

                line = line.replace("         ", "");

                value = encryption.decryption(line, "jfinance");
            }

        }while(! line.isNull());
    }

    emit finishedRestore();

}
