#include "kreuzung.h"

#include <QtDebug>

#include "konfiguration.h"
#include "statistikdaten.h"
#include "fahrzeugszenario.h"
#include "fussgaengerszenario.h"
#include "fahrzeugspur.h"
#include "fahrzeugampel.h"
#include "fussgaengerueberweg.h"
#include "fussgaengerampel.h"
#include "fahrzeug.h"
#include "fussgaenger.h"

Kreuzung::Kreuzung(QObject* parent, Konfiguration* konfiguration,
                   StatistikDaten* statistikDaten)
  : QObject(parent)
{
  konfiguration_ = konfiguration;
  statistikDaten_ = statistikDaten;

  kreuzungsScene_ = new QGraphicsScene(nullptr);
  kreuzungsScene_->setBackgroundBrush(QBrush(konfiguration_->grasFarbe));

  istSimulierend_ = false;

  aktuellePhase_ = 0;
  istGelbPhase_ = false;
  zeitschritteZurNaechstenPhase_ = 0;

  phasenDauern_ = QList<int>();
  phasenDauern_.append(10);

  fahrzeugAmpelphasen_ = QMap<FahrzeugAmpel*, QList<QString>>();
  fussgaengerAmpelphasen_ = QMap<FussgaengerAmpel*, QList<QString>>();

  nordFahrzeugSpuren_ = QList<FahrzeugSpur*>();
  suedFahrzeugSpuren_ = QList<FahrzeugSpur*>();
  westFahrzeugSpuren_ = QList<FahrzeugSpur*>();
  ostFahrzeugSpuren_ = QList<FahrzeugSpur*>();

  nordFussgaengerUeberweg_ = nullptr;
  suedFussgaengerUeberweg_ = nullptr;
  westFussgaengerUeberweg_ = nullptr;
  ostFussgaengerUeberweg_ = nullptr;

  nordFahrzeugSzenario_ = new FahrzeugSzenario(this, konfiguration_);
  suedFahrzeugSzenario_ = new FahrzeugSzenario(this, konfiguration_);
  westFahrzeugSzenario_ = new FahrzeugSzenario(this, konfiguration_);
  ostFahrzeugSzenario_ = new FahrzeugSzenario(this, konfiguration_);

  nordFussgaengerSzenario_ = new FussgaengerSzenario(this, konfiguration_);
  suedFussgaengerSzenario_ = new FussgaengerSzenario(this, konfiguration_);
  westFussgaengerSzenario_ = new FussgaengerSzenario(this, konfiguration_);
  ostFussgaengerSzenario_ = new FussgaengerSzenario(this, konfiguration_);

  dekorationen_ = QList<QGraphicsRectItem*>();
}



QGraphicsScene* Kreuzung::kreuzungsScene()
{
  return kreuzungsScene_;
}



void Kreuzung::zuruecksetzen()
{
    kreuzungsScene()->clear();

    istSimulierend_ = false;

    aktuellePhase_ = 0;
    istGelbPhase_ = false;
    zeitschritteZurNaechstenPhase_ = 0;
    phasenDauern_.clear();
    phasenDauern_.append(10);
    fahrzeugAmpelphasen_.clear();
    fussgaengerAmpelphasen_.clear();

    nordFahrzeugSpuren_.clear();
    suedFahrzeugSpuren_.clear();
    westFahrzeugSpuren_.clear();
    ostFahrzeugSpuren_.clear();

    nordFussgaengerUeberweg_ = nullptr;
    suedFussgaengerUeberweg_ = nullptr;
    westFussgaengerUeberweg_ = nullptr;
    ostFussgaengerUeberweg_ = nullptr;

    dekorationen_.clear();
}



void Kreuzung::fahrzeugSpurHinzufuegen(QString himmelsrichtung,
                                       QString richtung)
{
  /*
   * Erzeuge eine Ampel und fülle diese mit Phasen auf.
   */
  FahrzeugAmpel* neueAmpel = new FahrzeugAmpel(this, konfiguration_);
  QList<QString> ampelPhasen = QList<QString>();
  for(int i = 0; i < phasenDauern_.size(); ++i)
  {
    ampelPhasen.append(QString("rot"));
  }
  fahrzeugAmpelphasen_.insert(neueAmpel, ampelPhasen);

  /*
   * Erzeuge eine Spur, die eine Referenz auf die vorher
   * erzeugte Ampel bekommt.
   */
  FahrzeugSpur* neueSpur = new FahrzeugSpur(this, konfiguration_,
                                          statistikDaten_, neueAmpel);
  neueSpur->setzeRichtung(richtung);
  neueSpur->setzeHimmelsrichtung(himmelsrichtung);

  /*
   * Positioniere die Spur und die Ampel
   */
  qreal spurPosition;
  qreal ampelPosition;
  if(himmelsrichtung == "nord")
  {
    neueSpur->setzeIndex(nordFahrzeugSpuren_.size());

    spurPosition = -(konfiguration_->spurBreite * nordFahrzeugSpuren_.size());

    neueSpur->setPos(spurPosition, 0.0);
    neueSpur->setRotation(180.0);
    neueSpur->setZValue(-1.0);

    kreuzungsScene_->addItem(neueSpur);
    nordFahrzeugSpuren_.append(neueSpur);

    ampelPosition = spurPosition - (konfiguration_->spurBreite / 2) +
                    (konfiguration_->fahrzeugAmpelBreite / 2);

    neueAmpel->setPos(ampelPosition, 0.0);
    neueAmpel->setRotation(180.0);
    neueAmpel->setZValue(1.0);

    kreuzungsScene_->addItem(neueAmpel);
  }
  else if(himmelsrichtung == "sued")
  {
    neueSpur->setzeIndex(suedFahrzeugSpuren_.size());

    spurPosition = konfiguration_->spurBreite * suedFahrzeugSpuren_.size();

    neueSpur->setPos(spurPosition, 0.0);
    neueSpur->setZValue(-1.0);
    kreuzungsScene_->addItem(neueSpur);
    suedFahrzeugSpuren_.append(neueSpur);

    ampelPosition = spurPosition + (konfiguration_->spurBreite / 2) -
                    (konfiguration_->fahrzeugAmpelBreite / 2);

    neueAmpel->setPos(ampelPosition, 0.0);
    neueAmpel->setZValue(1.0);

    kreuzungsScene_->addItem(neueAmpel);
  }
  else if(himmelsrichtung == "west")
  {
    neueSpur->setzeIndex(westFahrzeugSpuren_.size());

    spurPosition = konfiguration_->spurBreite * westFahrzeugSpuren_.size();

    neueSpur->setPos(0.0, spurPosition);
    neueSpur->setRotation(90.0);
    neueSpur->setZValue(-1.0);

    kreuzungsScene_->addItem(neueSpur);
    westFahrzeugSpuren_.append(neueSpur);

    ampelPosition = spurPosition + (konfiguration_->spurBreite / 2) -
                    (konfiguration_->fahrzeugAmpelBreite / 2);

    neueAmpel->setPos(0.0, ampelPosition);
    neueAmpel->setRotation(90.0);
    neueAmpel->setZValue(1.0);

    kreuzungsScene_->addItem(neueAmpel);
  }
  else if(himmelsrichtung == "ost")
  {
    neueSpur->setzeIndex(ostFahrzeugSpuren_.size());

    spurPosition = -(konfiguration_->spurBreite * ostFahrzeugSpuren_.size());

    neueSpur->setPos(0.0, spurPosition);
    neueSpur->setRotation(270.0);
    neueSpur->setZValue(-1.0);

    kreuzungsScene_->addItem(neueSpur);
    ostFahrzeugSpuren_.append(neueSpur);

    ampelPosition = spurPosition - (konfiguration_->spurBreite / 2) +
                    (konfiguration_->fahrzeugAmpelBreite / 2);

    neueAmpel->setPos(0.0, ampelPosition);
    neueAmpel->setRotation(270.0);

    neueAmpel->setZValue(1.0);

    kreuzungsScene_->addItem(neueAmpel);
  }
  else
  {
    qDebug() << "In kreuzung.cpp, fahrzeugSpurHinzufuegen(): Keine gültige "
                "Himmelsrichtung";
  }

  aktualisierePositionen();
  aktualisiereDekorationen();
}



void Kreuzung::fahrzeugSpurEntfernen(QString himmelsrichtung)
{
  if(himmelsrichtung == "nord")
  {
    if(!(nordFahrzeugSpuren_.isEmpty()))
    {
      kreuzungsScene_->removeItem(nordFahrzeugSpuren_.last()->fahrzeugAmpel());
      fahrzeugAmpelphasen_.remove(nordFahrzeugSpuren_.last()->fahrzeugAmpel());

      kreuzungsScene_->removeItem(nordFahrzeugSpuren_.last());
      nordFahrzeugSpuren_.removeLast();
    }
  }
  else if(himmelsrichtung == "sued")
  {
    if(!(suedFahrzeugSpuren_.isEmpty()))
    {
      kreuzungsScene_->removeItem(suedFahrzeugSpuren_.last()->fahrzeugAmpel());
      fahrzeugAmpelphasen_.remove(suedFahrzeugSpuren_.last()->fahrzeugAmpel());

      kreuzungsScene_->removeItem(suedFahrzeugSpuren_.last());
      suedFahrzeugSpuren_.removeLast();
    }
  }
  else if(himmelsrichtung == "west")
  {
    if(!(westFahrzeugSpuren_.isEmpty()))
    {
      kreuzungsScene_->removeItem(westFahrzeugSpuren_.last()->fahrzeugAmpel());
      fahrzeugAmpelphasen_.remove(westFahrzeugSpuren_.last()->fahrzeugAmpel());

      kreuzungsScene_->removeItem(westFahrzeugSpuren_.last());
      westFahrzeugSpuren_.removeLast();
    }
  }
  else if(himmelsrichtung == "ost")
  {
    if(!(ostFahrzeugSpuren_.isEmpty()))
    {
      kreuzungsScene_->removeItem(ostFahrzeugSpuren_.last()->fahrzeugAmpel());
      fahrzeugAmpelphasen_.remove(ostFahrzeugSpuren_.last()->fahrzeugAmpel());

      kreuzungsScene_->removeItem(ostFahrzeugSpuren_.last());
      ostFahrzeugSpuren_.removeLast();
    }
  }
  else
  {
    qDebug() << "In kreuzung.cpp, fahrzeugSpurEntfernen: Keine gültige "
                "Himmelsrichtung";
  }

  aktualisierePositionen();
  aktualisiereDekorationen();
}



