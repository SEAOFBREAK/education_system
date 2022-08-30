#include "admin_page.h"
#include "ui_admin_page.h"
#include "item.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessagebox>
#include <QSqlQuery>
#include <QSqlRecord>

admin_page::admin_page(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::admin_page)
{
    ui->setupUi(this);
    ui->allstudent_modify->hide();
    ui->allteacher_modify->hide();
    ui->allcourse_modify->hide();

    ui->label_3->setText(user_infos.value(1));

    ui->treeWidget->setColumnCount(1);
    QStringList l;

    //第一类///////////////////////////////////////////////////////
    l<<"成员管理";
    QTreeWidgetItem *parent0 = new QTreeWidgetItem(ui->treeWidget,l);
    ui->treeWidget->insertTopLevelItem(0,parent0);

    l.clear();
    l<<"学生管理";
    QTreeWidgetItem *child0_1 = new QTreeWidgetItem(parent0,l);
    l.clear();
    l<<"教师管理";
    QTreeWidgetItem *child0_2 = new QTreeWidgetItem(parent0,l);
    l.clear();
    l<<"管理员信息";
    QTreeWidgetItem *child0_3 = new QTreeWidgetItem(parent0,l);
    parent0->addChild(child0_1);
    parent0->addChild(child0_2);
    parent0->addChild(child0_3);

    //第二类///////////////////////////////////////////////////////
    l.clear();
    l<<"学科管理";
    QTreeWidgetItem *parent1 = new QTreeWidgetItem(ui->treeWidget,l);
    ui->treeWidget->insertTopLevelItem(1,parent1);

    l.clear();
    l<<"课程管理";
    QTreeWidgetItem *child1_1 = new QTreeWidgetItem(parent1,l);
    parent1->addChild(child1_1);

    l.clear();
    l<<"成绩管理";
    QTreeWidgetItem *child1_2 = new QTreeWidgetItem(parent1,l);
    parent1->addChild(child1_2);

    //全部展开
    ui->treeWidget->expandAll();

    //默认显示学生页面
    ui->stackedWidget->setCurrentIndex(0);

    /********************************************学生管理****************************************************/
    //设置表头列数和内容
    ui->student_table->setColumnCount(8);
    QStringList header_student;
    header_student<<tr("姓名")<<tr("学号")<<tr("年龄")<<tr("性别")<<tr("年级")<<tr("班级")<<tr("电话")<<tr("密码");
    ui->student_table->setHorizontalHeaderLabels(header_student);

    //设置表头字体加粗
    QFont font_student_table = ui->student_table->horizontalHeader()->font();
    font_student_table.setBold(true);
    ui->student_table->horizontalHeader()->setFont(font_student_table);

    //设置整行选中
    ui->student_table->setSelectionBehavior ( QAbstractItemView::SelectRows);
    ui->student_table->setSelectionMode(QAbstractItemView::SingleSelection);
    //不可编辑
//    ui->student_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //设置水平平分表格
    ui->student_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for(int i=0;i<student_infos.length()/9;i++){
        //插入行
        int row_count=ui->student_table->rowCount();
        ui->student_table->insertRow(row_count);

        ui->student_table->setItem(row_count,0,new QTableWidgetItem(student_infos.value(i*9+1)));
        ui->student_table->setItem(row_count,1,new QTableWidgetItem(student_infos.value(i*9)));
        ui->student_table->setItem(row_count,2,new QTableWidgetItem(student_infos.value(i*9+2)));
        ui->student_table->setItem(row_count,3,new QTableWidgetItem(student_infos.value(i*9+3)));
        ui->student_table->setItem(row_count,4,new QTableWidgetItem(student_infos.value(i*9+4)));
        ui->student_table->setItem(row_count,5,new QTableWidgetItem(student_infos.value(i*9+5)));
        ui->student_table->setItem(row_count,6,new QTableWidgetItem(student_infos.value(i*9+6)));
        ui->student_table->setItem(row_count,7,new QTableWidgetItem(student_infos.value(i*9+7)));
    }

    /********************************************教师管理****************************************************/
    //设置表头列数和内容
    ui->teacher_table->setColumnCount(8);
    QStringList header_teacher;
    header_teacher<<tr("姓名")<<tr("教师id")<<tr("年龄")<<tr("性别")<<tr("电话")<<tr("密码")<<tr("个人介绍")<<tr("个人成就");
    ui->teacher_table->setHorizontalHeaderLabels(header_teacher);

    //设置表头字体加粗
    QFont font_teacher_table = ui->teacher_table->horizontalHeader()->font();
    font_teacher_table.setBold(true);
    ui->teacher_table->horizontalHeader()->setFont(font_teacher_table);

    //设置整行选中
    ui->teacher_table->setSelectionBehavior ( QAbstractItemView::SelectRows);
    ui->teacher_table->setSelectionMode(QAbstractItemView::SingleSelection);
    //不可编辑
//    ui->teacher_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //设置水平平分表格
    ui->teacher_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

//    qDebug()<<"登录用户的教师信息长度:"<<teacher_infos.length();
    for(int i=0;i<teacher_infos.length()/9;i++){
        //插入行
        int row_count=ui->teacher_table->rowCount();
        ui->teacher_table->insertRow(row_count);

        ui->teacher_table->setItem(row_count,0,new QTableWidgetItem(teacher_infos.value(i*9+1)));
        ui->teacher_table->setItem(row_count,1,new QTableWidgetItem(teacher_infos.value(i*9)));
        ui->teacher_table->setItem(row_count,2,new QTableWidgetItem(teacher_infos.value(i*9+2)));
        ui->teacher_table->setItem(row_count,3,new QTableWidgetItem(teacher_infos.value(i*9+3)));
        ui->teacher_table->setItem(row_count,4,new QTableWidgetItem(teacher_infos.value(i*9+4)));
        ui->teacher_table->setItem(row_count,5,new QTableWidgetItem(teacher_infos.value(i*9+5)));
        ui->teacher_table->setItem(row_count,6,new QTableWidgetItem(teacher_infos.value(i*9+7)));
        ui->teacher_table->setItem(row_count,7,new QTableWidgetItem(teacher_infos.value(i*9+8)));
    }

    /********************************************管理员信息****************************************************/
    //设置表头列数和内容
    ui->admin_table->setColumnCount(3);
    QStringList header_admin;
    header_admin<<tr("管理员姓名")<<tr("管理员id")<<tr("密码");
    ui->admin_table->setHorizontalHeaderLabels(header_admin);

    //设置表头字体加粗
    QFont font_admin_table = ui->admin_table->horizontalHeader()->font();
    font_admin_table.setBold(true);
    ui->admin_table->horizontalHeader()->setFont(font_admin_table);

    //设置整行选中
    ui->admin_table->setSelectionBehavior ( QAbstractItemView::SelectRows);
    ui->admin_table->setSelectionMode(QAbstractItemView::SingleSelection);
    //不可编辑
//    ui->admin_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //设置水平平分表格
    ui->admin_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for(int i=0;i<admin_infos.length()/3;i++){
        //插入行
        int row_count=ui->admin_table->rowCount();
        ui->admin_table->insertRow(row_count);

        ui->admin_table->setItem(row_count,0,new QTableWidgetItem(admin_infos.value(i*3+1)));
        ui->admin_table->setItem(row_count,1,new QTableWidgetItem(admin_infos.value(i*3)));
        ui->admin_table->setItem(row_count,2,new QTableWidgetItem(admin_infos.value(i*3+2)));
    }

    /********************************************课程管理****************************************************/
    //设置表头列数和内容
    ui->course_table->setColumnCount(6);
    QStringList header_course;
    header_course<<tr("课程名")<<tr("课程id")<<tr("授课教师id")<<tr("所在班级")<<tr("星期数")<<tr("节数");
    ui->course_table->setHorizontalHeaderLabels(header_course);

    //设置表头字体加粗
    QFont font_course_table = ui->course_table->horizontalHeader()->font();
    font_course_table.setBold(true);
    ui->course_table->horizontalHeader()->setFont(font_course_table);

    //设置整行选中
    ui->course_table->setSelectionBehavior ( QAbstractItemView::SelectRows);
    ui->course_table->setSelectionMode(QAbstractItemView::SingleSelection);
    //不可编辑
//    ui->course_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //设置水平平分表格
    ui->course_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for(int i=0;i<course_infos.length()/6;i++){
        //插入行
        int row_count=ui->course_table->rowCount();
        ui->course_table->insertRow(row_count);

        ui->course_table->setItem(row_count,0,new QTableWidgetItem(course_infos.value(i*6+1)));
        ui->course_table->setItem(row_count,1,new QTableWidgetItem(course_infos.value(i*6)));
        ui->course_table->setItem(row_count,2,new QTableWidgetItem(course_infos.value(i*6+2)));
        ui->course_table->setItem(row_count,3,new QTableWidgetItem(course_infos.value(i*6+3)));
        ui->course_table->setItem(row_count,4,new QTableWidgetItem(course_infos.value(i*6+4)));
        ui->course_table->setItem(row_count,5,new QTableWidgetItem(course_infos.value(i*6+5)));
    }


    /********************************************成绩管理****************************************************/
    //设置下拉按钮
    QString admin_gradeclass;
    ui->cb_grade_class->addItem("全部");
    ui->cb_course->addItem("全部");
    for (int i=0;i<admin_score_gradeclass.length()/2;i++) {
        admin_gradeclass.clear();
        admin_gradeclass.append(admin_score_gradeclass.value(i*2));
        admin_gradeclass.append("级");
        admin_gradeclass.append(admin_score_gradeclass.value(i*2+1));
        admin_gradeclass.append("班");
        ui->cb_grade_class->addItem(admin_gradeclass);
    }
    for (int i=0;i<admin_score_course.length();i++) {
        ui->cb_course->addItem(admin_score_course.value(i));
    }

    //设置表头列数和内容
    ui->score_table->setColumnCount(6);
    QStringList header_score;
    header_score<<tr("姓名")<<tr("学号")<<tr("年级")<<tr("班级")<<tr("学科")<<tr("成绩");
    ui->score_table->setHorizontalHeaderLabels(header_score);

    //设置表头字体加粗
    QFont font_score_table = ui->score_table->horizontalHeader()->font();
    font_score_table.setBold(true);
    ui->score_table->horizontalHeader()->setFont(font_score_table);

    //设置整行选中
    ui->score_table->setSelectionBehavior ( QAbstractItemView::SelectRows);
    ui->score_table->setSelectionMode(QAbstractItemView::SingleSelection);
    //不可编辑
//    ui->student_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //设置水平平分表格
    ui->score_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for(int i=0;i<score_infos.length()/6;i++){
        //插入行
        int row_count=ui->score_table->rowCount();
        ui->score_table->insertRow(row_count);

        ui->score_table->setItem(row_count,0,new QTableWidgetItem(score_infos.value(i*6)));
        ui->score_table->setItem(row_count,1,new QTableWidgetItem(score_infos.value(i*6+1)));
        ui->score_table->setItem(row_count,2,new QTableWidgetItem(score_infos.value(i*6+2)));
        ui->score_table->setItem(row_count,3,new QTableWidgetItem(score_infos.value(i*6+3)));
        ui->score_table->setItem(row_count,4,new QTableWidgetItem(score_infos.value(i*6+4)));
        if(score_infos.value(i*6+5)=="-1"){
            ui->score_table->setItem(row_count,5,new QTableWidgetItem("成绩暂未公布"));
        }else{
            ui->score_table->setItem(row_count,5,new QTableWidgetItem(score_infos.value(i*6+5)));
        }
    }



    /****************************************************************************************************/
    //绑定点击事件
    connect(ui->treeWidget,&QTreeWidget::itemClicked,this,&admin_page::treeWidgetClicked);
    connect(ui->cb_grade_class,SIGNAL(currentIndexChanged(QString)),this,SLOT(score_table_change()));
    connect(ui->cb_course,SIGNAL(currentIndexChanged(QString)),this,SLOT(score_table_change()));
}

