#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <GL/glu.h>

#include <QtOpenGL>
#include <QtWidgets>

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

  float posX = 0;
  float posY = 0;
  float posZ = 0;
  float rotationX = 0;
  float rotationY = 0;

  const float forwardSpeed = 0.5;
  const int forward = 1;
  const float sideSpeed = 0.5;
  const int side = 0;

  const float rotation = 10.0;
  const int rotationLeft = -1;
  const int rotationRight = 1;

  long long number_of_updates = 0;
  int variable = 0;

  void moveModel(float speed, int direction);
  void rotate(int direction);
};


#endif // MAINWINDOW_H
