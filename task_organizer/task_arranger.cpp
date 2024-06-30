#include"task_arranger.h"

TaskArranger::TaskArranger()
{

}//初始化，把存档里的任务安排取出来
void TaskArranger::read()
{
    QString basePath = QCoreApplication::applicationDirPath();
    QFile file(basePath+"/record/taskarrange.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        for(int i=0;i<7;i++)
        {
            QString str;
            int id;
            in>>str>>id;
            int blocksum;in>>str>>blocksum;
            for(int j=0;j<blocksum;j++)
            {
                Block newblock;
                int tasknum;
                in>>str>>newblock.starttime>>str>>newblock.endtime>>str>>tasknum>>str>>newblock.ddlday;
                newblock.day=i;
                for(int k=0;k<tasknum;k++)
                {
                    int num;in>>num;
                    newblock.taskindex.push_back(num);
                }
                week[i].blocklist.push_back(newblock);
            }
        }
        qDebug()<<"Taskarrange read successful\n";
    }
    else
        qDebug()<<"Error read taskarrange\n";
}
void TaskArranger::print2recorder()
{
    QString basePath = QCoreApplication::applicationDirPath();
    QFile file(basePath+"/record/taskarrange.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        for(int i=0;i<7;i++)
        {
            week[i].print2recorder(out);
        }
        qDebug()<<"Taskarrange write successful\n";
    }
    else
        qDebug()<<"Error write taskarrange\n";
}//做存档

void TaskArranger::freshindex(vector<int> newindex)
{
    for(int i=0;i<7;i++)
    {
        for(auto j=week[i].blocklist.begin();j!=week[i].blocklist.end();j++)
        {
            for(int k=0;k<int(j->taskindex.size());k++)
            {
                j->taskindex[k]=newindex[j->taskindex[k]];
            }
        }
    }
}
void TaskArranger::print2recorder(vector<int> newindex)
{
    freshindex(newindex);
    print2recorder();
}

double j_value(const Task&t){

    return -pow(1.05,t.hard)*t.worktime;

}
double j_value(const Task t1,const Task t2){
    return -pow(1.05,t1.hard+t2.hard)*max(t1.worktime,t2.worktime);
}