void Kreuzung::fussgaengerUeberwegUmschalten(QString himmelsrichtung)
{
  if(himmelsrichtung == QString("nord"))
  {
    if(nordFussgaengerUeberweg_ == nullptr)
    {
      if(nordFahrzeugSpuren_.isEmpty() &&
         ausgehendeSpuren("nord") == 0)
      {
        qDebug() << "In kreuzung.cpp, fussgaengerUeberwegUmschalten(): "
                    "Der Fußgängerüberweg benötigt eine Straße.";
      }
      else
      {
        FussgaengerAmpel* ampel = new FussgaengerAmpel(this, konfiguration_);
        FussgaengerUeberweg* ueberweg =
            new FussgaengerUeberweg(this, konfiguration_, statistikDaten_,
                                    ampel);

        QList<QString> phasen = QList<QString>();
        for(int i = 0; i < phasenDauern_.size(); ++i)
        {
          phasen.append(QString("rot"));
        }

        fussgaengerAmpelphasen_.insert(ampel, phasen);

        ueberweg->setZValue(-0.75);
        ampel->setZValue(1.0);

        kreuzungsScene_->addItem(ampel);
        kreuzungsScene_->addItem(ueberweg);

        nordFussgaengerUeberweg_ = ueberweg;
      }
    }
    else
    {
      kreuzungsScene_->removeItem(
            nordFussgaengerUeberweg_->fussgaengerAmpel());

      fussgaengerAmpelphasen_.remove(
            nordFussgaengerUeberweg_->fussgaengerAmpel());

      kreuzungsScene_->removeItem(nordFussgaengerUeberweg_);

      nordFussgaengerUeberweg_ = nullptr;
    }
  }
  else if(himmelsrichtung == QString("sued"))
  {
    if(suedFussgaengerUeberweg_ == nullptr)
    {
      if(suedFahrzeugSpuren_.isEmpty() &&
         ausgehendeSpuren("sued") == 0)
      {
        qDebug() << "In kreuzung.cpp, fussgaengerUeberwegUmschalten(): "
                    "Der Fußgängerüberweg benötigt eine Straße.";
      }
      else
      {
        FussgaengerAmpel* ampel = new FussgaengerAmpel(this, konfiguration_);
        FussgaengerUeberweg* ueberweg =
            new FussgaengerUeberweg(this, konfiguration_, statistikDaten_,
                                    ampel);

        QList<QString> phasen = QList<QString>();
        for(int i = 0; i < phasenDauern_.size(); ++i)
        {
          phasen.append(QString("rot"));
        }

        fussgaengerAmpelphasen_.insert(ampel, phasen);

        ueberweg->setZValue(-0.75);
        ampel->setZValue(1.0);

        kreuzungsScene_->addItem(ampel);
        kreuzungsScene_->addItem(ueberweg);

        suedFussgaengerUeberweg_ = ueberweg;
      }
    }
    else
    {
      kreuzungsScene_->removeItem(
            suedFussgaengerUeberweg_->fussgaengerAmpel());

      fussgaengerAmpelphasen_.remove(
            suedFussgaengerUeberweg_->fussgaengerAmpel());

      kreuzungsScene_->removeItem(suedFussgaengerUeberweg_);

      suedFussgaengerUeberweg_ = nullptr;
    }
  }
  else if(himmelsrichtung == QString("west"))
  {
    if(westFussgaengerUeberweg_ == nullptr)
    {
      if(westFahrzeugSpuren_.isEmpty() &&
         ausgehendeSpuren("west") == 0)
      {
        qDebug() << "In kreuzung.cpp, fussgaengerUeberwegUmschalten(): "
                    "Der Fußgängerüberweg benötigt eine Straße.";
      }
      else
      {
        FussgaengerAmpel* ampel = new FussgaengerAmpel(this, konfiguration_);
        FussgaengerUeberweg* ueberweg =
            new FussgaengerUeberweg(this, konfiguration_, statistikDaten_,
                                    ampel);

        QList<QString> phasen = QList<QString>();
        for(int i = 0; i < phasenDauern_.size(); ++i)
        {
          phasen.append(QString("rot"));
        }

        fussgaengerAmpelphasen_.insert(ampel, phasen);

        ueberweg->setZValue(-0.75);
        ampel->setZValue(1.0);

        kreuzungsScene_->addItem(ampel);
        kreuzungsScene_->addItem(ueberweg);

        westFussgaengerUeberweg_ = ueberweg;
      }
    }
    else
    {
      kreuzungsScene_->removeItem(
            westFussgaengerUeberweg_->fussgaengerAmpel());

      fussgaengerAmpelphasen_.remove(
            westFussgaengerUeberweg_->fussgaengerAmpel());

      kreuzungsScene_->removeItem(westFussgaengerUeberweg_);

      westFussgaengerUeberweg_ = nullptr;
    }
  }
  else if(himmelsrichtung == QString("ost"))
  {
    if(ostFussgaengerUeberweg_ == nullptr)
    {
      if(ostFahrzeugSpuren_.isEmpty() &&
         ausgehendeSpuren("ost") == 0)
      {
        qDebug() << "In kreuzung.cpp, fussgaengerUeberwegUmschalten(): "
                    "Der Fußgängerüberweg benötigt eine Straße.";
      }
      else
      {
        FussgaengerAmpel* ampel = new FussgaengerAmpel(this, konfiguration_);
        FussgaengerUeberweg* ueberweg =
            new FussgaengerUeberweg(this, konfiguration_, statistikDaten_,
                                    ampel);

        QList<QString> phasen = QList<QString>();
        for(int i = 0; i < phasenDauern_.size(); ++i)
        {
          phasen.append(QString("rot"));
        }

        fussgaengerAmpelphasen_.insert(ampel, phasen);

        ueberweg->setZValue(-0.75);
        ampel->setZValue(1.0);

        kreuzungsScene_->addItem(ampel);
        kreuzungsScene_->addItem(ueberweg);

        ostFussgaengerUeberweg_ = ueberweg;
      }
    }
    else
    {
      kreuzungsScene_->removeItem(
            ostFussgaengerUeberweg_->fussgaengerAmpel());

      fussgaengerAmpelphasen_.remove(
            ostFussgaengerUeberweg_->fussgaengerAmpel());

      kreuzungsScene_->removeItem(ostFussgaengerUeberweg_);

      ostFussgaengerUeberweg_ = nullptr;
    }
  }
  else
  {
    qDebug() << "In kreuzung.cpp, fussgaengerUeberwegUmschalten(): "
                "Keine gültige Himmelsrichtung";
  }

  aktualisierePositionen();
}



void Kreuzung::fuegeAmpelphaseHinzu()
{
  phasenDauern_.append(phasenDauern_[aktuellePhase_]);

  for(auto& phasen : fahrzeugAmpelphasen_)
  {
    phasen.append(QString("rot"));
  }

  for(auto& phasen : fussgaengerAmpelphasen_)
  {
    phasen.append(QString("rot"));
  }
}



void Kreuzung::entferneAmpelphase()
{
  if(phasenDauern_.size() > 1)
  {
    phasenDauern_.removeAt(aktuellePhase_);

    for(auto& phasen : fahrzeugAmpelphasen_)
    {
      phasen.removeAt(aktuellePhase_);
    }

    for(auto& phasen : fussgaengerAmpelphasen_)
    {
      phasen.removeAt(aktuellePhase_);
    }

    if(aktuellePhase_ >= phasenDauern_.size())
    {
      aktuellePhase_ = phasenDauern_.size() - 1;

      wechselZuAmpelphase(aktuellePhase_);
    }
  }
}



void Kreuzung::wechselZurzeitigeFahrzeugAmpelphase(FahrzeugAmpel* ampel)
{
  if(!(istSimulierend_))
  {
    if(fahrzeugAmpelphasen_[ampel][aktuellePhase_] == "rot")
    {
      fahrzeugAmpelphasen_[ampel][aktuellePhase_] = "gruen";
    }
    else
    {
      fahrzeugAmpelphasen_[ampel][aktuellePhase_] = "rot";
    }

    wechselZuAmpelphase(aktuellePhase_);
  }
}



void Kreuzung::wechselZurzeitigeFussgaengerAmpelphase(FussgaengerAmpel*
                                                        ampel)
{
  if(!(istSimulierend_))
  {
    if(fussgaengerAmpelphasen_[ampel][aktuellePhase_] == "rot")
    {
      fussgaengerAmpelphasen_[ampel][aktuellePhase_] = "gruen";
    }
    else
    {
      fussgaengerAmpelphasen_[ampel][aktuellePhase_] = "rot";
    }

    wechselZuAmpelphase(aktuellePhase_);
  }
}



void Kreuzung::wechselZuAmpelphase(int phase)
{
  aktuellePhase_ = phase;

  for(FahrzeugAmpel* ampel : fahrzeugAmpelphasen_.keys())
  {
    ampel->wechselZuPhase(fahrzeugAmpelphasen_[ampel][phase]);
  }

  for(FussgaengerAmpel* ampel : fussgaengerAmpelphasen_.keys())
  {
    ampel->wechselZuPhase(fussgaengerAmpelphasen_[ampel][phase]);
  }

  kreuzungsScene_->update();
}



void Kreuzung::aktualisierePhasenListe(QListView* listView)
{
  /*
   * Aktualisiert den ListView für die Ampelphasen,
   * der von der SimulationGUI benutzt wird.
   */
  QStringListModel* listModel = new QStringListModel(listView);
  QStringList stringList;

  for(int i = 0; i < phasenDauern_.size(); ++i)
  {
    stringList.append("Phase " + QString::number(i + 1) + ": " +
                      QString::number(phasenDauern_[i]) + " Sekunde(n)");
  }

  listModel->setStringList(stringList);

  listView->setModel(listModel);
  listView->setCurrentIndex(listModel->index(aktuellePhase_));
}



void Kreuzung::setzeStatusBar(QStatusBar* statusBar)
{
  statusBar_ = statusBar;
}



void Kreuzung::oeffnePhasendauerDialog(QWidget* parent)
{
  PhasendauerGUI* phasendauerGUI =
      new PhasendauerGUI(parent, &(phasenDauern_[aktuellePhase_]));

  phasendauerGUI->exec();
}



