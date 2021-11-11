#include "simulationgui.h"
#include "ui_simulationgui.h"

#include <QtDebug>

#include "konfiguration.h"
#include "statistikdaten.h"
#include "kreuzungsview.h"
#include "kreuzung.h"

SimulationGUI::SimulationGUI(QWidget *parent) : QMainWindow(parent),
                                                ui(new Ui::SimulationGUI)
{
  ui->setupUi(this);

  konfiguration_ = new Konfiguration(this);
  statistikDaten_ = new StatistikDaten(this, konfiguration_);
  kreuzungsView_ = new KreuzungsView(ui->centralWidget,
                                     konfiguration_,
                                     statistikDaten_);
  kreuzungsView_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  kreuzungsView_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  kreuzungsView_->setDragMode(QGraphicsView::ScrollHandDrag);
  ui->kreuzungLayout->addWidget(kreuzungsView_);

  ui->tabWidget->setCurrentIndex(0);
  ui->statusBar->showMessage(QString("Klicken Sie auf eine Spur, um die "
                                     "Abbiegerichtung zu ändern."));

  kreuzungsView_->kreuzung()->setzeStatusBar(ui->statusBar);

  timer_ = new QTimer();
  connect(timer_, SIGNAL(timeout()), kreuzungsView_, SLOT(advance()));
}



SimulationGUI::~SimulationGUI()
{
  delete ui;
}



void SimulationGUI::on_tabWidget_currentChanged(int index)
{
    switch(index)
    {
      case 0:
        // Tab 0 = Ändere Spuren
        ui->statusBar->showMessage(QString("Klicken Sie auf eine Spur, um die "
                                           "Abbiegerichtung zu ändern."));
        break;
      case 1:
        // Tab 1 = Ändere Ampelphasen
        ui->statusBar->showMessage(QString("Klicken Sie auf eine Ampel, "
                                           "um die derzeitige Phase "
                                           "der Ampel zu ändern."));

        kreuzungsView_->kreuzung()->aktualisierePhasenListe(ui->phasenList);
        break;
      case 2:
        // Tab 2 = Ändere Szenario
        ui->statusBar->showMessage(QString("Beeinflussen Sie hier den "
                                           "Verkehr, der aus einer "
                                           "ausgewählten Himmelsrichtung "
                                           "kommt."));
        break;
      case 3:
        // Tab 3 = Simuliere
        ui->statusBar->showMessage(QString("Passen Sie die Simulations"
                                           "geschwindigkeit mit dem Slider "
                                           "von 0x (pausiert) bis 4x an."));
        break;
      default:
        break;
    }
}



void SimulationGUI::on_nordSpurHinzufuegenButton_released()
{
  kreuzungsView_->kreuzung()->fahrzeugSpurHinzufuegen(QString("nord"));
}



void SimulationGUI::on_nordSpurEntfernenButton_released()
{
  kreuzungsView_->kreuzung()->fahrzeugSpurEntfernen(QString("nord"));
}



void SimulationGUI::on_nordFussgaengerUeberwegButton_released()
{
  kreuzungsView_->kreuzung()->fussgaengerUeberwegUmschalten(QString("nord"));
}



void SimulationGUI::on_suedSpurHinzufuegenButton_released()
{
  kreuzungsView_->kreuzung()->fahrzeugSpurHinzufuegen(QString("sued"));
}



void SimulationGUI::on_suedSpurEntfernenButton_released()
{
  kreuzungsView_->kreuzung()->fahrzeugSpurEntfernen(QString("sued"));
}



void SimulationGUI::on_suedFussgaengerUeberwegButton_released()
{
  kreuzungsView_->kreuzung()->fussgaengerUeberwegUmschalten(QString("sued"));
}



void SimulationGUI::on_westSpurHinzufuegenButton_released()
{
  kreuzungsView_->kreuzung()->fahrzeugSpurHinzufuegen(QString("west"));
}



