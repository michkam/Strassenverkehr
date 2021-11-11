#ifndef KONFIGURATION_H
#define KONFIGURATION_H

#include <QObject>
#include <QColor>

class Konfiguration : public QObject
{
  Q_OBJECT

  public:
    Konfiguration(QObject*);

    int sekundenZuZeitschritte(double sekunden);
    double zeitschritteZuSekunden(int zeitschritte);

  signals:

  public slots:

  public:
    double pi;

    int timerIntervall;

    double skalierungsFaktor;
    double standardSkalierung;

    int sceneRectBreite;
    int sceneRectHoehe;

    int spurLaenge;
    int spurBreite;

    int wartelinienDistanz;
    int wartelinienBreite;

    int anzahlRichtungspfeile;

    int fussgaengerUeberwegBreite;

    QColor grasFarbe;
    QColor buergersteigsFarbe;
    QColor strassenFarbe;

    int fahrzeugAmpelLaenge;
    int fahrzeugAmpelBreite;

    int fussgaengerAmpelLaenge;
    int fussgaengerAmpelBreite;

    int fahrzeugLaenge;
    int fahrzeugBreite;

    int fahrzeugAbstand;
    int fahrzeugDistanzBeiErzeugung;

    qreal punktGrenzwert;

    int fahrzeugGeschwindigkeit;

    int fussgaengerLaenge;
    int fussgaengerBreite;

    int fussgaengerStreuung;

    QColor fussgaengerFarbe;

    int fussgaengerGeschwindigkeit;
};

#endif // KONFIGURATION_H
