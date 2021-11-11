#ifndef STATISTIKDATEN_H
#define STATISTIKDATEN_H

#include <QObject>
#include <QString>
#include <QMap>

class Konfiguration;
class FahrzeugSpur;
class SpurStatistik;

class StatistikDaten : public QObject
{
  Q_OBJECT

  public:
    StatistikDaten(QObject*, Konfiguration*);

    void fahrzeugZeitEintragen(double);
    void fussgaengerZeitEintragen(double);

    void spurHinzufuegen(FahrzeugSpur*);

    int maximaleFahrzeugWartezeitschritte();
    int maximaleFussgaengerWartezeitschritte();

    QString druckeStatistik();

    void zuruecksetzen();

  signals:

  public slots:
    void advance();

  private:
    Konfiguration* konfiguration_;

    double simulationsZeit_;

    double durchschnittlicheFahrzeugWartezeit_;
    double minimaleFahrzeugWartezeit_;
    double maximaleFahrzeugWartezeit_;

    double durchschnittlicheFussgaengerWartezeit_;
    double minimaleFussgaengerWartezeit_;
    double maximaleFussgaengerWartezeit_;

    int anzahlFahrzeuge_;
    int anzahlFussgaenger_;

    QMap<FahrzeugSpur*, SpurStatistik*> spurStatistiken_;
};

#endif // STATISTIKDATEN_H
