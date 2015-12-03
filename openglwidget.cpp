#include "openglwidget.h"

#define SIZE 10000

//Globals
int oldX, oldY, currentX, currentY, nodes, k;
bool isDragging=false;


glm::mat4 modelT, viewT, projectionT;//The model, view and projection transformations

OpenGLWidget::~OpenGLWidget()
{
    glDeleteProgram(program);
}


// Passing information of nodes here.
void OpenGLWidget::setNodeInfo(std::vector<float> nodes)
{
    nodeInfo = nodes;
    for (int i = 0; i < nodeInfo.size(); i+=3)
    {
        nodeInfo[i] = (2*nodeInfo[i]/(screen_width) - 1);
        nodeInfo[i+1] = (1 - 2*nodeInfo[i+1]/(screen_height));
        nodeInfo[i+2] = (2*nodeInfo[i+2]/(screen_width) - 1);

    }
}

void OpenGLWidget::zoomIn()
{
    zoomVal -= 5.0f;
    viewT = glm::lookAt(glm::vec3(0.0, 0.0, zoomVal), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
    glUniformMatrix4fv(vView_uniform, 1, GL_FALSE, glm::value_ptr(viewT));
}

void OpenGLWidget::zoomOut()
{
    zoomVal += 5.0f;
    viewT = glm::lookAt(glm::vec3(0.0, 0.0, zoomVal), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
    glUniformMatrix4fv(vView_uniform, 1, GL_FALSE, glm::value_ptr(viewT));

}



void OpenGLWidget::initializeGL()
{
#ifndef __APPLE__
    GLenum glew_status = glewInit();
    if(glew_status != GLEW_OK)
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
        return;
    }
#endif
//    initializeOpenGLFunctions();
    //Enable certain OpenGL states
    glEnable(GL_DEPTH_TEST); //Enable Z-buffer
    glEnable(GL_MULTISAMPLE); //Draw smoothed polygons
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_POINT_SMOOTH);

    //Create program
    program = createProgram("./vshader_1.vs", "./fshader_1.fs");

    screen_width = this->size().width();
    screen_height = this->size().height();
//    fprintf(stderr, "W: %d, H: %d\n", screen_width, screen_height);


    //Create cube VAO
    createTree();

    //Setup Transformations
    setupModelTransformation();
    setupViewTransformation();
    setupProjectionTransformation();
}

void OpenGLWidget::resizeGL(int w, int h)
{
    screen_width = w;
    screen_height = h;
    glViewport(0, 0, screen_width, screen_height);
    setupProjectionTransformation();// Redo projection matrix
}

void OpenGLWidget::paintGL()
{
    /* Clear the background as white */
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //printOpenGLError();
    glUseProgram(program);
    glBindVertexArray(cube_VAO);
    onIdle();
    update();
    glDrawArrays(GL_LINES, 0, 3*k);
    glBindVertexArray(0);
}



void OpenGLWidget::setupModelTransformation()
{
    //Modelling transformations (Model -> World coordinates)
    modelT = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.0));//Model coordinates are the world coordinates

    //Pass on the modelling matrix to the vertex shader
    glUseProgram(program);
    vModel_uniform = glGetUniformLocation(program, "vModel");
    if(vModel_uniform == -1){
        fprintf(stderr, "Could not bind location: vModel\n");
        exit(0);
    }
    glUniformMatrix4fv(vModel_uniform, 1, GL_FALSE, glm::value_ptr(modelT));
}

