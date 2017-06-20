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

  terrain = QImage("//home//oczk//projektyOpenGl//skybox//terrain.jpg");
  texture1 = QImage("//home//oczk//projektyOpenGl//skybox//glass.jpg");
  texture1 = QGLWidget::convertToGLFormat( texture1 );
  skybox[0] = QImage("//home//oczk//projektyOpenGl//skybox//sky2_xn.jpg");
  skybox[1] = QImage("//home//oczk//projektyOpenGl//skybox//sky2_xp.jpg");
  skybox[2] = QImage("//home//oczk//projektyOpenGl//skybox//sky2_yn.jpg");
  skybox[3] = QImage("//home//oczk//projektyOpenGl//skybox//sky2_yp.jpg");
  skybox[4] = QImage("//home//oczk//projektyOpenGl//skybox//sky2_zn.jpg");
  skybox[5] = QImage("//home//oczk//projektyOpenGl//skybox//sky2_zp.jpg");

  glEnable(GL_TEXTURE_2D);
  glShadeModel(GL_SMOOTH);
  glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
  glClearDepth(1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

  glGenTextures( 3, &tex[0] );
  glBindTexture( GL_TEXTURE_2D, tex[0] );
    glTexImage2D(GL_TEXTURE_2D, 0, 4, texture1.width(), texture1.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture1.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, 0);

  glEnable(GL_TEXTURE_CUBE_MAP);
    glGenTextures( 1, &tex[1] );
    glBindTexture( GL_TEXTURE_CUBE_MAP, tex[1] );

    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, skybox[0].width(),skybox[0].height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, skybox[0].bits());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, skybox[1].width(), skybox[1].height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, skybox[1].bits());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, skybox[2].width(), skybox[2].height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, skybox[2].bits());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, skybox[3].width(), skybox[3].height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, skybox[3].bits());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, skybox[4].width(), skybox[4].height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, skybox[4].bits());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, skybox[5].width(), skybox[5].height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, skybox[5].bits());

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

  glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
  glDisable(GL_TEXTURE_CUBE_MAP);

  QTimer* timer = new QTimer();
  timer->setInterval(5);
  timer->setSingleShot(false);
  connect(timer,SIGNAL(timeout()),this,SLOT(update()));
  timer->start();
}


void MyGLWidget::createSkybox() {
   glDepthMask(GL_FALSE);
    glEnable(GL_TEXTURE_CUBE_MAP);
    glBindTexture(GL_TEXTURE_CUBE_MAP, tex[1]);

    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glEnable(GL_TEXTURE_GEN_R);

    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    GLfloat xPlane[]{1.0, 0.0, 0.0, 0.0};
    GLfloat yPlane[]{0.0, 1.0, 0.0, 0.0};
    GLfloat zPlane[]{0.0, 0.0, 1.0, 0.0};
    glTexGenfv(GL_S, GL_OBJECT_PLANE, xPlane);
    glTexGenfv(GL_T, GL_OBJECT_PLANE, yPlane);
    glTexGenfv(GL_R, GL_OBJECT_PLANE, zPlane);

    glTexCoord3f(posX, -posY, posZ);

    drawCube();

    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_GEN_R);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

   glDisable(GL_TEXTURE_CUBE_MAP);
   glDepthMask(GL_TRUE);
}

void MyGLWidget::drawCube() {
  glBegin(GL_QUADS);

    GLfloat x1=0, x2=110, y1=-10, y2=200, z1=0, z2=110;

      glColor3f(1.0, 1.0, 1.0);

      glVertex3f(x1, y1, z1);
      glVertex3f(x2, y1, z1);
      glVertex3f(x2, y1, z2);
      glVertex3f(x1, y1, z2);

      glVertex3f(x1, y1, z1);
      glVertex3f(x2, y1, z1);
      glVertex3f(x2, y2, z1);
      glVertex3f(x1, y2, z1);

      glVertex3f(x2, y1, z1);
      glVertex3f(x2, y1, z2);
      glVertex3f(x2, y2, z2);
      glVertex3f(x2, y2, z1);

      glVertex3f(x2, y1, z2);
      glVertex3f(x1, y1, z2);
      glVertex3f(x1, y2, z2);
      glVertex3f(x2, y2, z2);

      glVertex3f(x1, y1, z1);
      glVertex3f(x1, y1, z2);
      glVertex3f(x1, y2, z2);
      glVertex3f(x1, y2, z1);

      glVertex3f(x1, y2, z1);
      glVertex3f(x2, y2, z1);
      glVertex3f(x2, y2, z2);
      glVertex3f(x1, y2, z2);

  glEnd();
}

