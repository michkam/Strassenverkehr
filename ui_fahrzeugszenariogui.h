/********************************************************************************
** Form generated from reading UI file 'fahrzeugszenariogui.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FAHRZEUGSZENARIOGUI_H
#define UI_FAHRZEUGSZENARIOGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FahrzeugSzenarioGUI
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *fahrzeugeProMinuteLabel;
    QHBoxLayout *fahrzeugeProMinuteLayout;
    QSpinBox *fahrzeugeProMinuteSpinBox;
    QLabel *wahrscheinlichkeitenLabel;
    QGridLayout *gridLayout;
    QLabel *linksProzentLabel;
    QLabel *linksLabel;
    QSlider *geradeausSlider;
    QSlider *linksSlider;
    QSlider *rechtsSlider;
    QLabel *geradeasLabel;
    QLabel *rechtsLabel;
    QLabel *geradeausProzentLabel;
    QLabel *rechtsProzentLabel;
    QHBoxLayout *buttonLayout;
    QSpacerItem *buttonSpacer;
    QPushButton *abbrechenButton;
    QPushButton *okButton;

    void setupUi(QDialog *FahrzeugSzenarioGUI)
    {
        if (FahrzeugSzenarioGUI->objectName().isEmpty())
            FahrzeugSzenarioGUI->setObjectName(QStringLiteral("FahrzeugSzenarioGUI"));
        FahrzeugSzenarioGUI->resize(444, 178);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(FahrzeugSzenarioGUI->sizePolicy().hasHeightForWidth());
        FahrzeugSzenarioGUI->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(FahrzeugSzenarioGUI);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        fahrzeugeProMinuteLabel = new QLabel(FahrzeugSzenarioGUI);
        fahrzeugeProMinuteLabel->setObjectName(QStringLiteral("fahrzeugeProMinuteLabel"));

        verticalLayout->addWidget(fahrzeugeProMinuteLabel);

        fahrzeugeProMinuteLayout = new QHBoxLayout();
        fahrzeugeProMinuteLayout->setObjectName(QStringLiteral("fahrzeugeProMinuteLayout"));
        fahrzeugeProMinuteSpinBox = new QSpinBox(FahrzeugSzenarioGUI);
        fahrzeugeProMinuteSpinBox->setObjectName(QStringLiteral("fahrzeugeProMinuteSpinBox"));
        fahrzeugeProMinuteSpinBox->setMaximum(200);

        fahrzeugeProMinuteLayout->addWidget(fahrzeugeProMinuteSpinBox);


        verticalLayout->addLayout(fahrzeugeProMinuteLayout);

        wahrscheinlichkeitenLabel = new QLabel(FahrzeugSzenarioGUI);
        wahrscheinlichkeitenLabel->setObjectName(QStringLiteral("wahrscheinlichkeitenLabel"));

        verticalLayout->addWidget(wahrscheinlichkeitenLabel);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        linksProzentLabel = new QLabel(FahrzeugSzenarioGUI);
        linksProzentLabel->setObjectName(QStringLiteral("linksProzentLabel"));
        linksProzentLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(linksProzentLabel, 0, 2, 1, 1);

        linksLabel = new QLabel(FahrzeugSzenarioGUI);
        linksLabel->setObjectName(QStringLiteral("linksLabel"));

        gridLayout->addWidget(linksLabel, 0, 0, 1, 1);

        geradeausSlider = new QSlider(FahrzeugSzenarioGUI);
        geradeausSlider->setObjectName(QStringLiteral("geradeausSlider"));
        geradeausSlider->setMaximum(99);
        geradeausSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(geradeausSlider, 1, 1, 1, 1);

        linksSlider = new QSlider(FahrzeugSzenarioGUI);
        linksSlider->setObjectName(QStringLiteral("linksSlider"));
        linksSlider->setMaximum(99);
        linksSlider->setSliderPosition(0);
        linksSlider->setOrientation(Qt::Horizontal);
        linksSlider->setTickPosition(QSlider::NoTicks);

        gridLayout->addWidget(linksSlider, 0, 1, 1, 1);

        rechtsSlider = new QSlider(FahrzeugSzenarioGUI);
        rechtsSlider->setObjectName(QStringLiteral("rechtsSlider"));
        rechtsSlider->setMaximum(99);
        rechtsSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(rechtsSlider, 2, 1, 1, 1);

        geradeasLabel = new QLabel(FahrzeugSzenarioGUI);
        geradeasLabel->setObjectName(QStringLiteral("geradeasLabel"));

        gridLayout->addWidget(geradeasLabel, 1, 0, 1, 1);

        rechtsLabel = new QLabel(FahrzeugSzenarioGUI);
        rechtsLabel->setObjectName(QStringLiteral("rechtsLabel"));

        gridLayout->addWidget(rechtsLabel, 2, 0, 1, 1);

        geradeausProzentLabel = new QLabel(FahrzeugSzenarioGUI);
        geradeausProzentLabel->setObjectName(QStringLiteral("geradeausProzentLabel"));
        geradeausProzentLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(geradeausProzentLabel, 1, 2, 1, 1);

        rechtsProzentLabel = new QLabel(FahrzeugSzenarioGUI);
        rechtsProzentLabel->setObjectName(QStringLiteral("rechtsProzentLabel"));
        rechtsProzentLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(rechtsProzentLabel, 2, 2, 1, 1);

        gridLayout->setRowStretch(0, 1);
        gridLayout->setRowStretch(1, 1);
        gridLayout->setRowStretch(2, 1);
        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 6);
        gridLayout->setColumnStretch(2, 1);

        verticalLayout->addLayout(gridLayout);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName(QStringLiteral("buttonLayout"));
        buttonSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        buttonLayout->addItem(buttonSpacer);

        abbrechenButton = new QPushButton(FahrzeugSzenarioGUI);
        abbrechenButton->setObjectName(QStringLiteral("abbrechenButton"));
        abbrechenButton->setAutoDefault(false);

        buttonLayout->addWidget(abbrechenButton);

        okButton = new QPushButton(FahrzeugSzenarioGUI);
        okButton->setObjectName(QStringLiteral("okButton"));

        buttonLayout->addWidget(okButton);


        verticalLayout->addLayout(buttonLayout);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 1);
        verticalLayout->setStretch(2, 1);
        verticalLayout->setStretch(3, 5);
        verticalLayout->setStretch(4, 1);

        retranslateUi(FahrzeugSzenarioGUI);

        okButton->setDefault(true);


        QMetaObject::connectSlotsByName(FahrzeugSzenarioGUI);
    } // setupUi

    void retranslateUi(QDialog *FahrzeugSzenarioGUI)
    {
        FahrzeugSzenarioGUI->setWindowTitle(QApplication::translate("FahrzeugSzenarioGUI", "Fahrzeugfluss ver\303\244ndern...", 0));
        fahrzeugeProMinuteLabel->setText(QApplication::translate("FahrzeugSzenarioGUI", "Anzahl von Fahrzeugen (pro Minute):", 0));
        wahrscheinlichkeitenLabel->setText(QApplication::translate("FahrzeugSzenarioGUI", "Wahrscheinlichkeiten f\303\274r die Abbiegerichtungen:", 0));
        linksProzentLabel->setText(QApplication::translate("FahrzeugSzenarioGUI", "in %", 0));
        linksLabel->setText(QApplication::translate("FahrzeugSzenarioGUI", "Links:", 0));
        geradeasLabel->setText(QApplication::translate("FahrzeugSzenarioGUI", "Geradeaus:", 0));
        rechtsLabel->setText(QApplication::translate("FahrzeugSzenarioGUI", "Rechts:", 0));
        geradeausProzentLabel->setText(QApplication::translate("FahrzeugSzenarioGUI", "in %", 0));
        rechtsProzentLabel->setText(QApplication::translate("FahrzeugSzenarioGUI", "in %", 0));
        abbrechenButton->setText(QApplication::translate("FahrzeugSzenarioGUI", "Abbrechen", 0));
        okButton->setText(QApplication::translate("FahrzeugSzenarioGUI", "OK", 0));
    } // retranslateUi

};

namespace Ui {
    class FahrzeugSzenarioGUI: public Ui_FahrzeugSzenarioGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FAHRZEUGSZENARIOGUI_H
