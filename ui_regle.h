/********************************************************************************
** Form generated from reading UI file 'regle.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGLE_H
#define UI_REGLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Regle
{
public:
    QLabel *Reglement;
    QLabel *RegleTitre;
    QLabel *BackGround;
    QLabel *Retour;

    void setupUi(QWidget *Regle)
    {
        if (Regle->objectName().isEmpty())
            Regle->setObjectName("Regle");
        Regle->resize(1280, 720);
        Reglement = new QLabel(Regle);
        Reglement->setObjectName("Reglement");
        Reglement->setEnabled(true);
        Reglement->setGeometry(QRect(400, 110, 471, 400));
        QFont font;
        font.setPointSize(12);
        font.setBold(false);
        Reglement->setFont(font);
        Reglement->setAcceptDrops(false);
        Reglement->setAlignment(Qt::AlignmentFlag::AlignCenter);
        RegleTitre = new QLabel(Regle);
        RegleTitre->setObjectName("RegleTitre");
        RegleTitre->setGeometry(QRect(440, 50, 400, 50));
        QFont font1;
        font1.setPointSize(22);
        font1.setBold(true);
        RegleTitre->setFont(font1);
        RegleTitre->setAlignment(Qt::AlignmentFlag::AlignCenter);
        BackGround = new QLabel(Regle);
        BackGround->setObjectName("BackGround");
        BackGround->setGeometry(QRect(0, 0, 1280, 720));
        BackGround->setBaseSize(QSize(100, 100));
        BackGround->setAutoFillBackground(true);
        BackGround->setFrameShape(QFrame::Shape::Box);
        BackGround->setTextFormat(Qt::TextFormat::PlainText);
        BackGround->setPixmap(QPixmap(QString::fromUtf8(":/Decor/Image_Qt/Decor/Ciel_menu.jpg")));
        BackGround->setScaledContents(true);
        Retour = new QLabel(Regle);
        Retour->setObjectName("Retour");
        Retour->setGeometry(QRect(565, 540, 150, 40));
        Retour->setAutoFillBackground(true);
        Retour->setAlignment(Qt::AlignmentFlag::AlignCenter);
        BackGround->raise();
        Reglement->raise();
        RegleTitre->raise();
        Retour->raise();

        retranslateUi(Regle);

        QMetaObject::connectSlotsByName(Regle);
    } // setupUi

    void retranslateUi(QWidget *Regle)
    {
        Regle->setWindowTitle(QCoreApplication::translate("Regle", "Form", nullptr));
        Reglement->setText(QCoreApplication::translate("Regle", "<html><head/><body><p align=\"center\">Bienvenue dans Genimon!</p><p align=\"center\">Promenez-vous dans la facult\303\251 de g\303\251nie et rencontrez des</p><p align=\"center\">Genimons. Attrapez-les avec des balles pour les ajouter \303\240 votre</p><p align=\"center\">Genidex ou combattez-les pour tentez de gagner plus de balles.</p><p align=\"center\">Une aventure passionnante vous attend.</p><p align=\"center\">Bonne chasse!</p></body></html>", nullptr));
        RegleTitre->setText(QCoreApplication::translate("Regle", "<html><head/><body><p><span style=\" font-size:22pt;\">D\303\251roulement du jeu</span></p></body></html>", nullptr));
        BackGround->setText(QString());
        Retour->setText(QCoreApplication::translate("Regle", "Retour au menu (4)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Regle: public Ui_Regle {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGLE_H
