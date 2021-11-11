#ifndef SIMULATIONGUI_H
#define SIMULATIONGUI_H

#include <QString>
#include <QTextStream>
#include <QFile>
#include <QFileDialog>
#include <QMainWindow>
#include <QTimer>

#include "statistikgui.h"

class Konfiguration;
class StatistikDaten;
class KreuzungsView;
class Kreuzung;

namespace Ui
{
  class SimulationGUI;
}

class SimulationGUI : public QMainWindow
{
  Q_OBJECT

  public:
    explicit SimulationGUI(QWidget *parent = 0);
    ~SimulationGUI();

  private slots:
    void on_tabWidget_currentChanged(int index);

    void on_nordSpurHinzufuegenButton_released();
    void on_nordSpurEntfernenButton_released();
    void on_nordFussgaengerUeberwegButton_released();

    void on_suedSpurHinzufuegenButton_released();
    void on_suedSpurEntfernenButton_released();
    void on_suedFussgaengerUeberwegButton_released();

    void on_westSpurHinzufuegenButton_released();
    void on_westSpurEntfernenButton_released();
    void on_westFussgaengerUeberwegButton_released();

    void on_ostSpurHinzufuegenButton_released();
    void on_ostSpurEntfernenButton_released();
    void on_ostFussgaengerUeberwegButton_released();

    void on_nordFahrzeugSzenarioButton_released();
    void on_nordFussgaengerSzenarioButton_released();

    void on_suedFahrzeugSzenarioButton_released();
    void on_suedFussgaengerSzenarioButton_released();

    void on_westFahrzeugSzenarioButton_released();
    void on_westFussgaengerSzenarioButton_released();

    void on_ostFahrzeugSzenarioButton_released();
    void on_ostFussgaengerSzenarioButton_released();

    void on_geschwindigkeitsSlider_valueChanged(int value);
    void on_starteSimulationButton_released();
    void on_stoppeSimulationButton_released();
    void on_oeffneStatistikDialogButton_released();

    void on_actionNeu_triggered();
    void on_actionOeffnen_triggered();
    void on_actionSpeichern_triggered();

    void on_phaseHinzufuegenButton_released();
    void on_phaseEntfernenButton_released();
    void on_phasenDauerButton_released();

    void on_phasenList_clicked(const QModelIndex &index);

    void on_actionSzenarioNeu_triggered();

    void on_actionSzenarioOeffnen_triggered();

    void on_actionSzenarioSpeichern_triggered();

  private:
    Ui::SimulationGUI *ui;

    Konfiguration* konfiguration_;
    StatistikDaten* statistikDaten_;
    KreuzungsView* kreuzungsView_;
    QTimer* timer_;
};

#endif // SIMULATIONGUI_H
