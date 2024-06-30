#ifndef TASK_H
#define TASK_H

#include<Qstring>
#include<QTextStream>
#include<QDebug>
using namespace std;
#define FIXEDTASK 2
#define DDLTASK 1
class Task
{
public:
    int id;//每个任务独有的一个index
    int state;//状态
    QString name;//任务名称
    int label;//表示种类，DDLTASK为1，FIXEDTASK为2
    QString notes;//备注
    bool sametimeable;//是否可以同时做
    int hard;//任务的
    int worktime,ddlday,starttime,endtime,day;

    Task (int id,int state,QString name,int typelabel,QString note,bool sametime,int hard,int worktime,int ddlday);//ddltask初始化
    Task (int id,int state,QString name,int typelabel,QString note,bool sametime,int hard,int starttime,int endtime,int day);//
    Task(){}
    virtual ~Task(){}

    void print(QTextStream &out);//输出到文件
};

#endif //TASK_H
