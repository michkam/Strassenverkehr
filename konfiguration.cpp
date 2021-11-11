#include "konfiguration.h"

Konfiguration::Konfiguration(QObject* parent) : QObject(parent)
{
  pi =  3.14159265359;

  timerIntervall = 36; // ergibt ~28 Bilder pro Sekunde

  skalierungsFaktor = 1.03;
  standardSkalierung = 0.15;

  sceneRectBreite = 50000;
  sceneRectHoehe = 50000;

  spurLaenge = 20000;
  spurBreite = 300;

  wartelinienDistanz = 750;
  wartelinienBreite = 60;

  anzahlRichtungspfeile = 3;

  fussgaengerUeberwegBreite = 250;

  grasFarbe = QColor(44, 176, 55);
  buergersteigsFarbe = QColor(129, 131, 122);
  strassenFarbe = QColor(40, 43, 42);

  fahrzeugAmpelLaenge = spurBreite;
  fahrzeugAmpelBreite = spurBreite / 2;

  fussgaengerAmpelLaenge = spurBreite / 1.5;
  fussgaengerAmpelBreite = spurBreite / 2;

  fahrzeugLaenge = 400;
  fahrzeugBreite = 200;

  fahrzeugAbstand = 80;
  fahrzeugDistanzBeiErzeugung = 5000;

  punktGrenzwert = 50.0;

  fahrzeugGeschwindigkeit = 40; // Pixel pro Zeitschritt entspricht 40km/h

  fussgaengerLaenge = 75;
  fussgaengerBreite = 75;

  fussgaengerStreuung = 100;

  fussgaengerFarbe = QColor(65, 105, 225);

  fussgaengerGeschwindigkeit = 10; // Pixel pro Zeitschritt entspricht 10km/h
}



int Konfiguration::sekundenZuZeitschritte(double sekunden)
{
    return static_cast<int>((sekunden * (1000.0 / timerIntervall)));
}



double Konfiguration::zeitschritteZuSekunden(int zeitschritte)
{
  return (zeitschritte * timerIntervall) / 1000.0;
}
