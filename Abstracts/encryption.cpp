#include "encryption.h"
#include <QDebug>

Encryption::Encryption(QObject *parent) :
    QObject(parent)
{
}

int Encryption::ord(QString letter)
{
    char *c = letter.toAscii().data();

    return (int)*c;
}

QString Encryption::encryption(QString text, QString password)
{
    QList<int> asciiText = asciiArray(text);
    QList<int> asciiPassword = asciiArray(password);

    QList<int> asciiCripto;
    QList<QString> asciiCriptoStr;

    for (int i = 0; i < asciiText.length(); i++){
        asciiCripto << asciiText[i] * asciiPassword[i % asciiPassword.length()];

        asciiCriptoStr << QString::number(asciiCripto[i]);
    }

    int max = 0;

    foreach (QString t, asciiCriptoStr){
        if (t.length() > max)
            max = t.length();
    }

    for (int i = 0; i < asciiCriptoStr.length(); i++){
        while (asciiCriptoStr[i].length() < max){
            if (asciiCriptoStr[i][0] != '-')
                asciiCriptoStr[i] = "0" + asciiCriptoStr[i];
            else
                asciiCriptoStr[i] = QString("-") + QString("0") + asciiCriptoStr[i].mid(1);
        }
    }

    QString textReturn = QString::number(max);

    foreach (QString t, asciiCriptoStr){
        textReturn += t;
    }

    return textReturn;
}

QString Encryption::decryption(QString text, QString password)
{
    QList<int> asciiPassword = asciiArray(password);

    QList<int> textSplit;

    QList<QString> asciiText;

    int qnt = text.mid(0, 1).toInt();

    int i = 1;

    while (i < text.length()){
        textSplit << text.mid(i, qnt).toInt();

        qDebug() << textSplit;

        i+= qnt;
    }

    for (int i = 0; i < textSplit.length(); i++){
        textSplit[i] = textSplit[i] / asciiPassword[i % asciiPassword.length()];
    }

    foreach(int i, textSplit)
        asciiText << chr(i);

    QString textReturn = "";

    for (int i = 0; i < textSplit.length(); i++){
        textReturn += asciiText.at(i);
    }

    return textReturn;
}

QList<int> Encryption::asciiArray(QString word)
{
    QList<int> listAscii;

    foreach (QString letter, word){
        listAscii.append(ord(letter));
    }

    return listAscii;
}

QString Encryption::chr(int asciiCode)
{
    return QString("%1").arg(char(asciiCode));
}
