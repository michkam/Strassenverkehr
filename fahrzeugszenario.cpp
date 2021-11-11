#include "fahrzeugszenario.h"

#include <QtDebug>

#include "konfiguration.h"

FahrzeugSzenario::FahrzeugSzenario(QObject* parent,
                                   Konfiguration* konfiguration)
  : QObject(parent)
{
  konfiguration_ = konfiguration;

  zeitschritteBisNeuesFahrzeug_ = 0;

  fahrzeugeProMinute_ = 0;

  wahrscheinlichkeitLinks_ = 0;
  wahrscheinlichkeitRechts_ = 0;
  wahrscheinlichkeitGeradeaus_ = 0;
}



bool FahrzeugSzenario::sollFahrzeugErzeugtWerden() const
{
  int gesamtWahrscheinlichkeit = wahrscheinlichkeitLinks_ +
                                 wahrscheinlichkeitRechts_ +
                                 wahrscheinlichkeitGeradeaus_;

  if(fahrzeugeProMinute_ != 0 && gesamtWahrscheinlichkeit > 0)
  {
    if(zeitschritteBisNeuesFahrzeug_ <= 0)
    {
      return true;
    }
  }

  return false;
}



QString FahrzeugSzenario::waehleRichtung() const
{
  int gesamtWahrscheinlichkeit = wahrscheinlichkeitLinks_ +
                                 wahrscheinlichkeitRechts_ +
                                 wahrscheinlichkeitGeradeaus_;

  int zufallszahl = qrand() % gesamtWahrscheinlichkeit;
  if(zufallszahl >= 0 && zufallszahl <= wahrscheinlichkeitLinks_)
  {
    return QString("links");
  }
  else if(zufallszahl > wahrscheinlichkeitLinks_ &&
          zufallszahl <= wahrscheinlichkeitLinks_ + wahrscheinlichkeitRechts_)
  {
    return QString("rechts");
  }
  else if(zufallszahl > wahrscheinlichkeitLinks_ + wahrscheinlichkeitRechts_ &&
          zufallszahl <= gesamtWahrscheinlichkeit)
  {
    return QString("geradeaus");
  }
  else
  {
    qDebug() << "In fahrzeugszenario.cpp, waehleRichtung(): Keine gültige "
                "Richtung";

    return QString("");
  }
}



void FahrzeugSzenario::setzeZeitschritteZurueck()
{
  if(fahrzeugeProMinute_ != 0)
  {
    zeitschritteBisNeuesFahrzeug_ =
        konfiguration_->sekundenZuZeitschritte(60.0 /
                                      static_cast<double>(fahrzeugeProMinute_));
  }
}



void FahrzeugSzenario::setzeFahrzeugeProMinute(int fahrzeugeProMinute)
{
  fahrzeugeProMinute_ = fahrzeugeProMinute;
}



void FahrzeugSzenario::setzeWahrscheinlichkeitLinks(int wahrscheinlichkeit)
{
  wahrscheinlichkeitLinks_ = wahrscheinlichkeit;
}



void FahrzeugSzenario::setzeWahrscheinlichkeitRechts(int wahrscheinlichkeit)
{
  wahrscheinlichkeitRechts_ = wahrscheinlichkeit;
}



void FahrzeugSzenario::setzeWahrscheinlichkeitGeradeaus(int wahrscheinlichkeit)
{
  wahrscheinlichkeitGeradeaus_ = wahrscheinlichkeit;
}



int FahrzeugSzenario::fahrzeugeProMinute()
{
  return fahrzeugeProMinute_;
}



int FahrzeugSzenario::wahrscheinlichkeitLinks()
{
  return wahrscheinlichkeitLinks_;
}



int FahrzeugSzenario::wahrscheinlichkeitGeradeaus()
{
  return wahrscheinlichkeitGeradeaus_;
}



int FahrzeugSzenario::wahrscheinlichkeitRechts()
{
  return wahrscheinlichkeitRechts_;
}



void FahrzeugSzenario::advance()
{
  zeitschritteBisNeuesFahrzeug_ -= 1;
}
