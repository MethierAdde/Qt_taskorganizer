#ifndef EXPLAINING_H
#define EXPLAINING_H

#include <QWidget>


namespace Ui {
class explaining;
}

class explaining : public QWidget
{
    Q_OBJECT

public:
    explicit explaining(QWidget *parent = nullptr);
    ~explaining();

private:
    Ui::explaining *ui;
};

#endif // EXPLAINING_H
