#ifndef KREUZUNGSVIEW_H
#define KREUZUNGSVIEW_H

#include <QObject>
#include <QString>
#include <QGraphicsView>
#include <QWheelEvent>
#include <QMouseEvent>

class Konfiguration;
class StatistikDaten;
class Kreuzung;

class KreuzungsView : public QGraphicsView
{
  Q_OBJECT

  public:
    KreuzungsView(QWidget*, Konfiguration*, StatistikDaten*);

    Kreuzung* kreuzung();

  signals:

  public slots:
    void wheelEvent(QWheelEvent*);
    void mousePressEvent(QMouseEvent*);

    void advance();

  private:
    Konfiguration* konfiguration_;
    StatistikDaten* statistikDaten_;
    Kreuzung* kreuzung_;
};

#endif // KREUZUNGSVIEW_H
