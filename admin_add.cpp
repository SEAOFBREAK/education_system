#include "admin_add.h"
#include "ui_admin_add.h"
#include "item.h"
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>

admin_add::admin_add(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::admin_add)
{
    ui->setupUi(this);

    if(add_infos=="1"){
        ui->widget->setWindowTitle("添加学生信息");
        ui->widget->setToolTip("这是添加学生信息页面");

        ui->label->setText("学生信息添加");
        ui->label_1->setText("姓名：");
        ui->label_2->setText("学号：");
        ui->label_3->setText("年龄：");
        ui->label_4->setText("性别：");
        ui->label_5->setText("年级：");
        ui->label_6->setText("班级：");
        ui->label_7->setText("电话：");
        ui->label_8->setText("密码：");
    }else if (add_infos=="2") {
        ui->widget->setWindowTitle("添加教师信息");
        ui->widget->setToolTip("这是教师信息添加页面");

        ui->label->setText("教师信息添加");
        ui->label_1->setText("姓名：");
        ui->label_2->setText("ID：");
        ui->label_3->setText("年龄：");
        ui->label_4->setText("性别：");
        ui->label_5->setText("电话：");
        ui->label_6->setText("密码：");
        ui->label_7->setText("介绍：");
        ui->label_8->setText("成就：");
    }else if (add_infos=="3") {
        ui->widget->setWindowTitle("添加课程信息");
        ui->widget->setToolTip("这是学生信息添加页面");

        ui->label->setText("课程信息添加");
        ui->label_1->setText("课  程  名：");
        ui->label_2->setText("课  程  id：");
        ui->label_3->setText("授课教师id：");
        ui->label_4->setText("上课班级：");
        ui->label_5->setText("星  期  数：");
        ui->label_6->setText("节     数：");
        ui->label_7->hide();
        ui->lineEdit_7->hide();
        ui->label_8->hide();
        ui->lineEdit_8->hide();
    }else if (add_infos=="4") {
        ui->widget->setWindowTitle("添加管理员信息");
        ui->widget->setToolTip("这是管理员信息添加页面");

        ui->label->setText("管理员信息添加");
        ui->label_1->setText("姓名：");
        ui->label_2->setText("ID：");
        ui->label_3->setText("密码：");
        ui->label_4->hide();
        ui->lineEdit_4->hide();
        ui->label_5->hide();
        ui->lineEdit_5->hide();
        ui->label_6->hide();
        ui->lineEdit_6->hide();
        ui->label_7->hide();
        ui->lineEdit_7->hide();
        ui->label_8->hide();
        ui->lineEdit_8->hide();
    }
}

admin_add::~admin_add()
{
    delete ui;
}

void admin_add::on_pushButton_clicked()
{
    QSqlQuery query;
    QString sql;
    QStringList datalist;
    bool judge;

    if(ui->lineEdit_2->text().isEmpty()){
        QMessageBox::warning(this,"警告","id不能为空");
        return;
    }else{
        qDebug()<<"id:"<<ui->lineEdit_2->text();
    }

    if(add_infos=="1"){
        datalist<<ui->lineEdit_1->text();
        datalist<<ui->lineEdit_2->text();
        datalist<<ui->lineEdit_3->text();
        datalist<<ui->lineEdit_4->text();
        datalist<<ui->lineEdit_5->text();
        datalist<<ui->lineEdit_6->text();
        datalist<<ui->lineEdit_7->text();
        datalist<<ui->lineEdit_8->text();
        qDebug()<<"添加的学生信息："<<datalist;

        sql.append("INSERT INTO education_system.student VALUES('");
        sql.append(datalist.value(1));sql+="','";
        sql.append(datalist.value(0));sql+="','";
        sql.append(datalist.value(2));sql+="','";
        sql.append(datalist.value(3));sql+="','";
        sql.append(datalist.value(4));sql+="','";
        sql.append(datalist.value(5));sql+="','";
        sql.append(datalist.value(6));sql+="','";
        sql.append(datalist.value(7));
        //插入img为空
        sql+="','";sql+="')";
        qDebug()<<"添加学生信息sql："<<sql;

        judge=query.exec(sql);

    }else if (add_infos=="2") {
        datalist<<ui->lineEdit_1->text();
        datalist<<ui->lineEdit_2->text();
        datalist<<ui->lineEdit_3->text();
        datalist<<ui->lineEdit_4->text();
        datalist<<ui->lineEdit_5->text();
        datalist<<ui->lineEdit_6->text();
        datalist<<ui->lineEdit_7->text();
        datalist<<ui->lineEdit_8->text();
        qDebug()<<"添加的教师信息："<<datalist;

        sql.append("INSERT INTO education_system.teacher VALUES('");
        sql.append(datalist.value(1));sql+="','";
        sql.append(datalist.value(0));sql+="','";
        sql.append(datalist.value(2));sql+="','";
        sql.append(datalist.value(3));sql+="','";
        sql.append(datalist.value(4));sql+="','";
        sql.append(datalist.value(5));
        //插入img为空
        sql+="','";sql+="','";
        sql.append(datalist.value(6));sql+="','";
        sql.append(datalist.value(7));sql+="')";
        qDebug()<<"添加教师信息sql："<<sql;

        judge=query.exec(sql);

    }else if (add_infos=="3") {
        datalist<<ui->lineEdit_1->text();
        datalist<<ui->lineEdit_2->text();
        datalist<<ui->lineEdit_3->text();
        datalist<<ui->lineEdit_4->text();
        datalist<<ui->lineEdit_5->text();
        datalist<<ui->lineEdit_6->text();
        qDebug()<<"添加的课程信息："<<datalist;

        sql.append("INSERT INTO education_system.course VALUES('");
        sql.append(datalist.value(1));sql+="','";
        sql.append(datalist.value(0));sql+="','";
        sql.append(datalist.value(2));sql+="','";
        sql.append(datalist.value(3));sql+="','";
        sql.append(datalist.value(4));sql+="','";
        sql.append(datalist.value(5));sql+="')";
        qDebug()<<"添加课程信息sql："<<sql;

        judge=query.exec(sql);

    }else{
        datalist<<ui->lineEdit_1->text();
        datalist<<ui->lineEdit_2->text();
        datalist<<ui->lineEdit_3->text();
        qDebug()<<"添加的管理员信息："<<datalist;

        sql.append("INSERT INTO education_system.admin VALUES('");
        sql.append(datalist.value(1));sql+="','";
        sql.append(datalist.value(0));sql+="','";
        sql.append(datalist.value(2));sql+="')";
        qDebug()<<"添加管理员信息sql："<<sql;

        judge=query.exec(sql);

    }

    QMessageBox::StandardButton box;
    if(judge){
        box = QMessageBox::question(this, "提示", "添加成功，是否继续添加？", QMessageBox::Yes|QMessageBox::No);
        if(box==QMessageBox::No){
           this->close();
        }
    }else{
        QMessageBox::question(this, "提示", "添加失败，请检查添加信息！");
    }
}

void admin_add::on_pushButton_2_clicked()
{
    this->close();
}
