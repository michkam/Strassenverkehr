#ifndef FAHRZEUGSZENARIO_H
#define FAHRZEUGSZENARIO_H

#include <QObject>

class Konfiguration;

class FahrzeugSzenario : public QObject
{
  Q_OBJECT

  public:
    FahrzeugSzenario(QObject*, Konfiguration*);

    bool sollFahrzeugErzeugtWerden() const;  
    QString waehleRichtung() const;

    void setzeZeitschritteZurueck();

    void setzeFahrzeugeProMinute(int);
    void setzeWahrscheinlichkeitLinks(int);
    void setzeWahrscheinlichkeitGeradeaus(int);
    void setzeWahrscheinlichkeitRechts(int);

    int fahrzeugeProMinute();
    int wahrscheinlichkeitLinks();
    int wahrscheinlichkeitGeradeaus();
    int wahrscheinlichkeitRechts();

    void advance();

  signals:

  public slots:

  private:
    Konfiguration* konfiguration_;

    int zeitschritteBisNeuesFahrzeug_;

    int fahrzeugeProMinute_;

    int wahrscheinlichkeitLinks_;
    int wahrscheinlichkeitGeradeaus_;
    int wahrscheinlichkeitRechts_;
};

#endif // FAHRZEUGSZENARIO_H
