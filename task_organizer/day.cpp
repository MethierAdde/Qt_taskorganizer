#include"day.h"


Day::Day(int id):id(id)
{

}

void Day::print2recorder(QTextStream &out)
{
    out<<"Day: "<<id<<"\n";
    out<<"blocknum: "<<blocklist.size()<<"\n";
    for(auto i=blocklist.begin();i!=blocklist.end();i++)
    {
        i->print(out);
    }
}
