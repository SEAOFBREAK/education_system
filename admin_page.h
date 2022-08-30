#ifndef ADMIN_PAGE_H
#define ADMIN_PAGE_H

#include <QTreeWidget>
#include <QWidget>
#include "admin_add.h"
#include <QAxObject>

namespace Ui {
class admin_page;
}

class admin_page : public QWidget
{
    Q_OBJECT

public:
    explicit admin_page(QWidget *parent = nullptr);
    void treeWidgetClicked(QTreeWidgetItem *item);
    ~admin_page();

    bool IsNumber(QString &qstrSrc);
private slots:

    void on_student_add_clicked();

    void on_student_delete_clicked();

    void on_student_modify_clicked();

    void on_student_search_clicked();

    void refresh_student_table();

    void get_allstudent_information();


    void on_teacher_add_clicked();

    void on_teacher_delete_clicked();

    void on_teacher_modify_clicked();

    void on_teacher_search_clicked();

    void refresh_teacher_table();

    void get_allteacher_information();


    void on_course_add_clicked();

    void on_course_delete_clicked();

    void on_course_modify_clicked();

    void on_course_search_clicked();

    void refresh_course_table();

    void get_allcourse_information();


    void on_admin_add_clicked();

    void on_admin_delete_clicked();

    void on_admin_search_clicked();

    void on_admin_modify_clicked();

    void refresh_admin_table();

    void get_alladmin_information();

    void on_pushButton_clicked();

    void score_table_change();
    void get_allscore_information();
    void refresh_score_table();

    void on_pushButton_2_clicked();

signals:
    void Exit_admin();//新建一个信号槽


private:
    Ui::admin_page *ui;
    admin_add *aad;
};

#endif // ADMIN_PAGE_H
