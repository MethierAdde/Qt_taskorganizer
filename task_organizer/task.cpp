#include "task.h"

Task::Task (int id,int state,QString name,int typelabel,QString note,bool sametime,int hard,int worktime,int ddlday):
    id(id),state(state),name(name),label(typelabel),notes(note),sametimeable(sametime),hard(hard),worktime(worktime),ddlday(ddlday){
    starttime=endtime=day=-1;
}

Task::Task (int id,int state,QString name,int typelabel,QString note,bool sametime,int hard,int starttime,int endtime,int day):
    id(id),state(state),name(name),label(typelabel),notes(note),sametimeable(sametime),hard(hard),starttime(starttime),endtime(endtime),
    day(day),ddlday(day)
{
    worktime=endtime-starttime;
}


void Task::print(QTextStream& out){
    if(label==FIXEDTASK)
    {
        out<<id<<" "<<state<<" "<<name<<" "<<label<<" "<<notes<<" "<<sametimeable<<" "<<hard<<" "<<starttime<<" "<<endtime<<" "<<day<<"\n";
    }
    else if(label==DDLTASK)
        out<<id<<" "<<state<<" "<<name<<" "<<label<<" "<<notes<<" "<<sametimeable<<" "<<hard<<" "<<worktime<<" "<<ddlday<<"\n";
    else {
            qDebug()<<"record label error";
    }
}

