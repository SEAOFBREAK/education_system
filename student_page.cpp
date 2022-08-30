#include "student_page.h"
#include "ui_student_page.h"
#include <QtDebug>
#include "item.h"
#include <QString>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessagebox>
#include <QFileDialog>

student_page::student_page(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::student_page)
{
    ui->setupUi(this);

    //头像
    QString img_position=position;
    if(user_infos.value(8).isEmpty()){
        qDebug()<<"用户没有头像";
        img_position+="/img/";
        img_position.append("0.png");
    }else{
        img_position+="/user_img/";
        img_position.append(user_infos.value(8));
    }
    qDebug()<<"头像地址："<<img_position;
    QImage image(img_position);
    qDebug()<<" "<<image;

    ui->label_2->setPixmap(QPixmap::fromImage(image));
    ui->label_2->setScaledContents(true);

    //用户名
    ui->label_4->setText(user_infos.value(1));

    ui->treeWidget->setColumnCount(1);
    QStringList l;

    //第一类///////////////////////////////////////////////////////
    l<<"教学安排";
    QTreeWidgetItem *parent0 = new QTreeWidgetItem(ui->treeWidget,l);
    ui->treeWidget->insertTopLevelItem(0,parent0);

    l.clear();
    l<<"您的课表";
    QTreeWidgetItem *child0_1 = new QTreeWidgetItem(parent0,l);
    l.clear();
    l<<"授课教师";
    QTreeWidgetItem *child0_2 = new QTreeWidgetItem(parent0,l);
    parent0->addChild(child0_1);
    parent0->addChild(child0_2);

    //第二类///////////////////////////////////////////////////////
    l.clear();
    l<<"学籍管理";
    QTreeWidgetItem *parent1 = new QTreeWidgetItem(ui->treeWidget,l);
    ui->treeWidget->insertTopLevelItem(1,parent1);

    l.clear();
    l<<"个人信息";
    QTreeWidgetItem *child1_1 = new QTreeWidgetItem(parent1,l);
    parent1->addChild(child1_1);

    //第三类///////////////////////////////////////////////////////
    l.clear();
    l<<"成绩管理";
    QTreeWidgetItem *parent2 = new QTreeWidgetItem(ui->treeWidget,l);
    ui->treeWidget->insertTopLevelItem(2,parent2);

    l.clear();
    l<<"成绩查询";
    QTreeWidgetItem *child2_1 = new QTreeWidgetItem(parent2,l);
    parent1->addChild(child2_1);
    //第四类///////////////////////////////////////////////////////
    l.clear();
    l<<"个人配置";
    QTreeWidgetItem *parent3 = new QTreeWidgetItem(ui->treeWidget,l);
    ui->treeWidget->insertTopLevelItem(3,parent3);

    l.clear();
    l<<"修改密码";
    QTreeWidgetItem *child3_1 = new QTreeWidgetItem(parent3,l);
    parent1->addChild(child3_1);

    //全部展开
    ui->treeWidget->expandAll();

    //默认显示课表页
    ui->stackedWidget->setCurrentIndex(0);

    /********************************************您的课表****************************************************/
     ui->course_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

     //不可编辑
     ui->course_table->setEditTriggers(QAbstractItemView::NoEditTriggers);

//    QFont font_course_table = ui->score_table->horizontalHeader()->font();
//    font_course_table.setBold(true);
//    ui->course_table->horizontalHeader()->setFont(font_course_table);

    int day,time;
    for(int i=0;i<course_infos.length()/4;i++){
        day=course_infos.value(i*4+2).toInt()-1;
        time=course_infos.value(i*4+3).toInt()-1;
        if(time>3){time+=1;}
        ui->course_table->setItem(time,day,new QTableWidgetItem(course_infos.value(i*4)));
    }
    /********************************************授课教师****************************************************/
    //设置表头列数和内容
    ui->teacher_table->setColumnCount(5);
    QStringList header_teacher;
    header_teacher<<tr("授课教师")<<tr("科目")<<tr("年龄")<<tr("性别")<<tr("电话");
    ui->teacher_table->setHorizontalHeaderLabels(header_teacher);

    //设置表头字体加粗
    QFont font_teacher_table = ui->teacher_table->horizontalHeader()->font();
    font_teacher_table.setBold(true);
    ui->teacher_table->horizontalHeader()->setFont(font_teacher_table);

    //设置整行选中
    ui->teacher_table->setSelectionBehavior ( QAbstractItemView::SelectRows);
    ui->teacher_table->setSelectionMode(QAbstractItemView::SingleSelection);
    //不可编辑
    ui->teacher_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //设置水平平分表格
    ui->teacher_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

//    qDebug()<<"登录用户的教师信息长度:"<<teacher_infos.length();
    for(int i=0;i<teacher_infos.length()/8;i++){
        //插入行
        int row_count=ui->teacher_table->rowCount();
        ui->teacher_table->insertRow(row_count);

        ui->teacher_table->setItem(row_count,0,new QTableWidgetItem(teacher_infos.value(i*8+2)));
        ui->teacher_table->setItem(row_count,1,new QTableWidgetItem(teacher_infos.value(i*8)));
        ui->teacher_table->setItem(row_count,2,new QTableWidgetItem(teacher_infos.value(i*8+3)));
        ui->teacher_table->setItem(row_count,3,new QTableWidgetItem(teacher_infos.value(i*8+4)));
        ui->teacher_table->setItem(row_count,4,new QTableWidgetItem(teacher_infos.value(i*8+5)));
    }

   /********************************************个人信息****************************************************/
    ui->user_id->setText(user_infos.value(0));
    ui->user_name->setText(user_infos.value(1));
    ui->user_age->setText(user_infos.value(2));
    ui->user_sex->setText(user_infos.value(3));
    ui->user_grade->setText(user_infos.value(4));
    ui->user_class->setText(user_infos.value(5));
    ui->user_tel->setText(user_infos.value(6));
    //放图片
    ui->user_img->setPixmap(QPixmap::fromImage(image));
    ui->user_img->setScaledContents(true);
//    ui->user_img->resize(image.width(),image.height());


    ui->user_id->setTextInteractionFlags(Qt::TextSelectableByMouse);
    ui->user_name->setTextInteractionFlags(Qt::TextSelectableByMouse);
    ui->user_age->setTextInteractionFlags(Qt::TextSelectableByMouse);
    ui->user_sex->setTextInteractionFlags(Qt::TextSelectableByMouse);
    ui->user_grade->setTextInteractionFlags(Qt::TextSelectableByMouse);
    ui->user_class->setTextInteractionFlags(Qt::TextSelectableByMouse);
    ui->user_tel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    /********************************************成绩查询****************************************************/
    QString user_score;
    user_score.append(user_infos.value(0));
    user_score.append("  ");
    user_score.append(user_infos.value(1));
    user_score.append("  学科成绩");
    ui->label_23->setText(user_score);

    //设置整行选中
    ui->score_table->setSelectionBehavior ( QAbstractItemView::SelectRows);
    ui->score_table->setSelectionMode(QAbstractItemView::SingleSelection);
    //不可编辑
    ui->score_table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //设置表头列数和内容
    ui->score_table->setColumnCount(3);
    QStringList header_score;
    header_score<<tr("科目名称")<<tr("评分教师")<<tr("分数");
    ui->score_table->setHorizontalHeaderLabels(header_score);

    //设置表头字体加粗
    QFont font_score_table = ui->score_table->horizontalHeader()->font();
    font_score_table.setBold(true);
    ui->score_table->horizontalHeader()->setFont(font_score_table);

    ui->score_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //qDebug()<<"登录用户的成绩信息长度:"<<score_infos.length();
    for(int i=0;i<score_infos.length()/4;i++){
        //插入行
        int row_count=ui->score_table->rowCount();
        ui->score_table->insertRow(row_count);

        ui->score_table->setItem(row_count,0,new QTableWidgetItem(score_infos.value(i*4+1)));
        ui->score_table->setItem(row_count,1,new QTableWidgetItem(score_infos.value(i*4+2)));
        if(score_infos.value(i*4+3)=="-1"){
            ui->score_table->setItem(row_count,2,new QTableWidgetItem("该科成绩暂未公布"));
        }else{
            ui->score_table->setItem(row_count,2,new QTableWidgetItem(score_infos.value(i*4+3)));
        }
    }
     /*******************************************************************************************************/
    //绑定点击事件
    connect(ui->treeWidget,&QTreeWidget::itemClicked,this,&student_page::treeWidgetClicked);
}
void student_page::treeWidgetClicked(QTreeWidgetItem *item)
{
//    qDebug()<<item->text(0);
    if(item->text(0)=="您的课表"){
        qDebug()<<"您的课表";
        ui->stackedWidget->setCurrentIndex(0);

    }else if (item->text(0)=="授课教师") {
        qDebug()<<"授课教师";
        ui->stackedWidget->setCurrentIndex(1);

    }else if (item->text(0)=="个人信息") {
        qDebug()<<"个人信息";
        ui->stackedWidget->setCurrentIndex(2);

    }else if (item->text(0)=="成绩查询") {
        qDebug()<<"成绩查询";
        ui->stackedWidget->setCurrentIndex(3);

    }else if (item->text(0)=="修改密码") {
        qDebug()<<"修改密码";
        ui->stackedWidget->setCurrentIndex(4);
    }

}






