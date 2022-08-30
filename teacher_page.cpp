#include "teacher_page.h"
#include "ui_teacher_page.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessagebox>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>
#include "item.h"

teacher_page::teacher_page(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::teacher_page)
{
    ui->setupUi(this);

    ui->pushButton_3->hide();
    //头像
    QString img_position=position;
    if(user_infos.value(6).isEmpty()){
        qDebug()<<"用户没有头像";
        img_position+="/img/";
        img_position.append("0.png");
    }else{
        img_position+="/user_img/";
        img_position.append(user_infos.value(6));
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
    l<<"班级学生";
    QTreeWidgetItem *child0_2 = new QTreeWidgetItem(parent0,l);
    parent0->addChild(child0_1);
    parent0->addChild(child0_2);

    //第二类///////////////////////////////////////////////////////
    l.clear();
    l<<"教师信息";
    QTreeWidgetItem *parent1 = new QTreeWidgetItem(ui->treeWidget,l);
    ui->treeWidget->insertTopLevelItem(1,parent1);

    l.clear();
    l<<"个人信息";
    QTreeWidgetItem *child1_1 = new QTreeWidgetItem(parent1,l);
    parent1->addChild(child1_1);

    l.clear();
    l<<"学校教师";
    QTreeWidgetItem *child1_2 = new QTreeWidgetItem(parent1,l);
    parent1->addChild(child1_2);

    //第三类///////////////////////////////////////////////////////
    l.clear();
    l<<"成绩管理";
    QTreeWidgetItem *parent2 = new QTreeWidgetItem(ui->treeWidget,l);
    ui->treeWidget->insertTopLevelItem(2,parent2);

    l.clear();
    l<<"学生成绩";
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

       int day,time;
       QString countet;
       for(int i=0;i<course_infos.length()/4;i++){
           countet.clear();
           day=course_infos.value(i*4+2).toInt()-1;
           time=course_infos.value(i*4+3).toInt()-1;
           if(time>3){time+=1;}
           countet.append(course_infos.value(i*4));
           countet.append("(");
           countet.append(course_infos.value(i*4+1));
           countet.append("班)");
           ui->course_table->setItem(time,day,new QTableWidgetItem(countet));
       }

       /********************************************班级学生****************************************************/
       //设置表头列数和内容
       ui->student_table->setColumnCount(6);
       QStringList header_student;
       header_student<<tr("姓名")<<tr("学号")<<tr("班级")<<tr("年龄")<<tr("性别")<<tr("电话");
       ui->student_table->setHorizontalHeaderLabels(header_student);

       //设置表头字体加粗
       QFont font_student_table = ui->student_table->horizontalHeader()->font();
       font_student_table.setBold(true);
       ui->student_table->horizontalHeader()->setFont(font_student_table);

       //设置整行选中
       ui->student_table->setSelectionBehavior ( QAbstractItemView::SelectRows);
       ui->student_table->setSelectionMode(QAbstractItemView::SingleSelection);
       //不可编辑
       ui->student_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
       //设置水平平分表格
       ui->student_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

   //    qDebug()<<"登录用户的教师信息长度:"<<teacher_infos.length();
       for(int i=0;i<student_infos.length()/9;i++){
           //插入行
           int row_count=ui->student_table->rowCount();
           ui->student_table->insertRow(row_count);

           ui->student_table->setItem(row_count,0,new QTableWidgetItem(student_infos.value(i*9+1)));
           ui->student_table->setItem(row_count,1,new QTableWidgetItem(student_infos.value(i*9)));
           ui->student_table->setItem(row_count,2,new QTableWidgetItem(student_infos.value(i*9+5)));
           ui->student_table->setItem(row_count,3,new QTableWidgetItem(student_infos.value(i*9+2)));
           ui->student_table->setItem(row_count,4,new QTableWidgetItem(student_infos.value(i*9+3)));
           ui->student_table->setItem(row_count,5,new QTableWidgetItem(student_infos.value(i*9+6)));
       }
       /********************************************个人信息****************************************************/
        ui->teacher_name->setText(user_infos.value(1));
        ui->teacher_class->setText(course_infos.value(1));
        ui->teacher_age->setText(user_infos.value(2));
        ui->teacher_sex->setText(user_infos.value(3));
        ui->teacher_tel->setText(user_infos.value(4));
        if(user_infos.value(7)==NULL){
            ui->teacher_intro->setText("略");
        }else{
            ui->teacher_intro->setText(user_infos.value(7));
            ui->teacher_intro->setWordWrap(true);
        }
        if(user_infos.value(8)==NULL){
            ui->teacher_achieve->setText("略");
        }else{
            ui->teacher_achieve->setText(user_infos.value(8));
            ui->teacher_achieve->setWordWrap(true);
        }
        //放图片
        ui->teacher_img->setPixmap(QPixmap::fromImage(image));
        ui->teacher_img->setScaledContents(true);
    //    ui->user_img->resize(image.width(),image.height());


        ui->teacher_name->setTextInteractionFlags(Qt::TextSelectableByMouse);
        ui->teacher_class->setTextInteractionFlags(Qt::TextSelectableByMouse);
        ui->teacher_age->setTextInteractionFlags(Qt::TextSelectableByMouse);
        ui->teacher_sex->setTextInteractionFlags(Qt::TextSelectableByMouse);
        ui->teacher_tel->setTextInteractionFlags(Qt::TextSelectableByMouse);
        ui->teacher_intro->setTextInteractionFlags(Qt::TextSelectableByMouse);
        ui->teacher_achieve->setTextInteractionFlags(Qt::TextSelectableByMouse);

        /********************************************学校教师****************************************************/
        //设置表头列数和内容
        ui->teacher_table->setColumnCount(5);
        QStringList header_teacher;
        header_teacher<<tr("姓名")<<tr("教师id")<<tr("年龄")<<tr("性别")<<tr("电话");
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
        for(int i=0;i<teacher_infos.length()/7;i++){
            //插入行
            int row_count=ui->teacher_table->rowCount();
            ui->teacher_table->insertRow(row_count);

            ui->teacher_table->setItem(row_count,0,new QTableWidgetItem(teacher_infos.value(i*7+1)));
            ui->teacher_table->setItem(row_count,1,new QTableWidgetItem(teacher_infos.value(i*7)));
            ui->teacher_table->setItem(row_count,2,new QTableWidgetItem(teacher_infos.value(i*7+2)));
            ui->teacher_table->setItem(row_count,3,new QTableWidgetItem(teacher_infos.value(i*7+3)));
            ui->teacher_table->setItem(row_count,4,new QTableWidgetItem(teacher_infos.value(i*7+4)));
        }

        /********************************************学生成绩****************************************************/
        //设置整行选中
        ui->score_table->setSelectionBehavior ( QAbstractItemView::SelectRows);
        ui->score_table->setSelectionMode(QAbstractItemView::SingleSelection);

        //设置表头列数和内容
        ui->score_table->setColumnCount(3);
        QStringList header_score;
        header_score<<tr("学生姓名")<<tr("学生学号")<<tr("分数");
        ui->score_table->setHorizontalHeaderLabels(header_score);

        //设置表头字体加粗
        QFont font_score_table = ui->score_table->horizontalHeader()->font();
        font_score_table.setBold(true);
        ui->score_table->horizontalHeader()->setFont(font_score_table);

        ui->score_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

//        qDebug()<<"登录用户的成绩信息长度:"<<score_infos.length();
        for(int i=0;i<score_infos.length()/3;i++){
            //插入行
            int row_count=ui->score_table->rowCount();
            ui->score_table->insertRow(row_count);

            ui->score_table->setItem(row_count,0,new QTableWidgetItem(score_infos.value(i*3+1)));
            ui->score_table->setItem(row_count,1,new QTableWidgetItem(score_infos.value(i*3)));

            //禁止修改
            QTableWidgetItem* modify_score;
            modify_score = ui->score_table->item(row_count, 0);
            modify_score->setFlags(modify_score->flags() & (~Qt::ItemIsEditable));
            modify_score = ui->score_table->item(row_count, 1);
            modify_score->setFlags(modify_score->flags() & (~Qt::ItemIsEditable));


            if(score_infos.value(i*3+2)=="-1"){
                ui->score_table->setItem(row_count,2,new QTableWidgetItem("未打分"));
            }else{
                ui->score_table->setItem(row_count,2,new QTableWidgetItem(score_infos.value(i*3+2)));
            }
        }

    /****************************************************************************************************/
    //绑定点击事件
    connect(ui->treeWidget,&QTreeWidget::itemClicked,this,&teacher_page::treeWidgetClicked);
}

void teacher_page::treeWidgetClicked(QTreeWidgetItem *item)
{
    if(item->text(0)=="您的课表"){
        qDebug()<<"您的课表";
        ui->stackedWidget->setCurrentIndex(0);

    }else if (item->text(0)=="班级学生") {
        qDebug()<<"班级学生";
        ui->stackedWidget->setCurrentIndex(1);

    }else if (item->text(0)=="个人信息") {
        qDebug()<<"个人信息";
        ui->stackedWidget->setCurrentIndex(2);

    }else if (item->text(0)=="学校教师") {
        qDebug()<<"学校教师";
        ui->stackedWidget->setCurrentIndex(3);

    }else if (item->text(0)=="学生成绩") {
        qDebug()<<"学生成绩";
        ui->stackedWidget->setCurrentIndex(4);

    }else if (item->text(0)=="修改密码") {
        qDebug()<<"修改密码";
        ui->stackedWidget->setCurrentIndex(5);
    }
}



teacher_page::~teacher_page()
{
    delete ui;
}

void teacher_page::on_pushButton_5_clicked()
{
    QList<QTableWidgetSelectionRange> ranges = ui->teacher_table->selectedRanges();
    if(ranges.count() != 0){
        int row=ranges.at(0).topRow();
        qDebug()<<"行数："<<row;

        QSqlQuery query;
        QStringList datalist;
        QString sql;
        sql.append("SELECT * FROM education_system.teacher WHERE t_id='");
        sql.append(teacher_infos.value(row*7));
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

void teacher_page::on_pushButton_2_clicked()
{
    QList<QTableWidgetSelectionRange> ranges = ui->score_table->selectedRanges();
    if(ranges.count() != 0){

        QMessageBox::StandardButton box;
        box = QMessageBox::question(this, "提示", "是否确认修改该学生的成绩？", QMessageBox::Yes|QMessageBox::No);
        if(box==QMessageBox::No){
            refresh_score();
           return;
           }

        int row=ranges.at(0).topRow();
        qDebug()<<"行数："<<row;

        QSqlQuery query;
        QStringList datalist;
        QString sc;
        QString sql;

        sql.append("UPDATE education_system.score SET sc_score=");
        qDebug()<<"现在的成绩："<<ui->score_table->item(row,2)->text();
        sql.append(ui->score_table->item(row,2)->text());
        sql.append(" WHERE sc_s_id='");
        sql.append(score_infos.value(row*3));
        sql.append("' AND sc_t_id='");
        sql.append(user_infos.value(0));
        sql.append("'");
        qDebug()<<"更改单个学生成绩："<<sql;

        query.exec(sql);
    }
    else{
        QMessageBox::warning(this,"警告","请先选择一行再进行修改！");
    }
}

void teacher_page::refresh_score()
{
    for(int i=0;i<score_infos.length()/3;i++){

        ui->score_table->setItem(i,0,new QTableWidgetItem(score_infos.value(i*3+1)));
        ui->score_table->setItem(i,1,new QTableWidgetItem(score_infos.value(i*3)));

        //禁止修改
        QTableWidgetItem* modify_score;
        modify_score = ui->score_table->item(i, 0);
        modify_score->setFlags(modify_score->flags() & (~Qt::ItemIsEditable));
        modify_score = ui->score_table->item(i, 1);
        modify_score->setFlags(modify_score->flags() & (~Qt::ItemIsEditable));


        if(score_infos.value(i*3+2)=="-1"){
            ui->score_table->setItem(i,2,new QTableWidgetItem("未打分"));
        }else{
            ui->score_table->setItem(i,2,new QTableWidgetItem(score_infos.value(i*3+2)));
        }
    }
}

void teacher_page::on_pushButton_6_clicked()
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

            sql.append("UPDATE education_system.teacher SET t_img='");
            sql.append(fileInfo.fileName());
            sql.append("'");
            sql.append(" WHERE t_id='");
            sql.append(user_infos.value(0));
            sql.append("'");

            qDebug()<<"修改用户图片："<<sql;
            query.exec(sql);

            refresh_userinformation();
        }
}

void teacher_page::refresh_userinformation()
{
    QSqlQuery query;
    QStringList datalist;
    QString sql;

    sql.append("SELECT * FROM education_system.teacher WHERE t_id='");
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
    if(user_infos.value(6).isEmpty()){
        qDebug()<<"用户没有头像";
        img_position+="/img/";
        img_position.append("0.png");
    }else{
        img_position+="/user_img/";
        img_position.append(user_infos.value(6));
    }
    qDebug()<<"头像地址："<<img_position;
    QImage image(img_position);
    qDebug()<<" "<<image;

    ui->label_2->setPixmap(QPixmap::fromImage(image));
    ui->label_2->setScaledContents(true);
    ui->teacher_img->setPixmap(QPixmap::fromImage(image));
    ui->teacher_img->setScaledContents(true);
}

void teacher_page::on_pushButton_clicked()
{
    emit Exit_teacher();
    this->close();
}
