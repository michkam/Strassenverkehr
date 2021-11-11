#ifndef FAHRZEUGSPUR_H
#define FAHRZEUGSPUR_H

#include <QString>
#include <QList>
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPoint>

class Konfiguration;
class StatistikDaten;
class Kreuzung;
class FahrzeugAmpel;
class Fahrzeug;

class FahrzeugSpur : public QGraphicsItem
{
  public:
    FahrzeugSpur(Kreuzung*, Konfiguration*, StatistikDaten*, FahrzeugAmpel*);

    bool istBelegt() const;
    int anzahlFahrzeuge();

    void erzeugeFahrzeug(QString);
    void leeren();

    FahrzeugAmpel* fahrzeugAmpel();

    void setzeHimmelsrichtung(QString);
    void setzeRichtung(QString);
    void setzeIndex(int);

    QString himmelsrichtung();
    QString richtung();
    int index();

    QRectF boundingRect() const;
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);

    void fortschreiten();
    QPoint wartepunkt(int);

  protected:
    void mousePressEvent(QGraphicsSceneMouseEvent*);

  private:
    Kreuzung* kreuzung_;
    Konfiguration* konfiguration_;
    StatistikDaten* statistik_;

    FahrzeugAmpel* fahrzeugAmpel_;
    QString himmelsrichtung_;
    QString richtung_;
    int index_;

    QList<Fahrzeug*> fahrzeuge_;
    QList<Fahrzeug*> abgebogeneFahrzeuge_;
};

#endif // FAHRZEUGSPUR_H
