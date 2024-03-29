#include "tools.h"
#include <QDate>
#include <QFile>
#include <QDir>
#include <QTextStream>

Tools::Tools(QObject *parent) :
    QObject(parent)
{
}

//
QString Tools::currentDay()
{
    return QDate::currentDate().toString(Qt::SystemLocaleShortDate).mid(0,2);
}

QString Tools::currentMonth()
{
    return QDate::currentDate().toString(Qt::SystemLocaleShortDate).mid(3,2);
}

QString Tools::currentMonthSpelled()
{
    return upFirstLetter(QDate::currentDate().longMonthName(QDate::currentDate().toString(Qt::SystemLocaleShortDate).mid(3,2).toInt()));
}

QString Tools::currentYear()
{
    return QDate::currentDate().toString(Qt::SystemLocaleShortDate).mid(6,4);
}

QString Tools::monthSpelled(QString date){
    return upFirstLetter(QDate::fromString(date, "dd/MM/yyyy").longMonthName(date.mid(3,2).toInt()));
}

QString Tools::upFirstLetter(QString text)
{
    QString temp = text.mid(0,1).toUpper();
    temp += text.mid(1,text.length() -1);
    return temp;
}

bool Tools::betweenHours(QString hourI, QString hourF, QString hourC)
{
    int hourIInt = hourNumber(hourI);
    int hourFInt = hourNumber(hourF);
    int hourCInt = hourNumber(hourC);

    if (hourCInt >= hourIInt && hourCInt <= hourFInt)
        return true;

    return false;
}

unsigned int Tools::hourNumber(QString hour)
{
    return hour.mid(0,2).toInt() * 100 + hour.mid(3,2).toInt();
}

unsigned int Tools::dateNumber(QString date)
{
    QString dateString = date.mid(6, 4) + date.mid(3, 2) + date.mid(0, 2);

    return dateString.toInt();
}

QString Tools::convertMoney(QString value, QString separator){
    if (value == "0" || value.isEmpty())
        return "R$ 0,00";

    int i = -1;
    int pos = 0;
    bool neg = false;

    if (value.mid(0, 1) == "-"){
        neg = true;

        value = value.mid(1);
    }

    foreach (QString letter, value){
        i++;
        if (letter == "." || letter == ",")
            pos = i;
    }

    if (! pos == 0){
        if (value.length() >= pos+3){
            value = value.mid(0,pos+3);
        }else
            if (value.length() >= pos + 2){
                value = value.mid(0,pos+2) + "0";
            }
    }

    if (pos == 0)
        value = value + separator + "00";

    QString valueR = tr("R$ ");
    valueR += value;

    if (neg)
        valueR = "- " + valueR;

    return valueR;
}


QString Tools::currentDate(Qt::DateFormat format){

    QString sdata;
    int counter = 0, position = 0;

    QDate data = QDate::currentDate();

    if (format == Qt::SystemLocaleLongDate)
        sdata = data.toString(Qt::SystemLocaleLongDate);

    if (format == Qt::SystemLocaleShortDate)
        sdata = data.toString(Qt::SystemLocaleShortDate);

    if (format == Qt::SystemLocaleDate)
        sdata = data.toString(Qt::SystemLocaleDate);

    for (int letter = 0; letter < sdata.length() ; ++letter)
    {
        if(sdata.mid(letter,1) == " ")
            counter += 1;

        if(counter == 2)
            position = letter + 2;
    }
    QString retorno;

    retorno = sdata.mid(0,1).toUpper() + sdata.mid(1,position - 1) + sdata.mid(position,1).toUpper() + sdata.mid(position + 1, sdata.length() - position) ;

    return(sdata);
}

QString Tools::currentTime(QString format){

    QTime time = QTime::currentTime();

    return  time.toString(format);
}

QString Tools::indexState(int index)
{
    switch (index){
    case 0: return "AC";
    case 1: return "AL";
    case 2: return "AP";
    case 3: return "AM";
    case 4: return "BA";
    case 5: return "CE";
    case 6: return "DF";
    case 7: return "ES";
    case 8: return "GO";
    case 9: return "MA";
    case 10: return "MT";
    case 11: return "MS";
    case 12: return "MG";
    case 13: return "PR";
    case 14: return "PB";
    case 15: return "PA";
    case 16: return "PE";
    case 17: return "PI";
    case 18: return "RN";
    case 19: return "RS";
    case 20: return "RJ";
    case 21: return "RO";
    case 22: return "RR";
    case 23: return "SC";
    case 24: return "SE";
    case 25: return "SP";
    case 26: return "TO";
    default: return "";
    }
}

