#include "singlepage_teacher.h"
#include "ui_singlepage_teacher.h"
#include <QDebug>
#include "item.h"

singlepage_teacher::singlepage_teacher(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::singlepage_teacher)
{
    ui->setupUi(this);

    ui->tname->setText(singal_infos.value(1));
    ui->tage->setText(singal_infos.value(2));
    ui->tsex->setText(singal_infos.value(3));
    ui->ttel->setText(singal_infos.value(4));
    //图片  修改/////////////////////////////////////////////////////////////////////////
    QString img_position=position;
    img_position+="/img/2.jpg";
    QImage image(img_position);
    qDebug()<<img_position;
    ui->timg->setPixmap(QPixmap::fromImage(image));
    ui->timg->setScaledContents(true);
//    ui->timg->resize(image.width(),image.height());

    if(singal_infos.value(7)==NULL){
        ui->tintro->setText("略");
    }else{
        ui->tintro->setText(singal_infos.value(7));
        ui->tintro->setAlignment(Qt::AlignTop);
        ui->tintro->setWordWrap(true);
    }
    if(singal_infos.value(8)==NULL){
        ui->tachieve->setText("略");
    }else{
        ui->tachieve->setText(singal_infos.value(8));
        ui->tachieve->setWordWrap(true);
    }

    ui->tname->setTextInteractionFlags(Qt::TextSelectableByMouse);
    ui->tage->setTextInteractionFlags(Qt::TextSelectableByMouse);
    ui->tsex->setTextInteractionFlags(Qt::TextSelectableByMouse);
    ui->ttel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    ui->tintro->setTextInteractionFlags(Qt::TextSelectableByMouse);
    ui->tachieve->setTextInteractionFlags(Qt::TextSelectableByMouse);
}

singlepage_teacher::~singlepage_teacher()
{
    delete ui;
}