void admin_page::treeWidgetClicked(QTreeWidgetItem *item)
{
    if(item->text(0)=="学生管理"){
        qDebug()<<"学生管理";
        ui->stackedWidget->setCurrentIndex(0);

    }else if (item->text(0)=="教师管理") {
        qDebug()<<"教师管理";
        ui->stackedWidget->setCurrentIndex(1);

    }else if (item->text(0)=="课程管理") {
        qDebug()<<"课程管理";
        ui->stackedWidget->setCurrentIndex(2);

    }else if (item->text(0)=="管理员信息") {
        qDebug()<<"管理员信息";
        ui->stackedWidget->setCurrentIndex(3);

    }else if (item->text(0)=="成绩管理") {
        qDebug()<<"成绩管理";
        ui->stackedWidget->setCurrentIndex(4);

    }
}

admin_page::~admin_page()
{
    delete ui;
}

//学生管理点击事件///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void admin_page::on_student_add_clicked()
{
    add_infos="1";

    aad=new admin_add();
    aad->exec();

    get_allstudent_information();
    refresh_student_table();
}

void admin_page::on_student_delete_clicked()
{
    QSqlQuery query;
    QString sql;
    QStringList datalist;
    QList<QTableWidgetItem*> items = ui->student_table->selectedItems();

    if(!items.empty()){
        //进行确认
        QMessageBox::StandardButton box;
        box = QMessageBox::question(this, "提示", "是否确认删除该学生？", QMessageBox::Yes|QMessageBox::No);
        if(box==QMessageBox::No){
           return;
        }

        qDebug()<<"选中学生的学号"<<items.at(1)->text();

        sql.append("DELETE FROM education_system.student WHERE s_id='");
        sql.append(items.at(1)->text());
        sql.append("'");

        qDebug()<<"删除学生SQL："<<sql;
        query.exec(sql);

        get_allstudent_information();
         refresh_student_table();

    }else{
         QMessageBox::warning(this,"警告","请先选择一行再进行删除");
    }
}

