#include "fahrzeugszenariogui.h"
#include "ui_fahrzeugszenariogui.h"

#include "fahrzeugszenario.h"

FahrzeugSzenarioGUI::FahrzeugSzenarioGUI(QWidget *parent,
                                         FahrzeugSzenario* szenario) :
  QDialog(parent),
  ui(new Ui::FahrzeugSzenarioGUI)
{
  ui->setupUi(this);

  ui->fahrzeugeProMinuteSpinBox->setValue(szenario->fahrzeugeProMinute());
  ui->linksSlider->setValue(szenario->wahrscheinlichkeitLinks());
  ui->geradeausSlider->setValue(szenario->wahrscheinlichkeitGeradeaus());
  ui->rechtsSlider->setValue(szenario->wahrscheinlichkeitRechts());

  /*
   * Deaktiviere zuerst jeden Richtungsslider, damit später nur die benötigten
   * aktiviert werden.
   */
  ui->linksSlider->setEnabled(false);
  ui->geradeausSlider->setEnabled(false);
  ui->rechtsSlider->setEnabled(false);

  szenario_ = szenario;

  aktualisiereLabel();
}



FahrzeugSzenarioGUI::~FahrzeugSzenarioGUI()
{
  delete ui;
}



void FahrzeugSzenarioGUI::linksSliderAktivieren()
{
  ui->linksSlider->setEnabled(true);
}



void FahrzeugSzenarioGUI::geradeausSliderAktivieren()
{
  ui->geradeausSlider->setEnabled(true);
}



void FahrzeugSzenarioGUI::rechtsSliderAktivieren()
{
  ui->rechtsSlider->setEnabled(true);
}



void FahrzeugSzenarioGUI::on_linksSlider_valueChanged(int value)
{
  aktualisiereLabel();
}



void FahrzeugSzenarioGUI::on_geradeausSlider_valueChanged(int value)
{
  aktualisiereLabel();
}



void FahrzeugSzenarioGUI::on_rechtsSlider_valueChanged(int value)
{
  aktualisiereLabel();
}



void FahrzeugSzenarioGUI::on_abbrechenButton_released()
{
  this->close();
}



void FahrzeugSzenarioGUI::on_okButton_released()
{
  szenario_->setzeFahrzeugeProMinute(
        this->ui->fahrzeugeProMinuteSpinBox->value());

  szenario_->setzeWahrscheinlichkeitLinks(
        this->ui->linksSlider->value());
  szenario_->setzeWahrscheinlichkeitRechts(
        this->ui->rechtsSlider->value());
  szenario_->setzeWahrscheinlichkeitGeradeaus(
        this->ui->geradeausSlider->value());

  this->close();
}



void FahrzeugSzenarioGUI::aktualisiereLabel()
{
  double gesamt = ui->geradeausSlider->value() +
                  ui->linksSlider->value() +
                  ui->rechtsSlider->value();

  /*
   * Aktualisiere die Prozentlabel, sodass volle 100% entstehen, wenn
   * diese summiert werden.
   */
  if(gesamt != 0.0)
  {
    ui->linksProzentLabel->setText(
          QString::number(
            (static_cast<double>(ui->linksSlider->value()) / gesamt) * 100.0,
            'f', 0)
             + "%");
    ui->geradeausProzentLabel->setText(
          QString::number(
            (static_cast<double>(ui->geradeausSlider->value()) / gesamt) *
            100.0, 'f', 0) + "%");
    ui->rechtsProzentLabel->setText(
          QString::number(
            (static_cast<double>(ui->rechtsSlider->value()) / gesamt) * 100.0,
            'f', 0) + "%");
  }
  else
  {
    ui->linksProzentLabel->setText("0%");
    ui->geradeausProzentLabel->setText("0%");
    ui->rechtsProzentLabel->setText("0%");
  }
}
