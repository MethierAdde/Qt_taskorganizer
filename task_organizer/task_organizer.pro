QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    add_fixedddl.cpp \
    add_fixedtime.cpp \
    add_new.cpp \
    alltask_recorder.cpp \
    block.cpp \
    block_button.cpp \
    day.cpp \
    explaining.cpp \
    main.cpp \
    mainwindow.cpp \
    management.cpp \
    personalset.cpp \
    settings.cpp \
    task.cpp \
    task_arranger.cpp \
    task_button.cpp

HEADERS += \
    add_fixedddl.h \
    add_fixedtime.h \
    add_new.h \
    alltask_recorder.h \
    block.h \
    block_button.h \
    day.h \
    explaining.h \
    mainwindow.h \
    management.h \
    personalset.h \
    settings.h \
    task.h \
    task_arranger.h \
    task_button.h

FORMS += \
    add_fixedddl.ui \
    add_fixedtime.ui \
    add_new.ui \
    explaining.ui \
    mainwindow.ui \
    management.ui \
    settings.ui

TRANSLATIONS += \
    task_organizer_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=
