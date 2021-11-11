#include "fahrzeugspur.h"

#include <QtDebug>

#include "fussgaengerueberweg.h"
#include "konfiguration.h"
#include "statistikdaten.h"
#include "kreuzung.h"
#include "fahrzeugampel.h"
#include "fahrzeug.h"

FahrzeugSpur::FahrzeugSpur(Kreuzung* kreuzung, Konfiguration* konfiguration,
                           StatistikDaten* statistik, FahrzeugAmpel* ampel)
  : QGraphicsItem(nullptr)
{
  kreuzung_ = kreuzung;
  konfiguration_ = konfiguration;
  statistik_ = statistik;

  fahrzeugAmpel_ = ampel;
  himmelsrichtung_ = "";
  richtung_ = "alle";
  index_ = 0;

  fahrzeuge_ = QList<Fahrzeug*>();
  abgebogeneFahrzeuge_ = QList<Fahrzeug*>();
}



bool FahrzeugSpur::istBelegt() const
{
  if(fahrzeuge_.empty())
  {
    return false;
  }
  else
  {
    if(fahrzeugAmpel_->phase() == "rot")
    {
      /*
       * Die Spur gilt als belegt, wenn die Ampel rot ist und
       * Autos auf ihr stehen
       */
      return true;
    }
    else
    {
      return false;
    }
  }
}



int FahrzeugSpur::anzahlFahrzeuge()
{
  return fahrzeuge_.size();
}



void FahrzeugSpur::erzeugeFahrzeug(QString richtung)
{
  Fahrzeug* neuesFahrzeug = new Fahrzeug(kreuzung_, konfiguration_, statistik_);
  neuesFahrzeug->setzeRichtung(richtung);

  /*
   * Find einen Anfangspunkt für das Fahrzeug.
   */
  QPoint startPunkt = wartepunkt(fahrzeuge_.size());
  if(himmelsrichtung_ == "nord")
  {
    neuesFahrzeug->setRotation(180.0);

    neuesFahrzeug->setPos(
          startPunkt.x(),
          startPunkt.y() - konfiguration_->fahrzeugDistanzBeiErzeugung);
  }
  else if(himmelsrichtung_ == "sued")
  {
    neuesFahrzeug->setRotation(0.0);

    neuesFahrzeug->setPos(
          startPunkt.x(),
          startPunkt.y() + konfiguration_->fahrzeugDistanzBeiErzeugung);
  }
  else if(himmelsrichtung_ == "west")
  {
    neuesFahrzeug->setRotation(90.0);

    neuesFahrzeug->setPos(
          startPunkt.x() - konfiguration_->fahrzeugDistanzBeiErzeugung,
          startPunkt.y());
  }
  else if(himmelsrichtung_ == "ost")
  {
    neuesFahrzeug->setRotation(270.0);

    neuesFahrzeug->setPos(
          startPunkt.x() + konfiguration_->fahrzeugDistanzBeiErzeugung,
          startPunkt.y());
  }
  else
  {
    qDebug() << "In fahrzeugspur.cpp, erzeugeFahrzeug(): Keine gültige "
                "Richtung.";
  }
  neuesFahrzeug->fuegeZielHinzu(startPunkt.x(), startPunkt.y());

  fahrzeuge_.append(neuesFahrzeug);
  kreuzung_->kreuzungsScene()->addItem(neuesFahrzeug);
}



void FahrzeugSpur::leeren()
{
  for(Fahrzeug* fahrzeug : fahrzeuge_)
  {
    kreuzung_->kreuzungsScene()->removeItem(fahrzeug);
  }

  fahrzeuge_.clear();

  for(Fahrzeug* fahrzeug : abgebogeneFahrzeuge_)
  {
    kreuzung_->kreuzungsScene()->removeItem(fahrzeug);
  }

  abgebogeneFahrzeuge_.clear();
}



