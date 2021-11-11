#include "fussgaengerszenariogui.h"
#include "ui_fussgaengerszenariogui.h"

#include "fussgaengerszenario.h"

FussgaengerSzenarioGUI::FussgaengerSzenarioGUI(QWidget *parent,
                                             FussgaengerSzenario *szenario) :
  QDialog(parent),
  ui(new Ui::FussgaengerSzenarioGUI)
{
  ui->setupUi(this);

  ui->fussgaengerSpinBox->setValue(szenario->fussgaengerProMinute());

  szenario_ = szenario;
}



FussgaengerSzenarioGUI::~FussgaengerSzenarioGUI()
{
  delete ui;
}



void FussgaengerSzenarioGUI::on_abbrechenButton_released()
{
  this->close();
}



void FussgaengerSzenarioGUI::on_OKButton_released()
{
  szenario_->setzeFussgaengerProMinute(ui->fussgaengerSpinBox->value());

  this->close();
}