void admin_page::on_student_modify_clicked()
{
    QSqlQuery query;
    QString sql;
    QStringList datalist;
    QList<QTableWidgetItem*> items = ui->student_table->selectedItems();
    QList<QTableWidgetSelectionRange> ranges = ui->student_table->selectedRanges();

    if(!items.empty()){

        //行数
        int row=ranges.at(0).topRow();
        qDebug()<<"行数："<<row;

        int count = items.count();
        for(int i=0;i<count;i++){
            QTableWidgetItem *item=items.at(i);
            datalist<<item->text();
        }
        qDebug()<<"更改后的学生信息："<<datalist;

        //进行确认
        QMessageBox::StandardButton box;
        QString text;

        text.append("是否确认将学生:\n");
        text.append(student_infos.value(row*9+1));text+=" ";
        text.append(student_infos.value(row*9));text+=" ";
        text.append(student_infos.value(row*9+2));text+=" ";
        text.append(student_infos.value(row*9+3));text+=" ";
        text.append(student_infos.value(row*9+4));text+=" ";
        text.append(student_infos.value(row*9+5));text+=" ";
        text.append(student_infos.value(row*9+6));text+=" ";
        text.append(student_infos.value(row*9+7));
        text.append("\n的信息更改为:\n ");
        text.append(datalist.value(0));text+=" ";
        text.append(datalist.value(1));text+=" ";
        text.append(datalist.value(2));text+=" ";
        text.append(datalist.value(3));text+=" ";
        text.append(datalist.value(4));text+=" ";
        text.append(datalist.value(5));text+=" ";
        text.append(datalist.value(6));text+=" ";
        text.append(datalist.value(7));

        box = QMessageBox::question(this, "提示", text, QMessageBox::Yes|QMessageBox::No);
        if(box==QMessageBox::No){
            refresh_student_table();
           return;
        }

        //判断主键是否更改
        if(student_infos.value(row*9)!=datalist.value(1)){
            box = QMessageBox::warning(this, "警告", "是否确认更改学号(学号不建议更改)", QMessageBox::Yes|QMessageBox::No);
            if(box==QMessageBox::No){
                 refresh_student_table();
                  return;
             }
        }

        //数据库操作
        sql.append("UPDATE education_system.student SET s_id='");
        sql.append(datalist.value(1));sql+="'";
        sql.append(",s_name='");sql.append(datalist.value(0));sql+="'";
        sql.append(",s_age='"); sql.append(datalist.value(2));sql+="'";
        sql.append(",s_sex='");sql.append(datalist.value(3));sql+="'";
        sql.append(",s_grade='");sql.append(datalist.value(4));sql+="'";
        sql.append(",s_class='");sql.append(datalist.value(5));sql+="'";
        sql.append(",s_tel='");sql.append(datalist.value(6));sql+="'";
        sql.append(",s_password='");sql.append(datalist.value(7));sql+="'";
        sql.append(" WHERE s_id='");sql.append(student_infos.value(row*9));sql+="'";

        qDebug()<<"sql:"<<sql;
        query.exec(sql);

    }else{
        QMessageBox::warning(this,"警告","请先选择一行再进行修改");
    }

}


void admin_page::on_student_search_clicked()
{
    QSqlQuery query;
    QString sql;
    QStringList datalist;

    if(ui->student_le->text().isNull()){
        get_allstudent_information();
        refresh_student_table();    //刷新

    }else{

        QString data;
        data=ui->student_le->text();
        if(IsNumber(data)){
            //纯数字，查询学号
            sql.append("SELECT * FROM education_system.student WHERE s_id like '%");
            sql.append(ui->student_le->text());
            sql.append("%'");
            qDebug()<<"学生搜索sql："<<sql;

            query.exec(sql);
            while (query.next()) {
                for (int i=0;i<query.record().count();i++) {
                    datalist<<query.value(i).toString();
                }
            }
            student_infos.clear();
            student_infos=datalist;
            refresh_student_table();

        }else{
            //不是纯数字，查询姓名
            sql.append("SELECT * FROM education_system.student WHERE s_name like '%");
            sql.append(ui->student_le->text());
            sql.append("%'");
            qDebug()<<"学生搜索sql："<<sql;

            query.exec(sql);
            while (query.next()) {
                for (int i=0;i<query.record().count();i++) {
                    datalist<<query.value(i).toString();
                }
            }
            student_infos.clear();
            student_infos=datalist;
            refresh_student_table();

        }
    }
}

