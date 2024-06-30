#ifndef ADD_NEW_H
#define ADD_NEW_H
#include "add_fixedddl.h"
#include "add_fixedtime.h"
#include <QDialog>

namespace Ui {
class Add_New;
}

class Add_New : public QDialog
{
    Q_OBJECT

public:
    explicit Add_New(QWidget *parent = nullptr);
    ~Add_New();
signals:
    void to_add_ddl();
    void to_add_time();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Add_New *ui;
};

#endif // ADD_NEW_H
