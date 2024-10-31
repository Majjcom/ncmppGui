QT       += core gui
android: QT += androidextras

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

include(material-ui/material-ui.pri)

SOURCES += \
    main.cpp \
    src/mainwindow.cpp \
    src/ncmdump.cpp \
    src/base64.cpp \
    src/pkcs7.cpp \
    src/qlistwidget_withdrop.cpp \
    src/unlocker.cpp \
    src/getpath.cpp \
    src/unlockrunner.cpp

HEADERS += \
    src/base64.h \
    src/mainwindow.h \
    src/ncmdump.h \
    src/pkcs7.h \
    src/qlistwidget_withdrop.h \
    src/unlocker.h \
    src/getpath.h \
    src/unlockrunner.h

FORMS += \
    ui/mainwindow.ui

#QMAKE_CXXFLAGS += \
#    -std:c++17

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32: LIBS += \
    -L$$PWD/ext/lib/ -llibssl_static \
    -L$$PWD/ext/lib/ -llibcrypto_static

INCLUDEPATH += $$PWD/ext/include
DEPENDPATH += $$PWD/ext/include

INCLUDEPATH += $$PWD/material-ui

win32:!win32-g++: PRE_TARGETDEPS += \
    $$PWD/ext/lib/libssl_static.lib \
    $$PWD/ext/lib/libcrypto_static.lib
android: include(E:/Android/android-sdk-windows/android_openssl/openssl_use_armv8.pri)

android: DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
android: include(E:/Android/android-sdk-windows/android_openssl/openssl.pri)
