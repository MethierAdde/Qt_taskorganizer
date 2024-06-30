#ifndef BLOCK_H
#define BLOCK_H

#include "task.h"
#include "alltask_recorder.h"

class Block
{
public:
    int starttime;//一个block的开始时间
    int endtime;//一个block的结束时间
    int day;//一个block所在的天

    int label;
    int ddlday;
    int worktime;
    vector<int> taskindex;//包含的task索引
    Block();
    Block(Task t);
    Block(Task t1,Task t2);
    Block(const Block& x, int begin, int end, int days);
    bool operator==(const Block& other) const;



    void print(QTextStream &out)const;//输出到文件中，不用管
};

#endif // BLOCK_H
