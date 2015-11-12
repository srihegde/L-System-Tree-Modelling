#ifndef GLWIDGET_H
#define GLWIDGET_H
#include <GL/glew.h>
#include <QGLWidget>

#include <stdio.h>
#include "branch.h"

#include <QEvent>
#include <QMouseEvent>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace cv;
using namespace std;
class GLwidget : public QGLWidget
{
    Q_OBJECT
protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);

public:
    explicit GLwidget(QWidget *parent = 0);

    Branch drawnBranch[100];

    void drawPrevBranch();
    void drawPolyBranch_k(GLfloat branch_points[],int size);
    void findParent(float childx, float childy);
    void replacebyEqui(int find, int replace);
    bool test(int i, int j);
    void replacebySimi(int find, int replace);
    void clearScreen();
};

#endif // GLWIDGET_H
