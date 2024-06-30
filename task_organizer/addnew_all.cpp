#include "addnew_all.h"
#include "ui_addnew_all.h"

Addnew_all::Addnew_all(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Addnew_all)
{
    ui->setupUi(this);
}

Addnew_all::~Addnew_all()
{
    delete ui;
}