student_page::~student_page()
{
    delete ui;
}


void student_page::on_pushButton_3_clicked()
{
    QList<QTableWidgetSelectionRange> ranges = ui->teacher_table->selectedRanges();
    if(ranges.count() != 0){
        int row=ranges.at(0).topRow();
        qDebug()<<"行数："<<row;

        QSqlQuery query;
        QStringList datalist;
        QString sql;
        sql.append("SELECT * FROM education_system.teacher WHERE t_id='");
        sql.append(teacher_infos.value(row*8+1));
        sql.append("'");
        qDebug()<<"查询单个教师信息："<<sql;

        query.exec(sql);
        query.next();
        for (int i=0;i<query.record().count();i++) {
            datalist<<query.value(i).toString();
        }
        singal_infos.clear();
        singal_infos=datalist;
        qDebug()<<"查询单个教师信息："<<singal_infos;

        spt=new singlepage_teacher();
        spt->show();
    }
    else{
        QMessageBox::warning(this,"警告","请先选择一行再进行查询");
    }
}

void student_page::on_pushButton_4_clicked()
{
    QString file_path=QFileDialog::getOpenFileName(this,"请选择文件","./img/","*.jpg *.png *.jpeg *.webp");
        if(file_path.isEmpty())
        {
            return;
        }else{
            QSqlQuery query;
            QString sql;

            QFile *file = new QFile;
            file->setFileName(file_path);
            QFileInfo fileInfo(*file);
            qDebug() <<"dzy"<< fileInfo.filePath();
            qDebug() <<"dzy1"<< fileInfo.fileName();

            //源数文件 包含路径 文件名
            QString sCurrentPath = fileInfo.filePath();
            //备份文件 包含路径 文件名
            QString sBachUpPath = position;
            sBachUpPath+="/user_img/";
            sBachUpPath.append(fileInfo.fileName());

            QFile currenFile(sCurrentPath);
            currenFile.copy(sBachUpPath);

            sql.append("UPDATE education_system.student SET s_img='");
            sql.append(fileInfo.fileName());
            sql.append("'");
            sql.append(" WHERE s_id='");
            sql.append(user_infos.value(0));
            sql.append("'");

            qDebug()<<"修改用户图片："<<sql;
            query.exec(sql);

            refresh_userinformation();
            QMessageBox::question(this,"提示","头像修改成功！");
        }

}

