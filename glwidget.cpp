#include "glwidget.h"
#include "shader_utils.h"
#include <QDebug>
#include <QVector>
#include <iostream>
#include "mainwindow.h"
#include <math.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <string>

using namespace cv;
using namespace std;

GLwidget::GLwidget(QWidget *parent) :
    QGLWidget(parent)
{}

extern int m;
extern int color;
float xcoll,ycoll;
GLuint program;
GLint attribute_coord2d,attribute_v_color;
GLint uniform_red,uniform_green,uniform_blue;
int w_width=0;
int w_height=0;

vector<Point> dvertices;
vector<Point> DPvertices;

string rule[100];

//vector<Branch> drawnBranch;

static int branchNumber;

void GLwidget::initializeGL(){

#ifndef __APPLE__
    GLenum glew_status = glewInit();
    if(glew_status != GLEW_OK)
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
        return;
    }
#endif

    glEnable(GL_MULTISAMPLE); //Draw smoothed polygons
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_POINT_SMOOTH);

    program = createProgram("./vshader.vs", "./fshader.fs");

//    GLenum glew_status = glewInit();
//     if (glew_status != GLEW_OK)
//     {
//       fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));

//     }

//     GLint compile_ok = GL_FALSE, link_ok = GL_FALSE;

//     GLuint vs,fs;

//     vs = create_shader("./vshader.vs",GL_VERTEX_SHADER);
//     fs = create_shader("./fshader.fs",GL_FRAGMENT_SHADER);


//     program = glCreateProgram();
//       glAttachShader(program, vs);
//       glAttachShader(program, fs);
//       glLinkProgram(program);
//       glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
//       if (!link_ok) {
//         fprintf(stderr, "glLinkProgram:");
//         print_log(program);
//      //   return 0;
//       }

       const char* attribute_name = "coord2d";
       attribute_coord2d = glGetAttribLocation(program, attribute_name);


       attribute_name = "v_color";
        attribute_v_color = glGetAttribLocation(program, attribute_name);
        if (attribute_v_color == -1) {
          qDebug() << "Could not bind attribute " << attribute_name << endl;

        }


        const char* uniform_namer;
        uniform_namer = "red";
        uniform_red = glGetUniformLocation(program, uniform_namer);

        const char* uniform_nameg;
        uniform_nameg = "green";
        uniform_green = glGetUniformLocation(program, uniform_nameg);

        const char* uniform_nameb;
        uniform_nameb = "blue";
        uniform_blue = glGetUniformLocation(program, uniform_nameb);



}

