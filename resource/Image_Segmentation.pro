QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp\
    rnam.cpp \
    rnamDao.cpp \
    stc.cpp \
    stcDao.cpp


HEADERS += \
    mainwindow.h\
    rnam.h \
    rnamDao.h \
    stc.h \
    stcDao.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += D:\opencv\opencv_build\install\include

LIBS += D:\opencv\opencv_build\lib\libopencv_*.a

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

RC_ICONS = logo.ico
