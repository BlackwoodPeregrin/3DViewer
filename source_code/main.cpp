#include <QApplication>

#include "view/mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  s21_3DViewer::MainWindow w;
  w.show();
  return a.exec();
}