QPoint FahrzeugSpur::wartepunkt(int a)
{
  /*
   * Diese Funktion soll einen Wartepunkt für die Position "a" geben, damit
   * Fahrzeuge eine Reihe vor einer roten Ampel bilden.
   */
  int x = 0;
  int y = 0;

  if(himmelsrichtung_ == "nord")
  {
    x = -((index_ + 1) * konfiguration_->spurBreite) +
         (konfiguration_->spurBreite / 2);

    y = -(kreuzung_->ausgehendeSpuren("west") * konfiguration_->spurBreite) -
         (a * (konfiguration_->fahrzeugLaenge + konfiguration_->fahrzeugAbstand)) -
         (konfiguration_->fahrzeugLaenge) -
         konfiguration_->wartelinienDistanz;
  }
  else if(himmelsrichtung_ == "sued")
  {
    x = ((index_ + 1) * konfiguration_->spurBreite) -
        (konfiguration_->spurBreite / 2);

    y = (kreuzung_->ausgehendeSpuren("ost") * konfiguration_->spurBreite) +
        (a * (konfiguration_->fahrzeugLaenge + konfiguration_->fahrzeugAbstand)) +
        (konfiguration_->fahrzeugLaenge) +
        konfiguration_->wartelinienDistanz;
  }
  else if(himmelsrichtung_ == "west")
  {
    x = -(kreuzung_->ausgehendeSpuren("sued") * konfiguration_->spurBreite) -
         (a*(konfiguration_->fahrzeugLaenge + konfiguration_->fahrzeugAbstand)) -
         (konfiguration_->fahrzeugLaenge) -
         konfiguration_->wartelinienDistanz;

    y = ((index_ + 1) * konfiguration_->spurBreite) -
        (konfiguration_->spurBreite / 2);
  }
  else if(himmelsrichtung_ == "ost")
  {
    x = (kreuzung_->ausgehendeSpuren("nord") * konfiguration_->spurBreite) +
        (a*(konfiguration_->fahrzeugLaenge + konfiguration_->fahrzeugAbstand)) +
        (konfiguration_->fahrzeugLaenge) +
        konfiguration_->wartelinienDistanz;

    y = -((index_ + 1) * konfiguration_->spurBreite) +
         (konfiguration_->spurBreite / 2);
  }
  else
  {
    qDebug() << "In fahrzeugspur.cpp, wartepunkt(): Keine gültige Richtung";
  }

  return QPoint(x, y);
}



void FahrzeugSpur::setzeHimmelsrichtung(QString himmelsrichtung)
{
  himmelsrichtung_ = himmelsrichtung;
}



void FahrzeugSpur::setzeRichtung(QString richtung)
{
  richtung_ = richtung;
}



void FahrzeugSpur::setzeIndex(int index)
{
  index_ = index;
}



FahrzeugAmpel* FahrzeugSpur::fahrzeugAmpel()
{
  return fahrzeugAmpel_;
}



QString FahrzeugSpur::himmelsrichtung()
{
  return himmelsrichtung_;
}



QString FahrzeugSpur::richtung()
{
  return richtung_;
}



int FahrzeugSpur::index()
{
  return index_;
}



QRectF FahrzeugSpur::boundingRect() const
{
  return QRectF(0.0,
                0.0,
                konfiguration_->spurBreite,
                konfiguration_->spurLaenge);
}



