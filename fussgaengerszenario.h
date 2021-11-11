#ifndef FUSSGAENGERSZENARIO_H
#define FUSSGAENGERSZENARIO_H

#include <QObject>

class Konfiguration;

class FussgaengerSzenario : public QObject
{
  Q_OBJECT

  public:
    FussgaengerSzenario(QObject*, Konfiguration*);

    bool sollFussgaengerErzeugtWerden() const;
    void setzeZeitschritteZurueck();

    void setzeFussgaengerProMinute(int);
    int fussgaengerProMinute();

    void advance();

  signals:

  public slots:

  private:
    Konfiguration* konfiguration_;

    int zeitschritteBisNeuerFussgaenger_;

    int fussgaengerProMinute_;
};

#endif // FUSSGAENGERSZENARIO_H
