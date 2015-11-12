#-------------------------------------------------
#
# Project created by QtCreator 2015-10-29T13:44:07
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TreeModeler
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
    glwidget.cpp \
    shader_utils.cpp \
    branch.cpp \
    viewer.cpp \
    openglwidget.cpp \
    gl_utils.cpp \
    modeller.cpp

HEADERS  += mainwindow.h\
    glwidget.h \
    shader_utils.h\
    branch.h \
    viewer.h \
    openglwidget.h \
    gl_utils.h \
    modeller.h

FORMS    += mainwindow.ui \
    viewer.ui

INCLUDEPATH += "/usr/local/include/"


LIBS+=-lGL \
      -lGLEW \
       `pkg-config opencv --libs`

OTHER_FILES += \
    vshader.vs \
    fshader.fs \
    vshader_1.vs \
    fshader_1.fs \
    output.txt
