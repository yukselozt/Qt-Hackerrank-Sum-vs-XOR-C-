QT       += core gui network websockets


TRANSLATIONS = tr_TCMS68000_Turkish.ts\
                               tr_TCMS68000_English.ts


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    config.cpp\
    main.cpp \
    mainwindow.cpp

HEADERS += \
    config.h \
    config.h\
    mainwindow.h

FORMS += \
    mainwindow.ui

TRANSLATIONS +=    tr_TCMS68000_English.ts \
                                     tr_TCMS68000_Turkish.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
