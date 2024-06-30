#include "block.h"

Block::Block()
{

}

Block::Block(Task t){
    taskindex.push_back(t.id);
    worktime = t.worktime;
    ddlday = t.ddlday;
    label = t.label;
    starttime = t.starttime;
    endtime = t.endtime;
    day = t.day;
}
Block::Block(Task t1,Task t2){
    taskindex.push_back(t1.id);
    taskindex.push_back(t2.id);
    ddlday = min(t1.ddlday,t2.ddlday);
    worktime = max(t1.worktime, t2.worktime);
    label = t1.label + t2.label == 2 ? 1 : 2;
    if (t1.label == 2) {
        starttime = t1.starttime;
        endtime = t1.endtime;
        day = t1.day;
    }
    else if (t2.label == 2) {
        starttime = t2.starttime;
        endtime = t2.endtime;
        day = t2.day;
    }

}
Block::Block(const Block& x, int begin, int end, int days) {
    *this = x;
    starttime = begin;
    endtime = end;
    day = days;

}
void Block::print(QTextStream &out)const
{
    out<<"starttime: "<<starttime<<"  endtime: "<<endtime<<"\n";
    out<<"tasknum: "<<taskindex.size()<<"\n";
    out<<"ddlday: "<<ddlday<<"\n";
    for(auto i=taskindex.begin();i!=taskindex.end();i++)
    {
        out<<*i<<" ";
    }
    out<<"\n";
}
bool Block::operator==(const Block& other) const
{
    return this->taskindex==other.taskindex;
}
