include(3rdparty/QtGifImage/src/gifimage/qtgifimage.pri)

QT       += core gui widgets opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 warn_off

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    model/camera3D.cpp \
    model/settings.cpp \
    model/object3D.cpp \
    model/s21_matrix_oop.cpp \
    view/mainwindow.cpp \
    view/openGLWidget.cpp

HEADERS += \
    model/adapter.h \
    model/camera3D.h \
    model/object3D.h \
    model/s21_matrix_oop.h \
    model/settings.h \
    view/gifmaker.h \
    view/mainwindow.h \
    view/openGLWidget.h \
    controller/controller.h

FORMS += \
    view/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    icons.qrc \
    shaders.qrc \
    textures.qrc