void seperate(vector<Task>& allTask_Task,vector<Task>& able_Task, vector<Task>& independent_Task) {
    for (int i = 0; i <(int) allTask_Task.size(); i++) {
        if (allTask_Task[i].sametimeable == true) {
            able_Task.push_back(allTask_Task[i]);
        }
        else if(allTask_Task[i].sametimeable == false) independent_Task.push_back(allTask_Task[i]);
    }
}
void show_Block(const Block& t) {
    qDebug() <<"Block::label "<< t.label << " ";
    qDebug() << " Block::ddlday:" << t.ddlday << " Block::starttime:" << t.starttime << " Block::endtime:" << t.endtime;
    qDebug() << " Block::f_s:" << t.starttime << " Block::f_e" << t.endtime << " Block::f_d" << t.day << " Block::last" << t.worktime;
    qDebug() << '\n' << "Task::source: ";
    for (int j = 0; j < (int)t.taskindex.size(); j++) {
        qDebug() << " id:" << t.taskindex[j] << " ";
    }
    qDebug() << "--------------------------" << '\n';
}
bool operator!=(const Task& a, const Task& b) {
    //Task所有属性都相等
    if (a.ddlday != b.ddlday || a.day != b.day || a.endtime != b.endtime || a.starttime != b.starttime
        || a.hard != b.hard || a.id != b.id || a.label != b.label || a.worktime != b.worktime
        || a.name != b.name || a.sametimeable != b.sametimeable) return true;
    return false;
}
bool operator==(const vector<Task>& target, const vector<Task>& model) {
    if (target.size() != model.size()) return false;
    for (int i = 0; i <(int) target.size(); i++) {
        if (target[i] != model[i]) return false;
    }
    return true;
}
node combination_dfs(vector<Task>able_Task,vector<vector<Task>>&record, vector<node>& Block_record) {
    if (find(record.begin(), record.end(), able_Task) != record.end()) {
        auto it = find(record.begin(), record.end(), able_Task);
        return Block_record[it - record.begin()];
    }
    if (able_Task.size() == 0) {
        return node(vector<Block>(0), 0);
    }
    Task now_Task = *(able_Task.end() - 1);
    if (able_Task.size() == 1) {
        vector<Block> Block_now;
        Block_now.push_back(Block(now_Task));
        double hmax_value = j_value(now_Task);
        node final_out(Block_now, hmax_value);
        record.push_back(able_Task);
        Block_record.push_back(final_out);
        return final_out;
    }

    //op表示前些项的Task容器
    vector<Task> op(able_Task.begin(), able_Task.end()-1);
    vector<Block> Block_now;

    //
    //buzuhe
    Block_now = combination_dfs(op,record,Block_record).house;
    Block_now.push_back(Block(now_Task));
    double max_value = j_value(now_Task) + combination_dfs(op, record, Block_record).val;

    node final_out(Block_now, max_value);

    //组合
    for (int j = 0; j < (int)able_Task.size()-1; j++) {
        //状态
        //这里就没考虑两个fixed在同一时间的情况
        //目前结果是 fixed与ddlday可以混合组合，同时保证了不能fixed

        if (now_Task.label == 2 && able_Task[j].label == 2) continue;
        if(now_Task.label == 2&&able_Task[j].label == 1){
            if(now_Task.worktime<able_Task[j].worktime) continue;
            if(now_Task.ddlday>able_Task[j].ddlday) continue;
        }
        else if(now_Task.label == 1 && able_Task[j].label == 2){
            if(now_Task.worktime>able_Task[j].worktime) continue;
            if(now_Task.ddlday<able_Task[j].ddlday) continue;
        }
        vector<Task> op_copy(op);
        op_copy.erase(op_copy.begin() + j);//这里用到id与索引一致

        //index_now = got_index(op_copy, get_index);
        Block_now = combination_dfs(op_copy, record, Block_record).house;
        Block_now.push_back(Block(now_Task, able_Task[j]));

        //value
        double v_now = combination_dfs(op_copy, record, Block_record).val + j_value(now_Task, able_Task[j]);
        if (v_now > max_value) {
            final_out.house = Block_now;
            final_out.val = v_now;
            max_value = v_now;
        }
    }
    record.push_back(able_Task);
    Block_record.push_back(final_out);
    return final_out;
}
vector<Block> get_best_combination(vector<Task>& all_Task) {
    //将能组合的和不能组合的分开

    vector<Task>able_Task;
    vector<Task>independent_Task;
    seperate(all_Task, able_Task, independent_Task);

    vector<vector<Task>> record;
    vector<node> Block_record;
    vector<Block>final_out= combination_dfs(able_Task, record, Block_record).house;
    //加入indepent
    for (int i = 0; i <(int) independent_Task.size(); i++) final_out.push_back(Block(independent_Task[i]));
    return final_out;
}
vector<vector<vector<Block>>> get_everyday_source_Block( vector<Block>&allTask_Block) {
    vector<vector<vector<Block>>> outt;
    outt.resize(2);
    outt[0].resize(7);
    outt[1].resize(7);
    for (int day = 0; day <= 6; day++) {
        vector<Block> b;
        vector<Block> c;
        for (int i = 0; i < (int)allTask_Block.size(); i++) {
            if (allTask_Block[i].ddlday == day) {
                if (allTask_Block[i].label == 2) b.push_back(Block(allTask_Block[i]));
                else if (allTask_Block[i].label == 1) c.push_back(Block(allTask_Block[i]));
            }
        }
        outt[0][day]=b;
        outt[1][day] = c;
    }
    /*for (int i = 0; i < 7; i++) {
        for (int j = 0; j < outt[0][i].size(); j++) {
            show_Block(outt[0][i][j]);
        }
    }*/
    return outt;
}
vector<Block>get_today_Block(const vector<vector<Block>>& ddlday_Block,int day) {
    vector<Block>today_Block;
    for (int i = 0; i <(int) ddlday_Block[day].size(); i++) {
        if (ddlday_Block[day][i].ddlday != day) continue;
        else today_Block.push_back(ddlday_Block[day][i]);
    }
    return today_Block;
}