void Kreuzung::oeffneFahrzeugSzenarioDialog(QWidget* parent,
                                            QString himmelsrichtung)
{
  FahrzeugSzenarioGUI* szenarioGUI;

  if(himmelsrichtung == QString("nord"))
  {
    szenarioGUI = new FahrzeugSzenarioGUI(parent, nordFahrzeugSzenario_);

    szenarioGUI->show();

    // Aktiviere nur die Slider für die es Spuren gibt
    for(auto spur : nordFahrzeugSpuren_)
    {
      if(spur->richtung() == "alle")
      {
        szenarioGUI->linksSliderAktivieren();
        szenarioGUI->geradeausSliderAktivieren();
        szenarioGUI->rechtsSliderAktivieren();
      }
      else if(spur->richtung() == "links")
      {
        szenarioGUI->linksSliderAktivieren();
      }
      else if(spur->richtung() == "rechts")
      {
        szenarioGUI->rechtsSliderAktivieren();
      }
      else if(spur->richtung() == "geradeaus")
      {
        szenarioGUI->geradeausSliderAktivieren();
      }
      else if(spur->richtung() == "links-geradeaus")
      {
        szenarioGUI->linksSliderAktivieren();
        szenarioGUI->geradeausSliderAktivieren();
      }
      else if(spur->richtung() == "rechts-geradeaus")
      {
        szenarioGUI->geradeausSliderAktivieren();
        szenarioGUI->rechtsSliderAktivieren();
      }
      else if(spur->richtung() == "links-rechts")
      {
        szenarioGUI->linksSliderAktivieren();
        szenarioGUI->rechtsSliderAktivieren();
      }
      else
      {
        qDebug() << "In kreuzung.cpp, oeffneFahrzeugSzenarioDialog(): "
                    "Ungültige Richtung.";
      }
    }
  }
  else if(himmelsrichtung == QString("sued"))
  {
    szenarioGUI = new FahrzeugSzenarioGUI(parent, suedFahrzeugSzenario_);

    szenarioGUI->show();

    // Aktiviere nur die Slider für die es Spuren gibt
    for(auto spur : suedFahrzeugSpuren_)
    {
      if(spur->richtung() == "alle")
      {
        szenarioGUI->linksSliderAktivieren();
        szenarioGUI->geradeausSliderAktivieren();
        szenarioGUI->rechtsSliderAktivieren();
      }
      else if(spur->richtung() == "links")
      {
        szenarioGUI->linksSliderAktivieren();
      }
      else if(spur->richtung() == "rechts")
      {
        szenarioGUI->rechtsSliderAktivieren();
      }
      else if(spur->richtung() == "geradeaus")
      {
        szenarioGUI->geradeausSliderAktivieren();
      }
      else if(spur->richtung() == "links-geradeaus")
      {
        szenarioGUI->linksSliderAktivieren();
        szenarioGUI->geradeausSliderAktivieren();
      }
      else if(spur->richtung() == "rechts-geradeaus")
      {
        szenarioGUI->geradeausSliderAktivieren();
        szenarioGUI->rechtsSliderAktivieren();
      }
      else if(spur->richtung() == "links-rechts")
      {
        szenarioGUI->linksSliderAktivieren();
        szenarioGUI->rechtsSliderAktivieren();
      }
      else
      {
        qDebug() << "In kreuzung.cpp, oeffneFahrzeugSzenarioDialog(): "
                    "Ungültige Richtung.";
      }
    }
  }
  else if(himmelsrichtung == QString("west"))
  {
    szenarioGUI = new FahrzeugSzenarioGUI(parent, westFahrzeugSzenario_);

    szenarioGUI->show();

    // Aktiviere nur die Slider für die es Spuren gibt
    for(auto spur : westFahrzeugSpuren_)
    {
      if(spur->richtung() == "alle")
      {
        szenarioGUI->linksSliderAktivieren();
        szenarioGUI->geradeausSliderAktivieren();
        szenarioGUI->rechtsSliderAktivieren();
      }
      else if(spur->richtung() == "links")
      {
        szenarioGUI->linksSliderAktivieren();
      }
      else if(spur->richtung() == "rechts")
      {
        szenarioGUI->rechtsSliderAktivieren();
      }
      else if(spur->richtung() == "geradeaus")
      {
        szenarioGUI->geradeausSliderAktivieren();
      }
      else if(spur->richtung() == "links-geradeaus")
      {
        szenarioGUI->linksSliderAktivieren();
        szenarioGUI->geradeausSliderAktivieren();
      }
      else if(spur->richtung() == "rechts-geradeaus")
      {
        szenarioGUI->geradeausSliderAktivieren();
        szenarioGUI->rechtsSliderAktivieren();
      }
      else if(spur->richtung() == "links-rechts")
      {
        szenarioGUI->linksSliderAktivieren();
        szenarioGUI->rechtsSliderAktivieren();
      }
      else
      {
        qDebug() << "In kreuzung.cpp, oeffneFahrzeugSzenarioDialog(): "
                    "Ungültige Richtung.";
      }
    }
  }
  else if(himmelsrichtung == QString("ost"))
  {
    szenarioGUI = new FahrzeugSzenarioGUI(parent, ostFahrzeugSzenario_);

    szenarioGUI->show();

    // Aktiviere nur die Slider für die es Spuren gibt
    for(auto spur : ostFahrzeugSpuren_)
    {
      if(spur->richtung() == "alle")
      {
        szenarioGUI->linksSliderAktivieren();
        szenarioGUI->geradeausSliderAktivieren();
        szenarioGUI->rechtsSliderAktivieren();
      }
      else if(spur->richtung() == "links")
      {
        szenarioGUI->linksSliderAktivieren();
      }
      else if(spur->richtung() == "rechts")
      {
        szenarioGUI->rechtsSliderAktivieren();
      }
      else if(spur->richtung() == "geradeaus")
      {
        szenarioGUI->geradeausSliderAktivieren();
      }
      else if(spur->richtung() == "links-geradeaus")
      {
        szenarioGUI->linksSliderAktivieren();
        szenarioGUI->geradeausSliderAktivieren();
      }
      else if(spur->richtung() == "rechts-geradeaus")
      {
        szenarioGUI->geradeausSliderAktivieren();
        szenarioGUI->rechtsSliderAktivieren();
      }
      else if(spur->richtung() == "links-rechts")
      {
        szenarioGUI->linksSliderAktivieren();
        szenarioGUI->rechtsSliderAktivieren();
      }
      else
      {
        qDebug() << "In kreuzung.cpp, oeffneFahrzeugSzenarioDialog(): "
                    "Ungültige Richtung.";
      }
    }
  }
}



void Kreuzung::oeffneFussgaengerSzenarioDialog(QWidget* parent,
                                               QString himmelsrichtung)
{
  FussgaengerSzenarioGUI* szenarioGUI;

  if(himmelsrichtung == QString("nord"))
  {
    szenarioGUI = new FussgaengerSzenarioGUI(parent, nordFussgaengerSzenario_);

    szenarioGUI->show();
  }
  else if(himmelsrichtung == QString("sued"))
  {
    szenarioGUI = new FussgaengerSzenarioGUI(parent, suedFussgaengerSzenario_);

    szenarioGUI->show();
  }
  else if(himmelsrichtung == QString("west"))
  {
    szenarioGUI = new FussgaengerSzenarioGUI(parent, westFussgaengerSzenario_);

    szenarioGUI->show();
  }
  else if(himmelsrichtung == QString("ost"))
  {
    szenarioGUI = new FussgaengerSzenarioGUI(parent, ostFussgaengerSzenario_);

    szenarioGUI->show();
  }
}



bool Kreuzung::istSimulierend() const
{
  return istSimulierend_;
}



QList<QPoint> Kreuzung::fahrzeugPfad(QString himmelsrichtung,
                                     QString richtung,
                                     int index)
{
  QList<QPoint> pfad = QList<QPoint>();

  int x = 0;
  int y = 0;

  // 1. Punkt => In die Kreuzung vorfahren
  if(himmelsrichtung == "nord")
  {
    x = -((index + 1) * konfiguration_->spurBreite) +
         (konfiguration_->spurBreite / 2);
    y = -(ausgehendeSpuren("west") * konfiguration_->spurBreite) +
         (konfiguration_->spurBreite / 2);
  }
  else if(himmelsrichtung == "sued")
  {
    x = ((index + 1) * konfiguration_->spurBreite) -
        (konfiguration_->spurBreite / 2);
    y = (ausgehendeSpuren("ost") * konfiguration_->spurBreite) -
        (konfiguration_->spurBreite / 2);
  }
  else if(himmelsrichtung == "west")
  {
    x = -(ausgehendeSpuren("sued") * konfiguration_->spurBreite) +
         (konfiguration_->spurBreite / 2);
    y = ((index + 1) * konfiguration_->spurBreite) -
        (konfiguration_->spurBreite / 2);
  }
  else if(himmelsrichtung == "ost")
  {
    x = (ausgehendeSpuren("nord") * konfiguration_->spurBreite) -
        (konfiguration_->spurBreite / 2);
    y = -((index + 1) * konfiguration_->spurBreite) +
         (konfiguration_->spurBreite / 2);
  }
  else
  {
    qDebug() << "In kreuzung.cpp, fahrzeugPfad(): Keine gültige "
                "Himmelsrichtung";
  }
  pfad.append(QPoint(x, y));

  if(richtung == "geradeaus")
  {
    // 2. Punkt: Kreuzung verlassen
    if(himmelsrichtung == "nord")
    {
      y += 20000;
      pfad.append(QPoint(x, y));
    }
    else if(himmelsrichtung == "sued")
    {
      y -= 20000;
      pfad.append(QPoint(x, y));
    }
    else if(himmelsrichtung == "west")
    {
      x += 20000;
      pfad.append(QPoint(x, y));
    }
    else if(himmelsrichtung == "ost")
    {
      x -= 20000;
      pfad.append(QPoint(x, y));
    }
    else
    {
      qDebug() << "In kreuzung.cpp, fahrzeugPfad(): Keine gültige "
                  "Himmelsrichtung";
    }
  }
  else if(richtung == "links")
  {
    // 2. Punkt: Abbiegezielpunkt
    // 3. Punkt: Kreuzung verlassen
    if(himmelsrichtung == "nord")
    {
      int ziel = 1;
      for(int i = index - 1; i >= 0; --i)
      {
        if(nordFahrzeugSpuren_[i]->richtung() == "alle" ||
           nordFahrzeugSpuren_[i]->richtung() == "links" ||
           nordFahrzeugSpuren_[i]->richtung() == "links-geradeaus" ||
           nordFahrzeugSpuren_[i]->richtung() == "links-rechts")
        {
          ++ziel;
        }
      }

      x = ausgehendeSpuren("nord") * konfiguration_->spurBreite;
      y = ziel * konfiguration_->spurBreite -
          konfiguration_->spurBreite / 2;
      pfad.append(QPoint(x, y));

      x += 20000;
      pfad.append(QPoint(x, y));
    }
    else if(himmelsrichtung == "sued")
    {
      int ziel = 1;
      for(int i = index - 1; i >= 0; --i)
      {
        if(suedFahrzeugSpuren_[i]->richtung() == "alle" ||
           suedFahrzeugSpuren_[i]->richtung() == "links" ||
           suedFahrzeugSpuren_[i]->richtung() == "links-geradeaus" ||
           suedFahrzeugSpuren_[i]->richtung() == "links-rechts")
        {
          ++ziel;
        }
      }

      x = -(ausgehendeSpuren("sued") * konfiguration_->spurBreite);
      y = -(ziel * konfiguration_->spurBreite) +
           konfiguration_->spurBreite / 2;
      pfad.append(QPoint(x, y));

      x -= 20000;
      pfad.append(QPoint(x, y));
    }
    else if(himmelsrichtung == "west")
    {
      int ziel = 1;
      for(int i = index - 1; i >= 0; --i)
      {
        if(westFahrzeugSpuren_[i]->richtung() == "alle" ||
           westFahrzeugSpuren_[i]->richtung() == "links" ||
           westFahrzeugSpuren_[i]->richtung() == "links-geradeaus" ||
           westFahrzeugSpuren_[i]->richtung() == "links-rechts")
        {
          ++ziel;
        }
      }

      x = ziel * konfiguration_->spurBreite -
          konfiguration_->spurBreite / 2;
      y = -(ausgehendeSpuren("west") * konfiguration_->spurBreite);
      pfad.append(QPoint(x, y));

      y -= 20000;
      pfad.append(QPoint(x, y));
    }
    else if(himmelsrichtung == "ost")
    {
      int ziel = 1;
      for(int i = index - 1; i >= 0; --i)
      {
        if(ostFahrzeugSpuren_[i]->richtung() == "alle" ||
           ostFahrzeugSpuren_[i]->richtung() == "links" ||
           ostFahrzeugSpuren_[i]->richtung() == "links-geradeaus" ||
           ostFahrzeugSpuren_[i]->richtung() == "links-rechts")
        {
          ++ziel;
        }
      }

      x = -(ziel * konfiguration_->spurBreite) +
           konfiguration_->spurBreite / 2;
      y = ausgehendeSpuren("ost") * konfiguration_->spurBreite;
      pfad.append(QPoint(x, y));

      y += 20000;
      pfad.append(QPoint(x, y));
    }
    else
    {
      qDebug() << "In kreuzung.cpp, fahrzeugPfad(): Keine gültige "
                  "Himmelsrichtung";
    }
  }
  else if(richtung == "rechts")
  {
    // 2. Punkt: Abbiegezielpunkt
    // 3. Punkt: Kreuzung verlassen
    if(himmelsrichtung == "nord")
    {
      int ziel = 0;
      for(int i = index + 1; i < nordFahrzeugSpuren_.size(); ++i)
      {
        if(nordFahrzeugSpuren_[i]->richtung() == "alle" ||
           nordFahrzeugSpuren_[i]->richtung() == "rechts" ||
           nordFahrzeugSpuren_[i]->richtung() == "rechts-geradeaus" ||
           nordFahrzeugSpuren_[i]->richtung() == "links-rechts")
        {
          ++ziel;
        }
      }

      x = -(nordFahrzeugSpuren_.size() * konfiguration_->spurBreite);
      y = -(ausgehendeSpuren("west") * konfiguration_->spurBreite) +
          ziel * konfiguration_->spurBreite +
          konfiguration_->spurBreite / 2;
      pfad.append(QPoint(x, y));

      x -= 20000;
      pfad.append(QPoint(x, y));
    }
    else if(himmelsrichtung == "sued")
    {
      int ziel = 0;
      for(int i = index + 1; i < suedFahrzeugSpuren_.size(); ++i)
      {
        if(suedFahrzeugSpuren_[i]->richtung() == "alle" ||
           suedFahrzeugSpuren_[i]->richtung() == "rechts" ||
           suedFahrzeugSpuren_[i]->richtung() == "rechts-geradeaus" ||
           suedFahrzeugSpuren_[i]->richtung() == "links-rechts")
        {
          ++ziel;
        }
      }

      x = suedFahrzeugSpuren_.size() * konfiguration_->spurBreite;
      y = ausgehendeSpuren("ost") * konfiguration_->spurBreite -
          ziel * konfiguration_->spurBreite -
          konfiguration_->spurBreite / 2;
      pfad.append(QPoint(x, y));

      x += 20000;
      pfad.append(QPoint(x, y));
    }
    else if(himmelsrichtung == "west")
    {
      int ziel = 0;
      for(int i = index + 1; i < westFahrzeugSpuren_.size(); ++i)
      {
        if(westFahrzeugSpuren_[i]->richtung() == "alle" ||
           westFahrzeugSpuren_[i]->richtung() == "rechts" ||
           westFahrzeugSpuren_[i]->richtung() == "rechts-geradeaus" ||
           westFahrzeugSpuren_[i]->richtung() == "links-rechts")
        {
          ++ziel;
        }
      }

      x = -(ausgehendeSpuren("sued") * konfiguration_->spurBreite) +
           ziel * konfiguration_->spurBreite +
           konfiguration_->spurBreite / 2;
      y = westFahrzeugSpuren_.size() * konfiguration_->spurBreite;
      pfad.append(QPoint(x, y));

      y += 20000;
      pfad.append(QPoint(x, y));
    }
    else if(himmelsrichtung == "ost")
    {
      int ziel = 0;
      for(int i = index + 1; i < ostFahrzeugSpuren_.size(); ++i)
      {
        if(ostFahrzeugSpuren_[i]->richtung() == "alle" ||
           ostFahrzeugSpuren_[i]->richtung() == "rechts" ||
           ostFahrzeugSpuren_[i]->richtung() == "rechts-geradeaus" ||
           ostFahrzeugSpuren_[i]->richtung() == "links-rechts")
        {
          ++ziel;
        }
      }

      x = ausgehendeSpuren("nord") * konfiguration_->spurBreite -
          ziel * konfiguration_->spurBreite -
          konfiguration_->spurBreite / 2;
      y = -(ostFahrzeugSpuren_.size() * konfiguration_->spurBreite);
      pfad.append(QPoint(x, y));

      y -= 20000;
      pfad.append(QPoint(x, y));
    }
    else
    {
      qDebug() << "In kreuzung.cpp, fahrzeugPfad(): Keine gültige "
                  "Himmelsrichtung";
    }
  }
  else
  {
    qDebug() << "In kreuzung.cpp, fahrzeugPfad(): Keine gültige "
                "Richtung";
  }

  return pfad;
}



