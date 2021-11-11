#include "fussgaengerampel.h"

#include <QtDebug>

#include "konfiguration.h"
#include "kreuzung.h"

FussgaengerAmpel::FussgaengerAmpel(Kreuzung* kreuzung,
                                   Konfiguration* konfiguration)
  : QGraphicsItem(nullptr)
{
  kreuzung_ = kreuzung;
  konfiguration_ = konfiguration;

  zurzeitigePhase_ = "rot";
}



QString FussgaengerAmpel::phase() const
{
  return zurzeitigePhase_;
}



void FussgaengerAmpel::wechselZuPhase(QString phase)
{
  zurzeitigePhase_ = phase;
}



QRectF FussgaengerAmpel::boundingRect() const
{
  return QRectF(0.0, 0.0,
                konfiguration_->fussgaengerAmpelBreite,
                konfiguration_->fussgaengerAmpelLaenge);
}



void FussgaengerAmpel::paint(QPainter* painter,
                             const QStyleOptionGraphicsItem* styleOption,
                             QWidget* widget)
{
  // Zeichne Box
  painter->setPen(Qt::black);
  painter->setBrush(Qt::gray);
  painter->drawRect(0, 0,
                    konfiguration_->fussgaengerAmpelBreite,
                    konfiguration_->fussgaengerAmpelLaenge);

  // Zeichne Lampen
  if(zurzeitigePhase_ == "rot")
  {
    painter->setPen(Qt::red);
    painter->setBrush(Qt::red);
    painter->drawEllipse(QPoint(konfiguration_->fussgaengerAmpelBreite / 2,
                               (konfiguration_->fussgaengerAmpelLaenge / 5) * 1),
                         konfiguration_->fussgaengerAmpelBreite / 4,
                         konfiguration_->fussgaengerAmpelBreite / 4);
  }
  else if(zurzeitigePhase_ == "gruen")
  {
    painter->setBrush(Qt::green);
    painter->drawEllipse(QPoint(konfiguration_->fussgaengerAmpelBreite / 2,
                               (konfiguration_->fussgaengerAmpelLaenge / 5) * 4),
                         konfiguration_->fussgaengerAmpelBreite / 4,
                         konfiguration_->fussgaengerAmpelBreite / 4);
  }
  else
  {
    qDebug() << "In fussgaengerampel.cpp, paint(): Keine gültige Phase";
  }
}



void FussgaengerAmpel::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
  if(mouseEvent->button() == Qt::MouseButton::LeftButton)
  {
    kreuzung_->wechselZurzeitigeFussgaengerAmpelphase(this);
    mouseEvent->accept();
  }
  else
  {
    mouseEvent->ignore();
  }
}
