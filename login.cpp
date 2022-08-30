#include "login.h"
#include "ui_login.h"
#include <QtDebug>
#include <qsqldatabase.h>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDir>
#include <QMessagebox>

#include "item.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    //测试////////////////////////////////////////////////////
    ui->lineEdit->setText("1810300215");
    ui->lineEdit_2->setText("123456");
    ui->rb_student->setChecked(true);
}

Login::~Login()
{
    delete ui;
}

void Login::on_user_login_clicked()
{
//    qDebug()<<"dzy";

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName(db_name);
    db.setUserName(sqluser);
    db.setPassword(sqlpassword);
    if(db.open()){
        qDebug()<<"数据库连接成功!";

    }

    get_position();
    get_user_information();
    get_course_information();
    get_teacher_information();
    get_score_information();
    if(ui->rb_student->isChecked() and !user_infos.isEmpty()){
        this->hide();
        sp=new student_page;
        sp->show();

        connect(sp,SIGNAL(Exit_student()),this,SLOT(show()));

    }else if(ui->rb_teacher->isChecked() and !user_infos.isEmpty()){
        get_student_information();
        this->hide();
        tp=new teacher_page;
        tp->show();

        connect(tp,SIGNAL(Exit_teacher()),this,SLOT(show()));

    }else if(ui->rb_admin->isChecked() and !user_infos.isEmpty()){
        get_student_information();
        get_admin_information();
        this->hide();
        ap=new admin_page;
        ap->show();

        connect(ap,SIGNAL(Exit_admin()),this,SLOT(show()));

    }


}

void Login::get_position()
{
    //获取当前路径
    QString file_path = QDir::currentPath();
    position=file_path;
    qDebug()<<"当前路径："<<position;
     qDebug()<<"---------------------------------------------------------------------------------------------------";
}

void Login::get_user_information()
{
    QSqlQuery query;
    QString sql;
    QStringList datalist;
    user_infos.clear();

    if(ui->rb_student->isChecked()){
        sql.append("SELECT * FROM education_system.student WHERE s_id='");
        sql.append(ui->lineEdit->text());
        sql.append("' AND s_password='");
        sql.append(ui->lineEdit_2->text());
        sql.append("'");

        qDebug()<<"查询登录学生sql:"<<sql;
        query.exec(sql);
        if(query.next()){
            /***************************************************修改前****************************************************/
            for(int i=0;i<query.record().count();i++){
                datalist<<query.value(i).toString();
            }
            user_infos=datalist;

            qDebug()<<"user_infos:"<<user_infos;

            /***************************************************修改后****************************************************/
            /*student date(query.value(0).toString(),query.value(1).toString(),query.value(2).toString(),query.value(3).toString(),
                         query.value(4).toString(),query.value(5).toString(),query.value(6).toString(),query.value(7).toString(),query.value(8).toString());

            login_user_student=date;

            qDebug()<<"login_user_student:";
            login_user_student.student_show();*/
            qDebug()<<"---------------------------------------------------------------------------------------------------";

        }else{
            qDebug()<<"不存在";
            QMessageBox messbox;
            messbox.setText("用户名或密码错误！");
            messbox.exec();
            }
    }else if (ui->rb_teacher->isChecked()) {
        sql.append("SELECT * FROM education_system.teacher WHERE t_id='");
        sql.append(ui->lineEdit->text());
        sql.append("' AND t_password='");
        sql.append(ui->lineEdit_2->text());
        sql.append("'");

        qDebug()<<"查询登录教师sql:"<<sql;
        query.exec(sql);
        if(query.next()){
            /***************************************************修改前****************************************************/
            for(int i=0;i<query.record().count();i++){
                datalist<<query.value(i).toString();
            }
            user_infos=datalist;
            qDebug()<<"user_infos:"<<user_infos;

            /***************************************************修改后****************************************************/
            /*teacher date(query.value(0).toString(),query.value(1).toString(),query.value(2).toString(),query.value(3).toString(),
                         query.value(4).toString(),query.value(5).toString(),query.value(6).toString(),query.value(7).toString(),query.value(8).toString());

            login_user_teacher=date;

            qDebug()<<"login_user_teacher:";
            login_user_teacher.teacher_show();*/
            qDebug()<<"---------------------------------------------------------------------------------------------------";

        }else{
            qDebug()<<"不存在";
            QMessageBox messbox;
            messbox.setText("用户名或密码错误！");
            messbox.exec();
            }
    }else if (ui->rb_admin->isChecked()) {
        sql.append("SELECT * FROM education_system.admin WHERE a_id='");
        sql.append(ui->lineEdit->text());
        sql.append("' AND a_password='");
        sql.append(ui->lineEdit_2->text());
        sql.append("'");

        qDebug()<<"查询登录管理员sql:"<<sql;
                query.exec(sql);
                if(query.next()){
                    /***************************************************修改前****************************************************/
                    for(int i=0;i<query.record().count();i++){
                        datalist<<query.value(i).toString();
                    }
                    user_infos=datalist;
                    qDebug()<<"user_infos:"<<user_infos;

                    /***************************************************修改后****************************************************/
                    /*admin date(query.value(0).toString(),query.value(1).toString(),query.value(2).toString());

                    login_user_admin=date;

                    qDebug()<<"login_user_admin:";
                    login_user_admin.admin_show();*/
                    qDebug()<<"---------------------------------------------------------------------------------------------------";

                }else{
                    qDebug()<<"不存在";
                    QMessageBox messbox;
                    messbox.setText("用户名或密码错误！");
                    messbox.exec();
                    }
    }
}

