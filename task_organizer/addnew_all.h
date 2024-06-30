#ifndef ADDNEW_ALL_H
#define ADDNEW_ALL_H

#include <QDialog>

namespace Ui {
class Addnew_all;
}

class Addnew_all : public QDialog
{
    Q_OBJECT

public:
    explicit Addnew_all(QWidget *parent = nullptr);
    ~Addnew_all();

private:
    Ui::Addnew_all *ui;
};

#endif // ADDNEW_ALL_H
