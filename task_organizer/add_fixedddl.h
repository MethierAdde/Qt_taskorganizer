#ifndef ADD_FIXEDDDL_H
#define ADD_FIXEDDDL_H

#include <QDialog>

namespace Ui {
class Add_Fixed;
}

class Add_Fixed : public QDialog
{
    Q_OBJECT

public:
    explicit Add_Fixed(QWidget *parent = nullptr);
    void ddl_change(QString temp_name,QString temp_note,bool same,int temp_hard,int temp_ddl_day,int temp_work_time);
    ~Add_Fixed();


signals:
    void to_add_refresh();



private slots:
    void on_buttonBox_accepted();



private:
    Ui::Add_Fixed *ui;
    friend class MainWindow;
};

#endif // ADD_FIXEDDDL_H
