#include "fahrzeug.h"

#include "konfiguration.h"
#include "kreuzung.h"
#include "statistikdaten.h"

Fahrzeug::Fahrzeug(Kreuzung* kreuzung, Konfiguration* konfiguration,
                   StatistikDaten* statistik)
  : QGraphicsItem(nullptr), car(QPixmap(":/a/images/Car.png"))
{
  kreuzung_ = kreuzung;
  konfiguration_ = konfiguration;
  statistik_ = statistik;

  zielPunkte_ = QList<QPoint>();
  wartezeitSchritte_ = 0;
  istFertig_ = false;

  richtung_ = "";
}



void Fahrzeug::fuegeZielHinzu(int x, int y)
{
  QPoint neuerPunkt = QPoint(x, y);

  zielPunkte_.append(neuerPunkt);
}



bool Fahrzeug::istFertig()
{
  return istFertig_;
}



int Fahrzeug::zielpunkteAnzahl()
{
  return zielPunkte_.size();
}



QString Fahrzeug::richtung()
{
  return richtung_;
}



void Fahrzeug::setzeRichtung(QString richtung)
{
  richtung_ = richtung;
}



void Fahrzeug::entferne()
{
  statistik_->fahrzeugZeitEintragen(
        konfiguration_->zeitschritteZuSekunden(wartezeitSchritte_));

  kreuzung_->kreuzungsScene()->removeItem(this);
}



QRectF Fahrzeug::boundingRect() const
{
  return QRectF(-(konfiguration_->fahrzeugBreite / 2),
                -(konfiguration_->fahrzeugLaenge / 2),
                konfiguration_->fahrzeugBreite / 2,
                konfiguration_->fahrzeugLaenge / 2);
}



void Fahrzeug::paint(QPainter* painter,
                     const QStyleOptionGraphicsItem* styleOptionGraphicsItem,
                     QWidget* widget)
{
  painter->drawPixmap(-(konfiguration_->fahrzeugBreite / 2),
                      -(konfiguration_->fahrzeugLaenge / 2),
                      konfiguration_->fahrzeugBreite,
                      konfiguration_->fahrzeugLaenge,
                      car);

  // Punkt, der Wartezeit darstellt
  int farbe = 0;
  int maximum = statistik_->maximaleFahrzeugWartezeitschritte();

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
    /*
     * Am Anfang der Simulation ist der Punkt noch weiß, da noch
     * kein Fahrzeug seine Wartezeit gemeldet hat.
     */
    painter->setBrush(QBrush(QColor(255, 255, 255)));
  }

  painter->drawEllipse(QPoint(0, 0),
                       konfiguration_->fahrzeugBreite / 4,
                       konfiguration_->fahrzeugBreite / 4);
}



void Fahrzeug::bewegen()
{
  if(zielPunkte_.size() != 0)
  {
    qreal xDifferenz = zielPunkte_.front().x() - this->x();
    qreal yDifferenz = zielPunkte_.front().y() - this->y();

    if(qAbs(xDifferenz) < konfiguration_->punktGrenzwert &&
       qAbs(yDifferenz) < konfiguration_->punktGrenzwert)
    {
      /*
       * Fahrzeug ist am Ziel angekommen, und soll dieses Ziel löschen,
       * damit das nächste Ziel angesteuert wird.
       */
      zielPunkte_.removeFirst();
    }
    else
    {
      // Rotation
      qreal winkel = qAtan2(-yDifferenz, xDifferenz);
      winkel *= (180.0 / konfiguration_->pi);

      this->setRotation(90.0 - winkel);

      // Normiere den Vektor
      qreal laenge = qSqrt((xDifferenz * xDifferenz) +
                           (yDifferenz * yDifferenz));

      xDifferenz /= laenge;
      yDifferenz /= laenge;

      // Skaliere den Vektor mit der eingestellten Geschwindigkeit
      xDifferenz *= konfiguration_->fahrzeugGeschwindigkeit;
      yDifferenz *= konfiguration_->fahrzeugGeschwindigkeit;

      // Bewege das Fahrzeug
      this->setX(this->x() + xDifferenz);
      this->setY(this->y() + yDifferenz);
    }
  }
  else
  {
    ++wartezeitSchritte_;
  }
}
