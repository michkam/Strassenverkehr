#include "phasendauergui.h"
#include "ui_phasendauergui.h"

PhasendauerGUI::PhasendauerGUI(QWidget* parent, int* dauer) :
  QDialog(parent),
  ui(new Ui::PhasendauerGUI)
{
  ui->setupUi(this);

  dauer_ = dauer;

  ui->phasendauerSpinBox->setValue(*(dauer_));
}



PhasendauerGUI::~PhasendauerGUI()
{
  delete ui;
}



void PhasendauerGUI::on_abbrechenButton_released()
{
  this->close();
}



void PhasendauerGUI::on_OKButton_released()
{
  *dauer_ = ui->phasendauerSpinBox->value();

  this->close();
}