void Login::get_course_information()
{
    QSqlQuery query;
    QString sql;
    QStringList datalist;
    course_infos.clear();
    course_information.clear();     //重复登录需清空

    if(ui->rb_student->isChecked()){
        sql.append("SELECT * FROM education_system.course WHERE c_class=");
        sql.append(user_infos.value(5));
        qDebug()<<"查询学生课程sql："<<sql;

        query.exec(sql);
        while(query.next()){
            /***************************************************修改前****************************************************/
            datalist<<query.value(1).toString();
            datalist<<query.value(2).toString();
            datalist<<query.value(4).toString();
            datalist<<query.value(5).toString();

            /***************************************************修改后****************************************************/
            /*course date(query.value(0).toString(),query.value(1).toString(),query.value(2).toString(),
                        query.value(3).toString(),query.value(4).toString(),query.value(5).toString());
            course_information.append(date);*/
        }
    }else if (ui->rb_teacher->isChecked()) {
        sql.append("SELECT * FROM education_system.course WHERE c_teacher_id='");
        sql.append(user_infos.value(0));
        sql.append("'");
        qDebug()<<"查询教师课程sql："<<sql;

        query.exec(sql);
        while(query.next()){
            /***************************************************修改前****************************************************/
            datalist<<query.value(1).toString();
            datalist<<query.value(3).toString();
            datalist<<query.value(4).toString();
            datalist<<query.value(5).toString();

            /***************************************************修改后****************************************************/
            /*course date(query.value(0).toString(),query.value(1).toString(),query.value(2).toString(),
                        query.value(3).toString(),query.value(4).toString(),query.value(5).toString());
            course_information.append(date);*/
        }
    }else if (ui->rb_admin->isChecked()) {
        sql.append("SELECT * FROM education_system.course");
        qDebug()<<"查询所有课程sql："<<sql;

        query.exec(sql);
        while(query.next()){
            /***************************************************修改前****************************************************/
            for(int i=0;i<query.record().count();i++){
                datalist<<query.value(i).toString();
            }

            /***************************************************修改后****************************************************/
//            course date(query.value(0).toString(),query.value(1).toString(),query.value(2).toString(),
//                        query.value(3).toString(),query.value(4).toString(),query.value(5).toString());
//            course_information.append(date);
        }
    }

//    qDebug()<<"course_information：";
//    for(int i=0;i<course_information.size();i++){
//        course_information[i].course_show();
//    }
    course_infos=datalist;
    qDebug()<<"course_infos:"<<course_infos;
     qDebug()<<"---------------------------------------------------------------------------------------------------";
}

void Login::get_teacher_information()
{
    QSqlQuery query_tid;
    QSqlQuery query_tinfo;
    QSqlQuery query;
    QStringList datalist;
    QString sql;

    if(ui->rb_student->isChecked()){
        //跟据课程查询教师id
        sql.append("SELECT c_teacher_id,c_name FROM education_system.course group by c_teacher_id");

        query_tid.exec(sql);
        while (query_tid.next()) {
            sql.clear();
            sql.append("SELECT * FROM education_system.teacher WHERE t_id='");
            sql.append(query_tid.value(0).toString());
            sql.append("'");
    //        qDebug()<<"查询教师信息："<<sql;

            query_tinfo.exec(sql);
            query_tinfo.next();
            datalist<<query_tid.value(1).toString();
            for(int i=0;i<7;i++){
                datalist<<query_tinfo.value(i).toString();
            }
        }
    }else if(ui->rb_teacher->isChecked()){
        sql.append("SELECT * FROM education_system.teacher");
        query.exec(sql);

        while (query.next()){
            for(int i=0;i<7;i++){
                datalist<<query.value(i).toString();
            }
        }
    }else if(ui->rb_admin->isChecked()){
        sql.append("SELECT * FROM education_system.teacher");
        query.exec(sql);

        while (query.next()){
            for(int i=0;i<query.record().count();i++){
                datalist<<query.value(i).toString();
            }
        }
    }

    teacher_infos=datalist;
    qDebug()<<"teacher_infos："<<teacher_infos;
     qDebug()<<"---------------------------------------------------------------------------------------------------";
}

