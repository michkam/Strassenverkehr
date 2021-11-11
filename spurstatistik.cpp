#include "spurstatistik.h"

SpurStatistik::SpurStatistik(QObject* parent, QString name)
  : QObject(parent)
{
  this->name = name;

  zeitBelegt = 0.0;
  zeitFrei = 0.0;
}
