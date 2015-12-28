/********************************************************************************
** Form generated from reading UI file 'viewer.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWER_H
#define UI_VIEWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "openglwidget.h"

QT_BEGIN_NAMESPACE

class Ui_Viewer
{
public:
    QAction *actionZoom_In;
    QAction *actionZoom_Out;
    QAction *actionView_3D;
    QAction *actionShow_Skeleton;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    OpenGLWidget *widget;
    QMenuBar *menubar;
    QMenu *menuView;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Viewer)
    {
        if (Viewer->objectName().isEmpty())
            Viewer->setObjectName(QStringLiteral("Viewer"));
        Viewer->resize(800, 600);
        Viewer->setCursor(QCursor(Qt::OpenHandCursor));
        actionZoom_In = new QAction(Viewer);
        actionZoom_In->setObjectName(QStringLiteral("actionZoom_In"));
        actionZoom_Out = new QAction(Viewer);
        actionZoom_Out->setObjectName(QStringLiteral("actionZoom_Out"));
        actionView_3D = new QAction(Viewer);
        actionView_3D->setObjectName(QStringLiteral("actionView_3D"));
        actionShow_Skeleton = new QAction(Viewer);
        actionShow_Skeleton->setObjectName(QStringLiteral("actionShow_Skeleton"));
        centralwidget = new QWidget(Viewer);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        widget = new OpenGLWidget(centralwidget);
        widget->setObjectName(QStringLiteral("widget"));

        horizontalLayout->addWidget(widget);

        Viewer->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Viewer);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 25));
        menuView = new QMenu(menubar);
        menuView->setObjectName(QStringLiteral("menuView"));
        Viewer->setMenuBar(menubar);
        statusbar = new QStatusBar(Viewer);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        Viewer->setStatusBar(statusbar);

        menubar->addAction(menuView->menuAction());
        menuView->addAction(actionZoom_In);
        menuView->addAction(actionZoom_Out);
        menuView->addAction(actionShow_Skeleton);
        menuView->addAction(actionView_3D);

        retranslateUi(Viewer);

        QMetaObject::connectSlotsByName(Viewer);
    } // setupUi

    void retranslateUi(QMainWindow *Viewer)
    {
        Viewer->setWindowTitle(QApplication::translate("Viewer", "Viewer", 0));
        actionZoom_In->setText(QApplication::translate("Viewer", "Zoom In", 0));
        actionZoom_In->setShortcut(QApplication::translate("Viewer", "Ctrl+Up", 0));
        actionZoom_Out->setText(QApplication::translate("Viewer", "Zoom Out", 0));
        actionZoom_Out->setShortcut(QApplication::translate("Viewer", "Ctrl+Down", 0));
        actionView_3D->setText(QApplication::translate("Viewer", "View 3D", 0));
        actionView_3D->setShortcut(QApplication::translate("Viewer", "Shift+S", 0));
        actionShow_Skeleton->setText(QApplication::translate("Viewer", "Show Skeleton", 0));
        actionShow_Skeleton->setShortcut(QApplication::translate("Viewer", "Space", 0));
        menuView->setTitle(QApplication::translate("Viewer", "View", 0));
    } // retranslateUi

};

namespace Ui {
    class Viewer: public Ui_Viewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWER_H