// l�gica de valida��o de CPF / CNPJ n�o � de minha responsabilidade.
// apenas peguei a l�gica na internet e converti para o C++

bool Tools::isValidCNPJ(QString cnpj)
{
    QString cnpjO = cnpj;

    cnpj = cnpj.mid(0, cnpj.length() - 2);

    // primeira e segunda sequencia de valores
    QString v1 = "543298765432";
    QString v2 = "6543298765432";

    // valores multiplicados
    int mul = 0;
    for (int i = 0; i < v1.length(); i++){
        mul += v1.mid(i, 1).toInt() * cnpj.mid(i, 1).toInt();
    }

    QString digVC = "";

    mul = (int) mul % 11;

    if (mul < 2)
        digVC += "0";
    else
        digVC += QString::number(11 - mul);

    cnpj += digVC;

    mul = 0;
    for (int i = 0; i < v2.length(); i++){
        mul += v2.mid(i, 1).toInt() * cnpj.mid(i, 1).toInt();
    }

    mul = mul % 11;

    digVC = "";
    if (mul < 2)
        digVC += "0";
    else
        digVC += QString::number(11 - mul);

    cnpj += digVC;

    return (cnpj == cnpjO);
}

bool Tools::isValidCPF(QString cpf)
{
    int d1, d2;
    int digito1, digito2, resto;
    int digitoCPF;

    d1 = d2 = digito1 = digito2 = resto = 0;

    QString nDigResult;

    for (int i = 1; i < cpf.length() - 1; i++){
        digitoCPF = cpf.mid(i - 1, 1).toInt();

        d1 += (11 - i) * digitoCPF;

        d2 += (12 - i) * digitoCPF;
    }

    resto = (d1 % 11);

    if (resto < 2)
        digito1 = 0;
    else
        digito1 = 11 - resto;

    d2 += 2 * digito1;

    resto = (d2 % 11);

    if (resto < 2)
        digito2 = 0;
    else
        digito2 = 11 - resto;

    QString nDigVerifi = cpf.mid(cpf.length() - 2, 2);

    nDigResult = QString::number(digito1) + QString::number(digito2);

    return (nDigResult == nDigVerifi);
}

int Tools::module(int a, int e, int n)
{
    int p = 1;

    if (e == 0)
        return 1;

    while (e != 0){
        if (e % 2 == 1){
            p = (a * p) % n;
            e = (e - 1) / 2; // como 'e' � �mpar, esse valor ser� sempre inteiro
        }else{
            e = (e / 2);
        }
    }

    return p;
}

int Tools::dayOfWeek(QString date)
{
    // converte a data em formato de string para o formato de data
    QDate d = QDate::fromString(date, "dd/MM/yyyy");

    return d.dayOfWeek();
}

QString Tools::dayBeginWeek(QString date)
{
    QDate d = QDate::fromString(date, "dd/MM/yyyy");

    d = d.addDays(dayOfWeek(date) * (-1));

    return d.toString("dd/MM/yyyy");
}

QString Tools::dayEndWeek(QString date)
{
    QDate d = QDate::fromString(date, "dd/MM/yyyy");

    d = d.addDays(7 - dayOfWeek(date));

    return d.toString("dd/MM/yyyy");
}

QString Tools::dayBeginMonth(QString date){
    return "01" + date.mid(2);
}

QString Tools::dayEndMonth(QString date){
    QString qntDays = daysInMonth(date);

    return qntDays + date.mid(2);
}

QString Tools::dayBeginYear(QString date){
    return "01/01/" + date.mid(6);
}

QString Tools::dayEndYear(QString date){
    return "31/12/" + date.mid(6);
}

bool Tools::betweenDates(QString dateIS, QString dateFS, QString dateCS)
{
    QDate dateI = QDate::fromString(dateIS, "dd/MM/yyyy");
    QDate dateF = QDate::fromString(dateFS, "dd/MM/yyyy");
    QDate dateC = QDate::fromString(dateCS, "dd/MM/yyyy");

    if (dateC >= dateI && dateC <= dateF)
        return true;

    return false;
}

QString Tools::daysInMonth(QString date)
{
    QDate d = QDate::fromString(date, "dd/MM/yyyy");

    return QString::number(d.daysInMonth());
}

QString Tools::daysInYear(QString date)
{
    QDate d = QDate::fromString(date, "dd/MM/yyyy");

    return QString::number(d.daysInYear());
}