void FahrzeugSpur::paint(QPainter* painter,
                         const QStyleOptionGraphicsItem* styleOption,
                         QWidget* widget)
{
  // Zeichne die Straße
  painter->setPen(konfiguration_->strassenFarbe);
  painter->setBrush(QBrush(konfiguration_->strassenFarbe));
  painter->drawRect(0, 0,
                    konfiguration_->spurBreite,
                    konfiguration_->spurLaenge);


  painter->setPen(QColor(255, 255, 255));
  painter->setBrush(QBrush(QColor(255, 255, 255, 255)));

  // Wartelinie
  painter->drawRect(QRect(0,
                          konfiguration_->wartelinienDistanz,
                          konfiguration_->spurBreite,
                          konfiguration_->wartelinienBreite));

  // Richtungspfeile auf der Fahrbahn
  int n = konfiguration_->anzahlRichtungspfeile;
  int y = 0;
  if(richtung_ == "alle")
  {

  }
  else if(richtung_ == "links")
  {
    for(int i = 0; i < n; ++i)
    {
      painter->drawRect(QRect(125, 900 + y, 35, 650));
      painter->drawRect(QRect(85, 900 + y, 50, 40));

      QPointF punkte[3] = {
        QPointF(85, 880 + y),
        QPointF(15, 920 + y),
        QPointF(85, 960 + y)};
      painter->drawPolygon(punkte, 3);

      y += 2000;
    }
  }
  else if(richtung_ == "rechts")
  {
    for(int i = 0; i < n; ++i)
    {
      painter->drawRect(QRect(125, 900 + y, 35, 650));
      painter->drawRect(QRect(150, 900 + y, 50, 40));

      QPointF punkte[3] = {
        QPointF(200, 880 + y),
        QPointF(270, 920 + y),
        QPointF(200, 960 + y)};
      painter->drawPolygon(punkte, 3);

      y += 2000;
    }
  }
  else if(richtung_ == "geradeaus")
  {
    for(int i = 0; i < n; ++i)
    {
      painter->drawRect(QRect(125, 1050 + y, 35, 500));

      QPointF punkte[3] = {
        QPointF(140, 850 + y),
        QPointF(200, 1050 + y),
        QPointF(90, 1050 + y)};
      painter->drawPolygon(punkte, 3);

      y += 2000;
    }
  }
  else if(richtung_ == "links-geradeaus")
  {
    for(int i = 0; i < n; ++i)
    {
      painter->drawRect(QRect(125, 1050 + y, 35, 500));
      painter->drawRect(QRect(85, 1200 + y, 50, 40));

      QPointF punkteEins[3] = {
        QPointF(140, 850 +y),
        QPointF(200, 1050 + y),
        QPointF(90, 1050 + y)};
      painter->drawPolygon(punkteEins, 3);

      QPointF punkteZwei[3] = {
        QPointF(85, 1180 + y),
        QPointF(15, 1220 + y),
        QPointF(85, 1260 + y)};
      painter->drawPolygon(punkteZwei, 3);

      y += 2000;
    }
  }
  else if(richtung_ == "rechts-geradeaus")
  {
    for(int i = 0; i < n; ++i)
    {
      painter->drawRect(QRect(125, 1050 + y, 35, 500));
      painter->drawRect(QRect(150, 1200 + y, 50, 40));

      QPointF punkteEins[3] = {
        QPointF(140, 850 + y),
        QPointF(200, 1050 + y),
        QPointF(90, 1050 + y)};
      painter->drawPolygon(punkteEins, 3);

      QPointF punkteZwei[3] = {
        QPointF(200, 1180 + y),
        QPointF(270, 1220 + y),
        QPointF(200, 1260 + y)};
      painter->drawPolygon(punkteZwei, 3);

      y += 2000;
    }
  }
  else if(richtung_ == "links-rechts")
  {
    for(int i = 0; i < n; ++i)
    {
      painter->drawRect(QRect(125, 900 + y, 40, 650));
      painter->drawRect(QRect(150, 900 + y, 60, 30));
      painter->drawRect(QRect(85, 900 + y, 40, 30));

      QPointF punkteEins[3] = {
        QPointF(200, 850 + y),
        QPointF(240, 920 + y),
        QPointF(200, 960 + y)};
      painter->drawPolygon(punkteEins, 3);

      QPointF punkteZwei[3] = {
        QPointF(85, 850 + y),
        QPointF(50, 920 + y),
        QPointF(85, 960 + y)};
      painter->drawPolygon(punkteZwei, 3);

      y += 2000;
    }
  }
  else
  {
    qDebug() << "In fahrzeugspur.cpp, paint(): Keine gültige Richtung";
  }

  // Name der Spur schreiben
  painter->setPen(konfiguration_->strassenFarbe);
  painter->setBrush(QBrush(konfiguration_->strassenFarbe));
  painter->setFont(QFont("Arial", konfiguration_->wartelinienBreite / 2));

  painter->drawText(
        QRectF(konfiguration_->spurBreite / 4,
               konfiguration_->wartelinienDistanz,
               konfiguration_->spurBreite,
               konfiguration_->wartelinienBreite),
        QString::number(index_ + 1) + ". " + himmelsrichtung_.toUpper());
}