void MyGLWidget::cross(GLfloat n[3], GLfloat v1[3], GLfloat v2[3]) {
    n[0] = v1[1]*v2[2] - v2[1]*v1[2];
    n[1] = v1[2]*v2[0] - v1[0]*v2[2];
    n[2] = v1[0]*v2[1] - v1[1]*v2[0];
}

void MyGLWidget::normalize(GLfloat v[3]) {
    GLfloat d = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    if(d==0.0f)
        d = 1.0;

    v[0] /= -d;
    v[1] /= -d;
    v[2] /= -d;
}

void MyGLWidget::calculateNormals(vec3f vertices[], GLfloat normal1[3], GLfloat normal2[3]) {

    av[0] = vertices[0][0]-vertices[1][0];
    av[1] = vertices[0][1]-vertices[1][1];
    av[2] = vertices[0][2]-vertices[1][2];

    bv[0] = vertices[1][0]-vertices[3][0];
    bv[1] = vertices[1][1]-vertices[3][1];
    bv[2] = vertices[1][2]-vertices[3][2];
    cross(normal1, av, bv);
    normalize(normal1);

    av[0] = vertices[0][0]-vertices[3][0];
    av[1] = vertices[0][1]-vertices[3][1];
    av[2] = vertices[0][2]-vertices[3][2];

    bv[0] = vertices[3][0]-vertices[2][0];
    bv[1] = vertices[3][1]-vertices[2][1];
    bv[2] = vertices[3][2]-vertices[2][2];
    cross(normal2, av, bv);
    normalize(normal2);
}

void MyGLWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glRotatef(rotationX, 0.0, 1.0, 0.0);
  glColor3f(0.75,0.75,0.75);
  glTranslatef(posX, posY, posZ);
  GLfloat normal1[3], normal2[3], normal3[3];

  for(int z=0; z<terrain.height()-1; ++z){
      QRgb* line = (QRgb*) terrain.scanLine(z);
      QRgb* lowerLine = (QRgb*) terrain.scanLine(z+1);

      for(int x=0; x<terrain.width()-1; ++x){

          glBindTexture(GL_TEXTURE_2D, tex[0]);

          h1 = std::max(0, std::min(255, qRed(line[x])));
          h2 = std::max(0, std::min(255, qRed(line[x+1])));
          h3 = std::max(0, std::min(255, qRed(lowerLine[x])));
          h4 = std::max(0, std::min(255, qRed(lowerLine[x+1])));
          h1 =h1/div;
          h2 =h2/div;
          h3 =h3/div;
          h4 =h4/div;

          glPushMatrix();
          glBegin(GL_TRIANGLES);

          glVertex3f(x, h1, z);
          glTexCoord2f(0.0f, 0.0f);
          glVertex3f(x, h3, z+1);
          glTexCoord2f(0.0f, 0.0f);
          glVertex3f(x+1, h2, z);
          glTexCoord2f(1.0f, 0.0f);

          glVertex3f(x+1, h2, z);
          glTexCoord2f(1.0f, 0.0f);
          glVertex3f(x+1, h4, z+1);
          glTexCoord2f(1.0f, 0.0f);
          glVertex3f(x, h3, z+1);
          glTexCoord2f(0.0f, 0.0f);
          glEnd();
          glBindTexture(GL_TEXTURE_2D, 0);

          glPopMatrix();


          glEnable(GL_LIGHTING);
          glEnable(GL_LIGHT0);

          glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
          glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
          glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
          glLightfv(GL_LIGHT0, GL_POSITION, position);


          vec3f vertices[]= { (float)x, h1, (float)z, (float)(x+1), h2, (float)z, (float)x, h3, (float)(z+1), (float)(x+1), h4, (float)(z+1)};


          calculateNormals(vertices, normal1, normal2);

          normal3[0] = (normal1[0]+normal2[0])/2;
          normal3[1] = (normal1[1]+normal2[1])/2;
          normal3[2] = (normal1[2]+normal2[2])/2;

          vec3f normals[] = { normal3[0], normal3[1], normal3[2],
                              normal1[0], normal1[1], normal1[2],
                              normal3[0], normal3[1], normal3[2],
                              normal2[0], normal2[1], normal2[2] };

          glNormal3f(normal3[0], normal3[1], normal3[2]);


      }

  }

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