void admin_page::refresh_student_table()
{
    //清除所有行
    qDebug()<<"清除前行数："<<ui->student_table->rowCount();
    for(int i = ui->student_table->rowCount() - 1;i >= 0; i--)
    {
        ui->student_table->removeRow(i);
    }
    qDebug()<<"清除后行数："<<ui->student_table->rowCount();

    for(int i=0;i<student_infos.length()/9;i++){
        //插入行
        int row_count=ui->student_table->rowCount();
        ui->student_table->insertRow(row_count);

        ui->student_table->setItem(row_count,0,new QTableWidgetItem(student_infos.value(i*9+1)));
        ui->student_table->setItem(row_count,1,new QTableWidgetItem(student_infos.value(i*9)));
        ui->student_table->setItem(row_count,2,new QTableWidgetItem(student_infos.value(i*9+2)));
        ui->student_table->setItem(row_count,3,new QTableWidgetItem(student_infos.value(i*9+3)));
        ui->student_table->setItem(row_count,4,new QTableWidgetItem(student_infos.value(i*9+4)));
        ui->student_table->setItem(row_count,5,new QTableWidgetItem(student_infos.value(i*9+5)));
        ui->student_table->setItem(row_count,6,new QTableWidgetItem(student_infos.value(i*9+6)));
        ui->student_table->setItem(row_count,7,new QTableWidgetItem(student_infos.value(i*9+7)));
    }

}

void admin_page::get_allstudent_information()
{
    QString sql;
    QSqlQuery query;
    QStringList datalist;

    sql.append("SELECT * FROM education_system.student");
    query.exec(sql);

    while (query.next()) {
        for (int i=0;i<query.record().count();i++) {
            datalist<<query.value(i).toString();
        }
    }
    student_infos.clear();
    student_infos=datalist;


}

//教师管理点击事件///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void admin_page::on_teacher_add_clicked()
{
    add_infos="2";

    aad=new admin_add;
    aad->exec();

    get_allteacher_information();
    refresh_teacher_table();
}

void admin_page::on_teacher_delete_clicked()
{
    QSqlQuery query;
    QString sql;
    QStringList datalist;
    QList<QTableWidgetItem*> items = ui->teacher_table->selectedItems();

    if(!items.empty()){
        //进行确认
        QMessageBox::StandardButton box;
        box = QMessageBox::question(this, "提示", "是否确认删除该教师？", QMessageBox::Yes|QMessageBox::No);
        if(box==QMessageBox::No){
           return;
        }

        qDebug()<<"选中教师的id"<<items.at(1)->text();

        sql.append("DELETE FROM education_system.teacher WHERE t_id='");
        sql.append(items.at(1)->text());
        sql.append("'");

        qDebug()<<"删除教师SQL："<<sql;
        query.exec(sql);

        get_allteacher_information();
         refresh_teacher_table();

    }else{
         QMessageBox::warning(this,"警告","请先选择一行再进行删除");
    }
}

void admin_page::on_teacher_modify_clicked()
{
    QSqlQuery query;
    QString sql;
    QStringList datalist;
    QList<QTableWidgetItem*> items = ui->teacher_table->selectedItems();
    QList<QTableWidgetSelectionRange> ranges = ui->teacher_table->selectedRanges();

    if(!items.empty()){

        //行数
        int row=ranges.at(0).topRow();
        qDebug()<<"行数："<<row;

        int count = items.count();
        for(int i=0;i<count;i++){
            QTableWidgetItem *item=items.at(i);
            datalist<<item->text();
        }
        qDebug()<<"更改后的教师信息："<<datalist;

        //进行确认
        QMessageBox::StandardButton box;
        QString text;

        text.append("是否确认将教师:\n");
        text.append(teacher_infos.value(row*9+1));text+=" ";
        text.append(teacher_infos.value(row*9));text+=" ";
        text.append(teacher_infos.value(row*9+2));text+=" ";
        text.append(teacher_infos.value(row*9+3));text+=" ";
        text.append(teacher_infos.value(row*9+4));text+=" ";
        text.append(teacher_infos.value(row*9+5));text+=" ";
        text.append(teacher_infos.value(row*9+7));text+=" ";
        text.append(teacher_infos.value(row*9+8));
        text.append("\n的信息更改为:\n ");
        text.append(datalist.value(0));text+=" ";
        text.append(datalist.value(1));text+=" ";
        text.append(datalist.value(2));text+=" ";
        text.append(datalist.value(3));text+=" ";
        text.append(datalist.value(4));text+=" ";
        text.append(datalist.value(5));text+=" ";
        text.append(datalist.value(6));text+=" ";
        text.append(datalist.value(7));

        box = QMessageBox::question(this, "提示", text, QMessageBox::Yes|QMessageBox::No);
        if(box==QMessageBox::No){
            refresh_teacher_table();
           return;
        }

        //判断主键是否更改
        if(teacher_infos.value(row*9)!=datalist.value(1)){
            box = QMessageBox::warning(this, "警告", "是否确认更改教师id(id不建议更改)", QMessageBox::Yes|QMessageBox::No);
            if(box==QMessageBox::No){
                  refresh_teacher_table();
                  return;
             }
        }

        //数据库操作
        sql.append("UPDATE education_system.teacher SET t_id='");
        sql.append(datalist.value(1));sql+="'";
        sql.append(",t_name='");sql.append(datalist.value(0));sql+="'";
        sql.append(",t_age='"); sql.append(datalist.value(2));sql+="'";
        sql.append(",t_sex='");sql.append(datalist.value(3));sql+="'";
        sql.append(",t_tel='");sql.append(datalist.value(4));sql+="'";
        sql.append(",t_password='");sql.append(datalist.value(5));sql+="'";
        sql.append(",t_introducation='");sql.append(datalist.value(6));sql+="'";
        sql.append(",t_achiev='");sql.append(datalist.value(7));sql+="'";
        sql.append(" WHERE t_id='");sql.append(teacher_infos.value(row*9));sql+="'";

        qDebug()<<"sql:"<<sql;
        query.exec(sql);

    }else{
        QMessageBox::warning(this,"警告","请先选择一行再进行修改");
    }
}

