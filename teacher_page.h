#ifndef TEACHER_PAGE_H
#define TEACHER_PAGE_H

#include <QTreeWidget>
#include <QWidget>
#include "singlepage_teacher.h"

namespace Ui {
class teacher_page;
}

class teacher_page : public QWidget
{
    Q_OBJECT

public:
    explicit teacher_page(QWidget *parent = nullptr);
    void treeWidgetClicked(QTreeWidgetItem *item);
    ~teacher_page();

private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_2_clicked();
    void refresh_score();

    void on_pushButton_6_clicked();

    void refresh_userinformation();
    void on_pushButton_clicked();
signals:
    void Exit_teacher();//新建一个信号槽
private:
    Ui::teacher_page *ui;
    singlepage_teacher *spt;
};

#endif // TEACHER_PAGE_H
