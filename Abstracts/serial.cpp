#include "serial.h"
#include <QDebug>
#include <QTime>

Serial::Serial(QObject *parent) :
    QObject(parent)
{
}

QString Serial::generateRandomCode(int lengthCode)
{
    QTime midnight(0, 0, 0);
    int seed = midnight.secsTo(QTime::currentTime());

    QString randomCode;

    QString random;

    double randNumber;

    srand(seed);
    while (randomCode.length() < lengthCode){

        randNumber = rand();

        random.setNum(randNumber);

        random = random.mid(random.length() - 1, 1);

        if (random != "0")
            randomCode += random;
    }

    return randomCode;
}

QString Serial::generateSerial(QString randomCode){
    QString rc = randomCode;

    if (! rc.length() == 15)
        return "Random code invalid";

    int b1 = rc.mid(0, 5).toInt();
    int b2 = rc.mid(5, 5).toInt();
    int b3 = rc.mid(10, 5).toInt();

    QString b1s;
    QString b2s;
    QString b3s;

    // essa parte é para descobrir o "Fator multiplicador" aplicando-os nos blocos

    if (rc.mid(0,1).toInt() > rc.mid(13,1).toInt()){

        b1 *= rc.mid(0,1).toInt() - rc.mid(13,1).toInt();
        b2 *= rc.mid(0,1).toInt() - rc.mid(13,1).toInt();
        b3 *= rc.mid(0,1).toInt() - rc.mid(13,1).toInt();

    }else if (rc.mid(13,1).toInt() > rc.mid(0,1).toInt()){

        b1 *= rc.mid(13,1).toInt() - rc.mid(0,1).toInt();
        b2 *= rc.mid(13,1).toInt() - rc.mid(0,1).toInt();
        b3 *= rc.mid(13,1).toInt() - rc.mid(0,1).toInt();

    }else{

        b1 *= 2;
        b2 *= 2;
        b3 *= 2;

    }

    // aqui ele cria a versão strign dos blocos e, se tiver mais de 5 caracteres, ele os corta, deixando apenas os 5 primeiros

    b1s = QString::number(b1);
    b2s = QString::number(b2);
    b3s = QString::number(b3);

    b1s = (b1s.length() > 5)? b1s.mid(0,5): b1s;
    b2s = (b2s.length() > 5)? b2s.mid(0,5): b2s;
    b3s = (b3s.length() > 5)? b3s.mid(0,5): b3s;

    // agora ele volta-os para numero para ordenação
    b1 = b1s.toInt();
    b2 = b2s.toInt();
    b3 = b3s.toInt();

    // ordenando os numeros
    int b4; // variavel auxiliar.

    if (b1 > b2 && b3 > b2){
        b4 = b1;
        b1 = b2;
        b2 = b4;

    }else if (b1 > b3 && b2 > b3){
        b4 = b1;
        b1 = b3;
        b3 = b4;

    }

    if (b3 < b2){
        b4 = b2;
        b2 = b3;
        b3 = b4;
    }

    // devolve para numero e cria o serial intercalando os numeros, em ordem descrescente

    b1s = QString::number(b1);
    b2s = QString::number(b2);
    b3s = QString::number(b3);

    QString serial = "";

    for (int i = 0; i <= 5; i++){
        serial += b3s.mid(i, 1);
        serial += b2s.mid(i, 1);
        serial += b1s.mid(i, 1);
    }

    return serial;
}

QString Serial::generateSerialDate(QString date, QString randomCode)
{
    QString pos = ""; // posições alteradas

    int qnt = 0;

    QString d = ""; // data auxiliar

    int loop = date.length();

    for (int i = 0; i < loop; i++){
        if (date.mid(i, 1) == "0"){
            qnt ++;

            pos += QString::number(i);

            if (i == 0){
                d = QString::number(qnt);

                d += date.mid(1);
            }else if (i == date.length() - 1){
                d = date.mid(0, date.length() - 1);
                d += QString::number(qnt);
            }else{
                d = date.mid(0, i);
                d += QString::number(qnt);
                d += date.mid((i+1));
            }

            date = d;
        }
    }

    QString serial = "";

    for (int i = 0; i < date.length(); i++){
        serial += randomCode.mid(i,1);
        serial += date.mid(i,1);
    }

    // aqui os codigos ja estão misturados

    QString s = ""; // serial alterado

    int j = 0;

    for (int i = 0; i < pos.length(); i ++){
        j = i * 2;

        if (i == 0){
            s = pos.mid(0, 1);

            s += serial.mid(1);
        }else{
            s = serial.mid(0, j);
            s += pos.mid(i, 1);
            s += serial.mid((j+1));
        }


        serial = s;
    }

    s = serial.mid(0, serial.length() - 2);
    s += QString::number(pos.length());
    s += serial.mid(serial.length() - 1);

    serial = s;

    return serial;
}

QString Serial::decryptSerialDate(QString serial)
{
    //  primeiro passo, separar a data do codigo

    QString date = "";
    QString code = "";

    for (int i = 0; i < serial.length(); i++){
        if (i % 2 == 0)
            code += serial.mid(i, 1);
        else
            date += serial.mid(i, 1);
    }

    int qnt = code.mid(code.length() - 1, 1).toInt();

    for (int i = 0; i < qnt; i++){

        int pos = code.mid(i, 1).toInt(); // posição que tem que ser alterada

        QString d; // data auxiliar

        if (pos == 0){
            d = QString::number(0);

            d += date.mid(1);
        }else if (i == date.length() - 1){
            d = date.mid(0, date.length() - 1);
            d += QString::number(0);
        }else{
            d = date.mid(0, pos);
            d += QString::number(0);
            d += date.mid((pos+1));
        }

        date = d;
    }

    return date;
}
