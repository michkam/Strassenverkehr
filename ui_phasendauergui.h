/********************************************************************************
** Form generated from reading UI file 'phasendauergui.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PHASENDAUERGUI_H
#define UI_PHASENDAUERGUI_H

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

class Ui_PhasendauerGUI
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *phasendauerLabel;
    QSpinBox *phasendauerSpinBox;
    QHBoxLayout *buttonLayout;
    QSpacerItem *buttonSpacer;
    QPushButton *abbrechenButton;
    QPushButton *OKButton;

    void setupUi(QDialog *PhasendauerGUI)
    {
        if (PhasendauerGUI->objectName().isEmpty())
            PhasendauerGUI->setObjectName(QStringLiteral("PhasendauerGUI"));
        PhasendauerGUI->resize(400, 91);
        verticalLayout = new QVBoxLayout(PhasendauerGUI);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        phasendauerLabel = new QLabel(PhasendauerGUI);
        phasendauerLabel->setObjectName(QStringLiteral("phasendauerLabel"));

        verticalLayout->addWidget(phasendauerLabel);

        phasendauerSpinBox = new QSpinBox(PhasendauerGUI);
        phasendauerSpinBox->setObjectName(QStringLiteral("phasendauerSpinBox"));
        phasendauerSpinBox->setMinimum(1);
        phasendauerSpinBox->setMaximum(9999);
        phasendauerSpinBox->setValue(10);

        verticalLayout->addWidget(phasendauerSpinBox);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName(QStringLiteral("buttonLayout"));
        buttonSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        buttonLayout->addItem(buttonSpacer);

        abbrechenButton = new QPushButton(PhasendauerGUI);
        abbrechenButton->setObjectName(QStringLiteral("abbrechenButton"));
        abbrechenButton->setAutoDefault(false);

        buttonLayout->addWidget(abbrechenButton);

        OKButton = new QPushButton(PhasendauerGUI);
        OKButton->setObjectName(QStringLiteral("OKButton"));

        buttonLayout->addWidget(OKButton);


        verticalLayout->addLayout(buttonLayout);


        retranslateUi(PhasendauerGUI);

        OKButton->setDefault(true);


        QMetaObject::connectSlotsByName(PhasendauerGUI);
    } // setupUi

    void retranslateUi(QDialog *PhasendauerGUI)
    {
        PhasendauerGUI->setWindowTitle(QApplication::translate("PhasendauerGUI", "Dauer der zurzeitigen Phase einstellen...", 0));
        phasendauerLabel->setText(QApplication::translate("PhasendauerGUI", "Dauer der Phase (in Sekunden):", 0));
        abbrechenButton->setText(QApplication::translate("PhasendauerGUI", "Abbrechen", 0));
        OKButton->setText(QApplication::translate("PhasendauerGUI", "OK", 0));
    } // retranslateUi

};

namespace Ui {
    class PhasendauerGUI: public Ui_PhasendauerGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PHASENDAUERGUI_H
