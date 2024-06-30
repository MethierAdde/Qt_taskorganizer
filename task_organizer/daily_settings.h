#ifndef DAILY_SETTINGS_H
#define DAILY_SETTINGS_H

#include <QDialog>

namespace Ui {
class Daily_Settings;
}

class Daily_Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Daily_Settings(QWidget *parent = nullptr);
    ~Daily_Settings();

private:
    Ui::Daily_Settings *ui;
};

#endif // DAILY_SETTINGS_H
