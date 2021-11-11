#include "fussgaengerueberweg.h"

#include "konfiguration.h"
#include "statistikdaten.h"
#include "kreuzung.h"
#include "fussgaengerampel.h"
#include "fussgaenger.h"

FussgaengerUeberweg::FussgaengerUeberweg(Kreuzung* kreuzung,
                                         Konfiguration* konfiguration,
                                         StatistikDaten* statistik,
                                         FussgaengerAmpel* ampel)
  : QGraphicsItem(nullptr), symbol_(QPixmap(":/a/images/Fussgaenger.png"))
{
  kreuzung_ = kreuzung;
  konfiguration_ = konfiguration;
  statistik_ = statistik;

  fussgaengerAmpel_ = ampel;

  punktEins_ = QPoint(0, 0);
  punktZwei_ = QPoint(0, 0);

  fussgaenger_ = QList<Fussgaenger*>();
  laufendeFussgaenger_ = QList<Fussgaenger*>();
}



void FussgaengerUeberweg::setzePunktEins(int x, int y)
{
  punktEins_ = QPoint(x, y);
}



void FussgaengerUeberweg::setzePunktZwei(int x, int y)
{
  punktZwei_ = QPoint(x, y);
}



void FussgaengerUeberweg::erzeugeFussgaenger()
{
  Fussgaenger* neuerFussgaenger = new Fussgaenger(kreuzung_, konfiguration_,
                                                  statistik_);

  fussgaenger_.append(neuerFussgaenger);

  // Stelle den Fussgaenger zufällig um punktEins herum
  neuerFussgaenger->setPos(
        punktEins_.x() + (qrand() % konfiguration_->fussgaengerStreuung)
          - konfiguration_->fussgaengerStreuung * 2,
        punktEins_.y() + (qrand() % konfiguration_->fussgaengerStreuung)
          - konfiguration_->fussgaengerStreuung * 2);

  kreuzung_->kreuzungsScene()->addItem(neuerFussgaenger);
}



void FussgaengerUeberweg::leeren()
{
  for(auto fussgaenger : fussgaenger_)
  {
    kreuzung_->kreuzungsScene()->removeItem(fussgaenger);
  }

  fussgaenger_.clear();

  for(auto fussgaenger : laufendeFussgaenger_)
  {
    kreuzung_->kreuzungsScene()->removeItem(fussgaenger);
  }

  laufendeFussgaenger_.clear();
}



FussgaengerAmpel* FussgaengerUeberweg::fussgaengerAmpel()
{
  return fussgaengerAmpel_;
}



QRectF FussgaengerUeberweg::boundingRect() const
{
  return QRectF(-(symbol_.width() / 2),
                -(symbol_.height() / 2),
                symbol_.width(),
                symbol_.height());
}



void FussgaengerUeberweg::paint(QPainter* painter,
                                const QStyleOptionGraphicsItem* styleOption,
                                QWidget* widget)
{
  // Zeichne Fußgängersymbol
  painter->drawPixmap(-(symbol_.width() / 2),
                      -(symbol_.height() / 2),
                      symbol_.width(),
                      symbol_.height(),
                      symbol_);
}



void FussgaengerUeberweg::fortschreiten()
{
  /*
   * Wartende Fußgänger sollen zu den laufenden Fussgängern übergehen,
   * wenn die Ampel rot ist.
   */
  for(auto fussgaenger : fussgaenger_)
  {
    fussgaenger->bewegen();

    if(fussgaengerAmpel_->phase() == "gruen")
    {
      fussgaenger->setzeZielpunkt(punktZwei_.x(), punktZwei_.y());

      laufendeFussgaenger_.append(fussgaenger);
      fussgaenger_.removeAll(fussgaenger);
    }
  }

  /*
   * Schon laufende Fußgänger sollen laufen egal welche Ampelphase
   * grade ist.
   */
  for(auto fussgaenger : laufendeFussgaenger_)
  {
    fussgaenger->bewegen();

    if(fussgaenger->istFertig())
    {
      laufendeFussgaenger_.removeAll(fussgaenger);
    }
  }
}
