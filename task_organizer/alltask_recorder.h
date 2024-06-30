#ifndef ALLTASK_RECORDER_H
#define ALLTASK_RECORDER_H

#include <vector>
#include<QFile>
#include<QTextStream>
#include<QCoreApplication>
#include<QDebug>
#include "task.h"
using namespace std;
//记录所有task的类
class AlltaskRecorder
{
public:
    vector<Task*> alltask;//这个vector记录了所有的task
    int tasksum=0;//alltask中的任务总数
    AlltaskRecorder();
    void read();//初始化，一次运行只用初始化一次，因为我们只需要用一个alltask
    ~AlltaskRecorder();//析构的同时更新了文件
    void putnewtask(QString name,int typelabel,QString note,bool sametime,int hard,int starttime,int endtime,int day);//把一个新的定时task放到alltask里
    void putnewtask(QString name,int typelabel,QString note,bool sametime,int hard,int work_time,int ddlday);//新的ddltask
    //这个新任务的state直接设置成了newtask，也就是1
    void record();//别用它，这个只用在进程结束的时候保存

    Task*operator()(int i);//重载（int），获取id为i的task指针
    vector<int> getnewtask();//获取newtask索引
    vector<int> getarrangedtask();//获取已安排好的task索引
    vector<int> newindex();//别管，在进程结束保存文件时要用
    void erase(int id);//删除任务，，事实上是把state设置为0，进程结束时再删除
    void arrange(int id);//设置某任务已经被安排过
};
extern AlltaskRecorder alltask;




#endif // ALLTASK_RECORDER_H
