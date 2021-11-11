#include "fussgaenger.h"

#include "konfiguration.h"
#include "statistikdaten.h"
#include "kreuzung.h"

Fussgaenger::Fussgaenger(Kreuzung* kreuzung, Konfiguration* konfiguration,
                         StatistikDaten* statistik)
  : QGraphicsItem(nullptr)
{
  kreuzung_ = kreuzung;
  konfiguration_ = konfiguration;
  statistik_ = statistik;

  zielPunkt_ = QPoint(0, 0);
  wartezeitSchritte_ = 0;
  istFertig_ = false;
}



void Fussgaenger::setzeZielpunkt(int x, int y)
{
  zielPunkt_ = QPoint(x, y);
}



bool Fussgaenger::istFertig()
{
  return istFertig_;
}



QRectF Fussgaenger::boundingRect() const
{
  return QRectF(0.0, 0.0,
                konfiguration_->fussgaengerBreite,
                konfiguration_->fussgaengerLaenge);
}



void Fussgaenger::paint(QPainter* painter,
                        const QStyleOptionGraphicsItem* styleOptionGraphicsItem,
                        QWidget* widget)
{
  painter->setPen(Qt::black);

  /*
   * Färbe den Fußgänger wie bei den Fahrzeugen, je nachdem wie lange
   * er schon wartet.
   */
  int farbe = 0;
  int maximum = statistik_->maximaleFussgaengerWartezeitschritte();

  if(maximum != 0)
  {
    if(maximum > wartezeitSchritte_)
    {
      farbe = (static_cast<double>(wartezeitSchritte_) /
               static_cast<double>(maximum)) * 255.0;
    }
    else
    {
      farbe = 255;
    }

    painter->setBrush(QBrush(QColor(farbe, 255 - farbe, 0)));
  }
  else
  {
    painter->setBrush(QBrush(QColor(255, 255, 255)));
  }

  painter->drawEllipse(0, 0,
                       konfiguration_->fussgaengerBreite,
                       konfiguration_->fussgaengerLaenge);
}



void Fussgaenger::bewegen()
{
  if(zielPunkt_ != QPoint(0, 0))
  {
    qreal xDifferenz = zielPunkt_.x() - this->x();
    qreal yDifferenz = zielPunkt_.y() - this->y();

    if(qAbs(xDifferenz) < konfiguration_->punktGrenzwert &&
       qAbs(yDifferenz) < konfiguration_->punktGrenzwert)
    {
      istFertig_ = true;

      statistik_->fussgaengerZeitEintragen(
            konfiguration_->zeitschritteZuSekunden(wartezeitSchritte_));

      kreuzung_->kreuzungsScene()->removeItem(this);
    }
    else
    {
      // Normiere den Vektor
      qreal laenge = qSqrt((xDifferenz * xDifferenz) +
                           (yDifferenz * yDifferenz));

      xDifferenz /= laenge;
      yDifferenz /= laenge;

      xDifferenz *= konfiguration_->fussgaengerGeschwindigkeit;
      yDifferenz *= konfiguration_->fussgaengerGeschwindigkeit;

      this->setX(this->x() + xDifferenz);
      this->setY(this->y() + yDifferenz);
    }
  }
  else
  {
    ++wartezeitSchritte_;
  }
}