void Kreuzung::starteSimulation()
{
  statistikDaten_->zuruecksetzen();

  // Leere die Kreuzung
  for(FahrzeugSpur* spur : nordFahrzeugSpuren_)
  {
    statistikDaten_->spurHinzufuegen(spur);

    spur->leeren();
  }

  for(FahrzeugSpur* spur : suedFahrzeugSpuren_)
  {
    statistikDaten_->spurHinzufuegen(spur);

    spur->leeren();
  }

  for(FahrzeugSpur* spur : westFahrzeugSpuren_)
  {
    statistikDaten_->spurHinzufuegen(spur);

    spur->leeren();
  }

  for(FahrzeugSpur* spur : ostFahrzeugSpuren_)
  {
    statistikDaten_->spurHinzufuegen(spur);

    spur->leeren();
  }

  if(nordFussgaengerUeberweg_ != nullptr)
  {
    nordFussgaengerUeberweg_->leeren();
  }

  if(suedFussgaengerUeberweg_ != nullptr)
  {
    suedFussgaengerUeberweg_->leeren();
  }

  if(westFussgaengerUeberweg_ != nullptr)
  {
    westFussgaengerUeberweg_->leeren();
  }

  if(ostFussgaengerUeberweg_ != nullptr)
  {
    ostFussgaengerUeberweg_->leeren();
  }

  // Setze Ampelphasen zurück
  aktuellePhase_ = 0;
  zeitschritteZurNaechstenPhase_ =
      konfiguration_->sekundenZuZeitschritte(phasenDauern_[aktuellePhase_]);
  wechselZuAmpelphase(aktuellePhase_);

  istSimulierend_ = true;
}



void Kreuzung::stoppeSimulation()
{
  // Leere die Kreuzung
  for(FahrzeugSpur* spur : nordFahrzeugSpuren_)
  {
    spur->leeren();
  }

  for(FahrzeugSpur* spur : suedFahrzeugSpuren_)
  {
    spur->leeren();
  }

  for(FahrzeugSpur* spur : westFahrzeugSpuren_)
  {
    spur->leeren();
  }

  for(FahrzeugSpur* spur : ostFahrzeugSpuren_)
  {
    spur->leeren();
  }

  if(nordFussgaengerUeberweg_ != nullptr)
  {
    nordFussgaengerUeberweg_->leeren();
  }

  if(suedFussgaengerUeberweg_ != nullptr)
  {
    suedFussgaengerUeberweg_->leeren();
  }

  if(westFussgaengerUeberweg_ != nullptr)
  {
    westFussgaengerUeberweg_->leeren();
  }

  if(ostFussgaengerUeberweg_ != nullptr)
  {
    ostFussgaengerUeberweg_->leeren();
  }

  // Beseitige eine eventuelle Gelb-Phase
  if(istGelbPhase_)
  {
    wechselZuAmpelphase(aktuellePhase_);
  }

  // Aktualisiere Statusleiste des Hauptfensters
  statusBar_->showMessage(QString("Passen Sie die Simulations"
                                  "geschwindigkeit mit dem Slider "
                                  "von 0x (pausiert) bis 4x an."));

  istSimulierend_ = false;
}



QString Kreuzung::kreuzungZuString()
{
  QString kreuzungsDaten = "";

  // Schreibe Phasendauern
  for(int i = 0; i < phasenDauern_.size(); ++i)
  {
    kreuzungsDaten += QString::number(phasenDauern_[i]);

    if(i < (phasenDauern_.size() - 1))
    {
      kreuzungsDaten += ";";
    }
  }
  kreuzungsDaten += "\n---\n";

  // Schreibe Fahrzeugspuren
  for(int i = 0; i < nordFahrzeugSpuren_.size(); ++i)
  {
    kreuzungsDaten += nordFahrzeugSpuren_[i]->richtung();
    kreuzungsDaten += ":";

    for(auto phase :
        fahrzeugAmpelphasen_[nordFahrzeugSpuren_[i]->fahrzeugAmpel()])
    {
      kreuzungsDaten += phase;

      kreuzungsDaten += ";";
    }

    kreuzungsDaten += "\n";
  }
  kreuzungsDaten += "---\n";

  for(int i = 0; i < suedFahrzeugSpuren_.size(); ++i)
  {
    kreuzungsDaten += suedFahrzeugSpuren_[i]->richtung();
    kreuzungsDaten += ":";

    for(auto phase :
        fahrzeugAmpelphasen_[suedFahrzeugSpuren_[i]->fahrzeugAmpel()])
    {
      kreuzungsDaten += phase;

      kreuzungsDaten += ";";
    }

    kreuzungsDaten += "\n";
  }
  kreuzungsDaten += "---\n";

  for(int i = 0; i < westFahrzeugSpuren_.size(); ++i)
  {
    kreuzungsDaten += westFahrzeugSpuren_[i]->richtung();
    kreuzungsDaten += ":";

    for(auto phase :
        fahrzeugAmpelphasen_[westFahrzeugSpuren_[i]->fahrzeugAmpel()])
    {
      kreuzungsDaten += phase;

      kreuzungsDaten += ";";
    }

    kreuzungsDaten += "\n";
  }
  kreuzungsDaten += "---\n";

  for(int i = 0; i < ostFahrzeugSpuren_.size(); ++i)
  {
    kreuzungsDaten += ostFahrzeugSpuren_[i]->richtung();
    kreuzungsDaten += ":";

    for(auto phase :
        fahrzeugAmpelphasen_[ostFahrzeugSpuren_[i]->fahrzeugAmpel()])
    {
      kreuzungsDaten += phase;

      kreuzungsDaten += ";";
    }

    kreuzungsDaten += "\n";
  }
  kreuzungsDaten += "---\n";

  // Schreibe Fußgängerüberwege und deren Ampelphasen
  if(nordFussgaengerUeberweg_ != nullptr)
  {
    kreuzungsDaten += "y:";

    for(auto phase :
        fussgaengerAmpelphasen_[nordFussgaengerUeberweg_->fussgaengerAmpel()])
    {
      kreuzungsDaten += phase;

      kreuzungsDaten += ";";
    }
  }
  else
  {
    kreuzungsDaten += "n";
  }
  kreuzungsDaten += "\n---\n";

  if(suedFussgaengerUeberweg_ != nullptr)
  {
    kreuzungsDaten += "y:";

    for(auto phase :
        fussgaengerAmpelphasen_[suedFussgaengerUeberweg_->fussgaengerAmpel()])
    {
      kreuzungsDaten += phase;

      kreuzungsDaten += ";";
    }
  }
  else
  {
    kreuzungsDaten += "n";
  }
  kreuzungsDaten += "\n---\n";

  if(westFussgaengerUeberweg_ != nullptr)
  {
    kreuzungsDaten += "y:";

    for(auto phase :
        fussgaengerAmpelphasen_[westFussgaengerUeberweg_->fussgaengerAmpel()])
    {
      kreuzungsDaten += phase;

      kreuzungsDaten += ";";
    }
  }
  else
  {
    kreuzungsDaten += "n";
  }
  kreuzungsDaten += "\n---\n";

  if(ostFussgaengerUeberweg_ != nullptr)
  {
    kreuzungsDaten += "y:";

    for(auto phase :
        fussgaengerAmpelphasen_[ostFussgaengerUeberweg_->fussgaengerAmpel()])
    {
      kreuzungsDaten += phase;

      kreuzungsDaten += ";";
    }
  }
  else
  {
    kreuzungsDaten += "n";
  }

  return kreuzungsDaten;
}



