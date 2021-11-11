#ifndef FUSSGAENGERAMPEL_H
#define FUSSGAENGERAMPEL_H

#include <QString>
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

class Konfiguration;
class Kreuzung;

class FussgaengerAmpel : public QGraphicsItem
{
  public:
    FussgaengerAmpel(Kreuzung*, Konfiguration*);

    QString phase() const;
    void wechselZuPhase(QString);

    QRectF boundingRect() const;
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);

  protected:
    void mousePressEvent(QGraphicsSceneMouseEvent*);

  private:
    Kreuzung* kreuzung_;
    Konfiguration* konfiguration_;

    QString zurzeitigePhase_;
};

#endif // FUSSGAENGERAMPEL_H
