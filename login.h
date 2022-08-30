#ifndef LOGIN_H
#define LOGIN_H

#include <QSqlQuery>
#include <QWidget>
#include "student_page.h"
#include "teacher_page.h"
#include "admin_page.h"

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    void get_student_information();

private slots:
    void on_user_login_clicked();

    void get_position();
    void get_user_information();
    void get_course_information( );
    void get_teacher_information();
    void get_score_information();
    void get_admin_information();

private:
    Ui::Login *ui;
    student_page *sp;
    teacher_page *tp;
    admin_page *ap;
};

#endif // LOGIN_H
