#include "settings.h"
#include "ui_settings.h"
#include "personalset.h"
#include <QMessageBox>
Settings::Settings(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Settings)
{
    ui->setupUi(this);
//开始的
     begin_hour=int(personalset.start/2);
     end_hour=int(personalset.end/2);
     begin_minute=personalset.start*30-begin_hour*30;
     end_minute=personalset.end*30-end_hour*30;
    ui->ddl_changer->setValue(10*personalset.ddlwarrior);

    ui->night_changer->setValue(10*personalset.nightworker);
    ui->begin_hour->setValue(begin_hour);
    ui->begin_minute->setValue(begin_minute);
    ui->end_hour->setValue(end_hour);
    ui->end_minute->setValue(end_minute);
    this->setWindowModality(Qt::ApplicationModal);

}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_buttonBox_accepted()
{
    personalset.ddlwarrior=double(ui->ddl_changer->value())/10;
    personalset.nightworker=double(ui->night_changer->value())/10;

    personalset.setddl(double(personalset.ddlwarrior));
    personalset.setnight(personalset.nightworker);//前两个指标，不可能报错

    if(ui->begin_hour->value()*60+ui->begin_minute>ui->end_hour->value()*60+ui->end_minute)
    {
        QMessageBox::critical(nullptr,"警告！","您一天的起止时间设计不合法！");
        ui->night_changer->setValue(10*personalset.nightworker);
        ui->begin_hour->setValue(begin_hour);
        ui->begin_minute->setValue(begin_minute);
        ui->end_hour->setValue(end_hour);
        ui->end_minute->setValue(end_minute);


    }//如果不符合逻辑，进行报错
    else
    {
        personalset.start=ui->begin_hour->value()*2+ui->begin_minute->value()/30;
        personalset.end=ui->end_hour->value()*2+ui->end_minute->value()/30;
        personalset.setstart(personalset.start);
        personalset.setend(personalset.end);
    }



}


void Settings::on_buttonBox_rejected()
{

    ui->ddl_changer->setValue(personalset.ddlwarrior);
    ui->night_changer->setValue(personalset.nightworker);
    ui->night_changer->setValue(10*personalset.nightworker);
    ui->begin_hour->setValue(begin_hour);
    ui->begin_minute->setValue(begin_minute);
    ui->end_hour->setValue(end_hour);
    ui->end_minute->setValue(end_minute);
}

