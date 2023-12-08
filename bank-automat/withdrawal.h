#ifndef WITHDRAWAL_H
#define WITHDRAWAL_H

#include <QDialog>

namespace Ui {
class Withdrawal;
}

class Withdrawal : public QDialog
{
    Q_OBJECT

public:
    explicit Withdrawal(QWidget *parent = nullptr);
    ~Withdrawal();
    void showBalance(QString);

private slots:
    void on_btnSulje_clicked();

private:
    Ui::Withdrawal *ui;
};

#endif // WITHDRAWAL_H