void admin_page::on_teacher_search_clicked()
{
    QSqlQuery query;
    QString sql;
    QStringList datalist;

    if(ui->teacher_le->text().isNull()){
        get_allteacher_information();
        refresh_teacher_table();    //刷新

    }else{

        QString data;
        data=ui->teacher_le->text();
        if(IsNumber(data)){
            //纯数字，查询id
            sql.append("SELECT * FROM education_system.teacher WHERE t_id like '%");
            sql.append(ui->teacher_le->text());
            sql.append("%'");
            qDebug()<<"教师搜索sql："<<sql;

            query.exec(sql);
            while (query.next()) {
                for (int i=0;i<query.record().count();i++) {
                    datalist<<query.value(i).toString();
                }
            }
            teacher_infos.clear();
            teacher_infos=datalist;
            refresh_teacher_table();

        }else{
            //不是纯数字，查询姓名
            sql.append("SELECT * FROM education_system.teacher WHERE t_name like '%");
            sql.append(ui->teacher_le->text());
            sql.append("%'");
            qDebug()<<"教师搜索sql："<<sql;

            query.exec(sql);
            while (query.next()) {
                for (int i=0;i<query.record().count();i++) {
                    datalist<<query.value(i).toString();
                }
            }
            teacher_infos.clear();
            teacher_infos=datalist;
            refresh_teacher_table();

        }
    }
}

void admin_page::refresh_teacher_table()
{
    //清除所有行
    qDebug()<<"清除前行数："<<ui->teacher_table->rowCount();
    for(int i = ui->teacher_table->rowCount() - 1;i >= 0; i--)
    {
        ui->teacher_table->removeRow(i);
    }
    qDebug()<<"清除后行数："<<ui->teacher_table->rowCount();

    for(int i=0;i<teacher_infos.length()/9;i++){
        //插入行
        int row_count=ui->teacher_table->rowCount();
        ui->teacher_table->insertRow(row_count);

        ui->teacher_table->setItem(row_count,0,new QTableWidgetItem(teacher_infos.value(i*9+1)));
        ui->teacher_table->setItem(row_count,1,new QTableWidgetItem(teacher_infos.value(i*9)));
        ui->teacher_table->setItem(row_count,2,new QTableWidgetItem(teacher_infos.value(i*9+2)));
        ui->teacher_table->setItem(row_count,3,new QTableWidgetItem(teacher_infos.value(i*9+3)));
        ui->teacher_table->setItem(row_count,4,new QTableWidgetItem(teacher_infos.value(i*9+4)));
        ui->teacher_table->setItem(row_count,5,new QTableWidgetItem(teacher_infos.value(i*9+5)));
        ui->teacher_table->setItem(row_count,6,new QTableWidgetItem(teacher_infos.value(i*9+7)));
        ui->teacher_table->setItem(row_count,7,new QTableWidgetItem(teacher_infos.value(i*9+8)));
    }
}

void admin_page::get_allteacher_information()
{
    QString sql;
    QSqlQuery query;
    QStringList datalist;

    sql.append("SELECT * FROM education_system.teacher");
    query.exec(sql);

    while (query.next()) {
        for (int i=0;i<query.record().count();i++) {
            datalist<<query.value(i).toString();
        }
    }
    teacher_infos.clear();
    teacher_infos=datalist;
}

//课程管理点击事件///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void admin_page::on_course_add_clicked()
{
    add_infos="3";

    aad=new admin_add;
    aad->exec();

    get_allcourse_information();
    refresh_course_table();
}

void admin_page::on_course_delete_clicked()
{
    QSqlQuery query;
    QString sql;
    QStringList datalist;
    QList<QTableWidgetItem*> items = ui->course_table->selectedItems();

    if(!items.empty()){
        //进行确认
        QMessageBox::StandardButton box;
        box = QMessageBox::question(this, "提示", "是否确认删除该条课程信息？", QMessageBox::Yes|QMessageBox::No);
        if(box==QMessageBox::No){
           return;
        }

        qDebug()<<"选中课程的id"<<items.at(1)->text();

        sql.append("DELETE FROM education_system.course WHERE c_id='");
        sql.append(items.at(1)->text());
        sql.append("'");

        qDebug()<<"删除课程SQL："<<sql;
        query.exec(sql);

        get_allcourse_information();
         refresh_course_table();

    }else{
         QMessageBox::warning(this,"警告","请先选择一行再进行删除");
    }
}

void admin_page::on_course_modify_clicked()
{
    QSqlQuery query;
    QString sql;
    QStringList datalist;
    QList<QTableWidgetItem*> items = ui->course_table->selectedItems();
    QList<QTableWidgetSelectionRange> ranges = ui->course_table->selectedRanges();

    if(!items.empty()){

        //行数
        int row=ranges.at(0).topRow();
        qDebug()<<"行数："<<row;

        int count = items.count();
        for(int i=0;i<count;i++){
            QTableWidgetItem *item=items.at(i);
            datalist<<item->text();
        }
        qDebug()<<"更改后的课程信息："<<datalist;

        //进行确认
        QMessageBox::StandardButton box;
        QString text;

        text.append("是否确认将课程:\n");
        text.append(course_infos.value(row*6+1));text+=" ";
        text.append(course_infos.value(row*6));text+=" ";
        text.append(course_infos.value(row*6+2));text+=" ";
        text.append(course_infos.value(row*6+3));text+=" ";
        text.append(course_infos.value(row*6+4));text+=" ";
        text.append(course_infos.value(row*6+5));
        text.append("\n的信息更改为:\n ");
        text.append(datalist.value(0));text+=" ";
        text.append(datalist.value(1));text+=" ";
        text.append(datalist.value(2));text+=" ";
        text.append(datalist.value(3));text+=" ";
        text.append(datalist.value(4));text+=" ";
        text.append(datalist.value(5));

        box = QMessageBox::question(this, "提示", text, QMessageBox::Yes|QMessageBox::No);
        if(box==QMessageBox::No){
            refresh_course_table();
           return;
        }

        //判断主键是否更改
        if(course_infos.value(row*6)!=datalist.value(1)){
            box = QMessageBox::warning(this, "警告", "是否确认更改课程id(id不建议更改)", QMessageBox::Yes|QMessageBox::No);
            if(box==QMessageBox::No){
                  refresh_course_table();
                  return;
             }
        }

        //数据库操作
        sql.append("UPDATE education_system.course SET c_id='");
        sql.append(datalist.value(1));sql+="'";
        sql.append(",c_name='");sql.append(datalist.value(0));sql+="'";
        sql.append(",c_teacher_id='"); sql.append(datalist.value(2));sql+="'";
        sql.append(",c_class='");sql.append(datalist.value(3));sql+="'";
        sql.append(",c_time_day='");sql.append(datalist.value(4));sql+="'";
        sql.append(",c_time='");sql.append(datalist.value(5));sql+="'";
        sql.append(" WHERE c_id='");sql.append(course_infos.value(row*6));sql+="'";

        qDebug()<<"sql:"<<sql;
        query.exec(sql);

    }else{
        QMessageBox::warning(this,"警告","请先选择一行再进行修改");
    }
}

