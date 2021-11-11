#ifndef FUSSGAENGER_H
#define FUSSGAENGER_H

#include <qmath.h>

#include <QList>
#include <QPainter>
#include <QGraphicsItem>
#include <QPoint>

class Konfiguration;
class StatistikDaten;
class Kreuzung;

class Fussgaenger : public QGraphicsItem
{
  public:
    Fussgaenger(Kreuzung*, Konfiguration*, StatistikDaten*);

    bool istFertig();

    void setzeZielpunkt(int x, int y);
    void bewegen();

    QRectF boundingRect() const;
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);

  private:
    Kreuzung* kreuzung_;
    StatistikDaten* statistik_;
    Konfiguration* konfiguration_;

    QPoint zielPunkt_;
    int wartezeitSchritte_;
    bool istFertig_;
};

#endif // FUSSGAENGER_H
