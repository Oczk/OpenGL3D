#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <GL/glu.h>

#include <QtOpenGL>
#include <QtWidgets>

#include <QApplication>
#include <QGLWidget>
#include <QKeyEvent>
#include <QImage>
#include <QTimer>

typedef GLfloat vec3f[3];

class MyGLWidget : public QGLWidget {
  Q_OBJECT

 public:
  MyGLWidget(QGLWidget* parent = 0);
  ~MyGLWidget();

  void initializeGL();
  void paintGL();
  void resizeGL();
  void timerEvent(QTimerEvent* e);
  void keyPressEvent(QKeyEvent* e);

  QImage terrain;
  void cross(GLfloat n[3], GLfloat v1[3], GLfloat v2[3]);
  void normalize(GLfloat v[3]);
  void calculateNormals(vec3f vertices[], GLfloat normal1[3], GLfloat normal2[3]);
  float div = 9;
  float h1, h2, h3, h4;

  GLfloat av[3], bv[3];

  GLuint *tex = new GLuint[7];
  QImage texture1;
  QImage *skybox = new QImage[6];

    GLuint texHandle[3];

    void createSkybox();
    void drawCube();

  float ambient[3] = {1.1, 1.1, 1.08};
  float diffuse[3] = {2.0, 2.0, 1.96};
  float specular[3] = {2.0, 2.0, 1.96};
  float position[3] = {50.0, 15.0, 50.0};


  float posX = -0;
  float posY =-50;
  float posZ = -50;
  float rotationX = 118.5;
  float rotationY = 20;

  const float forwardSpeed = 0.5;
  const int forward = 1;
  const float sideSpeed = 0.1;
  const int side = 0;

  const float rotation = 1.0;
  const int rotationLeft = -1;
  const int rotationRight = 1;

  long long number_of_updates = 0;
  int variable = 0;

  void moveModel(float speed, int direction);
  void rotate(int direction);
};


#endif // MAINWINDOW_H