void Kreuzung::kreuzungAusString(QString& gespeicherteKreuzung)
{
  phasenDauern_.clear();

  int mode = 0;

  QStringList lines = gespeicherteKreuzung.split('\n');

  QStringList doppelpunktTeilung;
  QStringList semikolonTeilung;

  QList<QString> phasen;
  for(int i = 0; i < lines.size(); ++i)
  {
    if(lines[i] == "---")
    {
      mode += 1;
      continue;
    }

    doppelpunktTeilung = lines[i].split(':');

    if(mode == 0)
    {
      semikolonTeilung = lines[i].split(';');
    }
    else if(doppelpunktTeilung.size() == 2)
    {
      semikolonTeilung = doppelpunktTeilung[1].split(';');
    }
    else
    {
      continue;
    }

    switch(mode)
    {
      case 0:
        // Phasendauern
        for(QString wort : semikolonTeilung)
        {
          phasenDauern_.append(wort.toInt());
        }
        break;
      case 1:
        // Nord-Spuren
        fahrzeugSpurHinzufuegen(QString("nord"), doppelpunktTeilung[0]);

        phasen = QList<QString>();
        for(QString wort : semikolonTeilung)
        {
          if(wort.size() > 0)
          {
            phasen.append(wort);
          }
        }

        fahrzeugAmpelphasen_.insert(nordFahrzeugSpuren_.last()->fahrzeugAmpel(),
                                    phasen);
        break;
      case 2:
        // Süd-Spuren
        fahrzeugSpurHinzufuegen(QString("sued"), doppelpunktTeilung[0]);

        phasen = QList<QString>();
        for(QString wort : semikolonTeilung)
        {
          if(wort.size() > 0)
          {
            phasen.append(wort);
          }
        }

        fahrzeugAmpelphasen_.insert(suedFahrzeugSpuren_.last()->fahrzeugAmpel(),
                                    phasen);
        break;
      case 3:
        // West-Spuren
        fahrzeugSpurHinzufuegen(QString("west"), doppelpunktTeilung[0]);

        phasen = QList<QString>();
        for(QString wort : semikolonTeilung)
        {
          if(wort.size() > 0)
          {
            phasen.append(wort);
          }
        }

        fahrzeugAmpelphasen_.insert(westFahrzeugSpuren_.last()->fahrzeugAmpel(),
                                    phasen);
        break;
      case 4:
        // Ost-Spuren
        fahrzeugSpurHinzufuegen(QString("ost"), doppelpunktTeilung[0]);

        phasen = QList<QString>();
        for(QString wort : semikolonTeilung)
        {
          if(wort.size() > 0)
          {
            phasen.append(wort);
          }
        }

        fahrzeugAmpelphasen_.insert(ostFahrzeugSpuren_.last()->fahrzeugAmpel(),
                                    phasen);
        break;
      case 5:
        // Nord-Fußgängerüberweg
        if(doppelpunktTeilung.size() == 2)
        {
          if(doppelpunktTeilung[0] == "y")
          {
            fussgaengerUeberwegUmschalten(QString("nord"));

            phasen = QList<QString>();
            for(QString wort : semikolonTeilung)
            {
              if(wort.size() > 0)
              {
                phasen.append(wort);
              }
            }

            fussgaengerAmpelphasen_.insert(
                  nordFussgaengerUeberweg_->fussgaengerAmpel(), phasen);
          }
        }
        break;
      case 6:
        // Süd-Fußgängerüberweg
        if(doppelpunktTeilung.size() == 2)
        {
          if(doppelpunktTeilung[0] == "y")
          {
            fussgaengerUeberwegUmschalten(QString("sued"));

            phasen = QList<QString>();
            for(QString wort : semikolonTeilung)
            {
              if(wort.size() > 0)
              {
                phasen.append(wort);
              }
            }

            fussgaengerAmpelphasen_.insert(
                  suedFussgaengerUeberweg_->fussgaengerAmpel(), phasen);
          }
        }
        break;
      case 7:
        // West-Fußgängerüberweg
        if(doppelpunktTeilung.size() == 2)
        {
          if(doppelpunktTeilung[0] == "y")
          {
            fussgaengerUeberwegUmschalten(QString("west"));

            phasen = QList<QString>();
            for(QString wort : semikolonTeilung)
            {
              if(wort.size() > 0)
              {
                phasen.append(wort);
              }
            }

            fussgaengerAmpelphasen_.insert(
                  westFussgaengerUeberweg_->fussgaengerAmpel(), phasen);
          }
        }
        break;
      case 8:
        // Ost-Fußgängerüberweg
        if(doppelpunktTeilung.size() == 2)
        {
          if(doppelpunktTeilung[0] == "y")
          {
            fussgaengerUeberwegUmschalten(QString("ost"));

            phasen = QList<QString>();
            for(QString wort : semikolonTeilung)
            {
              if(wort.size() > 0)
              {
                phasen.append(wort);
              }
            }

            fussgaengerAmpelphasen_.insert(
                  ostFussgaengerUeberweg_->fussgaengerAmpel(), phasen);
          }
        }
        break;
      default:
        break;
    }
  }

  wechselZuAmpelphase(aktuellePhase_);
}



void Kreuzung::aktualisierePositionen()
{
  qreal positionNord = -(konfiguration_->spurBreite *
                         ausgehendeSpuren(QString("west")));

  qreal positionSued = konfiguration_->spurBreite *
                       ausgehendeSpuren(QString("ost"));

  qreal positionWest = -(konfiguration_->spurBreite *
                         ausgehendeSpuren(QString("sued")));

  qreal positionOst = konfiguration_->spurBreite *
                      ausgehendeSpuren(QString("nord"));

  // Fahrzugspuren
  for(FahrzeugSpur* spur : nordFahrzeugSpuren_)
  {
    spur->setPos(spur->pos().x(), positionNord);

    spur->fahrzeugAmpel()->setPos(spur->fahrzeugAmpel()->pos().x(),
                                  positionNord);
  }

  for(FahrzeugSpur* spur : suedFahrzeugSpuren_)
  {
    spur->setPos(spur->pos().x(), positionSued);

    spur->fahrzeugAmpel()->setPos(spur->fahrzeugAmpel()->pos().x(),
                                  positionSued);
  }

  for(FahrzeugSpur* spur : westFahrzeugSpuren_)
  {
    spur->setPos(positionWest, spur->pos().y());

    spur->fahrzeugAmpel()->setPos(positionWest,
                                  spur->fahrzeugAmpel()->pos().y());
  }

  for(FahrzeugSpur* spur : ostFahrzeugSpuren_)
  {
    spur->setPos(positionOst, spur->pos().y());

    spur->fahrzeugAmpel()->setPos(positionOst,
                                  spur->fahrzeugAmpel()->pos().y());
  }

  // Fussgängerüberwege
  if(nordFussgaengerUeberweg_ != nullptr)
  {
    nordFussgaengerUeberweg_->setPos(
          0,
          positionNord - konfiguration_->fahrzeugAmpelLaenge -
          nordFussgaengerUeberweg_->boundingRect().height() / 2);

    nordFussgaengerUeberweg_->fussgaengerAmpel()->setPos(
          -(konfiguration_->spurBreite *
            nordFahrzeugSpuren_.size()),
          positionNord - konfiguration_->fahrzeugAmpelLaenge -
          nordFussgaengerUeberweg_->boundingRect().height() / 2);

    nordFussgaengerUeberweg_->setzePunktEins(
          positionWest - 100,
          positionNord - konfiguration_->fahrzeugAmpelLaenge -
          nordFussgaengerUeberweg_->boundingRect().height() / 2);

    nordFussgaengerUeberweg_->setzePunktZwei(
          positionOst + 100,
          positionNord - konfiguration_->fahrzeugAmpelLaenge -
          nordFussgaengerUeberweg_->boundingRect().height() / 2);

    nordFussgaengerUeberweg_->setRotation(180.0);
    nordFussgaengerUeberweg_->fussgaengerAmpel()->setRotation(180.0);
  }

  if(suedFussgaengerUeberweg_ != nullptr)
  {
    suedFussgaengerUeberweg_->setPos(
          0,
          positionSued + konfiguration_->fahrzeugAmpelLaenge +
          suedFussgaengerUeberweg_->boundingRect().height() / 2);

    suedFussgaengerUeberweg_->fussgaengerAmpel()->setPos(
          konfiguration_->spurBreite *
          suedFahrzeugSpuren_.size(),
          positionSued + konfiguration_->fahrzeugAmpelLaenge +
          suedFussgaengerUeberweg_->boundingRect().height() / 2);

    suedFussgaengerUeberweg_->setzePunktEins(
          positionOst + 200,
          positionSued + konfiguration_->fahrzeugAmpelLaenge +
          suedFussgaengerUeberweg_->boundingRect().height() / 2);

    suedFussgaengerUeberweg_->setzePunktZwei(
          positionWest - 100,
          positionSued + konfiguration_->fahrzeugAmpelLaenge +
          suedFussgaengerUeberweg_->boundingRect().height() / 2);
  }

  if(westFussgaengerUeberweg_ != nullptr)
  {
    westFussgaengerUeberweg_->setPos(
          positionWest - konfiguration_->fahrzeugAmpelLaenge -
          westFussgaengerUeberweg_->boundingRect().height() / 2,
          0);

    westFussgaengerUeberweg_->fussgaengerAmpel()->setPos(
          positionWest - konfiguration_->fahrzeugAmpelLaenge -
          westFussgaengerUeberweg_->boundingRect().height() / 2,
          konfiguration_->spurBreite *
          westFahrzeugSpuren_.size());

    westFussgaengerUeberweg_->setzePunktEins(
          positionWest - konfiguration_->fahrzeugAmpelLaenge -
          westFussgaengerUeberweg_->boundingRect().height() / 2,
          positionSued + 200);

    westFussgaengerUeberweg_->setzePunktZwei(
          positionWest - konfiguration_->fahrzeugAmpelLaenge -
          westFussgaengerUeberweg_->boundingRect().height() / 2,
          positionNord - 200);

    westFussgaengerUeberweg_->setRotation(90.0);
    westFussgaengerUeberweg_->fussgaengerAmpel()->setRotation(90.0);
  }

  if(ostFussgaengerUeberweg_ != nullptr)
  {
    ostFussgaengerUeberweg_->setPos(
          positionOst + konfiguration_->fahrzeugAmpelLaenge +
          ostFussgaengerUeberweg_->boundingRect().height() / 2,
          0);

    ostFussgaengerUeberweg_->fussgaengerAmpel()->setPos(
          positionOst + konfiguration_->fahrzeugAmpelLaenge +
          ostFussgaengerUeberweg_->boundingRect().height() / 2,
          -(konfiguration_->spurBreite *
            ostFahrzeugSpuren_.size()));

    ostFussgaengerUeberweg_->setzePunktEins(
          positionOst + konfiguration_->fahrzeugAmpelLaenge +
          ostFussgaengerUeberweg_->boundingRect().height() / 2,
          positionNord - 100);

    ostFussgaengerUeberweg_->setzePunktZwei(
          positionOst + konfiguration_->fahrzeugAmpelLaenge +
          ostFussgaengerUeberweg_->boundingRect().height() / 2,
          positionSued + 100);

    ostFussgaengerUeberweg_->setRotation(270.0);
    ostFussgaengerUeberweg_->fussgaengerAmpel()->setRotation(270.0);
  }
}



