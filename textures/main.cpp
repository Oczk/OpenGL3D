#include "mainwindow.h"
#include <QApplication>

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  MyGLWidget w;

  w.setFixedSize(800, 800);


  w.show();

  return a.exec();
}