void Login::get_score_information()
{
    QSqlQuery query_scinfo;
    QSqlQuery query_name;
    QStringList datalist;
    QString sql;
    QSqlQuery query;
    QStringList datalist_gradeclass;
    QStringList datalist_course;

    if(ui->rb_student->isChecked()){

        sql.append("SELECT * FROM education_system.score WHERE sc_s_id='");
        sql.append(user_infos.value(0));
        sql.append("'");
        qDebug()<<"查询成绩sql："<<sql;

        query_scinfo.exec(sql);
        while (query_scinfo.next()) {
            datalist<<query_scinfo.value(2).toString();

            sql.clear();
            sql.append("SELECT c_name,t_name FROM education_system.course LEFT JOIN education_system.teacher ON c_teacher_id=t_id WHERE t_id='");
            sql.append(query_scinfo.value(2).toString());
            sql.append("'");
    //        qDebug()<<"查询课程名称:"<<sql;

            query_name.exec(sql);
            query_name.next();
            datalist<<query_name.value(0).toString();
            datalist<<query_name.value(1).toString();

            if(query_scinfo.value(3).isNull()){
                datalist<<"-1";
            }else{
                datalist<<query_scinfo.value(3).toString();
            }
        }

    }else if(ui->rb_teacher->isChecked()){
        sql.append("SELECT * FROM education_system.score WHERE sc_t_id=");
        sql.append(user_infos.value(0));

        query_scinfo.exec(sql);
        while (query_scinfo.next()) {
            datalist<<query_scinfo.value(1).toString();

            sql.clear();
            sql.append("SELECT s_name FROM education_system.student WHERE s_id='");
            sql.append(query_scinfo.value(1).toString());
            sql.append("'");

            query_name.exec(sql);
            query_name.next();
            datalist<<query_name.value(0).toString();

            if(query_scinfo.value(3).isNull()){
                datalist<<"-1";
            }else{
                datalist<<query_scinfo.value(3).toString();
            }
        }
    }else if(ui->rb_admin->isChecked()){
        sql.append("SELECT DISTINCT s_name,s_id,s_grade,s_class,c_name,sc_score "
                   "FROM education_system.student t1,education_system.score t2,education_system.course t3 "
                   "WHERE t1.s_id=t2.sc_s_id AND  t2.sc_t_id=t3.c_teacher_id");
        query.exec(sql);

        while (query.next()) {
            for (int i=0;i<query.record().count();i++) {
                if(query.value(i).isNull()){
                    datalist<<"-1";
                }else{
                    datalist<<query.value(i).toString();
                }
            }
        }

        //获取学生年级班级和学科
        sql.clear();
        sql.append("SELECT DISTINCT s_grade,s_class FROM education_system.student");
        query.exec(sql);
        while (query.next()) {
            if(query.value(0).toString().isNull() && query.value(1).toString().isNull()){
                continue;
            }
            datalist_gradeclass<<query.value(0).toString();
            datalist_gradeclass<<query.value(1).toString();
        }
        admin_score_gradeclass = datalist_gradeclass;
        qDebug()<<"admin_score_gradeclass:"<<admin_score_gradeclass;

        sql.clear();
        sql.append("SELECT DISTINCT c_name FROM education_system.course");
        query.exec(sql);
        while (query.next()) {
            datalist_course<<query.value(0).toString();
        }
        admin_score_course=datalist_course;
        qDebug()<<"admin_score_course:"<<admin_score_course;

    }

    score_infos=datalist;
    qDebug()<<"score_infos:"<<score_infos;
     qDebug()<<"---------------------------------------------------------------------------------------------------";
}

void Login::get_student_information()
{
    QSqlQuery query_cinfo;
    QSqlQuery query_sinfo;
    QSqlQuery query;
    QStringList datalist;
    QString sql;

    if(ui->rb_teacher->isChecked()){

        sql.append("SELECT c_class FROM education_system.course where c_teacher_id='");
        sql.append(user_infos.value(0));
        sql.append("' GROUP BY c_class");

        qDebug()<<"查询教师教课班级"<<sql;
        query_cinfo.exec(sql);
        while (query_cinfo.next()) {
            sql.clear();
            sql.append("SELECT * FROM education_system.student where s_class=");
            sql.append(query_cinfo.value(0).toString());

            query_sinfo.exec(sql);
            while (query_sinfo.next()) {
                for(int i=0;i<query_sinfo.record().count();i++){
                    datalist<<query_sinfo.value(i).toString();
                }
            }
        }

    }else if (ui->rb_admin->isChecked()) {

        sql.append("SELECT * FROM education_system.student");

        query.exec(sql);
        while (query.next()) {
            for(int i=0;i<query.record().count();i++){
                datalist<<query.value(i).toString();
            }
        }

    }


    student_infos=datalist;
    qDebug()<<"登录教师教课班级的学生信息："<<student_infos;
     qDebug()<<"---------------------------------------------------------------------------------------------------";
}

void Login::get_admin_information()
{
    QSqlQuery query;
    QStringList datalist;
    QString sql;

    sql.append("SELECT * FROM education_system.admin");
    query.exec(sql);

    while (query.next()) {
        for (int i=0;i<query.record().count();i++) {
            datalist<<query.value(i).toString();
        }
    }
    admin_infos=datalist;
    qDebug()<<"admin_infos:"<<admin_infos;
     qDebug()<<"---------------------------------------------------------------------------------------------------";
}

