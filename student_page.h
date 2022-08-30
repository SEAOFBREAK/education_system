#ifndef STUDENT_PAGE_H
#define STUDENT_PAGE_H

#include <QTreeWidget>
#include <QWidget>
#include "singlepage_teacher.h"

namespace Ui {
class student_page;
}

class student_page : public QWidget
{
    Q_OBJECT

public:
    explicit student_page(QWidget *parent = nullptr);
    ~student_page();

    void treeWidgetClicked(QTreeWidgetItem *item);

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void refresh_userinformation();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

signals:
    void Exit_student();//新建一个信号槽
private:
    Ui::student_page *ui;
    singlepage_teacher *spt;
};

#endif // STUDENT_PAGE_H