void OpenGLWidget::setupViewTransformation()
{
    zoomVal = 40.0f;
    //Viewing transformations (World -> Camera coordinates
    viewT = glm::lookAt(glm::vec3(0.0, 0.0, zoomVal), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
    //Camera at (0, 0, 20) looking down the negative Z-axis in a right handed coordinate system

    //Pass on the viewing matrix to the vertex shader
    glUseProgram(program);
    vView_uniform = glGetUniformLocation(program, "vView");
    if(vView_uniform == -1){
        fprintf(stderr, "Could not bind location: vView\n");
        exit(0);
    }
    glUniformMatrix4fv(vView_uniform, 1, GL_FALSE, glm::value_ptr(viewT));
}

void OpenGLWidget::setupProjectionTransformation()
{
    //Projection transformation (Orthographic projection)
    float aspect = (float)screen_width/(float)screen_height;
    float view_height = 100.0f;
    //glm::mat4 projection = glm::ortho(-view_height*aspect/2.0f, view_height*aspect/2.0f, -view_height/2.0f, view_height/2.0f, 0.1f, 1000.0f);
    glm::mat4 projectionT = glm::perspective(45.0f, aspect, 0.1f, 1000.0f);

    //Pass on the projection matrix to the vertex shader
    glUseProgram(program);
    vProjection_uniform = glGetUniformLocation(program, "vProjection");
    if(vProjection_uniform == -1){
        fprintf(stderr, "Could not bind location: vProjection\n");
        exit(0);
    }
    glUniformMatrix4fv(vProjection_uniform, 1, GL_FALSE, glm::value_ptr(projectionT));
}


void OpenGLWidget::createTree()
{
    glUseProgram(program);

    //Bind shader variables
    vVertex_attrib = glGetAttribLocation(program, "vVertex");
    if(vVertex_attrib == -1) {
        fprintf(stderr, "Could not bind location: vVertex\n");
        exit(0);
    }
    vColor_attrib = glGetAttribLocation(program, "vColor");
    if(vColor_attrib == -1) {
        fprintf(stderr, "Could not bind location: vColor\n");
        exit(0);
    }

    //Tree data
    printf("Reading nodes...\n");

    FILE *f = fopen("./output.txt", "r");
    fscanf(f,"%d",&nodes);
//    printf("%d\n",nodes);

    GLfloat tree_nodes[SIZE],x,y,z;
    int pts;
    k = 0;

    fprintf(stderr, "W: %d, H: %d\n", screen_width, screen_height);

//    fscanf(f,"%f %f %f",&x, &y, &z);
    // Setting node information
    for (int i = 0; i < nodes; i++)
    {
        fscanf(f,"%d",&pts);
        for (int j = 0; j < pts; ++j) {
            fscanf(f,"%f %f %f",&x, &y, &z);

            tree_nodes[k++] = (2*x/(float)(screen_width) - 1) * 10.0f;
            tree_nodes[k++] = (1 - 2*y/(float)(screen_height)) * 10.0f;
            tree_nodes[k++] = (2*z/(float)(screen_width) - 1) * 10.0f;   // Assuming the depth of the bounding box is same as width.
        }
    }

    glLineWidth(4.0f);

    // For Debugging
//    printf("%d", k);
//    for (int i = 0; i < k; i+=3)
//    {
//        printf("%f %f %f\n",tree_nodes[i], tree_nodes[i+1], tree_nodes[i+2]);
//    }

    // Setting color information
    GLfloat tree_color[SIZE] = {0};
    for (int i = 0; i < 3*k; i+=3)
    {
        tree_color[i] = 0.3;
        tree_color[i+1] = 0.6;
        tree_color[i+2] = 0.2;
    }

    // Creating and binding VBOs
    glGenVertexArrays(1, &cube_VAO);
    glBindVertexArray(cube_VAO);


    GLuint vertex_VBO;
    glGenBuffers(1, &vertex_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_VBO);
    glBufferData(GL_ARRAY_BUFFER, 3*k*sizeof(GLfloat), tree_nodes, GL_STATIC_DRAW);
    glEnableVertexAttribArray(vVertex_attrib);
    glVertexAttribPointer(vVertex_attrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

    GLuint color_VBO;
    glGenBuffers(1, &color_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, color_VBO);
    glBufferData(GL_ARRAY_BUFFER, 3*k*sizeof(GLfloat), tree_color, GL_STATIC_DRAW);
    glEnableVertexAttribArray(vColor_attrib);
    glVertexAttribPointer(vColor_attrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    fclose(f);

}


void OpenGLWidget::setupLighting()
{
//    float light_position[] = {100, 50, 0};

//    glUseProgram(program);
//    vLightPosition_uniform = glGetUniformLocation(program, "vLightPosition");
//    if(vLightPosition_uniform == -1)
//    {
//        fprintf(stderr, "Could not bind uniform: vLightPosition\n");
//        exit(0);
//    }
//    glUniform3f(vLightPosition_uniform, light_position[0], light_position[1], light_position[2]);
}

glm::vec3 OpenGLWidget::getTrackBallVector(int x, int y)
{
    glm::vec3 p = glm::vec3(2.0*x/screen_width - 1.0, 2.0*y/screen_height - 1.0, 0.0); //Normalize to [-1, +1]
    p.y = -p.y; //Invert Y since screen coordinate and OpenGL coordinates have different Y directions.
    float mag2 = p.x*p.x + p.y*p.y;
    if(mag2 <= 1.0)
        p.z = sqrt(1.0 - mag2);
    else
        p = glm::normalize(p); //Nearest point, close to the sides of the trackball
    return p;
}

void OpenGLWidget::onIdle()
{
    if(currentX !=oldX || currentY != oldY)
    {
        glm::vec3 va = getTrackBallVector(oldX, oldY);
        glm::vec3 vb = getTrackBallVector(currentX, currentY);
        float angle = acos(fmin(1.0f, glm::dot(va, vb)));
        glm::vec3 axis_in_camera_coord = glm::cross(va, vb);
        glm::mat3 camera2object = glm::inverse(glm::mat3(viewT*modelT));
        glm::vec3 axis_in_object_coord = camera2object * axis_in_camera_coord;
        modelT = glm::rotate(modelT, angle, axis_in_object_coord);
        glUniformMatrix4fv(vModel_uniform, 1, GL_FALSE, glm::value_ptr(modelT));
        oldX = currentX;
        oldY = currentY;
        update();
    }
}


void OpenGLWidget::mouseMoveEvent(QMouseEvent *mev)
{
    if(isDragging)
    {
        currentX = mev->x();
        currentY = mev->y();
    }
}

void OpenGLWidget::mousePressEvent(QMouseEvent *mev)
{
    isDragging = true;
    currentX = oldX = mev->x();
    currentY = oldY = mev->y();
}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent *mev)
{
    isDragging = false;
}
