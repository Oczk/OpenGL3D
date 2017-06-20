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

  float posX = 50;
  float posY = 30;
  float posZ = 50;
  float rotationX = -10;
  float rotationY = 110;

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
