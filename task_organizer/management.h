#ifndef MANAGEMENT_H
#define MANAGEMENT_H

#include <QDialog>

namespace Ui {
class Management;
}

class Management : public QDialog
{
    Q_OBJECT

public:
    explicit Management(QWidget *parent = nullptr);
    ~Management();

private:
    Ui::Management *ui;
};

#endif // MANAGEMENT_H