void GLwidget::paintGL() {


        glClearColor(1.0, 1.0, 1.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);


// ui->widget_2->setStyleSheet("background-color: rgba(1, 0, 0, 50%);");
        glUseProgram(program);
       // qDebug()<<"col"<<color;
        glEnableVertexAttribArray(attribute_v_color);
        if(color == 1){
            //qDebug()<<"here col"<<color;

            glUniform1f(uniform_red, 1.0);
            glUniform1f(uniform_green, 0.0);
            glUniform1f(uniform_blue, 0.0);

        }
        if(color == 2){
            //qDebug()<<"here col"<<color;

            glUniform1f(uniform_red, 0.0);
            glUniform1f(uniform_green, 1.0);
            glUniform1f(uniform_blue, 0.0);

        }
        if(color == 3){
           // qDebug()<<"here col"<<color;

            glUniform1f(uniform_red, 0.0);
            glUniform1f(uniform_green, 0.0);
            glUniform1f(uniform_blue, 1.0);

        }
        if(color == 4){
           // qDebug()<<"here col"<<color;

            glUniform1f(uniform_red, 1.0);
            glUniform1f(uniform_green, 1.0);
            glUniform1f(uniform_blue, 0.0);

        }



        glEnableVertexAttribArray(attribute_coord2d);
        /* Describe our vertices array to OpenGL (it can't guess its format automatically) */


       if(m==7){

           if( branchNumber > 0)
               drawPrevBranch();
            int size = dvertices.size();
            GLfloat quad_vertices[2*size];
           // qDebug() <<"Rendering user";
            for(int i=0;i<dvertices.size();i++){

                    float px,py;
                    px= dvertices.at(i).x;
                    py = dvertices.at(i).y;
                    float pxf,pyf;
                    pxf = -1.0 + 2*px/w_width;
                    pyf = 1- 2*py/w_height;
                    quad_vertices[2*i]=pxf;
                    quad_vertices[(2*i)+1]=pyf;


            }

            glPointSize(5.0f);

            /* Describe our vertices array to OpenGL (it can't guess its format automatically) */
            glVertexAttribPointer(
              attribute_coord2d, // attribute
              2,                 // number of elements per vertex, here (x,y)
              GL_FLOAT,          // the type of each element
              GL_FALSE,          // take our values as-is
              0,                 // no extra data between each position
              quad_vertices  // pointer to the C array
            );

            /* Push each element in buffer_vertices to the vertex shader */

            glDrawArrays(GL_POINTS, 0, size);

        }


        else if(m==8){

           if( branchNumber > 0)
               drawPrevBranch();

            int size = DPvertices.size();
            GLfloat quad_vertices[2*size];
           // qDebug() <<"Rendering user 2";
            for(int i=0;i<DPvertices.size();i++){

                float px,py;
                px= DPvertices.at(i).x;
                py = DPvertices.at(i).y;
                float pxf,pyf;
                pxf = -1.0 + 2*px/w_width;
                pyf = 1- 2*py/w_height;
                quad_vertices[2*i]=pxf;
                quad_vertices[(2*i)+1]=pyf;
            }
            glPointSize(5.0f);
            glLineWidth(5.0f);

            /* Describe our vertices array to OpenGL (it can't guess its format automatically) */
            glVertexAttribPointer(
              attribute_coord2d, // attribute
              2,                 // number of elements per vertex, here (x,y)
              GL_FLOAT,          // the type of each element
              GL_FALSE,          // take our values as-is
              0,                 // no extra data between each position
              quad_vertices  // pointer to the C array
            );

            /* Push each element in buffer_vertices to the vertex shader */
            glDrawArrays(GL_LINE_STRIP, 0, size);

        }

    /*   unsigned char pixel[4];
       glReadPixels(xcoll,ycoll,1,1,GL_RGB,GL_UNSIGNED_BYTE,pixel);
       qDebug() <<"1 R"<<(int)pixel[0]<<",G"<<(int)pixel[1]<<",B"<<(int)pixel[2];*/

        glDisableVertexAttribArray(attribute_coord2d);
        glDisableVertexAttribArray(attribute_v_color);

        glDeleteProgram(program);

}

void GLwidget::resizeGL(int w, int h) {
     glViewport(0,0,w,h);
     w_width=w;
     w_height=h;
}

