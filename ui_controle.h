/********************************************************************************
** Form generated from reading UI file 'controle.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROLE_H
#define UI_CONTROLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Controle
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Controle)
    {
        if (Controle->objectName().isEmpty())
            Controle->setObjectName("Controle");
        Controle->resize(1280, 750);
        centralwidget = new QWidget(Controle);
        centralwidget->setObjectName("centralwidget");
        Controle->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Controle);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1280, 25));
        Controle->setMenuBar(menubar);
        statusbar = new QStatusBar(Controle);
        statusbar->setObjectName("statusbar");
        Controle->setStatusBar(statusbar);

        retranslateUi(Controle);

        QMetaObject::connectSlotsByName(Controle);
    } // setupUi

    void retranslateUi(QMainWindow *Controle)
    {
        Controle->setWindowTitle(QCoreApplication::translate("Controle", "Controle", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Controle: public Ui_Controle {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROLE_H
