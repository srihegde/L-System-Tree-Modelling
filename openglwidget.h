/*References
  Trackball: http://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Arcball
*/

#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <stdio.h>
#include <stdlib.h>
#include <vector>

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glu.h>
#else
#include <GL/glew.h>
#include <GL/glu.h>
#endif

#include "shader_utils.h"
#include "gl_utils.h"

#define GLM_FORCE_RADIANS
#define GLM_SWIZZLE
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <QGLWidget>
#include <QMouseEvent>
#include <vector>

#define SIZE 1000000

class OpenGLWidget : public QGLWidget
{
public:
    OpenGLWidget(QWidget *parent) : QGLWidget(parent) {}
    ~OpenGLWidget();
    void setNodeInfo(std::vector<float> nodes);
    void zoomIn();
    void zoomOut();

    int stat;

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void setupModelTransformation();
    void setupViewTransformation();
    void setupProjectionTransformation();

    void createTree();
    void create3DTree();
    void drawGenCylinder(glm::vec3 c1, glm::vec3 c2, float r1, float r2);
    void drawSphere(glm::vec3 c, float r);
    void setupLighting();

    void mouseMoveEvent(QMouseEvent *mev);
    void mousePressEvent(QMouseEvent *mev);
    void mouseReleaseEvent(QMouseEvent *mev);
    glm::vec3 getTrackBallVector(int x, int y);
    void onIdle();


private:
    GLuint program;
    GLint vVertex_attrib, vColor_attrib, vNormal_attrib;
    GLint vModel_uniform, vView_uniform, vProjection_uniform, vLightPosition_uniform, vLightPosition1_uniform;
    int screen_width, screen_height;

    GLuint cube_VAO; //Vertex array object for cube
    std::vector<float> nodeInfo;
    float zoomVal;
    GLfloat tree_nodes[SIZE], normal_nodes[SIZE];
};

#endif // OPENGLWIDGET_H
