#ifndef FUSSGAENGERUEBERWEG_H
#define FUSSGAENGERUEBERWEG_H

#include <QList>
#include <QPainter>
#include <QGraphicsItem>
#include <QPoint>

class Konfiguration;
class StatistikDaten;
class Kreuzung;
class FussgaengerAmpel;
class Fussgaenger;

class FussgaengerUeberweg : public QGraphicsItem
{
  public:
    FussgaengerUeberweg(Kreuzung*, Konfiguration*, StatistikDaten*,
                        FussgaengerAmpel*);

    void setzePunktEins(int, int);
    void setzePunktZwei(int, int);
    void erzeugeFussgaenger();

    void leeren();

    FussgaengerAmpel* fussgaengerAmpel();

    QRectF boundingRect() const;
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);

    void fortschreiten();

  private:
    QPixmap symbol_;

    Kreuzung* kreuzung_;
    Konfiguration* konfiguration_;
    StatistikDaten* statistik_;

    FussgaengerAmpel* fussgaengerAmpel_;

    QPoint punktEins_;
    QPoint punktZwei_;

    QList<Fussgaenger*> fussgaenger_;
    QList<Fussgaenger*> laufendeFussgaenger_;
};

#endif // FUSSGAENGERUEBERWEG_H
