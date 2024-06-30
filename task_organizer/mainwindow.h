#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QDebug>
#include "alltask_recorder.h"
#include "personalset.h"
#include "qlabel.h"
#include "task_arranger.h"
#include "explaining.h"
#include "settings.h"
#include "add_new.h"
#include "add_fixedtime.h"
#include "add_fixedddl.h"
#include "management.h"
#include "block.h"
//#include <QtWidgets>
#include "task_arranger.h"
#include "day.h"
#include "block_button.h"
#include "task_button.h"
#include <QVBoxLayout>
#include <QFont>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void Refresh_MyDay();
    QString maintimes[48] = {
        "00:00", "00:30", "01:00", "01:30", "02:00", "02:30", "03:00", "03:30",
        "04:00", "04:30", "05:00", "05:30", "06:00", "06:30", "07:00", "07:30",
        "08:00", "08:30", "09:00", "09:30", "10:00", "10:30", "11:00", "11:30",
        "12:00", "12:30", "13:00", "13:30", "14:00", "14:30", "15:00", "15:30",
        "16:00", "16:30", "17:00", "17:30", "18:00", "18:30", "19:00", "19:30",
        "20:00", "20:30", "21:00", "21:30", "22:00", "22:30", "23:00", "23:30"
    };

    //变量
    explaining *exp;//解释窗口的指针
    Settings *set;
    Add_New *add;
    Add_FixedTime *f_time;
    Add_Fixed *f_ddl;
    Management * manage;

    int Display_Day=1;//代表显示的那一天

    QString all_day[8]={"useless","周一","周二","周三","周四","周五","周六","周日"};
    QLabel Daylabel=QLabel(all_day[Display_Day]);
    Day *thisday;
    vector<task_button *> all_task_button;//储存block中的任务按钮
    vector <block_button *> blockbuttons;//储存所有block按钮
    vector <task_button*> all_to_add_button;
    QVBoxLayout * block_layout;
    QVBoxLayout * task_from_block_layout;
    QVBoxLayout * to_be_task_layout;
    Task *now_task;//每次点击task_button时，会给now_task_button 赋地址，使得可以操作该task_button
    Block *now_block;//每次点击时间段按钮进行更新

    //每天的label
    void refresh_to_be_add();
    void delete_now_task();
private slots:


    void on_Main_set_clicked();

    void on_new_2_clicked();

    void on_instruction_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();
   //生成后调用，用来刷新
    void refresh_block();//刷新所有的block

    void on_pushButton_3_clicked();

    void on_cal_clicked();





    void on_Fixed_time_delete_clicked();

    void on_Ddl_delete_clicked();

    void on_Ddl_change_clicked();

    void on_Fixed_time_change_clicked();

public slots:
    void refresh_tasks(Block * thisblock);
    void tasks_displayed(Task * mytask);
    void add_fixed_ddl();
    void add_task();
    void add_fixed_time();




private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
