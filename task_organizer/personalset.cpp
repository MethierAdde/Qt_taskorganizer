#include "personalset.h"

PersonalSet::PersonalSet(double ddlwarrior,double nightworker,double earlygetuper,int start,int end):ddlwarrior(ddlwarrior),
    nightworker(nightworker),earlygetuper(earlygetuper),start(start),end(end)
{

}
void PersonalSet::read()
{
    QString basePath = QCoreApplication::applicationDirPath();
    QFile file(basePath+"/record/personalset.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString str;
        in>>str>>ddlwarrior;
        in>>str>>nightworker;
        in>>str>>earlygetuper;
        in>>str>>start;
        in>>str>>end;
        file.close();
        qDebug() << "personalset read successful\n";
    }
    else {
        qDebug() << "Error read personalset\n";
    }
}
void PersonalSet::setddl(double d)
{
    ddlwarrior=d;
    record();
}
void PersonalSet::setnight(double d)
{
    nightworker=d;
    record();
}
void PersonalSet::setearly(double d)
{
    earlygetuper=d;
    record();
}

void PersonalSet::setstart(int d)
{
    start =d;
    record();
}

void PersonalSet::setend(int d)
{
    end =d;
    record();
}

void PersonalSet::record()
{
    QString basePath = QCoreApplication::applicationDirPath();
    QFile file(basePath+"/record/personalset.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << "ddlwarrior: " << ddlwarrior<<"\n";
        out << "nightworker: " << nightworker<<"\n";
        out << "earlygetuper: " << earlygetuper<<"\n";
        out<<"starttme: "<<start<<"\n";
        out<<"endtime: "<<end<<"\n";
        file.close();
        qDebug() << "personalset write successful!\n";
    }
    else {
        qDebug() << "Error opening personalset!\n";
    }
}

PersonalSet personalset;
