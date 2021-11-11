/********************************************************************************
** Form generated from reading UI file 'statistikgui.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATISTIKGUI_H
#define UI_STATISTIKGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_StatistikGUI
{
public:
    QVBoxLayout *verticalLayout;
    QTextEdit *statistikTextEdit;
    QHBoxLayout *buttonLayout;
    QPushButton *speichernDialogButton;
    QSpacerItem *buttonSpacer;
    QPushButton *OKButton;

    void setupUi(QDialog *StatistikGUI)
    {
        if (StatistikGUI->objectName().isEmpty())
            StatistikGUI->setObjectName(QStringLiteral("StatistikGUI"));
        StatistikGUI->resize(400, 300);
        verticalLayout = new QVBoxLayout(StatistikGUI);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        statistikTextEdit = new QTextEdit(StatistikGUI);
        statistikTextEdit->setObjectName(QStringLiteral("statistikTextEdit"));
        statistikTextEdit->setReadOnly(true);

        verticalLayout->addWidget(statistikTextEdit);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName(QStringLiteral("buttonLayout"));
        speichernDialogButton = new QPushButton(StatistikGUI);
        speichernDialogButton->setObjectName(QStringLiteral("speichernDialogButton"));
        speichernDialogButton->setAutoDefault(false);

        buttonLayout->addWidget(speichernDialogButton);

        buttonSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        buttonLayout->addItem(buttonSpacer);

        OKButton = new QPushButton(StatistikGUI);
        OKButton->setObjectName(QStringLiteral("OKButton"));

        buttonLayout->addWidget(OKButton);


        verticalLayout->addLayout(buttonLayout);


        retranslateUi(StatistikGUI);

        OKButton->setDefault(true);


        QMetaObject::connectSlotsByName(StatistikGUI);
    } // setupUi

    void retranslateUi(QDialog *StatistikGUI)
    {
        StatistikGUI->setWindowTitle(QApplication::translate("StatistikGUI", "Statistik...", 0));
        statistikTextEdit->setHtml(QApplication::translate("StatistikGUI", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Hier soll die Statistik stehen.</p></body></html>", 0));
        speichernDialogButton->setText(QApplication::translate("StatistikGUI", "Speichern...", 0));
        OKButton->setText(QApplication::translate("StatistikGUI", "OK", 0));
    } // retranslateUi

};

namespace Ui {
    class StatistikGUI: public Ui_StatistikGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATISTIKGUI_H
