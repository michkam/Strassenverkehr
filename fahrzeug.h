#ifndef FAHRZEUG_H
#define FAHRZEUG_H

#include <qmath.h>

#include <QString>
#include <QList>
#include <QPainter>
#include <QGraphicsItem>
#include <QPixmap>
#include <QPoint>

class Konfiguration;
class StatistikDaten;
class Kreuzung;

class Fahrzeug : public QObject, public QGraphicsItem
{
    Q_OBJECT
  public:
    Fahrzeug(Kreuzung*, Konfiguration*, StatistikDaten*);

    bool istFertig();
    int zielpunkteAnzahl();

    void fuegeZielHinzu(int, int);
    void bewegen();

    QString richtung();
    void setzeRichtung(QString);

    void entferne();

    QRectF boundingRect() const;
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);

  private:
    QPixmap car;

    Kreuzung* kreuzung_;
    StatistikDaten* statistik_;
    Konfiguration* konfiguration_;

    QList<QPoint> zielPunkte_;
    int wartezeitSchritte_;
    bool istFertig_;

    QString richtung_;
};

#endif // FAHRZEUG_H
