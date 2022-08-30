QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin_add.cpp \
    admin_page.cpp \
    item.cpp \
    login.cpp \
    main.cpp \
    singlepage_teacher.cpp \
    student_page.cpp \
    teacher_page.cpp

HEADERS += \
    admin_add.h \
    admin_page.h \
    item.h \
    login.h \
    singlepage_teacher.h \
    student_page.h \
    teacher_page.h

FORMS += \
    admin_add.ui \
    admin_page.ui \
    login.ui \
    mainwindow.ui \
    singlepage_teacher.ui \
    student_page.ui \
    teacher_page.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc

QT += sql
QT += axcontainer
