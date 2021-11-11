#include "fahrzeugampel.h"

#include "konfiguration.h"
#include "kreuzung.h"

FahrzeugAmpel::FahrzeugAmpel(Kreuzung* kreuzung, Konfiguration* konfiguration)
  : QGraphicsItem(nullptr)
{
  kreuzung_ = kreuzung;
  konfiguration_ = konfiguration;
  zurzeitigePhase_ = "rot";
}



QString FahrzeugAmpel::phase() const
{
  return zurzeitigePhase_;
}



void FahrzeugAmpel::wechselZuPhase(QString phase)
{
  zurzeitigePhase_ = phase;
}



QRectF FahrzeugAmpel::boundingRect() const
{
  return QRectF(0.0,
                0.0,
                konfiguration_->fahrzeugAmpelBreite,
                konfiguration_->fahrzeugAmpelLaenge);
}



void FahrzeugAmpel::paint(QPainter* painter,
                          const QStyleOptionGraphicsItem* styleOption,
                          QWidget* widget)
{
  painter->setPen(Qt::black);
  painter->setBrush(Qt::gray);
  painter->drawRect(0.0,
                    0.0,
                    konfiguration_->fahrzeugAmpelBreite,
                    konfiguration_->fahrzeugAmpelLaenge);

  if(zurzeitigePhase_ == "rot" || zurzeitigePhase_ == "rot-gelb")
  {
    painter->setBrush(Qt::red);
  }
  else
  {
    painter->setBrush(Qt::gray);
  }
  painter->drawEllipse(30,
                       10,
                       (konfiguration_->fahrzeugAmpelLaenge - 30) / 3,
                       (konfiguration_->fahrzeugAmpelLaenge - 30) / 3);

  if(zurzeitigePhase_ == "rot-gelb" || zurzeitigePhase_ == "gelb")
  {
    painter->setBrush(Qt::yellow);
  }
  else
  {
    painter->setBrush(Qt::gray);
  }
  painter->drawEllipse(30,
                       (konfiguration_->fahrzeugAmpelLaenge - 30) / 3 + 15,
                       (konfiguration_->fahrzeugAmpelLaenge - 30) / 3,
                       (konfiguration_->fahrzeugAmpelLaenge - 30) / 3);

  if(zurzeitigePhase_ == "gruen")
  {
    painter->setBrush(Qt::green);
  }
  else
  {
    painter->setBrush(Qt::gray);
  }
  painter->drawEllipse(30,
                       2*(konfiguration_->fahrzeugAmpelLaenge - 30) / 3 + 20,
                       (konfiguration_->fahrzeugAmpelLaenge - 30) / 3,
                       (konfiguration_->fahrzeugAmpelLaenge - 30) / 3);
}



void FahrzeugAmpel::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
  if(mouseEvent->button() == Qt::MouseButton::LeftButton)
  {
   kreuzung_->wechselZurzeitigeFahrzeugAmpelphase(this);
   mouseEvent->accept();
  }
  else
  {
    mouseEvent->ignore();
  }
}
