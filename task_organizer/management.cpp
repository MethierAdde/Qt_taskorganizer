#include "management.h"
#include "ui_management.h"

Management::Management(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Management)
{   setWindowFlags(windowFlags() | Qt::Window);
    ui->setupUi(this);
    this->setWindowModality(Qt::ApplicationModal);
}

Management::~Management()
{
    delete ui;
}