void admin_page::on_course_search_clicked()
{
    QSqlQuery query;
    QString sql;
    QStringList datalist;

    if(ui->course_le->text().isNull()){
        get_allcourse_information();
        refresh_course_table();    //刷新

    }else{

        QString data;
        data=ui->course_le->text();
        if(IsNumber(data)){
            //纯数字，查询id
            sql.append("SELECT * FROM education_system.course WHERE c_id like '%");
            sql.append(ui->course_le->text());
            sql.append("%'");
            qDebug()<<"课程搜索sql："<<sql;

            query.exec(sql);
            while (query.next()) {
                for (int i=0;i<query.record().count();i++) {
                    datalist<<query.value(i).toString();
                }
            }
            course_infos.clear();
            course_infos=datalist;
            refresh_course_table();

        }else{
            //不是纯数字，查询姓名
            sql.append("SELECT * FROM education_system.course WHERE c_name like '%");
            sql.append(ui->course_le->text());
            sql.append("%'");
            qDebug()<<"课程搜索sql："<<sql;

            query.exec(sql);
            while (query.next()) {
                for (int i=0;i<query.record().count();i++) {
                    datalist<<query.value(i).toString();
                }
            }
            course_infos.clear();
            course_infos=datalist;
            refresh_course_table();

        }
    }
}

void admin_page::refresh_course_table()
{
    //清除所有行
    qDebug()<<"清除前行数："<<ui->course_table->rowCount();
    for(int i = ui->course_table->rowCount() - 1;i >= 0; i--)
    {
        ui->course_table->removeRow(i);
    }
    qDebug()<<"清除后行数："<<ui->course_table->rowCount();

    for(int i=0;i<course_infos.length()/6;i++){
        //插入行
        int row_count=ui->course_table->rowCount();
        ui->course_table->insertRow(row_count);

        ui->course_table->setItem(row_count,0,new QTableWidgetItem(course_infos.value(i*6+1)));
        ui->course_table->setItem(row_count,1,new QTableWidgetItem(course_infos.value(i*6)));
        ui->course_table->setItem(row_count,2,new QTableWidgetItem(course_infos.value(i*6+2)));
        ui->course_table->setItem(row_count,3,new QTableWidgetItem(course_infos.value(i*6+3)));
        ui->course_table->setItem(row_count,4,new QTableWidgetItem(course_infos.value(i*6+4)));
        ui->course_table->setItem(row_count,5,new QTableWidgetItem(course_infos.value(i*6+5)));
    }
}

void admin_page::get_allcourse_information()
{
    QString sql;
    QSqlQuery query;
    QStringList datalist;

    sql.append("SELECT * FROM education_system.course");
    query.exec(sql);

    while (query.next()) {
        for (int i=0;i<query.record().count();i++) {
            datalist<<query.value(i).toString();
        }
    }
    course_infos.clear();
    course_infos=datalist;
}



//管理员信息点击事件///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void admin_page::on_admin_add_clicked()
{
    add_infos="4";

    aad=new admin_add;
    aad->exec();

    get_alladmin_information();
    refresh_admin_table();
}

void admin_page::on_admin_delete_clicked()
{
    QSqlQuery query;
    QString sql;
    QStringList datalist;
    QList<QTableWidgetItem*> items = ui->admin_table->selectedItems();

    if(!items.empty()){

        qDebug()<<"选中管理员的id"<<items.at(1)->text();
        if(items.at(1)->text()!=user_infos.value(0)){
            QMessageBox::warning(this,"警告","不能删除其他管理员，只能对自己做删除操作！");
            return;
        }

        //进行确认
        QMessageBox::StandardButton box;
        box = QMessageBox::question(this, "提示", "是否确认删除该管理员？", QMessageBox::Yes|QMessageBox::No);
        if(box==QMessageBox::No){
           return;
        }

        sql.append("DELETE FROM education_system.admin WHERE a_id='");
        sql.append(items.at(1)->text());
        sql.append("'");

        qDebug()<<"删除管理员SQL："<<sql;
//        query.exec(sql);/////////////////////////////////////////////////////////////////////////////////////////////////

        get_alladmin_information();
        refresh_admin_table();

    }else{
         QMessageBox::warning(this,"警告","请先选择一行再进行删除");
    }
}

