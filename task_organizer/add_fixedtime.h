#ifndef ADD_FIXEDTIME_H
#define ADD_FIXEDTIME_H

#include <QDialog>

namespace Ui {
class Add_FixedTime;
}

class Add_FixedTime : public QDialog
{
    Q_OBJECT

public:
    explicit Add_FixedTime(QWidget *parent = nullptr);
    void fixed_time_change(QString temp_name,QString temp_note,bool same,int temp_hard,int starttime,int endtime,int ddlday);
    ~Add_FixedTime();

signals:
    void to_add_refresh();
public slots:

    void on_buttonBox_accepted();

private:
    Ui::Add_FixedTime *ui;
};

#endif // ADD_FIXEDTIME_H
