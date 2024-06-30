#include "add_new.h"
#include "ui_add_new.h"

Add_New::Add_New(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Add_New)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::Window);
    //this->setWindowModality(Qt::ApplicationModal);
}

Add_New::~Add_New()
{
    delete ui;
}

void Add_New::on_pushButton_clicked()
{
    emit to_add_ddl();
    this->close();
}


void Add_New::on_pushButton_2_clicked()
{
   emit to_add_time();
   this->close();
}

