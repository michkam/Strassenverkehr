#ifndef PHASENDAUERGUI_H
#define PHASENDAUERGUI_H

#include <QDialog>

namespace Ui
{
  class PhasendauerGUI;
}

class PhasendauerGUI : public QDialog
{
    Q_OBJECT

  public:
    explicit PhasendauerGUI(QWidget*, int*);
    ~PhasendauerGUI();

  private slots:
    void on_abbrechenButton_released();
    void on_OKButton_released();

  private:
    Ui::PhasendauerGUI *ui;

    int* dauer_;
};

#endif // PHASENDAUERGUI_H
