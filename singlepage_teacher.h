#ifndef SINGLEPAGE_TEACHER_H
#define SINGLEPAGE_TEACHER_H

#include <QWidget>

namespace Ui {
class singlepage_teacher;
}

class singlepage_teacher : public QWidget
{
    Q_OBJECT

public:
    explicit singlepage_teacher(QWidget *parent = nullptr);
    ~singlepage_teacher();

private:
    Ui::singlepage_teacher *ui;
};

#endif // SINGLEPAGE_TEACHER_H