bool Tools::isValidDate(QString date)
{
    if (date.length() < 10)
        return false;

    return QDate::isValid(date.mid(6).toInt(), date.mid(3, 2).toInt(), date.mid(0, 2).toInt());
}

bool Tools::isValidHour(QString hour)
{
    if (hour.length() < 5)
        return false;

    return QTime::isValid(hour.mid(0, 2).toInt(), hour.mid(3, 2).toInt(), 0);
}

QString Tools::currentTime()
{
    return QTime::currentTime().toString("hh:mm");
}

QString Tools::convertDate(QString date, QString separator)
{
    if (date.length() == 10)
        return date.mid(6, 4) + separator + date.mid(3, 2) + separator + date.mid(0, 2);

    return "";
}

QString Tools::convertDate2(QString date, QString separator)
{
    if (date.length() == 10)
        return date.mid(8, 2) + separator + date.mid(5, 2) + separator + date.mid(0, 4);

    return "";
}

QChar Tools::compareDate(QString date0, QString date1){
    QDate d0(QDate::fromString(date0, "dd/MM/yyyy"));
    QDate d1(QDate::fromString(date1, "dd/MM/yyyy"));

    if (d0 > d1)
        return QChar('0');
    else if (d1 > d0)
        return QChar('1');

    return QChar('-1');
}

QChar Tools::compareHour(QString hour0, QString hour1){
    QTime h0(QTime::fromString(hour0, "hh:mm"));
    QTime h1(QTime::fromString(hour1, "hh:mm"));

    if (h0 > h1)
        return QChar('0');
    else if (h1 > h0)
        return QChar('1');

    return QChar('-1');
}

QString Tools::secondsToTime(int seconds, bool isLong)
{
    int min = 0;
    int sec = 0;
    int hour = 0;

    hour = (int)(seconds/3600);
    min = seconds%3600;
    min = (int)(min/60);
    sec = min%60;

    QString temp;
    QString temp2;

    QString returnTime;

    if(isLong) // tempo de forma longa
    {

        if(hour > 0)
        {
            temp.setNum(hour);
            returnTime = temp + tr(" hora(s), ");
        }
        if(min > 0)
        {
            temp.setNum(min);
            returnTime += temp + tr(" minuto(s) ");
        }

        temp.setNum(sec);

        returnTime += tr("e ") + temp + tr("segundo(s)");
    }
    else // tempo de forma Curta
    {
        if(hour > 0)
        {                       
            temp.setNum(hour);
            if(temp.length() < 2)
                temp2 += "0" + temp;

            returnTime = temp2 + tr(":");

            temp2.clear();
        }
        else
            returnTime = "00:";

        if(min > 0)
        {
            temp.setNum(min);

            if(temp.length() < 2)
                temp2 += "0" + temp;

            returnTime += temp2 + tr(":");

            temp2.clear();
        }
        else
            returnTime += "00:";

        temp.setNum(sec);

        if(temp.length() < 2)
        {
            temp2 += "0" + temp;
            returnTime += temp2;
        }
        else
            returnTime += temp;
    }

    return returnTime;
}

QDateTime Tools::subDate(QString date, QString hour, int minutes)
{
    QDateTime dt(QDate::fromString(date, "dd/MM/yyyy"), QTime::fromString(hour, "hh:mm"));

    dt = dt.addSecs((-1) * minutes * 60);

    return dt;
}

bool Tools::createTextFile(QString fileName)
{
    QFile file(fileName);

    if(!file.open(QIODevice::ReadWrite | QIODevice::Append))
    {
        file.close();
        return true;
    }
    else
        return false;
}

QString Tools::readFile(QString fileName)
{
    QFile file(fileName);

    if(!file.open(QFile::ReadOnly))
        return "";

    QString bodyFile(QLatin1String(file.readAll()));

    file.close();

    return bodyFile;
}

bool Tools::writeFile(QString fileName, QString text)
{
    QFile file(fileName);

    if(!file.open(QIODevice::WriteOnly))
        return false;

    QTextStream stream(&file);

    stream << text;

    file.close();

    return true;
}

QString Tools::year(QString date)
{
    return date.mid(6);
}

QList<int> Tools::listToInt(QList<QString> list)
{
    QList<int> lReturn;

    foreach (QString value, list) {
        lReturn << value.toInt();
    }

    return lReturn;
}

QList<double> Tools::listToDouble(QList<QString> list)
{
    QList<double> lReturn;

    foreach (QString value, list) {
        lReturn << value.toDouble();
    }

    return lReturn;
}
