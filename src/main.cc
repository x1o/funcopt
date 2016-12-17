#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication qt_app(argc, argv);
  MainWindow mw;
  mw.show();

  return qt_app.exec();
}
