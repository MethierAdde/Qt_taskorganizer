#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "personalset.h"
#include "task_arranger.h"
#include "add_fixedddl.h"
//最后mainwindow的析构函数中要包括保存到文件夹中
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{   personalset.read();
    alltask.read();
    taskarrange.read();
    ui->setupUi(this);
    set=new Settings(this);//设置的主页面
    add=new Add_New(this);//添加任务的主页面
    exp=new explaining(this);
    f_time= new Add_FixedTime(this);
    f_ddl=new Add_Fixed(this);
    manage=new Management(this);
    block_layout=new  QVBoxLayout(ui->Theblock_contents);
    task_from_block_layout= new QVBoxLayout(ui->day_task);//先整这两个
to_be_task_layout= new QVBoxLayout(ui->to_be_added);
    ui->stackedWidget->setCurrentIndex(2);
    connect(f_ddl,&Add_Fixed::to_add_refresh,this,&MainWindow::add_task);
    connect(f_time,&Add_FixedTime::to_add_refresh,this,&MainWindow::add_task);
    connect(add,&Add_New::to_add_ddl,this,&MainWindow::add_fixed_ddl);
    connect(add,&Add_New::to_add_time,this,&MainWindow::add_fixed_time);
    //将其connect起来
    //每次相关操作要刷新myday

    Refresh_MyDay();
    refresh_to_be_add();




} ;


void MainWindow::add_fixed_ddl()
{
    f_ddl->show();
}
void MainWindow::add_fixed_time()
{
    f_time->show();
}
void MainWindow::add_task()
{
    refresh_to_be_add();
}
//可以用一个vector来储存这些按钮 然后需要进入删除界面的时候直接调用即可
void MainWindow::Refresh_MyDay()//用于更新myday区域中的任务;
{
    //重置vector

    if(!all_task_button.empty())
    {
        for (auto i=all_task_button.begin();i!=all_task_button.end();i++)
        {
            delete *i;
        }//先释放了按钮
        all_task_button.clear();//清空vector

    }

    //重建布局
    refresh_block();

    ui->Day_Name->setText(all_day[Display_Day]);
refresh_to_be_add();

}
void MainWindow::refresh_block()
{  if(!blockbuttons.empty())
    {
        for(auto it=blockbuttons.begin();it!=blockbuttons.end();it++)
        {
            delete *it;
        }
    }
    blockbuttons.clear();



    thisday=&taskarrange.week[Display_Day-1];//保存这一天的day
    for(auto it=thisday->blocklist.begin();it!=thisday->blocklist.end();it++)
    {
        //创建按钮并push_back

       // qDebug()<<temp_block->My_block->taskindex.size();

        qDebug()<<it->ddlday;
        block_button * temp_block=new block_button(&(*it));
         qDebug()<<"正常";

        block_layout->addWidget(temp_block);

        connect(temp_block,&block_button::block_button_clicked,this,&MainWindow::refresh_tasks);//进行连接
        blockbuttons.push_back(temp_block);

    }
    block_layout->setSpacing(0);
}

void MainWindow::refresh_to_be_add()
{
    if(!all_to_add_button.empty())
    {
        for(auto it=all_to_add_button.begin();it!=all_to_add_button.end();it++)
        {
            delete *it;
        }
    }
    vector<int> new_task_id=alltask.getnewtask();//获取所有新的任务
    all_to_add_button.clear();
    for(auto it=new_task_id.begin();it!=new_task_id.end();it++)
    {
        task_button *temp_task=new task_button(alltask.alltask[*it]);
        to_be_task_layout->addWidget(temp_task);
        connect(temp_task,&task_button::task_button_clicked,this,&MainWindow::tasks_displayed);
        all_to_add_button.push_back((temp_task));
    }
    to_be_task_layout->setSpacing(0);


}
//更新下面界面的东东,别忘了这个还要和旁边的联系起来
void MainWindow::refresh_tasks(Block * thisblock)
{   now_block=thisblock;

    if(!all_task_button.empty())
    {
        for(auto it=all_task_button.begin();it!=all_task_button.end();it++)
        {
            delete *it;
        }
    }

    all_task_button.clear();

    for(auto it=thisblock->taskindex.begin();it!=thisblock->taskindex.end();it++)
    {
        task_button * temp_task=new task_button(alltask.alltask[*it]);
        task_from_block_layout->addWidget(temp_task);
        connect(temp_task,&task_button::task_button_clicked,this,&MainWindow::tasks_displayed);
        all_task_button.push_back(temp_task);
    }

    task_from_block_layout->setSpacing(0);
}



MainWindow::~MainWindow()
{
    personalset.record();
    taskarrange.print2recorder(alltask.newindex());
    alltask.record();
    delete ui;
}


void MainWindow::tasks_displayed(Task * mytask)
{   now_task=mytask;
    QFont font("微软雅黑",12);
    ui->task_name_displayer->setFont(font);
    ui->task_name_displayer->setText(mytask->name);
    //判断label
    if(mytask->label==1)
    {
        ui->stackedWidget->setCurrentIndex(0);//转换页面
        ui->task_note->setPlainText(mytask->notes);
        //备注
        if(mytask->sametimeable)
        {
            ui->ddl_sametime->setText("是");
        }
        else
        {
            ui->ddl_sametime->setText("否");
        }//是否同时做
        ui->ddl_hard->setText(QString::number(mytask->hard));//精力消耗
        ui->ddl_ddltime->setText(all_day[mytask->ddlday+1]);
        ui->ddl_needtime->setText(QString::number(30*mytask->worktime)+"mins");


    }
    else if(mytask->label==2)
    {
        ui->stackedWidget->setCurrentIndex(1);
        ui->task_note_2->setPlainText(mytask->notes);
        //备注
        if(mytask->sametimeable)
        { ui->fixed_sametime_2->setText("是");}
        else
        {
            ui->fixed_sametime_2->setText("否");
        }
        ui->fixed_hard_2->setText(QString::number(mytask->hard));
        ui->fixed_time_range->setText(maintimes[mytask->starttime]+"-"+maintimes[mytask->endtime]);
        ui->fixed_needtime_2->setText(QString::number(30*mytask->worktime)+"mins");
    }

}