vector<slot> get_new_slot(vector<slot> cur_slot, int start, int end) {
    for (int i = 0; i < (int)cur_slot.size(); i++) {
        //事件的start和end一定在一个slot内
        if (cur_slot[i].begin < start && cur_slot[i].end >= end) {
            cur_slot[i].end = start - 1;
        }
        else if (cur_slot[i].begin >= start && cur_slot[i].begin <= end && cur_slot[i].end >= end) {
            cur_slot.erase(cur_slot.begin() + i);
            i--;
        }
    }
    return cur_slot;
}

vector<slot> get_today_slot(const vector<Block>& fixed_Task_Block, vector<slot>& last_slot, int day, int startning, int ending) {
    vector<slot>new_slot;
    for (int i = startning; i < ending; i++) {
        new_slot.push_back(slot(day, i, ending));
    }
    for (int i = 0; i < (int)fixed_Task_Block.size(); i++) {
        if (fixed_Task_Block[i].ddlday != day) continue;
        new_slot = get_new_slot(new_slot, fixed_Task_Block[i].starttime, fixed_Task_Block[i].endtime);
    }
    for (int i = 0; i < (int)new_slot.size(); i++) last_slot.push_back(new_slot[i]);
    return last_slot;
}


double get_value(Block Block,double ddlwarrior, double nightworker) {

    return -abs(Block.endtime / 48.0 - nightworker)
           + -abs((double(Block.day * 48 + Block.endtime)) / double((Block.ddlday + 1) * 48) - ddlwarrior)*2;//这里改了
}

void dfs(int Block_index,vector<slot>now_slot, const vector<Block>&today_Block,
         double value_now,double& max_value, vector<Block>&record_Block,//这个可以&吗
         vector<Block>&best_arrange, vector<slot>&last_slot, double ddlwarrior, double nightworker,int day,int start,int end) {
    if (Block_index == (int)today_Block.size()) {
        if (value_now > max_value) {
            best_arrange = record_Block;  max_value = value_now;

            //last_slot存储
            last_slot = now_slot;
        }
        return ;
    }
    for (int i = 0; i <(int) now_slot.size(); i++) {
        if (today_Block[Block_index].worktime + now_slot[i].begin > now_slot[i].end) continue;

        //填入起始终止时间\day
        Block op=Block(today_Block[Block_index], now_slot[i].begin, today_Block[Block_index].worktime + now_slot[i].begin,now_slot[i].day);//这里改了
        record_Block.push_back(op);

        //get_new_slot(now_slot, now_slot[i].begin, now_slot[i].end);

        dfs(Block_index + 1, get_new_slot(now_slot, now_slot[i].begin, now_slot[i].end), today_Block,
            value_now + get_value(op,ddlwarrior, nightworker),max_value,record_Block,
            best_arrange,last_slot,ddlwarrior,nightworker,day,start,end);

        record_Block.pop_back();
    }
    //如果存在有无法塞入的点，那么就会无法运行到开头的判断条件
    return;
}
bool time_arrange(vector<vector<Block>>&best_arrange,int start,int end,double ddlwarrior,double nightworker,vector<Block>Block_combination,vector<int>&wrong_answer) {

    //首先 得到的Block组中包含最优组合和只能独立完成两部分，其中二者都包括fixed
    //在这个函数中，想将含fixed的Block拎出来，再对不固定时间的Block进行排序

    //传入的是allTask_Task vector<Task>
    //
    //for (int i = 0; i < Block_combination.size(); i++) show_Block(Block_combination[i]);
    vector<vector<vector<Block>>> source_Block=get_everyday_source_Block(Block_combination);
    vector<vector<Block>>fixed_Task_Block = source_Block[0];
    //排序只需要排ddlday性质的Block
    vector<vector<Block>> all_ddlday_Block= source_Block[1];
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < (int)all_ddlday_Block[i].size(); j++) show_Block(all_ddlday_Block[i][j]);
    }
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < (int)fixed_Task_Block[i].size(); j++) show_Block(fixed_Task_Block[i][j]);
    }

    //day from 0 to 6
    bool outing=true;
    vector<slot>last_slot;
    for (int day = 0; day <= 6; day++) {
        //last_slot在函数中发生了改变
        vector<slot> today_slot(get_today_slot(fixed_Task_Block[day], last_slot, day, start, end));

        //先进入今天Block的是ddlday
        vector<Block>today_Block (get_today_Block(all_ddlday_Block,day));

        vector<Block> best_everyday_arrange;
        vector<Block>record;
        double max_value = -1000000;
        dfs(0,today_slot, today_Block,0, max_value,record, best_everyday_arrange, last_slot,ddlwarrior,nightworker,day,start, end);
        if (best_everyday_arrange.empty()&& !today_Block.empty()) {
            wrong_answer.push_back(day);
            outing=false;
            continue; //若非法，则这一天不会进入到安排中
        }
        //last slot已经在dfs中修改过
        qDebug() << "best_every:???????????????????????????????????" << '\n';
        qDebug()<< best_everyday_arrange.size();
        for (int i = 0; i <(int) best_everyday_arrange.size(); i++) {
            show_Block(best_everyday_arrange[i]);
        }
        //放入fixed_Block
        for (int i = 0; i < (int)fixed_Task_Block[day].size(); i++) {
            best_everyday_arrange.push_back(fixed_Task_Block[day][i]);
        }
        //xiugai
        //sort making from small to big
        //sort(best_everyday_arrange.begin(), best_everyday_arrange.end(), sort_judge());


        //**************修改
        for(int i=0;i<(int)best_everyday_arrange.size();i++){
            best_arrange[best_everyday_arrange[i].day].push_back(best_everyday_arrange[i]);
        }
        //best_arrange.push_back(best_everyday_arrange);
    }
    return outing;
    //best_arrange应是全局变量
}
//读入的是已经读好的allTask
//使用方式：
//首先定义出一个judge=true;
// vector<vector<Block>> Block_temp=arrange_running（.......,judge）；
//判断judge是否为false，进而提示是否需要重新输入，并终止进行
//调用类的成员函数init_day(Block_temp)


