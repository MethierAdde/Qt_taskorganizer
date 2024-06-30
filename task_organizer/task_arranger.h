#ifndef TASK_ARRANGER_H
#define TASK_ARRANGER_H

#include<QFile>
#include<QTextStream>
#include<QCoreApplication>
#include<QDebug>
#include"day.h"
#include"alltask_recorder.h"
#include"personalset.h"

class TaskArranger
{
public:
    Day week[7]{0,1,2,3,4,5,6};//访问day    改了
    TaskArranger();
    void read();
    void print2recorder();//记录到文件，每次安排过任务需要使用
    void print2recorder(vector<int>);//记录到文件，此时是要更新index，只用于进程结束
    void freshindex(vector<int>);//更新任务的index，别管
    //void arrange(AlltaskRecorder &alltask);
};

struct node {
    node(){}
    vector<Block> house;
    double val;
    node( vector<Block>b,double v):house(b),val(v){}
};
struct slot {
    int day;
    int begin, end;
    slot(int day, int begin, int end):day(day),begin(begin),end(end) {};
};
class sort_judge {
public:
    bool operator()(Block& t1, Block& t2) {
        return t1.starttime < t2.starttime;
    }
};

double j_value(const Task&t);

double j_value(const Task t1,const Task t2);

void seperate(vector<Task>& allTask_Task,vector<Task>& able_Task, vector<Task>& independent_Task);
//*******************************//
void show_Block(const Block& t);
/*********************************/

bool operator!=(const Task& a, const Task& b);

bool operator==(const vector<Task>& target, const vector<Task>& model);

int got_index(const vector<Task>&target,const vector<vector<Task>>&get_index);

node combination_dfs(vector<Task>able_Task,vector<vector<Task>>&record, vector<node>& Block_record);

vector<Block> get_best_combination(vector<Task>& all_Task);

vector<vector<vector<Block>>> get_everyday_source_Block( vector<Block>&allTask_Block);

vector<Block>get_today_Block(const vector<vector<Block>>& ddlday_Block,int day);

vector<slot> get_new_slot(vector<slot> cur_slot, int start, int end);

vector<slot> get_today_slot(const vector<Block>& fixed_Task_Block, vector<slot>& last_slot, int day, int startning, int ending);

double get_value(Block Block,double ddlwarrior, double nightworker);

void dfs(int Block_index,vector<slot>now_slot, const vector<Block>&today_Block,
         double value_now,double& max_value, vector<Block>&record_Block,
         vector<Block>&best_arrange, vector<slot>&last_slot, double ddlwarrior, double nightworker,int day,int start,int end);

bool time_arrange(vector<vector<Block>>&best_arrange,int start,int end,double ddlwarrior,double nightworker,vector<Block>Block_combination,vector<int>&wrong_answer);

bool arrange_running(AlltaskRecorder &allTask,PersonalSet &priority,TaskArranger &taskarrange,vector<int>&wrong_location);



extern TaskArranger taskarrange;
#endif // TASK_ARRANGER_H
