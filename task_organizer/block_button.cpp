#include "block_button.h"
#include "mainwindow.h"
block_button::block_button(QWidget *parent)
    : QPushButton {parent}
{



}
block_button:: block_button(Block *p)
{
    My_block=p;//传递给它指针
    //点击基类才会进行子类的读取
    setText(Times[p->starttime]+'-'+Times[p->endtime]);
    //对于每一个这个 创建一个
    connect(this,&QPushButton::clicked,this,&block_button::myclicked);//进行联系
}
block_button::~block_button()
{

}
void block_button::myclicked()
{
    //清除前面的
    emit block_button_clicked(My_block);
    //根据block来添加里面的按钮
}
//对于每一个blockbutton 初始化的时候应当传入对应的blockbutton指针