void Kreuzung::aktualisiereDekorationen()
{
  for(QGraphicsRectItem* rect : dekorationen_)
  {
    kreuzungsScene()->removeItem(rect);
  }
  dekorationen_.clear();

  qreal x;
  qreal y;
  qreal width;
  qreal height;

  QGraphicsRectItem* tempRect;

  // 1. Dekoration: Ausgehende Spuren
  // Nord
  if(ausgehendeSpuren("nord") > 0)
  {
    x = 0.0;
    y = -(konfiguration_->sceneRectHoehe / 2);
    width = konfiguration_->spurBreite * ausgehendeSpuren(QString("nord"));
    height = (konfiguration_->sceneRectHoehe / 2);

    tempRect = new QGraphicsRectItem(x, y, width, height);
    tempRect->setPen(QPen(konfiguration_->strassenFarbe));
    tempRect->setBrush(QBrush(konfiguration_->strassenFarbe));
    tempRect->setZValue(-1.0);

    kreuzungsScene_->addItem(tempRect);
    dekorationen_.append(tempRect);
  }

  // Süd
  if(ausgehendeSpuren("sued") > 0)
  {
    x = 0.0;
    y = -(konfiguration_->sceneRectHoehe / 2);
    width = konfiguration_->spurBreite * ausgehendeSpuren(QString("sued"));
    height = (konfiguration_->sceneRectHoehe / 2);

    tempRect = new QGraphicsRectItem(x, y, width, height);
    tempRect->setPen(QPen(konfiguration_->strassenFarbe));
    tempRect->setBrush(QBrush(konfiguration_->strassenFarbe));
    tempRect->setRotation(180.0);
    tempRect->setZValue(-1.0);

    kreuzungsScene_->addItem(tempRect);
    dekorationen_.append(tempRect);
  }

  // West
  if(ausgehendeSpuren("west") > 0)
  {
    x = 0.0;
    y = -(konfiguration_->sceneRectHoehe / 2);
    width = konfiguration_->spurBreite * ausgehendeSpuren(QString("west"));
    height = (konfiguration_->sceneRectHoehe / 2);

    tempRect = new QGraphicsRectItem(x, y, width, height);
    tempRect->setPen(QPen(konfiguration_->strassenFarbe));
    tempRect->setBrush(QBrush(konfiguration_->strassenFarbe));
    tempRect->setRotation(270.0);
    tempRect->setZValue(-1.0);

    kreuzungsScene_->addItem(tempRect);
    dekorationen_.append(tempRect);
  }

  // Ost
  if(ausgehendeSpuren("ost") > 0)
  {
    x = 0.0;
    y = -(konfiguration_->sceneRectHoehe / 2);
    width = konfiguration_->spurBreite * ausgehendeSpuren(QString("ost"));
    height = (konfiguration_->sceneRectHoehe / 2);

    tempRect = new QGraphicsRectItem(x, y, width, height);
    tempRect->setPen(QPen(konfiguration_->strassenFarbe));
    tempRect->setBrush(QBrush(konfiguration_->strassenFarbe));
    tempRect->setRotation(90.0);
    tempRect->setZValue(-1.0);

    kreuzungsScene_->addItem(tempRect);
    dekorationen_.append(tempRect);
  }

  // 2. Dekoration: Markierungen
  qreal topBorder = -(konfiguration_->spurBreite *
                      ausgehendeSpuren(QString("west")));
  qreal bottomBorder = konfiguration_->spurBreite *
                       ausgehendeSpuren(QString("ost"));

  qreal leftBorder = -(konfiguration_->spurBreite *
                       ausgehendeSpuren(QString("sued")));
  qreal rightBorder = konfiguration_->spurBreite *
                      ausgehendeSpuren(QString("nord"));
  // Nord
  if(ausgehendeSpuren(QString("nord")) > 0 &&
     nordFahrzeugSpuren_.size() > 0)
  {
    tempRect = new QGraphicsRectItem(-(konfiguration_->spurBreite / 20),
                                     topBorder - 750,
                                     konfiguration_->spurBreite / 10,
                                     -(konfiguration_->sceneRectHoehe / 2));
    tempRect->setPen(QPen(QColor(255, 255, 255)));
    tempRect->setBrush(QBrush(QColor(255, 255, 255)));
    // tempRect->setRotation(180.0);
    tempRect->setZValue(-0.5);

    kreuzungsScene_->addItem(tempRect);
    dekorationen_.append(tempRect);
  }

  // Süd
  if(ausgehendeSpuren(QString("sued")) > 0 &&
     suedFahrzeugSpuren_.size() > 0)
  {
    tempRect = new QGraphicsRectItem(-(konfiguration_->spurBreite / 20),
                                     bottomBorder + 750,
                                     konfiguration_->spurBreite / 10,
                                     konfiguration_->sceneRectHoehe / 2);
    tempRect->setPen(QPen(QColor(255, 255, 255)));
    tempRect->setBrush(QBrush(QColor(255, 255, 255)));
    tempRect->setZValue(-0.5);

    kreuzungsScene_->addItem(tempRect);
    dekorationen_.append(tempRect);
  }

  // West
  if(ausgehendeSpuren(QString("west")) > 0 &&
     westFahrzeugSpuren_.size() > 0)
  {
    tempRect = new QGraphicsRectItem(leftBorder - 750,
                                     -(konfiguration_->spurBreite / 20),
                                     -(konfiguration_->sceneRectBreite / 2),
                                     konfiguration_->spurBreite / 10);
    tempRect->setPen(QPen(QColor(255, 255, 255)));
    tempRect->setBrush(QBrush(QColor(255, 255, 255)));
    tempRect->setZValue(-0.5);

    kreuzungsScene_->addItem(tempRect);
    dekorationen_.append(tempRect);
  }

  // Ost
  if(ausgehendeSpuren(QString("ost")) > 0 &&
     ostFahrzeugSpuren_.size() > 0)
  {
    tempRect = new QGraphicsRectItem(rightBorder + 750,
                                     -(konfiguration_->spurBreite / 20),
                                     konfiguration_->sceneRectBreite / 2,
                                     konfiguration_->spurBreite / 10);
    tempRect->setPen(QPen(QColor(255, 255, 255)));
    tempRect->setBrush(QBrush(QColor(255, 255, 255)));
    tempRect->setZValue(-0.5);

    kreuzungsScene_->addItem(tempRect);
    dekorationen_.append(tempRect);
  }

  // 3. Dekoration: Bürgersteige
  qreal buergersteigPosition;
  qreal buergersteigBreite;

  // Nord
  if(nordFahrzeugSpuren_.size() > 0 || ausgehendeSpuren("nord") > 0)
  {
    buergersteigPosition = (nordFahrzeugSpuren_.size()) *
                           konfiguration_->spurBreite +
                           konfiguration_->fussgaengerUeberwegBreite;

    buergersteigBreite = (nordFahrzeugSpuren_.size() +
                          ausgehendeSpuren(QString("nord"))) *
                         konfiguration_->spurBreite +
                         konfiguration_->fussgaengerUeberwegBreite * 2;

    tempRect = new QGraphicsRectItem(-buergersteigPosition,
                                     0.0,
                                     buergersteigBreite,
                                     -(konfiguration_->sceneRectHoehe / 2));
    tempRect->setPen(QPen(konfiguration_->buergersteigsFarbe));
    tempRect->setBrush(QBrush(konfiguration_->buergersteigsFarbe));
    tempRect->setZValue(-2.0);

    kreuzungsScene_->addItem(tempRect);
    dekorationen_.append(tempRect);
  }

  // Süd
  if(suedFahrzeugSpuren_.size() > 0 || ausgehendeSpuren("sued") > 0)
  {
    buergersteigPosition = ausgehendeSpuren(QString("sued")) *
                           konfiguration_->spurBreite +
                           konfiguration_->fussgaengerUeberwegBreite;

    buergersteigBreite = (suedFahrzeugSpuren_.size() +
                          ausgehendeSpuren(QString("sued"))) *
                         konfiguration_->spurBreite +
                         konfiguration_->fussgaengerUeberwegBreite * 2;

    tempRect = new QGraphicsRectItem(-buergersteigPosition,
                                     0.0,
                                     buergersteigBreite,
                                     konfiguration_->sceneRectHoehe / 2);
    tempRect->setPen(QPen(konfiguration_->buergersteigsFarbe));
    tempRect->setBrush(QBrush(konfiguration_->buergersteigsFarbe));
    tempRect->setZValue(-2.0);

    kreuzungsScene_->addItem(tempRect);
    dekorationen_.append(tempRect);
  }

  // West
  if(westFahrzeugSpuren_.size() > 0 || ausgehendeSpuren("west") > 0)
  {
    buergersteigPosition = (ausgehendeSpuren(QString("west"))) *
                           konfiguration_->spurBreite +
                           konfiguration_->fussgaengerUeberwegBreite;

    buergersteigBreite = (westFahrzeugSpuren_.size() +
                          ausgehendeSpuren(QString("west"))) *
                         konfiguration_->spurBreite +
                         konfiguration_->fussgaengerUeberwegBreite * 2;

    tempRect = new QGraphicsRectItem(0.0,
                                     -buergersteigPosition,
                                     -(konfiguration_->sceneRectBreite / 2),
                                     buergersteigBreite);
    tempRect->setPen(QPen(konfiguration_->buergersteigsFarbe));
    tempRect->setBrush(QBrush(konfiguration_->buergersteigsFarbe));
    tempRect->setZValue(-2.0);

    kreuzungsScene_->addItem(tempRect);
    dekorationen_.append(tempRect);
  }

  // Ost
  if(ostFahrzeugSpuren_.size() > 0 || ausgehendeSpuren("ost") > 0)
  {
    buergersteigPosition = (ostFahrzeugSpuren_.size()) *
                           konfiguration_->spurBreite +
                           konfiguration_->fussgaengerUeberwegBreite;

    buergersteigBreite = (ostFahrzeugSpuren_.size() +
                          ausgehendeSpuren(QString("ost"))) *
                         konfiguration_->spurBreite +
                         konfiguration_->fussgaengerUeberwegBreite * 2;

    tempRect = new QGraphicsRectItem(0.0,
                                     -buergersteigPosition,
                                     (konfiguration_->sceneRectBreite / 2),
                                     buergersteigBreite);
    tempRect->setPen(QPen(konfiguration_->buergersteigsFarbe));
    tempRect->setBrush(QBrush(konfiguration_->buergersteigsFarbe));
    tempRect->setZValue(-2.0);

    kreuzungsScene_->addItem(tempRect);
    dekorationen_.append(tempRect);
  }

  kreuzungsScene_->update();
}



