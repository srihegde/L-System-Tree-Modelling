#include "mainwindow.h"
#include "ui_mainwindow.h"

int m;//for selecting shapes
int color; //for selecting colors
Modeller *mod;
using namespace cv;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}



void MainWindow::on_actionRed_triggered()
{
    color = 1;
}

void MainWindow::on_actionGreen_triggered()
{
    color = 2;
}

void MainWindow::on_actionBlue_triggered()
{
    color = 3;
}

void MainWindow::on_actionYellow_triggered()
{
    color = 4;
}

void MainWindow::on_actionDraw_triggered()
{
    m=7;
}

void MainWindow::on_actionGenerate_L_System_triggered()
{
    m=6;
}

void MainWindow::on_actionView_3D_Model_triggered()
{
    // For rules, look at the file lsysdecoder.h (starting comment).
//    String rules = " #define len 10; #define start w; w~F+[A]F-B; B~F-FF-[A]+FF; A~FF-wF++;";
    String rules = " #define len 1; #define start w; w~F[+Fw]-F[-Fw]+F";
    mod = new Modeller(ui->widget->drawnBranch, rules);


    viewer = new Viewer(this);
    viewer->show();

}

void MainWindow::on_actionClear_triggered()
{
    ui->widget->clearScreen();
}