void admin_page::on_admin_modify_clicked()
{
    QSqlQuery query;
    QString sql;
    QStringList datalist;
    QList<QTableWidgetItem*> items = ui->admin_table->selectedItems();
    QList<QTableWidgetSelectionRange> ranges = ui->admin_table->selectedRanges();

    if(!items.empty()){
        qDebug()<<"选中管理员的id"<<items.at(1)->text();
        if(items.at(1)->text()!=user_infos.value(0)){
            QMessageBox::warning(this,"警告","不能修改其他管理员信息，只能对自己做修改操作！");
            refresh_admin_table();
            return;
        }

        //行数
        int row=ranges.at(0).topRow();
        qDebug()<<"行数："<<row;

        int count = items.count();
        for(int i=0;i<count;i++){
            QTableWidgetItem *item=items.at(i);
            datalist<<item->text();
        }
        qDebug()<<"更改后的管理员信息："<<datalist;

        //进行确认
        QMessageBox::StandardButton box;
        QString text;

        text.append("是否确认将管理员:\n");
        text.append(admin_infos.value(row*3+1));text+=" ";
        text.append(admin_infos.value(row*3));text+=" ";
        text.append(admin_infos.value(row*3+2));
        text.append("\n的信息更改为:\n ");
        text.append(datalist.value(0));text+=" ";
        text.append(datalist.value(1));text+=" ";
        text.append(datalist.value(2));

        box = QMessageBox::question(this, "提示", text, QMessageBox::Yes|QMessageBox::No);
        if(box==QMessageBox::No){
            refresh_admin_table();
           return;
        }

        //判断主键是否更改
        if(admin_infos.value(row*3)!=datalist.value(1)){
            box = QMessageBox::warning(this, "警告", "是否确认更改管理员id(id不建议更改)", QMessageBox::Yes|QMessageBox::No);
            if(box==QMessageBox::No){
                  refresh_admin_table();
                  return;
             }
        }

        //数据库操作
        sql.append("UPDATE education_system.admin SET a_id='");
        sql.append(datalist.value(1));sql+="'";
        sql.append(",a_name='");sql.append(datalist.value(0));sql+="'";
        sql.append(",a_password='"); sql.append(datalist.value(2));sql+="'";
        sql.append(" WHERE a_id='");sql.append(admin_infos.value(row*3));sql+="'";

        qDebug()<<"sql:"<<sql;
        query.exec(sql);

    }else{
        QMessageBox::warning(this,"警告","请先选择一行再进行修改");
    }
}


void admin_page::on_admin_search_clicked()
{
    QSqlQuery query;
    QString sql;
    QStringList datalist;

    if(ui->admin_le->text().isNull()){
        get_alladmin_information();
        refresh_admin_table();    //刷新

    }else{

        QString data;
        data=ui->admin_le->text();
        if(IsNumber(data)){
            //纯数字，查询id
            sql.append("SELECT * FROM education_system.admin WHERE a_id like '%");
            sql.append(ui->admin_le->text());
            sql.append("%'");
            qDebug()<<"管理员搜索sql："<<sql;

            query.exec(sql);
            while (query.next()) {
                for (int i=0;i<query.record().count();i++) {
                    datalist<<query.value(i).toString();
                }
            }
            admin_infos.clear();
            admin_infos=datalist;
            refresh_admin_table();

        }else{
            //不是纯数字，查询姓名
            sql.append("SELECT * FROM education_system.admin WHERE a_name like '%");
            sql.append(ui->admin_le->text());
            sql.append("%'");
            qDebug()<<"管理员搜索sql："<<sql;

            query.exec(sql);
            while (query.next()) {
                for (int i=0;i<query.record().count();i++) {
                    datalist<<query.value(i).toString();
                }
            }
            admin_infos.clear();
            admin_infos=datalist;
            refresh_admin_table();

        }
    }
}


void admin_page::refresh_admin_table()
{
    //清除所有行
    qDebug()<<"清除前行数："<<ui->admin_table->rowCount();
    for(int i = ui->admin_table->rowCount() - 1;i >= 0; i--)
    {
        ui->admin_table->removeRow(i);
    }
    qDebug()<<"清除后行数："<<ui->admin_table->rowCount();

    for(int i=0;i<admin_infos.length()/3;i++){
        //插入行
        int row_count=ui->admin_table->rowCount();
        ui->admin_table->insertRow(row_count);

        ui->admin_table->setItem(row_count,0,new QTableWidgetItem(admin_infos.value(i*3+1)));
        ui->admin_table->setItem(row_count,1,new QTableWidgetItem(admin_infos.value(i*3)));
        ui->admin_table->setItem(row_count,2,new QTableWidgetItem(admin_infos.value(i*3+2)));
    }
}

void admin_page::get_alladmin_information()
{
    QString sql;
    QSqlQuery query;
    QStringList datalist;

    sql.append("SELECT * FROM education_system.admin");
    query.exec(sql);

    while (query.next()) {
        for (int i=0;i<query.record().count();i++) {
            datalist<<query.value(i).toString();
        }
    }
    admin_infos.clear();
    admin_infos=datalist;
}

//成绩信息点击事件///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void admin_page::score_table_change()
{
    QStringList datalist;
    QString sql;
    QSqlQuery query;

    qDebug()<<ui->cb_grade_class->currentText();
    qDebug()<<ui->cb_grade_class->currentIndex();

    if(ui->cb_grade_class->currentIndex()==0&&ui->cb_course->currentIndex()==0){
        get_allscore_information();
        refresh_score_table();
    }
    else{
        sql.append("SELECT DISTINCT s_name,s_id,s_grade,s_class,c_name,sc_score "
                   "FROM education_system.student t1,education_system.score t2,education_system.course t3 "
                   "WHERE t1.s_id=t2.sc_s_id AND  t2.sc_t_id=t3.c_teacher_id");
        if(ui->cb_grade_class->currentIndex()!=0){
            sql.append(" AND s_grade='");
            sql.append(admin_score_gradeclass.value((ui->cb_grade_class->currentIndex()-1)*2));
            sql.append("'");
            sql.append(" AND s_class='");
            sql.append(admin_score_gradeclass.value((ui->cb_grade_class->currentIndex()-1)*2+1));
            sql.append("'");
        }
        if(ui->cb_course->currentIndex()!=0){
            sql.append(" AND c_name='");
            sql.append(admin_score_course.value(ui->cb_course->currentIndex()-1));
            sql.append("'");
        }
        qDebug()<<"score_table_change-->sql:"<<sql;

        query.exec(sql);
        while (query.next()) {
            for (int i=0;i<query.record().count();i++) {
                datalist<<query.value(i).toString();
            }
        }

        score_infos.clear();
        score_infos=datalist;
        refresh_score_table();
        qDebug()<<"score_table_change-->score_infos:"<<score_infos;
    }


}

void admin_page::get_allscore_information()
{
    QStringList datalist;
    QString sql;
    QSqlQuery query;

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

    score_infos=datalist;
    qDebug()<<"get_allscore_information-->score_infos:"<<score_infos;
}

