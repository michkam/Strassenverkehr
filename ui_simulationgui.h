/********************************************************************************
** Form generated from reading UI file 'simulationgui.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMULATIONGUI_H
#define UI_SIMULATIONGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SimulationGUI
{
public:
    QAction *actionNeu;
    QAction *actionOeffnen;
    QAction *actionSpeichern;
    QAction *actionSzenarioNeu;
    QAction *actionSzenarioOeffnen;
    QAction *actionSzenarioSpeichern;
    QWidget *centralWidget;
    QVBoxLayout *hauptVertikalesLayout;
    QTabWidget *tabWidget;
    QWidget *spurenTab;
    QVBoxLayout *verticalLayout;
    QTabWidget *spurenTabWidget;
    QWidget *nordSpurenTab;
    QHBoxLayout *horizontalLayout;
    QPushButton *nordSpurHinzufuegenButton;
    QPushButton *nordSpurEntfernenButton;
    QPushButton *nordFussgaengerUeberwegButton;
    QWidget *suedSpurenTab;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *suedSpurHinzufuegenButton;
    QPushButton *suedSpurEntfernenButton;
    QPushButton *suedFussgaengerUeberwegButton;
    QWidget *westSpurenTab;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *westSpurHinzufuegenButton;
    QPushButton *westSpurEntfernenButton;
    QPushButton *westFussgaengerUeberwegButton;
    QWidget *ostSpurenTab;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *ostSpurHinzufuegenButton;
    QPushButton *ostSpurEntfernenButton;
    QPushButton *ostFussgaengerUeberwegButton;
    QWidget *phasenTab;
    QHBoxLayout *horizontalLayout_11;
    QListView *phasenList;
    QVBoxLayout *phasenLayout;
    QPushButton *phaseHinzufuegenButton;
    QPushButton *phaseEntfernenButton;
    QPushButton *phasenDauerButton;
    QWidget *szenarioTab;
    QHBoxLayout *horizontalLayout_2;
    QTabWidget *szenarienTabWidget;
    QWidget *nordSzenarienTab;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *nordFahrzeugSzenarioButton;
    QPushButton *nordFussgaengerSzenarioButton;
    QWidget *suedSzenarienTab;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *suedFahrzeugSzenarioButton;
    QPushButton *suedFussgaengerSzenarioButton;
    QWidget *westSzenarienTab;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *westFahrzeugSzenarioButton;
    QPushButton *westFussgaengerSzenarioButton;
    QWidget *ostSzenarienTab;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *ostFahrzeugSzenarioButton;
    QPushButton *ostFussgaengerSzenarioButton;
    QWidget *simuliereTab;
    QHBoxLayout *horizontalLayout_10;
    QSlider *geschwindigkeitsSlider;
    QPushButton *starteSimulationButton;
    QPushButton *stoppeSimulationButton;
    QPushButton *oeffneStatistikDialogButton;
    QHBoxLayout *kreuzungLayout;
    QMenuBar *menuBar;
    QMenu *menuKreuzung;
    QMenu *menuSzenario;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SimulationGUI)
    {
        if (SimulationGUI->objectName().isEmpty())
            SimulationGUI->setObjectName(QStringLiteral("SimulationGUI"));
        SimulationGUI->resize(856, 644);
        actionNeu = new QAction(SimulationGUI);
        actionNeu->setObjectName(QStringLiteral("actionNeu"));
        actionOeffnen = new QAction(SimulationGUI);
        actionOeffnen->setObjectName(QStringLiteral("actionOeffnen"));
        actionSpeichern = new QAction(SimulationGUI);
        actionSpeichern->setObjectName(QStringLiteral("actionSpeichern"));
        actionSzenarioNeu = new QAction(SimulationGUI);
        actionSzenarioNeu->setObjectName(QStringLiteral("actionSzenarioNeu"));
        actionSzenarioOeffnen = new QAction(SimulationGUI);
        actionSzenarioOeffnen->setObjectName(QStringLiteral("actionSzenarioOeffnen"));
        actionSzenarioSpeichern = new QAction(SimulationGUI);
        actionSzenarioSpeichern->setObjectName(QStringLiteral("actionSzenarioSpeichern"));
        centralWidget = new QWidget(SimulationGUI);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        hauptVertikalesLayout = new QVBoxLayout(centralWidget);
        hauptVertikalesLayout->setSpacing(6);
        hauptVertikalesLayout->setContentsMargins(11, 11, 11, 11);
        hauptVertikalesLayout->setObjectName(QStringLiteral("hauptVertikalesLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setMaximumSize(QSize(16777215, 125));
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setTabsClosable(false);
        spurenTab = new QWidget();
        spurenTab->setObjectName(QStringLiteral("spurenTab"));
        verticalLayout = new QVBoxLayout(spurenTab);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        spurenTabWidget = new QTabWidget(spurenTab);
        spurenTabWidget->setObjectName(QStringLiteral("spurenTabWidget"));
        nordSpurenTab = new QWidget();
        nordSpurenTab->setObjectName(QStringLiteral("nordSpurenTab"));
        horizontalLayout = new QHBoxLayout(nordSpurenTab);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        nordSpurHinzufuegenButton = new QPushButton(nordSpurenTab);
        nordSpurHinzufuegenButton->setObjectName(QStringLiteral("nordSpurHinzufuegenButton"));

        horizontalLayout->addWidget(nordSpurHinzufuegenButton);

        nordSpurEntfernenButton = new QPushButton(nordSpurenTab);
        nordSpurEntfernenButton->setObjectName(QStringLiteral("nordSpurEntfernenButton"));

        horizontalLayout->addWidget(nordSpurEntfernenButton);

        nordFussgaengerUeberwegButton = new QPushButton(nordSpurenTab);
        nordFussgaengerUeberwegButton->setObjectName(QStringLiteral("nordFussgaengerUeberwegButton"));

        horizontalLayout->addWidget(nordFussgaengerUeberwegButton);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 1);
        horizontalLayout->setStretch(2, 2);
        spurenTabWidget->addTab(nordSpurenTab, QString());
        suedSpurenTab = new QWidget();
        suedSpurenTab->setObjectName(QStringLiteral("suedSpurenTab"));
        horizontalLayout_3 = new QHBoxLayout(suedSpurenTab);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        suedSpurHinzufuegenButton = new QPushButton(suedSpurenTab);
        suedSpurHinzufuegenButton->setObjectName(QStringLiteral("suedSpurHinzufuegenButton"));

        horizontalLayout_3->addWidget(suedSpurHinzufuegenButton);

        suedSpurEntfernenButton = new QPushButton(suedSpurenTab);
        suedSpurEntfernenButton->setObjectName(QStringLiteral("suedSpurEntfernenButton"));

        horizontalLayout_3->addWidget(suedSpurEntfernenButton);

        suedFussgaengerUeberwegButton = new QPushButton(suedSpurenTab);
        suedFussgaengerUeberwegButton->setObjectName(QStringLiteral("suedFussgaengerUeberwegButton"));

        horizontalLayout_3->addWidget(suedFussgaengerUeberwegButton);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 1);
        horizontalLayout_3->setStretch(2, 2);
        spurenTabWidget->addTab(suedSpurenTab, QString());
        westSpurenTab = new QWidget();
        westSpurenTab->setObjectName(QStringLiteral("westSpurenTab"));
        horizontalLayout_4 = new QHBoxLayout(westSpurenTab);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        westSpurHinzufuegenButton = new QPushButton(westSpurenTab);
        westSpurHinzufuegenButton->setObjectName(QStringLiteral("westSpurHinzufuegenButton"));

        horizontalLayout_4->addWidget(westSpurHinzufuegenButton);

        westSpurEntfernenButton = new QPushButton(westSpurenTab);
        westSpurEntfernenButton->setObjectName(QStringLiteral("westSpurEntfernenButton"));

        horizontalLayout_4->addWidget(westSpurEntfernenButton);

        westFussgaengerUeberwegButton = new QPushButton(westSpurenTab);
        westFussgaengerUeberwegButton->setObjectName(QStringLiteral("westFussgaengerUeberwegButton"));

        horizontalLayout_4->addWidget(westFussgaengerUeberwegButton);

        horizontalLayout_4->setStretch(0, 1);
        horizontalLayout_4->setStretch(1, 1);
        horizontalLayout_4->setStretch(2, 2);
        spurenTabWidget->addTab(westSpurenTab, QString());
        ostSpurenTab = new QWidget();
        ostSpurenTab->setObjectName(QStringLiteral("ostSpurenTab"));
        horizontalLayout_5 = new QHBoxLayout(ostSpurenTab);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        ostSpurHinzufuegenButton = new QPushButton(ostSpurenTab);
        ostSpurHinzufuegenButton->setObjectName(QStringLiteral("ostSpurHinzufuegenButton"));

        horizontalLayout_5->addWidget(ostSpurHinzufuegenButton);

        ostSpurEntfernenButton = new QPushButton(ostSpurenTab);
        ostSpurEntfernenButton->setObjectName(QStringLiteral("ostSpurEntfernenButton"));

        horizontalLayout_5->addWidget(ostSpurEntfernenButton);

        ostFussgaengerUeberwegButton = new QPushButton(ostSpurenTab);
        ostFussgaengerUeberwegButton->setObjectName(QStringLiteral("ostFussgaengerUeberwegButton"));

        horizontalLayout_5->addWidget(ostFussgaengerUeberwegButton);

        horizontalLayout_5->setStretch(0, 1);
        horizontalLayout_5->setStretch(1, 1);
        horizontalLayout_5->setStretch(2, 2);
        spurenTabWidget->addTab(ostSpurenTab, QString());

        verticalLayout->addWidget(spurenTabWidget);

        tabWidget->addTab(spurenTab, QString());
        phasenTab = new QWidget();
        phasenTab->setObjectName(QStringLiteral("phasenTab"));
        horizontalLayout_11 = new QHBoxLayout(phasenTab);
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        phasenList = new QListView(phasenTab);
        phasenList->setObjectName(QStringLiteral("phasenList"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(phasenList->sizePolicy().hasHeightForWidth());
        phasenList->setSizePolicy(sizePolicy1);
        phasenList->setMaximumSize(QSize(16777215, 100));
        phasenList->setEditTriggers(QAbstractItemView::NoEditTriggers);

        horizontalLayout_11->addWidget(phasenList);

        phasenLayout = new QVBoxLayout();
        phasenLayout->setSpacing(6);
        phasenLayout->setObjectName(QStringLiteral("phasenLayout"));
        phaseHinzufuegenButton = new QPushButton(phasenTab);
        phaseHinzufuegenButton->setObjectName(QStringLiteral("phaseHinzufuegenButton"));

        phasenLayout->addWidget(phaseHinzufuegenButton);

        phaseEntfernenButton = new QPushButton(phasenTab);
        phaseEntfernenButton->setObjectName(QStringLiteral("phaseEntfernenButton"));

        phasenLayout->addWidget(phaseEntfernenButton);

        phasenDauerButton = new QPushButton(phasenTab);
        phasenDauerButton->setObjectName(QStringLiteral("phasenDauerButton"));

        phasenLayout->addWidget(phasenDauerButton);


        horizontalLayout_11->addLayout(phasenLayout);

        horizontalLayout_11->setStretch(0, 7);
        horizontalLayout_11->setStretch(1, 3);
        tabWidget->addTab(phasenTab, QString());
        szenarioTab = new QWidget();
        szenarioTab->setObjectName(QStringLiteral("szenarioTab"));
        horizontalLayout_2 = new QHBoxLayout(szenarioTab);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        szenarienTabWidget = new QTabWidget(szenarioTab);
        szenarienTabWidget->setObjectName(QStringLiteral("szenarienTabWidget"));
        nordSzenarienTab = new QWidget();
        nordSzenarienTab->setObjectName(QStringLiteral("nordSzenarienTab"));
        horizontalLayout_6 = new QHBoxLayout(nordSzenarienTab);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        nordFahrzeugSzenarioButton = new QPushButton(nordSzenarienTab);
        nordFahrzeugSzenarioButton->setObjectName(QStringLiteral("nordFahrzeugSzenarioButton"));

        horizontalLayout_6->addWidget(nordFahrzeugSzenarioButton);

        nordFussgaengerSzenarioButton = new QPushButton(nordSzenarienTab);
        nordFussgaengerSzenarioButton->setObjectName(QStringLiteral("nordFussgaengerSzenarioButton"));

        horizontalLayout_6->addWidget(nordFussgaengerSzenarioButton);

        szenarienTabWidget->addTab(nordSzenarienTab, QString());
        suedSzenarienTab = new QWidget();
        suedSzenarienTab->setObjectName(QStringLiteral("suedSzenarienTab"));
        horizontalLayout_7 = new QHBoxLayout(suedSzenarienTab);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        suedFahrzeugSzenarioButton = new QPushButton(suedSzenarienTab);
        suedFahrzeugSzenarioButton->setObjectName(QStringLiteral("suedFahrzeugSzenarioButton"));

        horizontalLayout_7->addWidget(suedFahrzeugSzenarioButton);

        suedFussgaengerSzenarioButton = new QPushButton(suedSzenarienTab);
        suedFussgaengerSzenarioButton->setObjectName(QStringLiteral("suedFussgaengerSzenarioButton"));

        horizontalLayout_7->addWidget(suedFussgaengerSzenarioButton);

        szenarienTabWidget->addTab(suedSzenarienTab, QString());
        westSzenarienTab = new QWidget();
        westSzenarienTab->setObjectName(QStringLiteral("westSzenarienTab"));
        horizontalLayout_8 = new QHBoxLayout(westSzenarienTab);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        westFahrzeugSzenarioButton = new QPushButton(westSzenarienTab);
        westFahrzeugSzenarioButton->setObjectName(QStringLiteral("westFahrzeugSzenarioButton"));

        horizontalLayout_8->addWidget(westFahrzeugSzenarioButton);

        westFussgaengerSzenarioButton = new QPushButton(westSzenarienTab);
        westFussgaengerSzenarioButton->setObjectName(QStringLiteral("westFussgaengerSzenarioButton"));

        horizontalLayout_8->addWidget(westFussgaengerSzenarioButton);

        szenarienTabWidget->addTab(westSzenarienTab, QString());
        ostSzenarienTab = new QWidget();
        ostSzenarienTab->setObjectName(QStringLiteral("ostSzenarienTab"));
        horizontalLayout_9 = new QHBoxLayout(ostSzenarienTab);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        ostFahrzeugSzenarioButton = new QPushButton(ostSzenarienTab);
        ostFahrzeugSzenarioButton->setObjectName(QStringLiteral("ostFahrzeugSzenarioButton"));

        horizontalLayout_9->addWidget(ostFahrzeugSzenarioButton);

        ostFussgaengerSzenarioButton = new QPushButton(ostSzenarienTab);
        ostFussgaengerSzenarioButton->setObjectName(QStringLiteral("ostFussgaengerSzenarioButton"));

        horizontalLayout_9->addWidget(ostFussgaengerSzenarioButton);

        szenarienTabWidget->addTab(ostSzenarienTab, QString());

        horizontalLayout_2->addWidget(szenarienTabWidget);

        tabWidget->addTab(szenarioTab, QString());
        simuliereTab = new QWidget();
        simuliereTab->setObjectName(QStringLiteral("simuliereTab"));
        horizontalLayout_10 = new QHBoxLayout(simuliereTab);
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        geschwindigkeitsSlider = new QSlider(simuliereTab);
        geschwindigkeitsSlider->setObjectName(QStringLiteral("geschwindigkeitsSlider"));
        geschwindigkeitsSlider->setMaximum(4);
        geschwindigkeitsSlider->setPageStep(1);
        geschwindigkeitsSlider->setValue(1);
        geschwindigkeitsSlider->setOrientation(Qt::Horizontal);
        geschwindigkeitsSlider->setTickPosition(QSlider::TicksBothSides);

        horizontalLayout_10->addWidget(geschwindigkeitsSlider);

        starteSimulationButton = new QPushButton(simuliereTab);
        starteSimulationButton->setObjectName(QStringLiteral("starteSimulationButton"));

        horizontalLayout_10->addWidget(starteSimulationButton);

        stoppeSimulationButton = new QPushButton(simuliereTab);
        stoppeSimulationButton->setObjectName(QStringLiteral("stoppeSimulationButton"));

        horizontalLayout_10->addWidget(stoppeSimulationButton);

        oeffneStatistikDialogButton = new QPushButton(simuliereTab);
        oeffneStatistikDialogButton->setObjectName(QStringLiteral("oeffneStatistikDialogButton"));

        horizontalLayout_10->addWidget(oeffneStatistikDialogButton);

        tabWidget->addTab(simuliereTab, QString());

        hauptVertikalesLayout->addWidget(tabWidget);

        kreuzungLayout = new QHBoxLayout();
        kreuzungLayout->setSpacing(6);
        kreuzungLayout->setObjectName(QStringLiteral("kreuzungLayout"));

        hauptVertikalesLayout->addLayout(kreuzungLayout);

        hauptVertikalesLayout->setStretch(1, 9);
        SimulationGUI->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(SimulationGUI);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 856, 19));
        menuKreuzung = new QMenu(menuBar);
        menuKreuzung->setObjectName(QStringLiteral("menuKreuzung"));
        menuSzenario = new QMenu(menuBar);
        menuSzenario->setObjectName(QStringLiteral("menuSzenario"));
        SimulationGUI->setMenuBar(menuBar);
        statusBar = new QStatusBar(SimulationGUI);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        SimulationGUI->setStatusBar(statusBar);

        menuBar->addAction(menuKreuzung->menuAction());
        menuBar->addAction(menuSzenario->menuAction());
        menuKreuzung->addAction(actionNeu);
        menuKreuzung->addSeparator();
        menuKreuzung->addAction(actionOeffnen);
        menuKreuzung->addAction(actionSpeichern);
        menuSzenario->addAction(actionSzenarioNeu);
        menuSzenario->addSeparator();
        menuSzenario->addAction(actionSzenarioOeffnen);
        menuSzenario->addAction(actionSzenarioSpeichern);

        retranslateUi(SimulationGUI);

        tabWidget->setCurrentIndex(0);
        spurenTabWidget->setCurrentIndex(0);
        szenarienTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SimulationGUI);
    } // setupUi

    void retranslateUi(QMainWindow *SimulationGUI)
    {
        SimulationGUI->setWindowTitle(QApplication::translate("SimulationGUI", "Kreuzungssimulator", 0));
        actionNeu->setText(QApplication::translate("SimulationGUI", "Neu", 0));
        actionOeffnen->setText(QApplication::translate("SimulationGUI", "\303\226ffnen...", 0));
        actionSpeichern->setText(QApplication::translate("SimulationGUI", "Speichern...", 0));
        actionSzenarioNeu->setText(QApplication::translate("SimulationGUI", "Neu", 0));
        actionSzenarioOeffnen->setText(QApplication::translate("SimulationGUI", "\303\226ffnen...", 0));
        actionSzenarioSpeichern->setText(QApplication::translate("SimulationGUI", "Speichern", 0));
        nordSpurHinzufuegenButton->setText(QApplication::translate("SimulationGUI", "Spur hinzuf\303\274gen", 0));
        nordSpurEntfernenButton->setText(QApplication::translate("SimulationGUI", "Spur entfernen", 0));
        nordFussgaengerUeberwegButton->setText(QApplication::translate("SimulationGUI", "Fu\303\237g\303\244nger\303\274berweg", 0));
        spurenTabWidget->setTabText(spurenTabWidget->indexOf(nordSpurenTab), QApplication::translate("SimulationGUI", "Nord", 0));
        suedSpurHinzufuegenButton->setText(QApplication::translate("SimulationGUI", "Spur hinzuf\303\274gen", 0));
        suedSpurEntfernenButton->setText(QApplication::translate("SimulationGUI", "Spur entfernen", 0));
        suedFussgaengerUeberwegButton->setText(QApplication::translate("SimulationGUI", "Fu\303\237g\303\244nger\303\274berweg", 0));
        spurenTabWidget->setTabText(spurenTabWidget->indexOf(suedSpurenTab), QApplication::translate("SimulationGUI", "S\303\274d", 0));
        westSpurHinzufuegenButton->setText(QApplication::translate("SimulationGUI", "Spur hinzuf\303\274gen", 0));
        westSpurEntfernenButton->setText(QApplication::translate("SimulationGUI", "Spur entfernen", 0));
        westFussgaengerUeberwegButton->setText(QApplication::translate("SimulationGUI", "Fu\303\237g\303\244nger\303\274berweg", 0));
        spurenTabWidget->setTabText(spurenTabWidget->indexOf(westSpurenTab), QApplication::translate("SimulationGUI", "West", 0));
        ostSpurHinzufuegenButton->setText(QApplication::translate("SimulationGUI", "Spur hinzuf\303\274gen", 0));
        ostSpurEntfernenButton->setText(QApplication::translate("SimulationGUI", "Spur entfernen", 0));
        ostFussgaengerUeberwegButton->setText(QApplication::translate("SimulationGUI", "Fu\303\237g\303\244nger\303\274berweg", 0));
        spurenTabWidget->setTabText(spurenTabWidget->indexOf(ostSpurenTab), QApplication::translate("SimulationGUI", "Ost", 0));
        tabWidget->setTabText(tabWidget->indexOf(spurenTab), QApplication::translate("SimulationGUI", "\303\204ndere Spuren", 0));
        phaseHinzufuegenButton->setText(QApplication::translate("SimulationGUI", "Hinzuf\303\274gen", 0));
        phaseEntfernenButton->setText(QApplication::translate("SimulationGUI", "Entfernen", 0));
        phasenDauerButton->setText(QApplication::translate("SimulationGUI", "Phasendauer...", 0));
        tabWidget->setTabText(tabWidget->indexOf(phasenTab), QApplication::translate("SimulationGUI", "\303\204ndere Ampelphasen", 0));
        nordFahrzeugSzenarioButton->setText(QApplication::translate("SimulationGUI", "Fahrzeuge...", 0));
        nordFussgaengerSzenarioButton->setText(QApplication::translate("SimulationGUI", "Fu\303\237g\303\244nger...", 0));
        szenarienTabWidget->setTabText(szenarienTabWidget->indexOf(nordSzenarienTab), QApplication::translate("SimulationGUI", "Nord", 0));
        suedFahrzeugSzenarioButton->setText(QApplication::translate("SimulationGUI", "Fahrzeuge...", 0));
        suedFussgaengerSzenarioButton->setText(QApplication::translate("SimulationGUI", "Fu\303\237g\303\244nger...", 0));
        szenarienTabWidget->setTabText(szenarienTabWidget->indexOf(suedSzenarienTab), QApplication::translate("SimulationGUI", "S\303\274d", 0));
        westFahrzeugSzenarioButton->setText(QApplication::translate("SimulationGUI", "Fahrzeuge...", 0));
        westFussgaengerSzenarioButton->setText(QApplication::translate("SimulationGUI", "Fu\303\237g\303\244nger...", 0));
        szenarienTabWidget->setTabText(szenarienTabWidget->indexOf(westSzenarienTab), QApplication::translate("SimulationGUI", "West", 0));
        ostFahrzeugSzenarioButton->setText(QApplication::translate("SimulationGUI", "Fahrzeuge...", 0));
        ostFussgaengerSzenarioButton->setText(QApplication::translate("SimulationGUI", "Fu\303\237g\303\244nger...", 0));
        szenarienTabWidget->setTabText(szenarienTabWidget->indexOf(ostSzenarienTab), QApplication::translate("SimulationGUI", "Ost", 0));
        tabWidget->setTabText(tabWidget->indexOf(szenarioTab), QApplication::translate("SimulationGUI", "\303\204ndere Verkehrsfluss", 0));
        starteSimulationButton->setText(QApplication::translate("SimulationGUI", "Start", 0));
        stoppeSimulationButton->setText(QApplication::translate("SimulationGUI", "Stopp", 0));
        oeffneStatistikDialogButton->setText(QApplication::translate("SimulationGUI", "Statistik...", 0));
        tabWidget->setTabText(tabWidget->indexOf(simuliereTab), QApplication::translate("SimulationGUI", "Simuliere", 0));
        menuKreuzung->setTitle(QApplication::translate("SimulationGUI", "Kreuzung", 0));
        menuSzenario->setTitle(QApplication::translate("SimulationGUI", "Szenario", 0));
    } // retranslateUi

};

namespace Ui {
    class SimulationGUI: public Ui_SimulationGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMULATIONGUI_H
