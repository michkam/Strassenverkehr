#ifndef FUSSGAENGERSZENARIOGUI_H
#define FUSSGAENGERSZENARIOGUI_H

#include <QDialog>

class FussgaengerSzenario;

namespace Ui
{
  class FussgaengerSzenarioGUI;
}

class FussgaengerSzenarioGUI : public QDialog
{
    Q_OBJECT

  public:
    explicit FussgaengerSzenarioGUI(QWidget*,
                                    FussgaengerSzenario*);
    ~FussgaengerSzenarioGUI();

  private slots:
    void on_abbrechenButton_released();

    void on_OKButton_released();

  private:
    Ui::FussgaengerSzenarioGUI *ui;

    FussgaengerSzenario* szenario_;
};

#endif // FUSSGAENGERSZENARIOGUI_H
