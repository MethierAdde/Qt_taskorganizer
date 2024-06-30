#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include<QDir>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString basePath = QCoreApplication::applicationDirPath();
    QDir dir;
    if(!dir.exists(basePath+"/record"))
    {
        if(dir.mkpath(basePath+"/record"))
            qDebug()<<"record目录创建成功\n";
        else
            qDebug()<<"record目录创建失败\n";
    }
    else
        qDebug()<<"record目录已存在\n";

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "task_organizer_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    MainWindow w;
    w.show();

    return a.exec();
}
