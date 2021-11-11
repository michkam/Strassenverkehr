#ifndef STATISTIKGUI_H
#define STATISTIKGUI_H

#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QString>
#include <QDialog>

namespace Ui
{
  class StatistikGUI;
}

class StatistikGUI : public QDialog
{
    Q_OBJECT

  public:
    explicit StatistikGUI(QWidget*, QString);
    ~StatistikGUI();

  private slots:
    void on_speichernDialogButton_released();
    void on_OKButton_released();

  private:
    Ui::StatistikGUI *ui;
};

#endif // STATISTIKGUI_H