void GLwidget::mousePressEvent(QMouseEvent *ev)
{

    updateGL();
    float x,y;
    x= ev->x();
    y=ev->y();
    float xf,yf;
    xf = -1.0 + 2*x/w_width;
    yf = 1- 2*y/w_height;
    xcoll =xf;
    ycoll =yf;

   // qDebug() <<x<<","<<y;
  //  qDebug() <<"m=" <<m;
    if(m==7){

        dvertices.push_back(Point2f(x, y));
    }
    else{
        qDebug() <<"Please select a shape from the menu to draw.";
    }


    if(m==7){
        qDebug()<<"draw user";
        updateGL();
    }

    if(m==6){
        qDebug()<<"-----------------Displaying the parent child relationship ---------------------";

        //00 order the childids in branch by increasing order of number of children of child ids
        for(int i=0;i<branchNumber;i++){
            if(drawnBranch[i].consider==1){

                for(int j=0;j<drawnBranch[i].childrenIds.size();j++){
                    int m =drawnBranch[i].childrenIds.at(j);
                    int min = drawnBranch[m].nChildren;
                    int pos = j;
                    for(int k=j;k<drawnBranch[i].childrenIds.size();k++){
                        int n;
                        n=drawnBranch[i].childrenIds.at(k);
                        if(drawnBranch[n].nChildren<min){
                            min = n;
                            pos =k;
                        }
                    }
                    int temp;
                    temp = drawnBranch[i].childrenIds.at(j);
                    drawnBranch[i].childrenIds[j] = drawnBranch[i].childrenIds.at(pos);
                    drawnBranch[i].childrenIds[pos]=temp;
                }

            }
        }

        //0 display parent child relation
        for(int i =0;i < branchNumber; i++){
            qDebug()<<"Branch id"<<drawnBranch[i].polyBranchId<<" has followin children:";
            for(int j =0; j<drawnBranch[i].nChildren;j++){
                qDebug()<<drawnBranch[i].childrenIds.at(j);
            }
        }


//--------------------------------------------------------------------------------------------------

        //1 get terminal ids
        vector<int> terminals;
        for(int i=0; i<branchNumber;i++){
            if(drawnBranch[i].nChildren==0)
                terminals.push_back(drawnBranch[i].polyBranchId);
        }
        //2 replace terminals
        for(int i=0; i<branchNumber;i++){
            for(int j=0;j<drawnBranch[i].childrenIds.size();j++){
                for(int k=0;k<terminals.size();k++){
                    if(drawnBranch[i].childrenIds.at(j)==terminals.at(k)){
                        drawnBranch[i].childrenIds[j] = 999;
                        break;
                    }
                }
            }
        }


 //------------------------------------------------------------------------------------------------
        //3 find redundant production & replace
        qDebug()<<"-------step 2 After finding redundant production & replacing them- preprocessing--------------";
       int redundant = 0;
        for(int i=0; i<branchNumber;i++){
            for(int j=i+1; j<branchNumber;j++){
                if(drawnBranch[i].nChildren == drawnBranch[j].nChildren){

                    for(int k=0;k<drawnBranch[i].nChildren;k++){
                        if(drawnBranch[i].childrenIds.at(k)==drawnBranch[j].childrenIds.at(k) && drawnBranch[i].childrenIds.at(k)==999)
                            redundant = 1;
                        else{
                            redundant = 0;
                            break;
                        }
                    }
                }
                if(redundant == 1){
                    drawnBranch[i].consider = 0;
                    redundant = 0;
                    replacebyEqui(drawnBranch[i].polyBranchId,drawnBranch[j].polyBranchId);
                }
            }
        }

        for(int i =0;i < branchNumber; i++){
            if(drawnBranch[i].consider == 1){
                qDebug()<<"Branch id"<<drawnBranch[i].polyBranchId<<" has followin children:";
                for(int j =0; j<drawnBranch[i].nChildren;j++){
                    qDebug()<<drawnBranch[i].childrenIds.at(j);
                }
            }
        }


//-----------------------------------------------------------------------------------------------------
         //4 identify similar structures
        //4a don't consider terminal productions
        qDebug()<<"-------------Identifying the similar structures in the drawn tree -------------";
        for(int i=0;i<branchNumber;i++){
            if(drawnBranch[i].nChildren==0)
                drawnBranch[i].consider=0;
        }


        //4b find similar structure
       for(int i=0; i<branchNumber;i++){
            if(drawnBranch[i].consider==1 && drawnBranch[i].visited==0){
                for(int j = 0; j<branchNumber ; j++){
                    if(drawnBranch[j].consider == 1 && drawnBranch[j].visited==0){
                        bool similar = false;
                        if(drawnBranch[i].nChildren == drawnBranch[j].nChildren && i!=j ) {
                            qDebug()<<"test"<<i<<","<<j;
                            similar = test(i,j);
                            if(similar == true){
                                drawnBranch[j].similarBranchIds.push_back(i);
                                drawnBranch[j].visited=1;
                                drawnBranch[i].visited=1;
                            }

                        }
                    }
                }
            }
        }

         for(int i =0;i < branchNumber; i++){
            if(drawnBranch[i].consider == 1){
                qDebug()<<"Branch id"<<drawnBranch[i].polyBranchId<<" has followin similar branches:";
                for(int j =0; j<drawnBranch[i].similarBranchIds.size();j++){
                    qDebug()<<drawnBranch[i].similarBranchIds.at(j);
                }
            }
        }
//------------------------------------------------------------------------------------------------
         //final step of lsystem deduction- replacement on basis of similar structures found in tree
         //5b don't consider similar branches
        for(int i=0;i<branchNumber;i++){
            if(drawnBranch[i].consider == 1 && drawnBranch[i].similarBranchIds.size()!=0){
                replacebyEqui(i,drawnBranch[i].similarBranchIds.at(0));
                drawnBranch[i].consider=0;
            }
        }
        qDebug()<<"-----------------Lsystem rules are-----------------------------------------";

                for(int i =0;i < branchNumber; i++){
                    if(drawnBranch[i].consider == 1){

                        //qDebug()<<"Branch id"<<char(drawnBranch[i].polyBranchId+65+5)<<" goes to ->:";
                        rule[i] = rule[i]+char(drawnBranch[i].polyBranchId+65+5);

//                        symbol_lsys++;
                        rule[i] = rule[i] + "->";

                        for(int j =0; j<drawnBranch[i].nChildren;j++){
                            if(drawnBranch[i].childrenIds.at(j) == 999)
                                drawnBranch[i].childrenIds[j] = 0;
                           // qDebug()<<char(drawnBranch[i].childrenIds.at(j)+65+5);

                            rule[i] = rule[i] + "[";
                            rule[i] = rule[i] +char(drawnBranch[i].childrenIds.at(j)+65+5);
                            rule[i] = rule[i] +"]";
                        }
                    }
                }

                QDebug debug = qDebug();
                for(int i =0;i < branchNumber; i++){
                    debug<<"R"<<i<<":";
                    for(int j =0; j<rule[i].size();j++){
                        if(drawnBranch[i].consider == 1)
                            debug<<rule[i].at(j);
                    }
                    debug<<" , ";
                }
//-------------------------------------------------------------------------------------------------------
    }

}

