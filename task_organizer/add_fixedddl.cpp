#include "add_fixedddl.h"
#include "ui_add_fixedddl.h"
#include "alltask_recorder.h"
#include <Qstring>
#include <QMessageBox>
#include "mainwindow.h"
Add_Fixed::Add_Fixed(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Add_Fixed)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::Window);
   // this->setWindowModality(Qt::ApplicationModal);

}

Add_Fixed::~Add_Fixed()
{
    delete ui;
}

void Add_Fixed::on_buttonBox_accepted()
{
    QString temp_name=ui->task_name->text();
    QString temp_note=ui->task_note->text();
    if(temp_note=="")
        temp_note="nothing";
    bool same=ui->same_1->isChecked();
    int temp_hard=ui->hard_changer->value();
    int temp_ddl_day=ui->ddl_day->value();
    int temp_work_time=ui->time->value();
    if(temp_name.size()==0)
    {
         QMessageBox::critical(nullptr,"警告！","您的任务名为空！");
    }
    else
    {
        alltask.putnewtask(temp_name,1,temp_note,same,temp_hard,temp_work_time,temp_ddl_day-1);
        this->close();
        emit to_add_refresh();//发送
    }
   //发送更新界面的signal

    //这里调用 main中的refresh

}
//label 为1
void Add_Fixed::ddl_change(QString temp_name,QString temp_note,bool same,int temp_hard,int temp_ddl_day,int temp_work_time)
{
    ui->task_name->setText(temp_name);
    ui->task_note->setText(temp_note);
    if(same)
    {
        ui->same_1->setChecked(true);
    }
    else ui->same_0->setChecked(true);
    ui->hard_changer->setValue(temp_hard);
    ui->ddl_day->setValue(temp_ddl_day);
    ui->time->setValue(temp_work_time+1);
}