void SimulationGUI::on_westSpurEntfernenButton_released()
{
  kreuzungsView_->kreuzung()->fahrzeugSpurEntfernen(QString("west"));
}



void SimulationGUI::on_westFussgaengerUeberwegButton_released()
{
  kreuzungsView_->kreuzung()->fussgaengerUeberwegUmschalten(QString("west"));
}



void SimulationGUI::on_ostSpurHinzufuegenButton_released()
{
  kreuzungsView_->kreuzung()->fahrzeugSpurHinzufuegen(QString("ost"));
}



void SimulationGUI::on_ostSpurEntfernenButton_released()
{
  kreuzungsView_->kreuzung()->fahrzeugSpurEntfernen(QString("ost"));
}



void SimulationGUI::on_ostFussgaengerUeberwegButton_released()
{
  kreuzungsView_->kreuzung()->fussgaengerUeberwegUmschalten(QString("ost"));
}



void SimulationGUI::on_nordFahrzeugSzenarioButton_released()
{
  kreuzungsView_->kreuzung()->oeffneFahrzeugSzenarioDialog(ui->centralWidget,
                                                           QString("nord"));
}



void SimulationGUI::on_nordFussgaengerSzenarioButton_released()
{
  kreuzungsView_->kreuzung()->oeffneFussgaengerSzenarioDialog(ui->centralWidget,
                                                              QString("nord"));
}



void SimulationGUI::on_suedFahrzeugSzenarioButton_released()
{
  kreuzungsView_->kreuzung()->oeffneFahrzeugSzenarioDialog(ui->centralWidget,
                                                           QString("sued"));
}



void SimulationGUI::on_suedFussgaengerSzenarioButton_released()
{
  kreuzungsView_->kreuzung()->oeffneFussgaengerSzenarioDialog(ui->centralWidget,
                                                              QString("sued"));
}



void SimulationGUI::on_westFahrzeugSzenarioButton_released()
{
  kreuzungsView_->kreuzung()->oeffneFahrzeugSzenarioDialog(ui->centralWidget,
                                                           QString("west"));
}



void SimulationGUI::on_westFussgaengerSzenarioButton_released()
{
  kreuzungsView_->kreuzung()->oeffneFussgaengerSzenarioDialog(ui->centralWidget,
                                                              QString("west"));
}



void SimulationGUI::on_ostFahrzeugSzenarioButton_released()
{
  kreuzungsView_->kreuzung()->oeffneFahrzeugSzenarioDialog(ui->centralWidget,
                                                           QString("ost"));
}



void SimulationGUI::on_ostFussgaengerSzenarioButton_released()
{
  kreuzungsView_->kreuzung()->oeffneFussgaengerSzenarioDialog(ui->centralWidget,
                                                              QString("ost"));
}



void SimulationGUI::on_geschwindigkeitsSlider_valueChanged(int value)
{
  /*
   * Ändere die Simulationsgeschwindigkeit, bei einer 0 wird
   * der Timer einfach gestoppt.
   */
  if(kreuzungsView_->kreuzung()->istSimulierend())
  {
    if(value != 0)
    {
      timer_->start(konfiguration_->timerIntervall / value);
    }
    else
    {
      timer_->stop();
    }
  }
}



void SimulationGUI::on_starteSimulationButton_released()
{
  ui->tabWidget->setTabEnabled(0, false);
  ui->tabWidget->setTabEnabled(1, false);

  kreuzungsView_->kreuzung()->starteSimulation();

  if(ui->geschwindigkeitsSlider->value() != 0)
  {
    timer_->start(konfiguration_->timerIntervall /
                  ui->geschwindigkeitsSlider->value());
  }
  else
  {
    timer_->stop();
  }
}



void SimulationGUI::on_stoppeSimulationButton_released()
{
  ui->tabWidget->setTabEnabled(0, true);
  ui->tabWidget->setTabEnabled(1, true);

  kreuzungsView_->kreuzung()->stoppeSimulation();

  timer_->stop();
}



