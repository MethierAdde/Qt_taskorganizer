#include"alltask_recorder.h"

AlltaskRecorder::AlltaskRecorder()
{

}
void AlltaskRecorder::read()
{
    QString basePath = QCoreApplication::applicationDirPath();
    QFile file(basePath+"/record/alltask.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        in>>tasksum;
        for(int i=0;i<tasksum;i++)
        {
            Task *onetask;
            int id,label,state,sametime,hard;
            QString name,note;
            in>>id>>state>>name>>label>>note>>sametime>>hard;
            if(label==FIXEDTASK)
            {
                int starttime,endtime,day;
                in>>starttime>>endtime>>day;
                onetask=new Task(id,state,name,label,note,sametime,hard,starttime,endtime,day);
            }
            if(label==DDLTASK)
            {
                int worktime,ddlday;
                in>>worktime>>ddlday;
                onetask = new Task(id,state,name,label,note,sametime,hard,worktime,ddlday);
            }
            alltask.push_back(onetask);
        }
        qDebug()<<"alltask read successful\n";
    }
    else
        qDebug()<<"error read alltask\n";
}
void AlltaskRecorder::putnewtask(QString name,int label,QString note,bool sametime,int hard,int starttime,int endtime,int day)
{
    Task *onetask;
    if(label==FIXEDTASK)
    {
        onetask=new Task(tasksum,1,name,label,note,sametime,hard,starttime,endtime,day);
        qDebug()<<"New fixed task "<<name<<" get";
    tasksum++;
    alltask.push_back(onetask);
    }
    else
        qDebug()<<"task label error";
}
void AlltaskRecorder::putnewtask(QString name,int label,QString note,bool sametime,int hard,int worktime,int ddlday)
{
    Task *onetask;
    if(label==DDLTASK)
    {
        onetask=new Task(tasksum,1,name,label,note,sametime,hard,worktime,ddlday);
        qDebug()<<"New ddl task "<<name<<" get";
        tasksum++;
        alltask.push_back(onetask);
    }
    else
        qDebug()<<"task label error";
}

void AlltaskRecorder::record()
{
    QString basePath = QCoreApplication::applicationDirPath();
    QFile file(basePath+"/record/alltask.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        int sum=0;
        for(int i=0;i<tasksum;i++)
        {
            if(alltask[i]->state!=0)
            {
                alltask[i]->id=(sum++);
            }
        }
        tasksum=sum;
        out<<tasksum<<"\n";
        for(int i=0;i<int(alltask.size());i++)
        {
            if(alltask[i]->state!=0)
            {
                alltask[i]->print(out);
            }
        }
        qDebug()<<"alltask write successful\n";
    }
    else
        qDebug()<<"error write alltask\n";
}

void AlltaskRecorder::erase(int id)
{
    alltask[id]->state=0;
    qDebug()<<"erase task "<<alltask[id]->name;
}

void AlltaskRecorder::arrange(int id)
{
    alltask[id]->state=2;
}

AlltaskRecorder::~AlltaskRecorder()
{
    for(auto i=alltask.begin();i!=alltask.end();i++)
        delete *i;
}

Task*AlltaskRecorder::operator()(int i)
{
    return alltask[i];
}

vector<int> AlltaskRecorder::getnewtask()
{
    vector<int> newtask;
    for(int i=0;i<tasksum;i++)
    {
        if(alltask[i]->state==1)
            newtask.push_back(i);
    }
    return newtask;
}
vector<int> AlltaskRecorder::getarrangedtask()
{
    vector<int> arrangedtask;
    for(int i=0;i<tasksum;i++)
    {
        if(alltask[i]->state==2)
            arrangedtask.push_back(i);
    }
    return arrangedtask;
}

vector<int> AlltaskRecorder::newindex()
{
    vector<int> newindex;
    int sum=0;
    for(int i=0;i<tasksum;i++)
    {
        if(alltask[i]->state==0)
            newindex.push_back(-1);
        else
            newindex.push_back(sum++);
    }
    return newindex;
}
AlltaskRecorder alltask;