//每一天的展示:
//1.有一个vector 是用来储存所有按钮的指针的 对于每个按钮 按动后会导致旁边进行显示
//2.有一个int型变量，记录现在显示的是星期几
// 全用一个widget来进行排列
//
//程序开始运行 默认是星期一 就按照星期一来创建  注意每一个按钮要进行关联   *释放
//·点击下一天 释放掉vector中所有的按钮
//·删除某个任务的时候
//然后根据day+1的任务重新创建按钮 同上，别忘了拉伸


//对于任务可视化的想法: 设置一个 时间段类和  任务类
// 时间段类和任务类 分别 放置对应的指针
//在refresh 中-> 获取这一天的block指针 后 利用block指针创建 时间段按钮 创建时间段按钮后，







void MainWindow::on_Main_set_clicked()
{
    set->show();
}


void MainWindow::on_new_2_clicked()
{
    add->show();
}


void MainWindow::on_instruction_clicked()
{
    exp->show();
}


void MainWindow::on_pushButton_2_clicked()//翻页
{
    Display_Day+=1;
    if(Display_Day>7) Display_Day=1;
    Refresh_MyDay();
}


void MainWindow::on_pushButton_clicked()
{
    Display_Day-=1;
    if(Display_Day<=0) Display_Day=7;
    Refresh_MyDay();
}


void MainWindow::on_pushButton_3_clicked()
{
     refresh_to_be_add();
}


void MainWindow::on_cal_clicked()
{    vector<int> wrong_location;
    if(arrange_running(alltask,personalset,taskarrange,wrong_location))
    {
        //可视化
        Refresh_MyDay();
        QMessageBox::information(nullptr,"提示","生成成功");
    }
    else
    {  QString a;
        for(auto it=wrong_location.begin();it!=wrong_location.end();it++)
        {
            a+=all_day[(*it)+1];
            if(it==wrong_location.end()-1)
            {
                break;
            }
            a+=',';
        }
        a+="的任务太多，无法合理安排";
       QMessageBox::critical(nullptr,"警告！",a);
    }
     refresh_to_be_add();
}


void MainWindow::delete_now_task()
{
    //一,若已经安排 则需要考虑block
    //1.从block中擦除 blcok的starttime和endtime都要改
    //2.从alltaskrecorder中删除
    //二。 若未安排 直接erase并刷新即可
    int delete_id=now_task->id;
    if(now_task->state==2) {

        auto delete_it=std::find(now_block->taskindex.begin(),now_block->taskindex.end(),delete_id);
        if(delete_it!=now_block->taskindex.end())
        {
            now_block->taskindex.erase(delete_it);
            //如果删掉以后block任务量为0 就删掉
            if(now_block->taskindex.size()==0)//删掉
            {
                Block temp_block=*now_block;
                auto delete_blockit=std::find(thisday->blocklist.begin(),thisday->blocklist.end(),temp_block);
                if(delete_blockit!=thisday->blocklist.end())
                {
                    thisday->blocklist.erase(delete_blockit);
                }
            }
        }
        alltask.erase(delete_id);//最后删除该任务
        Refresh_MyDay();
        ui->stackedWidget->setCurrentIndex(2);
    }
    else if(now_task->state==1)
    {
        alltask.erase(delete_id);
        Refresh_MyDay();
        refresh_to_be_add();
        ui->stackedWidget->setCurrentIndex(2);
    }
}
void MainWindow::on_Fixed_time_delete_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("提示");
    msgBox.setText("你确定要删除该任务吗?");
    msgBox.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    msgBox.button(QMessageBox::Yes)->setText("确定");
    msgBox.button(QMessageBox::No)->setText("取消");


    int choice=msgBox.exec();
    if(choice==QMessageBox::Yes)
    {
        delete_now_task();
    }//如果确认删除,

}
void MainWindow::on_Ddl_delete_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("提示");
    msgBox.setText("你确定要删除该任务吗?");
    msgBox.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    msgBox.button(QMessageBox::Yes)->setText("确定");
    msgBox.button(QMessageBox::No)->setText("取消");

    int choice=msgBox.exec();
    if(choice==QMessageBox::Yes)
    {
        delete_now_task();
    }//如果确认删除,
}



//修改功能：先将文本框里的内容设置成此任务的形式 按一下确定， 即删除原来的，添加新的
void MainWindow::on_Ddl_change_clicked()
{
    f_ddl->show();
    f_ddl->ddl_change(now_task->name,now_task->notes,now_task->sametimeable,now_task->hard,now_task->ddlday,now_task->worktime);
        delete_now_task();
    //新创建一个add_fixedddl 用构造函数来填充文字内容，删除掉
}


void MainWindow::on_Fixed_time_change_clicked()
{
    f_time->show();
    f_time->fixed_time_change(now_task->name,now_task->notes,now_task->sametimeable,now_task->hard,now_task->starttime,now_task->endtime,now_task->day);
        delete_now_task();
}

