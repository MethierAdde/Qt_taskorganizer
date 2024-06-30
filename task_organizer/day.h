#ifndef DAY_H
#define DAY_H

#include "block.h"
#include<QTextStream>
//一周内某一天的类
class Day{
public:
    int id;//表示周几
    Day(int day);//初始化
    vector<Block> blocklist;//包含的block
    void print2recorder(QTextStream &out);//输出到文件
    ~Day(){}
};




#endif // DAY_H
