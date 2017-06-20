#include "mainwindow.h"


MyGLWidget::MyGLWidget(QGLWidget* parent) : QGLWidget(parent) {}

MyGLWidget::~MyGLWidget() {}

void MyGLWidget::initializeGL() {
  glClearColor(0, 0, 0, 1);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0, 0, this->width(), this->height());
  gluPerspective(100, 1.0 * this->width() / this->height(), 0.11, 100.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();


  terrain = QImage("//home//oczk//projektyOpenGl//terrain//terrain.jpg");

  //terrain = QGLWidget::convertToGLFormat( terrain );


}


void MyGLWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glRotatef(rotationY, 0.0, 1.0, 0.0);
  glTranslatef(-posX, -posY, -posZ);
  glPushMatrix();

  for(int z=0; z<terrain.height()-1; ++z){
      QRgb* line = (QRgb*) terrain.scanLine(z);
      QRgb* lineBelow = (QRgb*) terrain.scanLine(z+1);

      for(int x=0; x<terrain.width()-1; ++x){

          int h1 = std::max(0, std::min(255, qRed(line[x])));
          int h2 = std::max(0, std::min(255, qRed(line[x+1])));
          int h3 = std::max(0, std::min(255, qRed(lineBelow[x])));
          int h4 = std::max(0, std::min(255, qRed(lineBelow[x+1])));

          glBegin(GL_LINES);
          glColor3f(100, 100, 100);
          glVertex3f(x, h1/20, z);
          glVertex3f(x, h3/20, z+1);

          glVertex3f(x, h1/20, z);
          glVertex3f(x+1, h2/20, z);

          //glVertex3f(x, h2/20, z+1);
          //glVertex3f(x+1, h3/20, z);

          glVertex3f(x+1, h2/20, z);
          glVertex3f(x+1, h4/20, z+1);

          glVertex3f(x+1, h4/20, z+1);
          glVertex3f(x, h3/20, z+1);
          glEnd();



      }

  }



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