void Kreuzung::advance()
{
  if(istSimulierend_)
  {
    statistikDaten_->advance();

    // Zähle die Zeit von jeden Fahrzeugszenario runter
    nordFahrzeugSzenario_->advance();
    suedFahrzeugSzenario_->advance();
    westFahrzeugSzenario_->advance();
    ostFahrzeugSzenario_->advance();

    // Zähle die Zeit von jeden Fussgaengerszenario runter
    nordFussgaengerSzenario_->advance();
    suedFussgaengerSzenario_->advance();
    westFussgaengerSzenario_->advance();
    ostFussgaengerSzenario_->advance();

    // Bewege die Fahrzeuge auf den Spuren
    for(auto x : nordFahrzeugSpuren_)
    {
      x->fortschreiten();
    }

    for(auto x : suedFahrzeugSpuren_)
    {
      x->fortschreiten();
    }

    for(auto x : westFahrzeugSpuren_)
    {
      x->fortschreiten();
    }

    for(auto x : ostFahrzeugSpuren_)
    {
      x->fortschreiten();
    }

    // Bewege die Fussgänger
    if(nordFussgaengerUeberweg_ != nullptr)
    {
      nordFussgaengerUeberweg_->fortschreiten();
    }

    if(suedFussgaengerUeberweg_ != nullptr)
    {
      suedFussgaengerUeberweg_->fortschreiten();
    }

    if(westFussgaengerUeberweg_ != nullptr)
    {
      westFussgaengerUeberweg_->fortschreiten();
    }

    if(ostFussgaengerUeberweg_ != nullptr)
    {
      ostFussgaengerUeberweg_->fortschreiten();
    }

    // Erzeuge Fahrzeuge
    if(nordFahrzeugSzenario_->sollFahrzeugErzeugtWerden())
    {
      QString zielRichtung = nordFahrzeugSzenario_->waehleRichtung();

      bool spurGefunden = false;
      int minimumIndex = 0;
      for(int i = 0; i < nordFahrzeugSpuren_.size(); ++i)
      {
        if(nordFahrzeugSpuren_[i]->anzahlFahrzeuge() <=
           nordFahrzeugSpuren_[minimumIndex]->anzahlFahrzeuge())
        {
          // Prüfe Richtung
          if(zielRichtung == "links")
          {
            if(nordFahrzeugSpuren_[i]->richtung() == "alle" ||
               nordFahrzeugSpuren_[i]->richtung() == "links" ||
               nordFahrzeugSpuren_[i]->richtung() == "links-rechts" ||
               nordFahrzeugSpuren_[i]->richtung() == "links-geradeaus")
            {
              minimumIndex = i;
              spurGefunden = true;
            }
          }
          else if(zielRichtung == "rechts")
          {
            if(nordFahrzeugSpuren_[i]->richtung() == "alle" ||
               nordFahrzeugSpuren_[i]->richtung() == "rechts" ||
               nordFahrzeugSpuren_[i]->richtung() == "links-rechts" ||
               nordFahrzeugSpuren_[i]->richtung() == "rechts-geradeaus")
            {
              minimumIndex = i;
              spurGefunden = true;
            }
          }
          else if(zielRichtung == "geradeaus")
          {
            if(nordFahrzeugSpuren_[i]->richtung() == "alle" ||
               nordFahrzeugSpuren_[i]->richtung() == "geradeaus" ||
               nordFahrzeugSpuren_[i]->richtung() == "links-geradeaus" ||
               nordFahrzeugSpuren_[i]->richtung() == "rechts-geradeaus")
            {
              minimumIndex = i;
              spurGefunden = true;
            }
          }
          else
          {
            qDebug() << "In kreuzung.cpp, advance(): Keine gültige "
                        "Zielrichtung";
          }
        }
      }

      if(spurGefunden)
      {
        nordFahrzeugSpuren_[minimumIndex]->erzeugeFahrzeug(zielRichtung);
      }

      nordFahrzeugSzenario_->setzeZeitschritteZurueck();
    }

    if(suedFahrzeugSzenario_->sollFahrzeugErzeugtWerden())
    {
      QString zielRichtung = suedFahrzeugSzenario_->waehleRichtung();

      bool spurGefunden = false;
      int minimumIndex = 0;
      for(int i = 0; i < suedFahrzeugSpuren_.size(); ++i)
      {
        if(suedFahrzeugSpuren_[i]->anzahlFahrzeuge() <=
           suedFahrzeugSpuren_[minimumIndex]->anzahlFahrzeuge())
        {
          // Prüfe Richtung
          if(zielRichtung == "links")
          {
            if(suedFahrzeugSpuren_[i]->richtung() == "alle" ||
               suedFahrzeugSpuren_[i]->richtung() == "links" ||
               suedFahrzeugSpuren_[i]->richtung() == "links-rechts" ||
               suedFahrzeugSpuren_[i]->richtung() == "links-geradeaus")
            {
              minimumIndex = i;
              spurGefunden = true;
            }
          }
          else if(zielRichtung == "rechts")
          {
            if(suedFahrzeugSpuren_[i]->richtung() == "alle" ||
               suedFahrzeugSpuren_[i]->richtung() == "rechts" ||
               suedFahrzeugSpuren_[i]->richtung() == "links-rechts" ||
               suedFahrzeugSpuren_[i]->richtung() == "rechts-geradeaus")
            {
              minimumIndex = i;
              spurGefunden = true;
            }
          }
          else if(zielRichtung == "geradeaus")
          {
            if(suedFahrzeugSpuren_[i]->richtung() == "alle" ||
               suedFahrzeugSpuren_[i]->richtung() == "geradeaus" ||
               suedFahrzeugSpuren_[i]->richtung() == "links-geradeaus" ||
               suedFahrzeugSpuren_[i]->richtung() == "rechts-geradeaus")
            {
              minimumIndex = i;
              spurGefunden = true;
            }
          }
          else
          {
            qDebug() << "In kreuzung.cpp, advance(): Keine gültige "
                        "Zielrichtung";
          }
        }
      }

      if(spurGefunden)
      {
        suedFahrzeugSpuren_[minimumIndex]->erzeugeFahrzeug(zielRichtung);
      }

      suedFahrzeugSzenario_->setzeZeitschritteZurueck();
    }

    if(westFahrzeugSzenario_->sollFahrzeugErzeugtWerden())
    {
      QString zielRichtung = nordFahrzeugSzenario_->waehleRichtung();

      bool spurGefunden = false;
      int minimumIndex = 0;
      for(int i = 0; i < westFahrzeugSpuren_.size(); ++i)
      {
        if(westFahrzeugSpuren_[i]->anzahlFahrzeuge() <=
           westFahrzeugSpuren_[minimumIndex]->anzahlFahrzeuge())
        {
          // Prüfe Richtung
          if(zielRichtung == "links")
          {
            if(westFahrzeugSpuren_[i]->richtung() == "alle" ||
               westFahrzeugSpuren_[i]->richtung() == "links" ||
               westFahrzeugSpuren_[i]->richtung() == "links-rechts" ||
               westFahrzeugSpuren_[i]->richtung() == "links-geradeaus")
            {
              minimumIndex = i;
              spurGefunden = true;
            }
          }
          else if(zielRichtung == "rechts")
          {
            if(westFahrzeugSpuren_[i]->richtung() == "alle" ||
               westFahrzeugSpuren_[i]->richtung() == "rechts" ||
               westFahrzeugSpuren_[i]->richtung() == "links-rechts" ||
               westFahrzeugSpuren_[i]->richtung() == "rechts-geradeaus")
            {
              minimumIndex = i;
              spurGefunden = true;
            }
          }
          else if(zielRichtung == "geradeaus")
          {
            if(westFahrzeugSpuren_[i]->richtung() == "alle" ||
               westFahrzeugSpuren_[i]->richtung() == "geradeaus" ||
               westFahrzeugSpuren_[i]->richtung() == "links-geradeaus" ||
               westFahrzeugSpuren_[i]->richtung() == "rechts-geradeaus")
            {
              minimumIndex = i;
              spurGefunden = true;
            }
          }
          else
          {
            qDebug() << "In kreuzung.cpp, advance(): Keine gültige "
                        "Zielrichtung";
          }
        }
      }

      if(spurGefunden)
      {
        westFahrzeugSpuren_[minimumIndex]->erzeugeFahrzeug(zielRichtung);
      }

      westFahrzeugSzenario_->setzeZeitschritteZurueck();
    }

    if(ostFahrzeugSzenario_->sollFahrzeugErzeugtWerden())
    {
      QString zielRichtung = ostFahrzeugSzenario_->waehleRichtung();

      bool spurGefunden = false;
      int minimumIndex = 0;
      for(int i = 0; i < ostFahrzeugSpuren_.size(); ++i)
      {
        if(ostFahrzeugSpuren_[i]->anzahlFahrzeuge() <=
           ostFahrzeugSpuren_[minimumIndex]->anzahlFahrzeuge())
        {
          // Prüfe Richtung
          if(zielRichtung == "links")
          {
            if(ostFahrzeugSpuren_[i]->richtung() == "alle" ||
               ostFahrzeugSpuren_[i]->richtung() == "links" ||
               ostFahrzeugSpuren_[i]->richtung() == "links-rechts" ||
               ostFahrzeugSpuren_[i]->richtung() == "links-geradeaus")
            {
              minimumIndex = i;
              spurGefunden = true;
            }
          }
          else if(zielRichtung == "rechts")
          {
            if(ostFahrzeugSpuren_[i]->richtung() == "alle" ||
               ostFahrzeugSpuren_[i]->richtung() == "rechts" ||
               ostFahrzeugSpuren_[i]->richtung() == "links-rechts" ||
               ostFahrzeugSpuren_[i]->richtung() == "rechts-geradeaus")
            {
              minimumIndex = i;
              spurGefunden = true;
            }
          }
          else if(zielRichtung == "geradeaus")
          {
            if(ostFahrzeugSpuren_[i]->richtung() == "alle" ||
               ostFahrzeugSpuren_[i]->richtung() == "geradeaus" ||
               ostFahrzeugSpuren_[i]->richtung() == "links-geradeaus" ||
               ostFahrzeugSpuren_[i]->richtung() == "rechts-geradeaus")
            {
              minimumIndex = i;
              spurGefunden = true;
            }
          }
          else
          {
            qDebug() << "In kreuzung.cpp, advance(): Keine gültige "
                        "Zielrichtung";
          }
        }
      }

      if(spurGefunden)
      {
        ostFahrzeugSpuren_[minimumIndex]->erzeugeFahrzeug(zielRichtung);
      }

      ostFahrzeugSzenario_->setzeZeitschritteZurueck();
    }

    // Erzeuge Fußgänger
    if(nordFussgaengerSzenario_->sollFussgaengerErzeugtWerden())
    {
      if(nordFussgaengerUeberweg_ != nullptr)
      {
        nordFussgaengerUeberweg_->erzeugeFussgaenger();
      }

      nordFussgaengerSzenario_->setzeZeitschritteZurueck();
    }

    if(suedFussgaengerSzenario_->sollFussgaengerErzeugtWerden())
    {
      if(suedFussgaengerUeberweg_ != nullptr)
      {
        suedFussgaengerUeberweg_->erzeugeFussgaenger();
      }

      suedFussgaengerSzenario_->setzeZeitschritteZurueck();
    }

    if(westFussgaengerSzenario_->sollFussgaengerErzeugtWerden())
    {
      if(westFussgaengerUeberweg_ != nullptr)
      {
        westFussgaengerUeberweg_->erzeugeFussgaenger();
      }

      westFussgaengerSzenario_->setzeZeitschritteZurueck();
    }

    if(ostFussgaengerSzenario_->sollFussgaengerErzeugtWerden())
    {
      if(ostFussgaengerUeberweg_ != nullptr)
      {
        ostFussgaengerUeberweg_->erzeugeFussgaenger();
      }

      ostFussgaengerSzenario_->setzeZeitschritteZurueck();
    }

    // Phasenwechsel
    zeitschritteZurNaechstenPhase_ -= 1;
    if(zeitschritteZurNaechstenPhase_ <= 0)
    {
      if(istGelbPhase_)
      {
        aktuellePhase_ = (aktuellePhase_ + 1) % phasenDauern_.size();

        zeitschritteZurNaechstenPhase_ =
            konfiguration_->sekundenZuZeitschritte(phasenDauern_[aktuellePhase_]);

        wechselZuAmpelphase(aktuellePhase_);

        istGelbPhase_ = false;
      }
      else
      {
        zeitschritteZurNaechstenPhase_ =
            konfiguration_->sekundenZuZeitschritte(3.0);

        int naechstePhase = (aktuellePhase_ + 1) % phasenDauern_.size();

        for(FahrzeugAmpel* ampel : fahrzeugAmpelphasen_.keys())
        {
          QString neuePhase = fahrzeugAmpelphasen_[ampel][naechstePhase];

          if(neuePhase != ampel->phase())
          {
            if(neuePhase == "gruen")
            {
              ampel->wechselZuPhase("rot-gelb");
            }
            else
            {
              ampel->wechselZuPhase("gelb");
            }
          }
        }

        for(FussgaengerAmpel* ampel : fussgaengerAmpelphasen_.keys())
        {
          ampel->wechselZuPhase("rot");
        }

        istGelbPhase_ = true;
      }
    }

    // Aktualisiere Statusleiste des Hauptfensters
    statusBar_->showMessage(
          QString::number((konfiguration_->zeitschritteZuSekunden(
                          zeitschritteZurNaechstenPhase_)), 'f', 1) +
          " Sekunden bis zur nächsten Ampelphase.");

    kreuzungsScene()->update();
  }
}



