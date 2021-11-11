#include "fussgaengerszenario.h"

#include "konfiguration.h"

FussgaengerSzenario::FussgaengerSzenario(QObject* parent,
                                         Konfiguration* konfiguration)
  : QObject(parent)
{
  konfiguration_ = konfiguration;

  zeitschritteBisNeuerFussgaenger_ = 0;

  fussgaengerProMinute_ = 0;
}



bool FussgaengerSzenario::sollFussgaengerErzeugtWerden() const
{
  if(fussgaengerProMinute_ != 0)
  {
    if(zeitschritteBisNeuerFussgaenger_ <= 0)
    {
      return true;
    }
  }

  return false;
}



void FussgaengerSzenario::setzeZeitschritteZurueck()
{
  if(fussgaengerProMinute_ != 0)
  {
    zeitschritteBisNeuerFussgaenger_ =
        konfiguration_->sekundenZuZeitschritte(60.0 /
                                    static_cast<double>(fussgaengerProMinute_));
  }
}



void FussgaengerSzenario::setzeFussgaengerProMinute(int fussgaengerProMinute)
{
  fussgaengerProMinute_ = fussgaengerProMinute;
}



int FussgaengerSzenario::fussgaengerProMinute()
{
  return fussgaengerProMinute_;
}



void FussgaengerSzenario::advance()
{
  zeitschritteBisNeuerFussgaenger_ -= 1;
}
