#include "daily_settings.h"
#include "ui_daily_settings.h"

Daily_Settings::Daily_Settings(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Daily_Settings)
{
    ui->setupUi(this);
}

Daily_Settings::~Daily_Settings()
{
    delete ui;
}