void GLwidget::mouseMoveEvent(QMouseEvent *ev)
{
    float x,y;
    x= ev->x();
    y=ev->y();
 //   qDebug() <<x<<","<<y;

    dvertices.push_back(Point2f(x, y));
    updateGL();


}

void GLwidget::mouseReleaseEvent(QMouseEvent *ev)
{
    if(m==7){
    m=8;

    qDebug()<<"dvertices size="<<dvertices.size();
    cv::approxPolyDP(dvertices, DPvertices, 2, false);
    qDebug()<<"DPvertices size="<<DPvertices.size();
  /*  for(int i =0;i<DPvertices.size();i++){
        float px,py;
        px= DPvertices.at(i).x;
        py = DPvertices.at(i).y;
        qDebug()<<"px"<<px;
        qDebug()<<"py"<<DPvertices.at(i).y;
    }*/
/*    for(int i =0;i<dvertices.size();i++){
        float px,py;
        px= dvertices.at(i).x;
        py = dvertices.at(i).y;
        qDebug()<<"px"<<px;
        qDebug()<<"py"<<dvertices.at(i).y;
    }*/

    drawnBranch[branchNumber].polyBranch=DPvertices;
    drawnBranch[branchNumber].polyBranchId=branchNumber;
    drawnBranch[branchNumber].polyBranchSize=drawnBranch[branchNumber].polyBranch.size();
    ++branchNumber;
    if(branchNumber>1)
        findParent(DPvertices.at(0).x, DPvertices.at(0).y);
    updateGL();
    qDebug()<<"now  releasing";
    m=7;

    dvertices.clear();
}
}

void GLwidget::drawPrevBranch()
{
    for(int k=0;k<branchNumber;k++){
        vector<Point> branch_k;
        branch_k = drawnBranch[k].polyBranch;
        int size = drawnBranch[k].polyBranchSize;
        GLfloat branch_points[2*size];
        for(int i=0;i<branch_k.size();i++){

            float px,py;
            px= branch_k.at(i).x;
            py = branch_k.at(i).y;
            float pxf,pyf;
            pxf = -1.0 + 2*px/w_width;
            pyf = 1- 2*py/w_height;
            branch_points[2*i]=pxf;
            branch_points[(2*i)+1]=pyf;
        }
        drawPolyBranch_k(branch_points,size);
    }
}

void GLwidget::drawPolyBranch_k(GLfloat branch_points[], int size)
{
    glPointSize(5.0f);
    glLineWidth(5.0f);

    /* Describe our vertices array to OpenGL (it can't guess its format automatically) */
    glVertexAttribPointer(
      attribute_coord2d, // attribute
      2,                 // number of elements per vertex, here (x,y)
      GL_FLOAT,          // the type of each element
      GL_FALSE,          // take our values as-is
      0,                 // no extra data between each position
      branch_points  // pointer to the C array
    );

    /* Push each element in buffer_vertices to the vertex shader */
    glDrawArrays(GL_LINE_STRIP, 0, size);
}

