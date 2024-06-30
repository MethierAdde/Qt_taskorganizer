#include "explaining.h"
#include "ui_explaining.h"

explaining::explaining(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::explaining)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::Window);
    this->setWindowModality(Qt::ApplicationModal);
}

explaining::~explaining()
{
    delete ui;
}