int Kreuzung::ausgehendeSpuren(QString himmelsrichtung)
{
  int maximum = 0;

  int spurenLinks = 0;
  int spurenGeradeaus = 0;
  int spurenRechts = 0;

  if(himmelsrichtung == "nord")
  {
    // Zähle Spuren, die von links kommen
    for(FahrzeugSpur* spur : westFahrzeugSpuren_)
    {
      if(spur->richtung() == "alle" || spur->richtung() == "links" ||
         spur->richtung() == "links-geradeaus" ||
         spur->richtung() == "links-rechts")
      {
        spurenLinks += 1;
      }
    }

    if(spurenLinks > maximum)
    {
      maximum = spurenLinks;
    }

    // Zähle Spuren, die von unten kommen
    for(FahrzeugSpur* spur : suedFahrzeugSpuren_)
    {
      if(spur->richtung() == "alle" || spur->richtung() == "geradeaus" ||
         spur->richtung() == "links-geradeaus" ||
         spur->richtung() == "rechts-geradeaus")
      {
        spurenGeradeaus += 1;
      }
    }

    if(spurenGeradeaus > maximum)
    {
      maximum = spurenGeradeaus;
    }

    // Zähle Spuren, die von rechts kommen
    for(FahrzeugSpur* spur : ostFahrzeugSpuren_)
    {
      if(spur->richtung() == "alle" || spur->richtung() == "rechts" ||
         spur->richtung() == "rechts-geradeaus" ||
         spur->richtung() == "links-rechts")
      {
        spurenRechts += 1;
      }
    }

    if(spurenRechts > maximum)
    {
      maximum = spurenRechts;
    }

    // Extraregelung, damit die Kreuzung in Extremfällen nicht unrealistisch
    // klein wird.
    if(suedFahrzeugSpuren_.size() > maximum && maximum != 0)
    {
      maximum = suedFahrzeugSpuren_.size();
    }
  }
  else if(himmelsrichtung == "sued")
  {
    // Zähle Spuren, die von links kommen
    for(FahrzeugSpur* spur : westFahrzeugSpuren_)
    {
      if(spur->richtung() == "alle" || spur->richtung() == "rechts" ||
         spur->richtung() == "rechts-geradeaus" ||
         spur->richtung() == "links-rechts")
      {
        spurenLinks += 1;
      }
    }

    if(spurenLinks > maximum)
    {
      maximum = spurenLinks;
    }

    // Zähle Spuren, die von oben kommen
    for(FahrzeugSpur* spur : nordFahrzeugSpuren_)
    {
      if(spur->richtung() == "alle" || spur->richtung() == "geradeaus" ||
         spur->richtung() == "links-geradeaus" ||
         spur->richtung() == "rechts-geradeaus")
      {
        spurenGeradeaus += 1;
      }
    }

    if(spurenGeradeaus > maximum)
    {
      maximum = spurenGeradeaus;
    }

    // Zähle Spuren, die von rechts kommen
    for(FahrzeugSpur* spur : ostFahrzeugSpuren_)
    {
      if(spur->richtung() == "alle" || spur->richtung() == "links" ||
         spur->richtung() == "links-geradeaus" ||
         spur->richtung() == "links-rechts")
      {
        spurenRechts += 1;
      }
    }

    if(spurenRechts > maximum)
    {
      maximum = spurenRechts;
    }

    // Extraregelung, damit die Kreuzung in Extremfällen nicht unrealistisch
    // klein wird.
    if(nordFahrzeugSpuren_.size() > maximum && maximum != 0)
    {
      maximum = nordFahrzeugSpuren_.size();
    }
  }
  else if(himmelsrichtung == "west")
  {
    // Zähle Spuren, die von links kommen
    for(FahrzeugSpur* spur : nordFahrzeugSpuren_)
    {
      if(spur->richtung() == "alle" || spur->richtung() == "rechts" ||
         spur->richtung() == "rechts-geradeaus" ||
         spur->richtung() == "links-rechts")
      {
        spurenLinks += 1;
      }
    }

    if(spurenLinks > maximum)
    {
      maximum = spurenLinks;
    }

    // Zähle Spuren, die von gegenüber kommen
    for(FahrzeugSpur* spur : ostFahrzeugSpuren_)
    {
      if(spur->richtung() == "alle" || spur->richtung() == "geradeaus" ||
         spur->richtung() == "links-geradeaus" ||
         spur->richtung() == "rechts-geradeaus")
      {
        spurenGeradeaus += 1;
      }
    }

    if(spurenGeradeaus > maximum)
    {
      maximum = spurenGeradeaus;
    }

    // Zähle Spuren, die von rechts kommen
    for(FahrzeugSpur* spur : suedFahrzeugSpuren_)
    {
      if(spur->richtung() == "alle" || spur->richtung() == "links" ||
         spur->richtung() == "links-geradeaus" ||
         spur->richtung() == "links-rechts")
      {
        spurenRechts += 1;
      }
    }

    if(spurenRechts > maximum)
    {
      maximum = spurenRechts;
    }

    // Extraregelung, damit die Kreuzung in Extremfällen nicht unrealistisch
    // klein wird.
    if(ostFahrzeugSpuren_.size() > maximum && maximum != 0)
    {
      maximum = ostFahrzeugSpuren_.size();
    }
  }
  else if(himmelsrichtung == "ost")
  {
    // Zähle Spuren, die von links kommen
    for(FahrzeugSpur* spur : suedFahrzeugSpuren_)
    {
      if(spur->richtung() == "alle" || spur->richtung() == "rechts" ||
         spur->richtung() == "rechts-geradeaus" ||
         spur->richtung() == "links-rechts")
      {
        spurenLinks += 1;
      }
    }

    if(spurenLinks > maximum)
    {
      maximum = spurenLinks;
    }

    // Zähle Spuren, die von gegenüber kommen
    for(FahrzeugSpur* spur : westFahrzeugSpuren_)
    {
      if(spur->richtung() == "alle" || spur->richtung() == "geradeaus" ||
         spur->richtung() == "links-geradeaus" ||
         spur->richtung() == "rechts-geradeaus")
      {
        spurenGeradeaus += 1;
      }
    }

    if(spurenGeradeaus > maximum)
    {
      maximum = spurenGeradeaus;
    }

    // Zähle Spuren, die von rechts kommen
    for(FahrzeugSpur* spur : nordFahrzeugSpuren_)
    {
      if(spur->richtung() == "alle" || spur->richtung() == "links" ||
         spur->richtung() == "links-geradeaus" ||
         spur->richtung() == "links-rechts")
      {
        spurenRechts += 1;
      }
    }

    if(spurenRechts > maximum)
    {
      maximum = spurenRechts;
    }

    // Extraregelung, damit die Kreuzung in Extremfällen nicht unrealistisch
    // klein wird.
    if(westFahrzeugSpuren_.size() > maximum && maximum != 0)
    {
      maximum = westFahrzeugSpuren_.size();
    }
  }
  else
  {
    qDebug() << "In kreuzung.cpp, ausgehendeSpuren(): Keine gültige "
                "Himmelsrichtung";
  }

  return maximum;
}



void Kreuzung::szenarioZuruecksetzen()
{
  nordFahrzeugSzenario_->setzeFahrzeugeProMinute(0);
  nordFahrzeugSzenario_->setzeWahrscheinlichkeitGeradeaus(0);
  nordFahrzeugSzenario_->setzeWahrscheinlichkeitLinks(0);
  nordFahrzeugSzenario_->setzeWahrscheinlichkeitRechts(0);

  suedFahrzeugSzenario_->setzeFahrzeugeProMinute(0);
  suedFahrzeugSzenario_->setzeWahrscheinlichkeitGeradeaus(0);
  suedFahrzeugSzenario_->setzeWahrscheinlichkeitLinks(0);
  suedFahrzeugSzenario_->setzeWahrscheinlichkeitRechts(0);

  westFahrzeugSzenario_->setzeFahrzeugeProMinute(0);
  westFahrzeugSzenario_->setzeWahrscheinlichkeitGeradeaus(0);
  westFahrzeugSzenario_->setzeWahrscheinlichkeitLinks(0);
  westFahrzeugSzenario_->setzeWahrscheinlichkeitRechts(0);

  ostFahrzeugSzenario_->setzeFahrzeugeProMinute(0);
  ostFahrzeugSzenario_->setzeWahrscheinlichkeitGeradeaus(0);
  ostFahrzeugSzenario_->setzeWahrscheinlichkeitLinks(0);
  ostFahrzeugSzenario_->setzeWahrscheinlichkeitRechts(0);

  nordFussgaengerSzenario_->setzeFussgaengerProMinute(0);
  suedFussgaengerSzenario_->setzeFussgaengerProMinute(0);
  westFussgaengerSzenario_->setzeFussgaengerProMinute(0);
  ostFussgaengerSzenario_->setzeFussgaengerProMinute(0);
}



QString Kreuzung::szenarioZuString()
{
  QString szenario = "";

  szenario +=
      QString::number(nordFahrzeugSzenario_->fahrzeugeProMinute()) + ";";
  szenario +=
      QString::number(nordFahrzeugSzenario_->wahrscheinlichkeitGeradeaus()) + ";";
  szenario +=
      QString::number(nordFahrzeugSzenario_->wahrscheinlichkeitLinks()) + ";";
  szenario +=
      QString::number(nordFahrzeugSzenario_->wahrscheinlichkeitRechts()) + ";";

  szenario +=
      QString::number(suedFahrzeugSzenario_->fahrzeugeProMinute()) + ";";
  szenario +=
      QString::number(suedFahrzeugSzenario_->wahrscheinlichkeitGeradeaus()) + ";";
  szenario +=
      QString::number(suedFahrzeugSzenario_->wahrscheinlichkeitLinks()) + ";";
  szenario +=
      QString::number(suedFahrzeugSzenario_->wahrscheinlichkeitRechts()) + ";";

  szenario +=
      QString::number(westFahrzeugSzenario_->fahrzeugeProMinute()) + ";";
  szenario +=
      QString::number(westFahrzeugSzenario_->wahrscheinlichkeitGeradeaus()) + ";";
  szenario +=
      QString::number(westFahrzeugSzenario_->wahrscheinlichkeitLinks()) + ";";
  szenario +=
      QString::number(westFahrzeugSzenario_->wahrscheinlichkeitRechts()) + ";";

  szenario +=
      QString::number(ostFahrzeugSzenario_->fahrzeugeProMinute()) + ";";
  szenario +=
      QString::number(ostFahrzeugSzenario_->wahrscheinlichkeitGeradeaus()) + ";";
  szenario +=
      QString::number(ostFahrzeugSzenario_->wahrscheinlichkeitLinks()) + ";";
  szenario +=
      QString::number(ostFahrzeugSzenario_->wahrscheinlichkeitRechts()) + ";";

  szenario +=
      QString::number(nordFussgaengerSzenario_->fussgaengerProMinute()) + ";";
  szenario +=
      QString::number(suedFussgaengerSzenario_->fussgaengerProMinute()) + ";";
  szenario +=
      QString::number(westFussgaengerSzenario_->fussgaengerProMinute()) + ";";
  szenario +=
      QString::number(ostFussgaengerSzenario_->fussgaengerProMinute());

  return szenario;
}



void Kreuzung::szenarioAusString(QString& szenario)
{
  QStringList werte = szenario.split(';');

  if(werte.size() == 20)
  {
    nordFahrzeugSzenario_->setzeFahrzeugeProMinute(werte[0].toInt());
    nordFahrzeugSzenario_->setzeWahrscheinlichkeitGeradeaus(werte[1].toInt());
    nordFahrzeugSzenario_->setzeWahrscheinlichkeitLinks(werte[2].toInt());
    nordFahrzeugSzenario_->setzeWahrscheinlichkeitRechts(werte[3].toInt());

    suedFahrzeugSzenario_->setzeFahrzeugeProMinute(werte[4].toInt());
    suedFahrzeugSzenario_->setzeWahrscheinlichkeitGeradeaus(werte[5].toInt());
    suedFahrzeugSzenario_->setzeWahrscheinlichkeitLinks(werte[6].toInt());
    suedFahrzeugSzenario_->setzeWahrscheinlichkeitRechts(werte[7].toInt());

    westFahrzeugSzenario_->setzeFahrzeugeProMinute(werte[8].toInt());
    westFahrzeugSzenario_->setzeWahrscheinlichkeitGeradeaus(werte[9].toInt());
    westFahrzeugSzenario_->setzeWahrscheinlichkeitLinks(werte[10].toInt());
    westFahrzeugSzenario_->setzeWahrscheinlichkeitRechts(werte[11].toInt());

    ostFahrzeugSzenario_->setzeFahrzeugeProMinute(werte[12].toInt());
    ostFahrzeugSzenario_->setzeWahrscheinlichkeitGeradeaus(werte[13].toInt());
    ostFahrzeugSzenario_->setzeWahrscheinlichkeitLinks(werte[14].toInt());
    ostFahrzeugSzenario_->setzeWahrscheinlichkeitRechts(werte[15].toInt());

    nordFussgaengerSzenario_->setzeFussgaengerProMinute(werte[16].toInt());
    suedFussgaengerSzenario_->setzeFussgaengerProMinute(werte[17].toInt());
    westFussgaengerSzenario_->setzeFussgaengerProMinute(werte[18].toInt());
    ostFussgaengerSzenario_->setzeFussgaengerProMinute(werte[19].toInt());
  }
  else
  {
    qDebug() << "In kreuzung.cpp, szenarioAusString(): String hat ein "
                "falsches Format";
  }
}
