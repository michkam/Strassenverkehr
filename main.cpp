#include "simulationgui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  SimulationGUI w;
  w.show();

  return a.exec();
}
