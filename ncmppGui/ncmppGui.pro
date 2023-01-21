QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

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
    main.cpp \
    src/base64.cpp \
    src/mainwindow.cpp \
    src/ncmdump.cpp \
    src/pkcs7.cpp \
    src/qlistwidget_withdrop.cpp \
    src/unlocker.cpp

HEADERS += \
    src/base64.h \
    src/mainwindow.h \
    src/ncmdump.h \
    src/pkcs7.h \
    src/qlistwidget_withdrop.h \
    src/unlocker.h

FORMS += \
    ui/mainwindow.ui

QMAKE_CXXFLAGS += \
    -std:c++17

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32: LIBS += \
    -L$$PWD/ext/lib/ -llibssl_static \
    -L$$PWD/ext/lib/ -llibcrypto_static

INCLUDEPATH += $$PWD/ext/include
DEPENDPATH += $$PWD/ext/include

win32:!win32-g++: PRE_TARGETDEPS += \
    $$PWD/ext/lib/libssl_static.lib \
    $$PWD/ext/lib/libcrypto_static.lib
