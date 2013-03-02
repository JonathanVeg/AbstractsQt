#ifndef TOOLS_H
#define TOOLS_H

#include <QObject>
#include <QDebug>

class Tools : public QObject
{
    Q_OBJECT
public:
    explicit Tools(QObject *parent = 0);

    // data
    QString currentDate(Qt::DateFormat format = Qt::SystemLocaleShortDate);
    QString currentDay();
    QString currentMonth();
    QString currentMonthSpelled();
    QString currentYear();
    QString monthSpelled(QString date);
    QString year(QString date);
    int dayOfWeek(QString date); // pega o dia da semana de determinada data
    QString dayBeginWeek(QString date); // pega o primeiro dia da semana da data especificada
    QString dayEndWeek(QString date); // pega o último dia da semana da data especificada
    QString dayBeginMonth(QString date); // pega o primeiro dia da semana da data especificada
    QString dayEndMonth(QString date); // pega o último dia da semana da data especificada
    QString dayBeginYear(QString date); // pega o primeiro dia da semana da data especificada
    QString dayEndYear(QString date); // pega o último dia da semana da data especificada

    QDateTime subDate(QString date, QString hour, int minutes); // pega a data e hora e diminui o número de dias.

    QString daysInMonth(QString date);
    QString daysInYear(QString date);

    // hora
    QString currentTime();
    QString secondsToTime(int seconds, bool isLong = false);
    QString upFirstLetter(QString text);

    // arquivo
    bool createTextFile(QString fileName);
    QString readFile(QString fileName);
    bool writeFile(QString fileName, QString text);

    bool betweenDates(QString dateI, QString dateF, QString dateC); // ve se a date se esta entre as outras datas, inclusive

    QString currentTime(QString format);

    QString convertDate(QString date, QString separator = "/"); // converte de ddmmyyyy para yyyymmdd
    QString convertDate2(QString date, QString separator = "/"); // reverte a conversão acima - tenho que ver um nome melhor para isso

    QChar compareDate(QString date0, QString date1); // retorna o numero da data maior

    QChar compareHour(QString hour0, QString hour1); // retorna o numero da data maior

    QString indexState(int index);

    // funções para trabalhar com horas
    bool betweenHours(QString hourI, QString hourF, QString hourC);
    unsigned int hourNumber(QString hour);

    unsigned int dateNumber(QString date);

    // recebe um valor e converte em formato monetário
    QString convertMoney(QString value, QString separator = ",");

    // função que matemática que pode ser útil em futuras criptografias
    int module(int a, int e, int n); // retorna (a^e)%n

    bool isValidDate(QString date);

    bool isValidHour(QString hour);

    // validações
    bool isValidCNPJ(QString cnpj);
    bool isValidCPF(QString cpf);

    // QList

    QList<int> listToInt(QList<QString> list);
    QList<double> listToDouble(QList<QString> list);
signals:

public slots:

};

#endif // TOOLS_H
