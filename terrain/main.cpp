#include "mainwindow.h"
#include <QApplication>

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  MyGLWidget w;

  w.setFixedSize(1024, 1024);


  w.show();

  return a.exec();
}