void student_page::refresh_userinformation()
{
    QSqlQuery query;
    QStringList datalist;
    QString sql;

    sql.append("SELECT * FROM education_system.student WHERE s_id='");
    sql.append(user_infos.value(0));
    sql.append("'");

    query.exec(sql);
    query.next();
    for(int i=0;i<query.record().count();i++){
        datalist<<query.value(i).toString();
    }
    user_infos.clear();
    user_infos=datalist;
    qDebug()<<"user_infos:"<<user_infos;

    QString img_position=position;
    if(user_infos.value(8).isEmpty()){
        qDebug()<<"用户没有头像";
        img_position+="/img/";
        img_position.append("0.png");
    }else{
        img_position+="/user_img/";
        img_position.append(user_infos.value(8));
    }
    qDebug()<<"头像地址："<<img_position;
    QImage image(img_position);
    qDebug()<<" "<<image;

    ui->label_2->setPixmap(QPixmap::fromImage(image));
    ui->label_2->setScaledContents(true);
    ui->user_img->setPixmap(QPixmap::fromImage(image));
    ui->user_img->setScaledContents(true);
}

void student_page::on_pushButton_clicked()
{
    emit Exit_student();
    this->close();
}

void student_page::on_pushButton_2_clicked()
{
    QString pw_before,pw_after1,pw_after2;

   pw_before= ui->lineEdit->text();
   pw_after1=ui->lineEdit_2->text();
   pw_after2=ui->lineEdit_3->text();
   if(pw_after1.isEmpty()){
       QMessageBox::question(this,"提示","密码不能为空！");
       return;
   }
   if(pw_after1!=pw_after2){
       QMessageBox::question(this,"提示","新密码不一致！");
       return;
   }
   if(pw_before!=user_infos.value(7)){
       QMessageBox::question(this,"提示","原密码不正确！");
       return;
   }

   QString sql;
   QSqlQuery query;

   sql.append("UPDATE education_system.student SET s_password='");
   sql.append(pw_after1);
   sql.append("'");
   sql.append(" WHERE s_id='");
   sql.append(user_infos.value(0));
   sql.append("'");

   qDebug()<<"修改用户密码："<<sql;
   query.exec(sql);
   QMessageBox::question(this,"提示","密码修改成功！");

   refresh_userinformation();
}
