include(3rdparty/QtGifImage/src/gifimage/qtgifimage.pri)

QT       += core gui widgets opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#LIBS += -lopengl32

CONFIG += c++17 warn_off

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    controller/controller.cpp \
    main.cpp \
    model/groupObject3D.cpp \
    model/object3D.cpp \
    model/settings/drawSetting.cpp \
    model/settings/groupSetting.cpp \
    model/settings/lightSetting.cpp \
    view/camera3D.cpp \
    view/mainwindow.cpp \
    view/openGLWidget.cpp

HEADERS += \
    memento/memento.h \
    memento/state.h \
    model/groupObject3D.h \
    model/infoObject3D.h \
    model/loaderObjFile.h \
    model/object3D.h \
    model/settings/defaultDrawSetting.h \
    model/settings/defaultLightSetting.h \
    model/settings/defaultMainSetting.h \
    model/settings/defineSetting.h \
    model/settings/drawSetting.h \
    model/settings/groupSetting.h \
    model/settings/lightSetting.h \
    model/vertexData.h \
    view/camera3D.h \
    view/gifmaker.h \
    view/mainwindow.h \
    view/openGLWidget.h \
    controller/controller.h

FORMS += \
    view/mainwindow.ui

# Default rules for deployment
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    icons.qrc \
    shaders.qrc \
    textures.qrc


ICON += icon.png

win32:RC_FILE = icon.rc
