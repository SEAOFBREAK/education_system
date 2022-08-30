#ifndef TEST_H
#define TEST_H

#include <QString>
#include <QStringList>
//#include <QMetaType>
#include<QDebug>

extern QString sqluser;
extern QString sqlpassword;
extern QString db_name;
extern QStringList user_infos;
extern QStringList course_infos;
extern QStringList teacher_infos;
extern QStringList student_infos;
extern QStringList score_infos;
extern QString position;
extern QStringList singal_infos;
extern QStringList admin_infos;
extern QString add_infos;
extern QStringList admin_score_gradeclass;
extern QStringList admin_score_course;

/*******************************修改后**********************************/
class student{
public:
    QString s_id,s_name,s_age,s_sex;
    QString s_grade,s_class,s_tel,s_password,s_img;

    student(QString a,QString b,QString c,QString d,QString e,QString f, QString g, QString h,QString i):
        s_id(a),s_name(b),s_age(c),s_sex(d),s_grade(e),s_class(f),s_tel(g),s_password(h),s_img(i){}

    void student_show(){
        qDebug()<<s_id<<" "<<s_name<<" "<<s_age<<" "<<s_sex<<" "
               <<s_grade<<" "<<s_class<<" "<<s_tel<<" "<<s_password<<" "<<s_img;
    }

    void set_student(QString a,QString b,QString c,QString d,QString e,QString f, QString g, QString h,QString i){
        s_id=a,s_name=b,s_age=c,s_sex=d;
        s_grade=e,s_class=f,s_tel=g,s_password=h,s_img=i;
    }

};

class teacher{
public:
    QString t_id,t_name,t_age,t_sex,t_tel;
    QString t_password,t_img,t_introduction,t_achievement;

    teacher(QString a,QString b,QString c,QString d,QString e,QString f, QString g, QString h,QString i):
        t_id(a),t_name(b),t_age(c),t_sex(d),t_tel(e),t_password(f),t_img(g),t_introduction(h),t_achievement(i){}

    void teacher_show(){
        qDebug()<<t_id<<" "<<t_name<<" "<<t_age<<" "<<t_sex<<" "
               <<t_tel<<" "<<t_password<<" "<<t_img<<" "<<t_introduction<<" "<<t_achievement;
    }

    void set_teacher(QString a,QString b,QString c,QString d,QString e,QString f, QString g, QString h,QString i){
        t_id=a,t_name=b,t_age=c,t_sex=d;
        t_tel=e,t_password=f,t_img=g,t_introduction=h,t_achievement=i;
    }

};

class admin{
public:
    QString a_id,a_name,a_password;

    admin(QString a,QString b,QString c):a_id(a),a_name(b),a_password(c){}

    void admin_show(){
           qDebug()<<a_id<<" "<<a_name<<" "<<a_password;
       }

       void set_admin(QString a,QString b,QString c){
           a_id=a,a_name=b,a_password=c;
       }

};

class score{
public:
    QString sc_id,sc_s_id,sc_t_id,sc_score;

    score(QString a,QString b,QString c,QString d):sc_id(a),sc_s_id(b),sc_t_id(c),sc_score(d){}

    void score_show(){
        qDebug()<<sc_id<<" "<<sc_s_id<<" "<<sc_t_id<<" "<<sc_score;
    }

};

class course{
public:
    QString c_id,c_name,c_teacher_id;
    QString c_class,c_time_day,c_time;

    course(QString a,QString b,QString c,QString d,QString e,QString f):
        c_id(a),c_name(b),c_teacher_id(c),c_class(d),c_time_day(e),c_time(f){}

    void course_show(){
        qDebug()<<c_id<<" "<<c_name<<" "<<c_teacher_id
               <<" "<<c_class<<" "<<c_time_day<<" "<<c_time;
    }
};

extern student login_user_student;
extern teacher login_user_teacher;
extern admin login_user_admin;
extern QVector<student> student_information;
extern QVector<teacher> teacher_information;
extern QVector<admin> admin_information;

extern QVector<score> score_information;
extern QVector<course> course_information;

#endif
