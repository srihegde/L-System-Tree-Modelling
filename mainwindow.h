#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "viewer.h"
#include "modeller.h"
#include "openglwidget.h"
#include "lsysdecoder.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Viewer *viewer;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();

    void on_actionRed_triggered();

    void on_actionGreen_triggered();

    void on_actionBlue_triggered();

    void on_actionYellow_triggered();

    void on_actionDraw_triggered();



    void on_actionGenerate_L_System_triggered();

    void on_actionView_3D_Model_triggered();

    void on_actionClear_triggered();

public:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
