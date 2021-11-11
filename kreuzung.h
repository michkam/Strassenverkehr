#ifndef KREUZUNG_H
#define KREUZUNG_H

#include <QObject>
#include <QString>
#include <QStringListModel>
#include <QStringList>
#include <QList>
#include <QMap>
#include <QWidget>
#include <QListView>
#include <QStatusBar>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QPoint>

#include "fahrzeugszenariogui.h"
#include "fussgaengerszenariogui.h"
#include "phasendauergui.h"

class Konfiguration;
class StatistikDaten;
class FahrzeugSzenario;
class FussgaengerSzenario;
class FahrzeugSpur;
class FahrzeugAmpel;
class FussgaengerUeberweg;
class FussgaengerAmpel;
class Fahrzeug;
class Fussgaenger;

class Kreuzung : public QObject
{
  Q_OBJECT

  public:
    Kreuzung(QObject*, Konfiguration*, StatistikDaten*);

    QGraphicsScene* kreuzungsScene();

    bool istSimulierend() const;
    void zuruecksetzen();

    void fahrzeugSpurHinzufuegen(QString, QString richtung = "alle");
    void fahrzeugSpurEntfernen(QString);
    void fussgaengerUeberwegUmschalten(QString);

    void fuegeAmpelphaseHinzu();
    void entferneAmpelphase();
    void wechselZurzeitigeFahrzeugAmpelphase(FahrzeugAmpel*);
    void wechselZurzeitigeFussgaengerAmpelphase(FussgaengerAmpel*);
    void wechselZuAmpelphase(int);

    void aktualisierePhasenListe(QListView*);
    void setzeStatusBar(QStatusBar*);

    void oeffnePhasendauerDialog(QWidget*);
    void oeffneFahrzeugSzenarioDialog(QWidget*, QString);
    void oeffneFussgaengerSzenarioDialog(QWidget*, QString);

    QList<QPoint> fahrzeugPfad(QString, QString, int);

    void starteSimulation();
    void stoppeSimulation();

    QString kreuzungZuString();
    void kreuzungAusString(QString&);

    void aktualisierePositionen();
    void aktualisiereDekorationen();

    int ausgehendeSpuren(QString);

    void szenarioZuruecksetzen();
    QString szenarioZuString();
    void szenarioAusString(QString&);

  signals:

  public slots:
    void advance();

  private:
    QGraphicsScene* kreuzungsScene_;

    QStatusBar* statusBar_;
    QListView* phasenList_;

    Konfiguration* konfiguration_;
    StatistikDaten* statistikDaten_;

    bool istSimulierend_;

    int aktuellePhase_;
    bool istGelbPhase_;
    int zeitschritteZurNaechstenPhase_;
    QList<int> phasenDauern_;
    QMap<FahrzeugAmpel*, QList<QString> > fahrzeugAmpelphasen_;
    QMap<FussgaengerAmpel*, QList<QString> > fussgaengerAmpelphasen_;

    QList<FahrzeugSpur*> nordFahrzeugSpuren_;
    QList<FahrzeugSpur*> suedFahrzeugSpuren_;
    QList<FahrzeugSpur*> westFahrzeugSpuren_;
    QList<FahrzeugSpur*> ostFahrzeugSpuren_;

    FussgaengerUeberweg* nordFussgaengerUeberweg_;
    FussgaengerUeberweg* suedFussgaengerUeberweg_;
    FussgaengerUeberweg* westFussgaengerUeberweg_;
    FussgaengerUeberweg* ostFussgaengerUeberweg_;

    FahrzeugSzenario* nordFahrzeugSzenario_;
    FahrzeugSzenario* suedFahrzeugSzenario_;
    FahrzeugSzenario* westFahrzeugSzenario_;
    FahrzeugSzenario* ostFahrzeugSzenario_;

    FussgaengerSzenario* nordFussgaengerSzenario_;
    FussgaengerSzenario* suedFussgaengerSzenario_;
    FussgaengerSzenario* westFussgaengerSzenario_;
    FussgaengerSzenario* ostFussgaengerSzenario_;

    QList<QGraphicsRectItem*> dekorationen_;
};

#endif // KREUZUNG_H
