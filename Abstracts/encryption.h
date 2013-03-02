#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <QObject>

class Encryption : public QObject
{
    Q_OBJECT
public:
    explicit Encryption(QObject *parent = 0);

    int ord(QString chr);

    QString chr(int ord);

    QString encryption(QString text, QString password);

    QString decryption(QString text, QString password);

    QList<int> asciiArray(QString word); // manda uma palavra e ele retorna uma lista com os ascii's dos caracteres

signals:

public slots:

};

#endif // ENCRYPTION_H
