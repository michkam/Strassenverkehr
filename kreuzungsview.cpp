#include "kreuzungsview.h"

#include "konfiguration.h"
#include "statistikdaten.h"
#include "kreuzung.h"

KreuzungsView::KreuzungsView(QWidget* parent,
                             Konfiguration* konfiguration,
                             StatistikDaten* statistikDaten)
  : QGraphicsView(parent)
{
  konfiguration_ = konfiguration;
  statistikDaten_ = statistikDaten;

  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

  kreuzung_ = new Kreuzung(this, konfiguration_, statistikDaten_);

  this->setSceneRect(-(konfiguration_->sceneRectBreite / 2),
                     -(konfiguration_->sceneRectHoehe / 2),
                      konfiguration_->sceneRectBreite,
                      konfiguration_->sceneRectHoehe);

  this->setScene(kreuzung_->kreuzungsScene());

  this->scale(konfiguration_->standardSkalierung,
              konfiguration_->standardSkalierung);

  this->setViewportUpdateMode(
        QGraphicsView::ViewportUpdateMode::FullViewportUpdate);
}



Kreuzung* KreuzungsView::kreuzung()
{
  return kreuzung_;
}



void KreuzungsView::wheelEvent(QWheelEvent* wheelEvent)
{
  setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

  if(wheelEvent->delta() > 0)
  {
    // Vergrößern
    this->scale(konfiguration_->skalierungsFaktor,
                  konfiguration_->skalierungsFaktor);
  }
  else
  {
    // Verkleinern
    this->scale(1.0 / konfiguration_->skalierungsFaktor,
                  1.0 / konfiguration_->skalierungsFaktor);
  }

  wheelEvent->ignore();
}



void KreuzungsView::mousePressEvent(QMouseEvent *mouseEvent)
{
  if(mouseEvent->button() == Qt::MouseButton::LeftButton)
  {
    QGraphicsView::mousePressEvent(mouseEvent);
  }
  else if(mouseEvent->button() == Qt::MouseButton::RightButton)
  {
    resetMatrix();
    resetTransform();
    centerOn(0.0, 0.0);

    this->scale(konfiguration_->standardSkalierung,
                konfiguration_->standardSkalierung);

    mouseEvent->accept();
  }

  mouseEvent->ignore();
}



void KreuzungsView::advance()
{
  kreuzung_->advance();
}
