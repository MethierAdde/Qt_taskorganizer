#ifndef TASK_BUTTON_H
#define TASK_BUTTON_H

#include <QPushButton>
#include "task.h"
class task_button : public QPushButton
{
    Q_OBJECT
public:
    explicit task_button(QWidget *parent = nullptr);
    //将task包含的内容全部记录在内  这样初始化的时候便于整
    Task* my_task=nullptr;







    task_button(Task* thetask);
    ~task_button();
signals:
    void task_button_clicked(Task * mytask);

public slots:
    void my_task_button_clicked();
};

#endif // TASK_BUTTON_H
