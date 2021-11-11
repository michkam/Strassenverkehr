#include "statistikgui.h"
#include "ui_statistikgui.h"

StatistikGUI::StatistikGUI(QWidget* parent, QString text) :
  QDialog(parent),
  ui(new Ui::StatistikGUI)
{
  ui->setupUi(this);

  ui->statistikTextEdit->setText(text);
}



StatistikGUI::~StatistikGUI()
{
  delete ui;
}



void StatistikGUI::on_speichernDialogButton_released()
{
  QString fileName =
      QFileDialog::getSaveFileName(this, "Statistik speichern...", "",
                                   "Alle Dateien (*)");

  QFile outFile(fileName);

  if(outFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
  {
    QTextStream stream(&outFile);

    stream << ui->statistikTextEdit->toPlainText();
  }

  outFile.close();
}



void StatistikGUI::on_OKButton_released()
{
  this->close();
}