void admin_page::refresh_score_table()
{
    //清除所有行
    qDebug()<<"清除前行数："<<ui->score_table->rowCount();
    for(int i = ui->score_table->rowCount() - 1;i >= 0; i--)
    {
        ui->score_table->removeRow(i);
    }
    qDebug()<<"清除后行数："<<ui->score_table->rowCount();

    for(int i=0;i<score_infos.length()/6;i++){
        //插入行
        int row_count=ui->score_table->rowCount();
        ui->score_table->insertRow(row_count);

        ui->score_table->setItem(row_count,0,new QTableWidgetItem(score_infos.value(i*6)));
        ui->score_table->setItem(row_count,1,new QTableWidgetItem(score_infos.value(i*6+1)));
        ui->score_table->setItem(row_count,2,new QTableWidgetItem(score_infos.value(i*6+2)));
        ui->score_table->setItem(row_count,3,new QTableWidgetItem(score_infos.value(i*6+3)));
        ui->score_table->setItem(row_count,4,new QTableWidgetItem(score_infos.value(i*6+4)));
        if(score_infos.value(i*6+5)=="-1"){
            ui->score_table->setItem(row_count,5,new QTableWidgetItem("成绩暂未公布"));
        }else{
            ui->score_table->setItem(row_count,5,new QTableWidgetItem(score_infos.value(i*6+5)));
        }
    }
}


void admin_page::on_pushButton_2_clicked()
{
    QString filepath=QFileDialog::getSaveFileName(this,tr("Save orbit"),".",tr("Microsoft Office 2007 (*.xlsx)"));//获取保存路径
    if(!filepath.isEmpty()){
        QAxObject *excel = new QAxObject(this);
        excel->setControl("Excel.Application");//连接Excel控件
        excel->dynamicCall("SetVisible (bool Visible)","false");//不显示窗体
        excel->setProperty("DisplayAlerts", false);//不显示任何警告信息。如果为true那么在关闭是会出现类似“文件已修改，是否保存”的提示

        QAxObject *workbooks = excel->querySubObject("WorkBooks");//获取工作簿集合
        workbooks->dynamicCall("Add");//新建一个工作簿
        QAxObject *workbook = excel->querySubObject("ActiveWorkBook");//获取当前工作簿
        QAxObject *worksheets = workbook->querySubObject("Sheets");//获取工作表集合
        QAxObject *worksheet = worksheets->querySubObject("Item(int)",1);//获取工作表集合的工作表1，即sheet1

        QAxObject *cellA,*cellB,*cellC,*cellD,*cellE,*cellF;

        //设置标题
        int cellrow=1;
        QString A="A"+QString::number(cellrow);//设置要操作的单元格，如A1
        QString B="B"+QString::number(cellrow);
        QString C="C"+QString::number(cellrow);
        QString D="D"+QString::number(cellrow);
        QString E="E"+QString::number(cellrow);
        QString F="F"+QString::number(cellrow);
        cellA = worksheet->querySubObject("Range(QVariant, QVariant)",A);//获取单元格
        cellB = worksheet->querySubObject("Range(QVariant, QVariant)",B);
        cellC=worksheet->querySubObject("Range(QVariant, QVariant)",C);
        cellD=worksheet->querySubObject("Range(QVariant, QVariant)",D);
        cellE=worksheet->querySubObject("Range(QVariant, QVariant)",E);
        cellF=worksheet->querySubObject("Range(QVariant, QVariant)",F);
        cellA->dynamicCall("SetValue(const QVariant&)",QVariant("姓名"));//设置单元格的值
        cellB->dynamicCall("SetValue(const QVariant&)",QVariant("学号"));
        cellC->dynamicCall("SetValue(const QVariant&)",QVariant("年级"));
        cellD->dynamicCall("SetValue(const QVariant&)",QVariant("班级"));
        cellE->dynamicCall("SetValue(const QVariant&)",QVariant("学科"));
        cellF->dynamicCall("SetValue(const QVariant&)",QVariant("成绩"));
        cellrow++;

        int rows=score_infos.length()/6;
        for(int i=0;i<rows;i++){
            QString A="A"+QString::number(cellrow);//设置要操作的单元格，如A1
            QString B="B"+QString::number(cellrow);
            QString C="C"+QString::number(cellrow);
            QString D="D"+QString::number(cellrow);
            QString E="E"+QString::number(cellrow);
            QString F="F"+QString::number(cellrow);
            cellA = worksheet->querySubObject("Range(QVariant, QVariant)",A);//获取单元格
            cellB = worksheet->querySubObject("Range(QVariant, QVariant)",B);
            cellC=worksheet->querySubObject("Range(QVariant, QVariant)",C);
            cellD=worksheet->querySubObject("Range(QVariant, QVariant)",D);
            cellE=worksheet->querySubObject("Range(QVariant, QVariant)",E);
            cellF=worksheet->querySubObject("Range(QVariant, QVariant)",F);
            cellA->dynamicCall("SetValue(const QVariant&)",score_infos.value(i*6));//设置单元格的值
            cellB->dynamicCall("SetValue(const QVariant&)",score_infos.value(i*6+1));
            cellC->dynamicCall("SetValue(const QVariant&)",score_infos.value(i*6+2));
            cellD->dynamicCall("SetValue(const QVariant&)",score_infos.value(i*6+3));
            cellE->dynamicCall("SetValue(const QVariant&)",score_infos.value(i*6+4));
            if(score_infos.value(i*6+5)=="-1"){
                cellF->dynamicCall("SetValue(const QVariant&)",QString("成绩暂未公布"));
            }else{
                cellF->dynamicCall("SetValue(const QVariant&)",score_infos.value(i*6+5));
            }
            cellrow++;
        }

        workbook->dynamicCall("SaveAs(const QString&)",QDir::toNativeSeparators(filepath));//保存至filepath，注意一定要用QDir::toNativeSeparators将路径中的"/"转换为"\"，不然一定保存不了。
        workbook->dynamicCall("Close()");//关闭工作簿
        excel->dynamicCall("Quit()");//关闭excel
        delete excel;
        excel=NULL;
    }

}



//其他/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool admin_page::IsNumber(QString &qstrSrc)
{
    QByteArray ba = qstrSrc.toLatin1();
    const char *s = ba.data();
    bool bret = true;
    while(*s)
    {
        if(*s>='0' && *s<='9')
        {

        }
        else
        {
            bret = false;
            break;
        }
        s++;
    }
    return bret;
}

void admin_page::on_pushButton_clicked()
{
    emit Exit_admin();
    this->close();
}


