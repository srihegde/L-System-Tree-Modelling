/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

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
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "glwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QAction *actionTriangle;
    QAction *actionLine;
    QAction *actionPentagon;
    QAction *actionQuad;
    QAction *actionCircle;
    QAction *actionRed;
    QAction *actionGreen;
    QAction *actionBlue;
    QAction *actionYellow;
    QAction *actionDraw;
    QAction *actionGenerate_L_System;
    QAction *actionView_3D_Model;
    QAction *actionClear;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    GLwidget *widget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuShapes;
    QMenu *menuColors;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(600, 500);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionTriangle = new QAction(MainWindow);
        actionTriangle->setObjectName(QStringLiteral("actionTriangle"));
        actionLine = new QAction(MainWindow);
        actionLine->setObjectName(QStringLiteral("actionLine"));
        actionPentagon = new QAction(MainWindow);
        actionPentagon->setObjectName(QStringLiteral("actionPentagon"));
        actionQuad = new QAction(MainWindow);
        actionQuad->setObjectName(QStringLiteral("actionQuad"));
        actionCircle = new QAction(MainWindow);
        actionCircle->setObjectName(QStringLiteral("actionCircle"));
        actionRed = new QAction(MainWindow);
        actionRed->setObjectName(QStringLiteral("actionRed"));
        actionGreen = new QAction(MainWindow);
        actionGreen->setObjectName(QStringLiteral("actionGreen"));
        actionBlue = new QAction(MainWindow);
        actionBlue->setObjectName(QStringLiteral("actionBlue"));
        actionYellow = new QAction(MainWindow);
        actionYellow->setObjectName(QStringLiteral("actionYellow"));
        actionDraw = new QAction(MainWindow);
        actionDraw->setObjectName(QStringLiteral("actionDraw"));
        actionGenerate_L_System = new QAction(MainWindow);
        actionGenerate_L_System->setObjectName(QStringLiteral("actionGenerate_L_System"));
        actionView_3D_Model = new QAction(MainWindow);
        actionView_3D_Model->setObjectName(QStringLiteral("actionView_3D_Model"));
        actionClear = new QAction(MainWindow);
        actionClear->setObjectName(QStringLiteral("actionClear"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        widget = new GLwidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setCursor(QCursor(Qt::CrossCursor));
        widget->setStyleSheet(QStringLiteral("background-color: rgb(206, 45, 45);"));

        horizontalLayout->addWidget(widget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 25));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuShapes = new QMenu(menuBar);
        menuShapes->setObjectName(QStringLiteral("menuShapes"));
        menuColors = new QMenu(menuBar);
        menuColors->setObjectName(QStringLiteral("menuColors"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuShapes->menuAction());
        menuBar->addAction(menuColors->menuAction());
        menuFile->addAction(actionExit);
        menuShapes->addAction(actionDraw);
        menuShapes->addAction(actionGenerate_L_System);
        menuShapes->addAction(actionView_3D_Model);
        menuShapes->addAction(actionClear);
        menuColors->addAction(actionRed);
        menuColors->addAction(actionGreen);
        menuColors->addAction(actionBlue);
        menuColors->addAction(actionYellow);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "TreeModeler", 0));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0));
        actionTriangle->setText(QApplication::translate("MainWindow", "Triangle", 0));
        actionLine->setText(QApplication::translate("MainWindow", "Line", 0));
        actionPentagon->setText(QApplication::translate("MainWindow", "Pentagon", 0));
        actionQuad->setText(QApplication::translate("MainWindow", "Quad", 0));
        actionCircle->setText(QApplication::translate("MainWindow", "Circle", 0));
        actionRed->setText(QApplication::translate("MainWindow", "Red", 0));
        actionGreen->setText(QApplication::translate("MainWindow", "Green", 0));
        actionBlue->setText(QApplication::translate("MainWindow", "Blue", 0));
        actionYellow->setText(QApplication::translate("MainWindow", "Yellow", 0));
        actionDraw->setText(QApplication::translate("MainWindow", "Draw", 0));
        actionGenerate_L_System->setText(QApplication::translate("MainWindow", "Generate L System", 0));
        actionView_3D_Model->setText(QApplication::translate("MainWindow", "View 3D Model", 0));
        actionClear->setText(QApplication::translate("MainWindow", "Clear", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuShapes->setTitle(QApplication::translate("MainWindow", "Edit", 0));
        menuColors->setTitle(QApplication::translate("MainWindow", "Colors", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
