#include "task_button.h"

task_button::task_button(QWidget *parent)
    : QPushButton{parent}
{


}
task_button::task_button(Task* thetask )
{  my_task=thetask;setText(my_task->name);
    connect(this,&QPushButton::clicked,this,&task_button::my_task_button_clicked);
}
 task_button::~task_button()
{

}

void task_button::my_task_button_clicked()
{
    emit task_button_clicked(my_task);//发射信号
}