void FahrzeugSpur::fortschreiten()
{
  for(int i = 0; i < abgebogeneFahrzeuge_.size(); ++i)
  {
    abgebogeneFahrzeuge_[i]->bewegen();

    if(abgebogeneFahrzeuge_[i]->zielpunkteAnzahl() == 0)
    {
      abgebogeneFahrzeuge_[i]->entferne();
      abgebogeneFahrzeuge_.removeAt(i);
    }
  }

  for(int i = 0; i < fahrzeuge_.size(); ++i)
  {
    fahrzeuge_[i]->bewegen();

    if(i == 0)
    {
      if(fahrzeugAmpel_->phase() == "gruen")
      {
        /*
         * Das erste Fahrzeug in der Liste soll bei einer grünen
         * Ampel abbiegen, wenn es den ersten Wartepunkt erreicht hat.
         */

        QPoint ersterWartepunkt = wartepunkt(0);

        int xDifferenz = abs(ersterWartepunkt.x() - fahrzeuge_[0]->x());
        int yDifferenz = abs(ersterWartepunkt.y() - fahrzeuge_[0]->y());

        if(xDifferenz <= konfiguration_->punktGrenzwert &&
           yDifferenz <= konfiguration_->punktGrenzwert)
        {
          /*
           * Generiere einen Pfad, den das Fahrzeug abfahren soll.
           */
          QList<QPoint> pfad =
              kreuzung_->fahrzeugPfad(himmelsrichtung_,
                                      fahrzeuge_[0]->richtung(), index_);

          for(int j = 0; j < pfad.size(); ++j)
          {
            fahrzeuge_[0]->fuegeZielHinzu(pfad[j].x(), pfad[j].y());
          }

          abgebogeneFahrzeuge_.append(fahrzeuge_[0]);
          fahrzeuge_.removeAt(0);
        }
        else
        {
          if(fahrzeuge_[0]->zielpunkteAnzahl() == 0)
          {
            fahrzeuge_[0]->fuegeZielHinzu(ersterWartepunkt.x(),
                                          ersterWartepunkt.y());
          }
        }
      }
      else
      {
        // Aufrücken des ersten Fahrzeugs bei Grün
        if(fahrzeuge_[0]->zielpunkteAnzahl() == 0)
        {
          QPoint neuerWartepunkt = wartepunkt(0);

          int xDifferenz = abs(neuerWartepunkt.x() - fahrzeuge_[0]->x());
          int yDifferenz = abs(neuerWartepunkt.y() - fahrzeuge_[0]->y());

          if(xDifferenz > konfiguration_->punktGrenzwert ||
             yDifferenz > konfiguration_->punktGrenzwert)
          {
            fahrzeuge_[0]->fuegeZielHinzu(neuerWartepunkt.x(),
                                          neuerWartepunkt.y());
          }
        }
      }
    }
    else
    {
      // Aufrücken der Fahrzeuge bei Rot
      if(fahrzeuge_[i]->zielpunkteAnzahl() == 0)
      {
        QPoint neuerWartepunkt = wartepunkt(i);

        int xDifferenz = abs(neuerWartepunkt.x() - fahrzeuge_[i]->x());
        int yDifferenz = abs(neuerWartepunkt.y() - fahrzeuge_[i]->y());

        if(xDifferenz > konfiguration_->punktGrenzwert ||
           yDifferenz > konfiguration_->punktGrenzwert)
        {
          fahrzeuge_[i]->fuegeZielHinzu(neuerWartepunkt.x(),
                                        neuerWartepunkt.y());
        }
      }
    }
  }
}



void FahrzeugSpur::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
  if(!(kreuzung_->istSimulierend()))
  {
    if(richtung_ == "alle")
    {
      richtung_ = "links";
    }
    else if(richtung_ == "links")
    {
      richtung_ = "rechts";
    }
    else if(richtung_ == "rechts")
    {
      richtung_ = "geradeaus";
    }
    else if(richtung_ == "geradeaus")
    {
      richtung_ = "links-geradeaus";
    }
    else if(richtung_ == "links-geradeaus")
    {
      richtung_ = "rechts-geradeaus";
    }
    else if(richtung_ == "rechts-geradeaus")
    {
      richtung_ = "links-rechts";
    }
    else
    {
      richtung_ = "alle";
    }

    kreuzung_->aktualisierePositionen();
    kreuzung_->aktualisiereDekorationen();
    kreuzung_->kreuzungsScene()->update();

    mouseEvent->accept();
  }
  else
  {
    mouseEvent->ignore();
  }
}