void GLwidget::findParent(float x0, float y0)
{
    float xnew,ynew,xfnew,yfnew,a,b,c;
    vector<float> potentialmindist;
    vector<int> coreepondingParent;
    int pos = 0;
    int subpos=0;
    float d = 0.0f;
    float min = 20.0f;
    float min1 = 10.0f;
    float min2 = 10.0f;
    float d1,d2;

    for(int k=0;k<branchNumber-1;k++){
        vector<Point> branch_k;
        branch_k = drawnBranch[k].polyBranch;

        for(int i=0;i<branch_k.size()-1;i++){

            float x1,y1,x2,y2;
            x1 = branch_k.at(i).x;
            y1 = branch_k.at(i).y;
            x2 = branch_k.at(i+1).x;
            y2 = branch_k.at(i+1).y;
            d = (abs((y2-y1)*x0 - (x2-x1)*y0 + x2*y1 - y2*x1))/(sqrt(pow((y2-y1),2)+pow((x2-x1),2)));
            //d1 = sqrt(pow((x2-x0),2)+pow((y2-y0),2));
            //d2 = d1+d;
          //  qDebug ()<<"distance of point from line "<<k<<" & segment "<<i<<" = "<<d;
          //  if(x0<(x1+5.0f) && x0>(x1-5.0f) && y0<(y1+5.0f) && y0<(y1-5.0f)){
            if(d<min){
                    min = d;
                    pos = k;
                    subpos = i;
            }
           // }

        }

    }



    float x1,y1,x2,y2;
    x1 = drawnBranch[pos].polyBranch.at(subpos).x;
    y1 = drawnBranch[pos].polyBranch.at(subpos).y;
    x2 = drawnBranch[pos].polyBranch.at(subpos+1).x;
    y2 = drawnBranch[pos].polyBranch.at(subpos+1).y;
    a = y2-y1;
    b = x1-x2;
    c = y1*(x2-x1) - x1*(y2-y1);
    xnew = (b*(b*x0 - a*y0) - a*c) /(pow(a,2)+pow(b,2));
    ynew = (a*(-b*x0 + a*y0) - b*c) /(pow(a,2)+pow(b,2));
    qDebug ()<<"d="<<d;
    qDebug ()<<"parent point is: "<<x1<<","<<y1<<"; "<<x2 <<","<<y2;
    qDebug ()<<"old point is:"<<x0<<","<<y0;
   // qDebug ()<<"New point is: "<<xnew<<","<<ynew;

    qDebug()<<pos<<"parent of"<<branchNumber-1;
    drawnBranch[branchNumber-1].parentId = pos;
    drawnBranch[pos].nChildren = drawnBranch[pos].nChildren + 1;
    drawnBranch[pos].childrenIds.push_back(branchNumber-1);

}

void GLwidget::replacebyEqui(int find, int replace)
{
    for(int i=0; i<branchNumber;i++){
        for(int j=0;j<drawnBranch[i].childrenIds.size();j++){
            if(drawnBranch[i].childrenIds.at(j) == find)
                drawnBranch[i].childrenIds[j] = replace;
        }
    }
}

bool GLwidget::test(int i, int j)
{
    qDebug()<<"testrec"<<i<<","<<j;
    if(i == 999 || j == 999)
        return true;
    else if(drawnBranch[i].nChildren ==0 || drawnBranch[j].nChildren == 0)
        return true;
    else if (drawnBranch[i].nChildren != drawnBranch[j].nChildren)
        return false;
    else if(drawnBranch[i].nChildren == drawnBranch[j].nChildren){
        bool x =false;
        for(int k=0; k< drawnBranch[i].nChildren; k++){
            x = test(drawnBranch[i].childrenIds.at(k),drawnBranch[j].childrenIds.at(k));
            if(x==false)
                break;

        }
        return x;
    }
}

void GLwidget::replacebySimi(int find, int replace)
{

}

void GLwidget::clearScreen()
{
    update();
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    memset(drawnBranch, 0, sizeof(drawnBranch));
    update();
}
