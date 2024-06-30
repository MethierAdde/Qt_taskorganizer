#include "add_fixedtime.h"
#include "ui_add_fixedtime.h"
#include <qdebug.h>
#include <QString>
#include "alltask_recorder.h"
#include <QMessageBox>
Add_FixedTime::Add_FixedTime(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Add_FixedTime)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::Window);

}

Add_FixedTime::~Add_FixedTime()
{
    delete ui;
}

//ddl为2

void Add_FixedTime::on_buttonBox_accepted()
{
    QString temp_name=ui->task_name->text();
    QString temp_note=ui->task_note->text();
    if(temp_note=="")
        temp_note="nothing";
    bool temp_sametime=!ui->same0->isChecked();
    int hard=ui->task_hard->value();
    int temp_starttime=ui->task_begin->value();
    int temp_endtime=ui->task_end->value();
    int temp_day=ui->task_day->value();

    if(temp_name.size()==0)
    {
        QMessageBox::critical(nullptr,"错误！","您的任务名为空！");
    }
    if(temp_endtime<temp_starttime)
    {
       QMessageBox::critical(nullptr,"错误！","起止时间设计不合法！");
    }
    else
    {
        alltask.putnewtask(temp_name,2,temp_note,temp_sametime,hard,temp_starttime,temp_endtime,temp_day-1);
        emit to_add_refresh();
    }
}

void Add_FixedTime::fixed_time_change(QString temp_name,QString temp_note,bool same,int temp_hard,int starttime,int endtime,int temp_day)
{

    ui->task_name->setText(temp_name);
    ui->task_note->setText(temp_note);
    if(same)
    {
        ui->same1->setCheckable(true);
    }
    else ui->same0->setChecked(true);
    ui->task_hard->setValue(temp_hard);
    ui->task_begin->setValue(starttime);
    ui->task_end->setValue(endtime);
    ui->task_day->setValue(temp_day+1);
}

