#include "viewer.h"
#include "ui_viewer.h"

Viewer::Viewer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Viewer)
{
    ui->setupUi(this);
}

Viewer::~Viewer()
{
    delete ui;
}

void Viewer::setPoints(std::vector<float> nodes)
{
    ui->widget->setNodeInfo(nodes);
}


void Viewer::on_actionZoom_In_triggered()
{
    ui->widget->zoomIn();
}

void Viewer::on_actionZoom_Out_triggered()
{
    ui->widget->zoomOut();
}