bool arrange_running(AlltaskRecorder& allTask,PersonalSet& priority,TaskArranger& taskarrange,vector<int>&wrong_location) {
    //首先得到vector<Task>类型的source

    vector<Task>allTask_Task;
    for (int i = 0; i < allTask.tasksum; i++)
        if (allTask(i)->state != 0) {
            qDebug() << allTask(i)->state << " ";
            allTask_Task.push_back(*allTask(i));
        }

    //进行组合
    vector<Block>Block_combination = get_best_combination(allTask_Task);

    //show
    for (int i = 0; i < (int)Block_combination.size(); i++) {
        show_Block(Block_combination[i]);
    }
    qDebug() << "******组合完成***************************" << '\n';
    //进行排列
    vector<vector<Block>>best_arrange(7);
    bool judge_in_law=time_arrange(best_arrange, priority.start, priority.end, priority.ddlwarrior, priority.nightworker, Block_combination,wrong_location);


    //修改
    for(int i=0;i<7;i++) sort(best_arrange[i].begin(),best_arrange[i].end(),sort_judge());


    if(judge_in_law){
        for(int i=1;i<=7;i++){
            taskarrange.week[i-1].blocklist=best_arrange[i-1];
        }
        taskarrange.print2recorder();
        //************************show*******************************//
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j <(int) best_arrange[i].size(); j++) {
                show_Block(best_arrange[i][j]);
            }
        }
        for(int i=0;i<allTask.tasksum;i++)
        {
            if(allTask(i)->state)
            { allTask.arrange(i);}
        }
    }
    if(judge_in_law==false){
        for(int i=0;i<(int)wrong_location.size();i++){
            qDebug()<<"在周"<<wrong_location[i]+1<<"任务过多";
        }
    }




    return judge_in_law;
}
//注意，得到的最终结果time可能大于48

TaskArranger taskarrange;
