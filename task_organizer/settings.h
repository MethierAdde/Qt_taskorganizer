#ifndef SETTINGS_H
#define SETTINGS_H
#include<QMessageBox>
#include <QDialog>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    int begin_hour;
    int end_hour;
    int begin_minute;
    int end_minute;
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();


private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
