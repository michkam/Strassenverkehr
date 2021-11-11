#ifndef FAHRZEUGSZENARIOGUI_H
#define FAHRZEUGSZENARIOGUI_H

#include <QDialog>

class FahrzeugSzenario;

namespace Ui
{
  class FahrzeugSzenarioGUI;
}

class FahrzeugSzenarioGUI : public QDialog
{
    Q_OBJECT

  public:
    explicit FahrzeugSzenarioGUI(QWidget*, FahrzeugSzenario*);
    ~FahrzeugSzenarioGUI();

    void linksSliderAktivieren();
    void geradeausSliderAktivieren();
    void rechtsSliderAktivieren();

  private slots:
    void on_linksSlider_valueChanged(int value);
    void on_geradeausSlider_valueChanged(int value);
    void on_rechtsSlider_valueChanged(int value);

    void on_abbrechenButton_released();
    void on_okButton_released();

    void aktualisiereLabel();

  private:
    Ui::FahrzeugSzenarioGUI *ui;

    FahrzeugSzenario* szenario_;
};

#endif // FAHRZEUGSZENARIOGUI_H
