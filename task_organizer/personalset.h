#ifndef PERSONALSET_H
#define PERSONALSET_H

#include<QDebug>
#include<QFile>
#include<QTextStream>
#include<QCoreApplication>
//个人偏好设置的类，目前只用实现ddlwarrior和nightworker
class PersonalSet
{
public:
    double ddlwarrior;//更偏向于赶ddl
    double nightworker;//更偏向于熬夜完成任务
    double earlygetuper;
    int start;
    int end;
    PersonalSet(double ddlwarrior = 0.8,double nightworker=0.8,double earlygetuper=0.2,int start =16,int end=46);//可以直接从文件读入设置
    void setddl(double d);//设置ddlwarrior
    void setnight(double d);//设置nightworker，我推荐使用这两个函数，因为可以直接写入文件
    void setearly(double d);
    void setstart(int start);
    void setend(int end);

    void read();
    void record();
};
extern PersonalSet personalset;

#endif // PERSONALSET_H
