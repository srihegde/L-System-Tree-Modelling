#ifndef VIEWER_H
#define VIEWER_H

#include <QMainWindow>
#include <vector>

namespace Ui {
class Viewer;
}

class Viewer : public QMainWindow
{
    Q_OBJECT

public:
    explicit Viewer(QWidget *parent = 0);
    ~Viewer();
    void setPoints(std::vector<float> nodes);

private:
    Ui::Viewer *ui;
};

#endif // VIEWER_H
