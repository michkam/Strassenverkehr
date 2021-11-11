#include "statistikdaten.h"

#include "konfiguration.h"
#include "fahrzeugspur.h"
#include "spurstatistik.h"

StatistikDaten::StatistikDaten(QObject* parent, Konfiguration* konfiguration)
  : QObject(parent)
{
  konfiguration_ = konfiguration;

  simulationsZeit_ = 0.0;

  durchschnittlicheFahrzeugWartezeit_ = 0.0;
  minimaleFahrzeugWartezeit_ = 99999.9;
  maximaleFahrzeugWartezeit_ = 0.0;

  durchschnittlicheFussgaengerWartezeit_ = 0.0;
  minimaleFussgaengerWartezeit_ = 99999.9;
  maximaleFussgaengerWartezeit_ = 0.0;

  anzahlFahrzeuge_ = 0;
  anzahlFussgaenger_ = 0;

  spurStatistiken_ = QMap<FahrzeugSpur*, SpurStatistik*>();
}



void StatistikDaten::fahrzeugZeitEintragen(double zeit)
{
  double alteGesamteZeit = durchschnittlicheFahrzeugWartezeit_ *
                           anzahlFahrzeuge_;

  anzahlFahrzeuge_ += 1;

  durchschnittlicheFahrzeugWartezeit_ = (alteGesamteZeit + zeit) /
                                        static_cast<double>(anzahlFahrzeuge_);

  if(zeit > maximaleFahrzeugWartezeit_)
  {
    maximaleFahrzeugWartezeit_ = zeit;
  }

  if(zeit < minimaleFahrzeugWartezeit_)
  {
    minimaleFahrzeugWartezeit_ = zeit;
  }
}



void StatistikDaten::fussgaengerZeitEintragen(double zeit)
{
  double alteGesamteZeit = durchschnittlicheFussgaengerWartezeit_ *
                           anzahlFussgaenger_;

  anzahlFussgaenger_ += 1;

  durchschnittlicheFussgaengerWartezeit_ = (alteGesamteZeit + zeit) /
                                        static_cast<double>(anzahlFussgaenger_);

  if(zeit > maximaleFussgaengerWartezeit_)
  {
    maximaleFussgaengerWartezeit_ = zeit;
  }

  if(zeit < minimaleFussgaengerWartezeit_)
  {
    minimaleFussgaengerWartezeit_ = zeit;
  }
}



void StatistikDaten::spurHinzufuegen(FahrzeugSpur* spur)
{
  SpurStatistik* spurStatistik =
      new SpurStatistik(this, QString::number(spur->index() + 1) + ". " +
                        spur->himmelsrichtung().toUpper());

  spurStatistiken_.insert(spur, spurStatistik);
}



int StatistikDaten::maximaleFahrzeugWartezeitschritte()
{
  return konfiguration_->sekundenZuZeitschritte(maximaleFahrzeugWartezeit_);
}



int StatistikDaten::maximaleFussgaengerWartezeitschritte()
{
  return konfiguration_->sekundenZuZeitschritte(maximaleFussgaengerWartezeit_);
}



QString StatistikDaten::druckeStatistik()
{
  QString statistik = QString();

  statistik += "Alle Zeitangaben in Sekunden\n---\n";
  statistik += "Simulationszeit: ";
  statistik += QString::number(simulationsZeit_);
  statistik += "\n---\n";

  statistik += "Anzahl der Fahrzeuge: ";
  statistik += QString::number(anzahlFahrzeuge_);
  statistik += "\nDurchschnittliche Fahrzeugwartezeit: ";
  statistik += QString::number(durchschnittlicheFahrzeugWartezeit_);
  statistik += "\nMinimale Fahrzeugwartezeit: ";
  statistik += QString::number(minimaleFahrzeugWartezeit_);
  statistik += "\nMaximale Fahrzeugwartezeit: ";
  statistik += QString::number(maximaleFahrzeugWartezeit_);
  statistik += "\n---\n";

  statistik += "Anzahl der Fußgänger: ";
  statistik += QString::number(anzahlFussgaenger_);
  statistik += "\nDurchschnittliche Fußgängerwartezeit: ";
  statistik += QString::number(durchschnittlicheFussgaengerWartezeit_);
  statistik += "\nMinimale Fußgängerwartezeit: ";
  statistik += QString::number(minimaleFussgaengerWartezeit_);
  statistik += "\nMaximale Fußgängerwartezeit: ";
  statistik += QString::number(maximaleFussgaengerWartezeit_);
  statistik += "\n---\n";

  statistik += "Fahrzeugspuren: \n";
  for(auto& spur : spurStatistiken_)
  {
    statistik += spur->name + ": ";
    statistik += QString::number(
                   (spur->zeitBelegt /
                    (spur->zeitBelegt + spur->zeitFrei) * 100));
    statistik += "% der Zeit warten Fahrzeuge.\n";
  }

  return statistik;
}



void StatistikDaten::zuruecksetzen()
{
  simulationsZeit_ = 0.0;

  durchschnittlicheFahrzeugWartezeit_ = 0.0;
  minimaleFahrzeugWartezeit_ = 0.0;
  maximaleFahrzeugWartezeit_ = 0.0;

  durchschnittlicheFussgaengerWartezeit_ = 0.0;
  minimaleFussgaengerWartezeit_ = 0.0;
  maximaleFussgaengerWartezeit_ = 0.0;

  anzahlFahrzeuge_ = 0;
  anzahlFussgaenger_ = 0;

  spurStatistiken_.clear();
}



void StatistikDaten::advance()
{
  double zeitschrittInSekunden =
      (static_cast<double>(konfiguration_->timerIntervall) / 1000.0);

  simulationsZeit_ += zeitschrittInSekunden;

  for(auto& spur : spurStatistiken_.keys())
  {
    if(spur->istBelegt())
    {
      spurStatistiken_[spur]->zeitBelegt += zeitschrittInSekunden;
    }
    else
    {
      spurStatistiken_[spur]->zeitFrei += zeitschrittInSekunden;
    }
  }
}
