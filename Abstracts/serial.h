#ifndef SERIAL_H
#define SERIAL_H

#include <QObject>

class Serial : public QObject
{
    Q_OBJECT
public:
    explicit Serial(QObject *parent = 0);

    QString generateRandomCode(int lengthCode); // gera um codigo pseudo-aleatório com a quantidade de numeros pedidos

    QString generateSerial(QString randomCode); // gera um serial baseado no codigo gerado acima. tem que ter 15 caracteres

    QString generateSerialDate(QString date, QString randomCode); // date com ddmmaaaa sem separadores. ele gera um serial baseado na data e no codigo aleatório
                                                                  // ambos tem que ter 8 caracteres

    QString decryptSerialDate(QString serial); // ele pega o serial date, gerado na função acima e retorna a data original

signals:

public slots:

};

#endif // SERIAL_H
