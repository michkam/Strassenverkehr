#ifndef SPURSTATISTIK_H
#define SPURSTATISTIK_H

#include <QObject>

class SpurStatistik : public QObject
{
  Q_OBJECT

  public:
    SpurStatistik(QObject*, QString);

    QString name;

    double zeitBelegt;
    double zeitFrei;

  signals:

  public slots:

  private:
};

#endif // SPURSTATISTIK_H