void SimulationGUI::on_oeffneStatistikDialogButton_released()
{
  StatistikGUI* statistikDialog =
      new StatistikGUI(this->centralWidget(),
                       statistikDaten_->druckeStatistik());

  statistikDialog->show();
}



void SimulationGUI::on_actionNeu_triggered()
{
  ui->tabWidget->setTabEnabled(0, true);
  ui->tabWidget->setTabEnabled(1, true);

  ui->tabWidget->setCurrentIndex(0);

  timer_->stop();

  kreuzungsView_->kreuzung()->zuruecksetzen();
}



void SimulationGUI::on_actionOeffnen_triggered()
{
  QString fileName =
      QFileDialog::getOpenFileName(this, "Kreuzung öffnen...", "",
                                   "Alle Dateien (*)");

  /*
   * Versuche nur die Datei zu öffnen, wenn OK gedrückt wurde.
   */
  if(fileName.size() > 0)
  {
    on_actionNeu_triggered();

    QFile inFile(fileName);

    /*
     * Lese die ganze Kreuzung zu einen String.
     */
    if(inFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      QTextStream stream(&inFile);
      QString input = stream.readAll();

      kreuzungsView_->kreuzung()->kreuzungAusString(input);
    }

    inFile.close();
  }
}



void SimulationGUI::on_actionSpeichern_triggered()
{
  QString fileName =
      QFileDialog::getSaveFileName(this, "Kreuzung speichern...", "",
                                   "Alle Dateien (*)");

  QFile outFile(fileName);

  if(outFile.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
  {
    QTextStream stream(&outFile);

    stream << kreuzungsView_->kreuzung()->kreuzungZuString();
  }

  outFile.close();
}



void SimulationGUI::on_phaseHinzufuegenButton_released()
{
  kreuzungsView_->kreuzung()->fuegeAmpelphaseHinzu();

  kreuzungsView_->kreuzung()->aktualisierePhasenListe(ui->phasenList);
}



void SimulationGUI::on_phaseEntfernenButton_released()
{
  kreuzungsView_->kreuzung()->entferneAmpelphase();

  kreuzungsView_->kreuzung()->aktualisierePhasenListe(ui->phasenList);
}



void SimulationGUI::on_phasenDauerButton_released()
{
  kreuzungsView_->kreuzung()->oeffnePhasendauerDialog(this->centralWidget());

  kreuzungsView_->kreuzung()->aktualisierePhasenListe(ui->phasenList);
}



void SimulationGUI::on_phasenList_clicked(const QModelIndex &index)
{
  kreuzungsView_->kreuzung()->wechselZuAmpelphase(index.row());
}



void SimulationGUI::on_actionSzenarioNeu_triggered()
{
  kreuzungsView_->kreuzung()->szenarioZuruecksetzen();
}



void SimulationGUI::on_actionSzenarioOeffnen_triggered()
{
  QString fileName =
      QFileDialog::getOpenFileName(this, "Szenario öffnen...", "",
                                   "Alle Dateien (*)");

  /*
   * Versuche nur die Datei zu öffnen, wenn auch eine ausgewählt wurde.
   */
  if(fileName.size() > 0)
  {
    QFile inFile(fileName);

    /*
     * Lese die ganze Datei zu einen String, der von der Kreuzung
     * verarbeitet wird.
     */
    if(inFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      QTextStream stream(&inFile);
      QString input = stream.readAll();

      kreuzungsView_->kreuzung()->szenarioAusString(input);
    }

    inFile.close();
  }
}



void SimulationGUI::on_actionSzenarioSpeichern_triggered()
{
  QString fileName =
      QFileDialog::getSaveFileName(this, "Szenario speichern...", "",
                                   "Alle Dateien (*)");

  QFile outFile(fileName);

  if(outFile.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
  {
    QTextStream stream(&outFile);

    stream << kreuzungsView_->kreuzung()->szenarioZuString();
  }

  outFile.close();
}
