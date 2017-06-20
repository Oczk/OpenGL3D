#include "mainwindow.h"


MyGLWidget::MyGLWidget(QGLWidget* parent) : QGLWidget(parent) {}

MyGLWidget::~MyGLWidget() {}

void MyGLWidget::initializeGL() {
  glClearColor(1, 0.5, 0, 1);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0, 0, this->width(), this->height());
  gluPerspective(80, 1.0 * this->width() / this->height(), 0.11, 200.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

}

void MyGLWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glRotatef(rotationY, 0.0, 1.0, 0.0);
  glTranslatef(-posX, -posY, posZ);
  glPushMatrix();
  glTranslatef(0, 0, -10);

  glBegin(GL_TRIANGLES);
  glColor3f(1.0, 0.0, 0.0);
  glVertex3f( 0.0, 1.0, 0.0);
  glVertex3f(-1.0,-1.0, 1.0);
  glVertex3f( 1.0,-1.0, 1.0);

  glColor3f(0.0, 0.0, 1.0);
  glVertex3f( 0.0, 1.0, 0.0);
  glVertex3f( 1.0,-1.0, 1.0);
  glVertex3f( 1.0,-1.0, -1.0);

  glColor3f(0.0, 1.0, 0.0);
  glVertex3f( 0.0, 1.0, 0.0);
  glVertex3f( 1.0,-1.0, -1.0);
  glVertex3f(-1.0,-1.0, -1.0);

  glColor3f(1.0, 1.0, 0.0);
  glVertex3f( 0.0, 1.0, 0.0);
  glVertex3f(-1.0,-1.0,-1.0);
  glVertex3f(-1.0,-1.0, 1.0);
  glEnd();

  glPopMatrix();
  glFlush();
}

void MyGLWidget::resizeGL() {}

void MyGLWidget::timerEvent(QTimerEvent* e) {
  updateGL();
}

void MyGLWidget::keyPressEvent(QKeyEvent* e) {

  switch (e->key()) {
    case Qt::Key_W: {
      moveModel(forwardSpeed, forward);
    } break;

    case Qt::Key_A: {
      moveModel(sideSpeed, side);
    } break;

    case Qt::Key_S: {
      moveModel(-forwardSpeed, forward);
    } break;

    case Qt::Key_D: {
      moveModel(-sideSpeed, side);
    } break;

    case Qt::Key_Q: {
      rotate(rotationLeft);
    } break;

    case Qt::Key_E: {
      rotate(rotationRight);
    }
  }

  updateGL();
}

void MyGLWidget::moveModel(float speed, int direction) {
  float radians = (rotationY + 90 * direction) * M_PI / 180;
  posZ += speed * sin(radians);
  posX -= speed * cos(radians);
}

void MyGLWidget::rotate(int direction) {
  rotationY += direction * rotation;
}
