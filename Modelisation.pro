QT += core gui opengl
win32 {
    LIBS += -LC:\QtCreator\5.9.1\mingw53_32\lib\libQt5OpenGL.a -lopengl32
}

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#LIBS += -L extern\x86_64-w64-mingw32\lib  -lmingw32 -mwindows -mconsole -lSDL2main -lSDL2
#INCLUDEPATH += extern\x86_64-w64-mingw32\include


SOURCES += main.cpp \
    noisef.cpp \
    vec.cpp \
 #   image.cpp \
 #   image_io.cpp \
 #   color.cpp \
    heightField.cpp \
    layerField.cpp \
    scalarField.cpp \
    box2.cpp \
    array2.cpp \
    gldisplay.cpp \
    mainwindow.cpp

HEADERS += \
    noisef.h \
    vec.h \
  #  image.h \
  #  image_io.h \
  #  color.h \
    heightField.h \
    layerField.h \
    scalarField.h \
    box2.h \
    array2.h \
    gldisplay.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

DISTFILES +=
