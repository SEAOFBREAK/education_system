#ifndef ADMIN_ADD_H
#define ADMIN_ADD_H

#include <QDialog>
#include <QWidget>

namespace Ui {
class admin_add;
}

class admin_add : public QDialog
{
    Q_OBJECT

public:
    explicit admin_add(QDialog *parent = nullptr);
    ~admin_add();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::admin_add *ui;
};

#endif // ADMIN_ADD_H
