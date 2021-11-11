/********************************************************************************
** Form generated from reading UI file 'fussgaengerszenariogui.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FUSSGAENGERSZENARIOGUI_H
#define UI_FUSSGAENGERSZENARIOGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FussgaengerSzenarioGUI
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *fussgaengerProMinuteLabel;
    QSpinBox *fussgaengerSpinBox;
    QHBoxLayout *buttonLayout;
    QSpacerItem *buttonSpacer;
    QPushButton *abbrechenButton;
    QPushButton *OKButton;

    void setupUi(QDialog *FussgaengerSzenarioGUI)
    {
        if (FussgaengerSzenarioGUI->objectName().isEmpty())
            FussgaengerSzenarioGUI->setObjectName(QStringLiteral("FussgaengerSzenarioGUI"));
        FussgaengerSzenarioGUI->resize(400, 91);
        verticalLayout = new QVBoxLayout(FussgaengerSzenarioGUI);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        fussgaengerProMinuteLabel = new QLabel(FussgaengerSzenarioGUI);
        fussgaengerProMinuteLabel->setObjectName(QStringLiteral("fussgaengerProMinuteLabel"));

        verticalLayout->addWidget(fussgaengerProMinuteLabel);

        fussgaengerSpinBox = new QSpinBox(FussgaengerSzenarioGUI);
        fussgaengerSpinBox->setObjectName(QStringLiteral("fussgaengerSpinBox"));
        fussgaengerSpinBox->setMaximum(200);

        verticalLayout->addWidget(fussgaengerSpinBox);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName(QStringLiteral("buttonLayout"));
        buttonSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        buttonLayout->addItem(buttonSpacer);

        abbrechenButton = new QPushButton(FussgaengerSzenarioGUI);
        abbrechenButton->setObjectName(QStringLiteral("abbrechenButton"));
        abbrechenButton->setAutoDefault(false);

        buttonLayout->addWidget(abbrechenButton);

        OKButton = new QPushButton(FussgaengerSzenarioGUI);
        OKButton->setObjectName(QStringLiteral("OKButton"));

        buttonLayout->addWidget(OKButton);


        verticalLayout->addLayout(buttonLayout);


        retranslateUi(FussgaengerSzenarioGUI);

        OKButton->setDefault(true);


        QMetaObject::connectSlotsByName(FussgaengerSzenarioGUI);
    } // setupUi

    void retranslateUi(QDialog *FussgaengerSzenarioGUI)
    {
        FussgaengerSzenarioGUI->setWindowTitle(QApplication::translate("FussgaengerSzenarioGUI", "Fu\303\237g\303\244ngeraufkommen \303\244ndern...", 0));
        fussgaengerProMinuteLabel->setText(QApplication::translate("FussgaengerSzenarioGUI", "Fu\303\237g\303\244nger (pro Minute):", 0));
        abbrechenButton->setText(QApplication::translate("FussgaengerSzenarioGUI", "Abbrechen", 0));
        OKButton->setText(QApplication::translate("FussgaengerSzenarioGUI", "OK", 0));
    } // retranslateUi

};

namespace Ui {
    class FussgaengerSzenarioGUI: public Ui_FussgaengerSzenarioGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FUSSGAENGERSZENARIOGUI_H
