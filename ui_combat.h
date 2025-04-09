/********************************************************************************
** Form generated from reading UI file 'combat.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMBAT_H
#define UI_COMBAT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Combat
{
public:
    QLabel *HP2;
    QLabel *Genimon2;
    QLabel *Genimon1;
    QLabel *TableauInfo;
    QLabel *BackGround;
    QLabel *HP1;
    QLabel *Nom1;
    QLabel *Contoles;
    QLabel *Nom2;
    QLabel *Alerte;
    QLabel *Manche;
    QLabel *Attaque;
    QLabel *Bloquer;
    QLabel *Bonus;
    QLabel *Nb_attaque;
    QLabel *Nb_bouclier;
    QLabel *Nb_bonus;

    void setupUi(QWidget *Combat)
    {
        if (Combat->objectName().isEmpty())
            Combat->setObjectName("Combat");
        Combat->resize(1280, 720);
        HP2 = new QLabel(Combat);
        HP2->setObjectName("HP2");
        HP2->setGeometry(QRect(900, 300, 150, 31));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        HP2->setFont(font);
        HP2->setAutoFillBackground(true);
        HP2->setFrameShape(QFrame::Shape::Box);
        HP2->setLineWidth(3);
        Genimon2 = new QLabel(Combat);
        Genimon2->setObjectName("Genimon2");
        Genimon2->setGeometry(QRect(900, 140, 150, 150));
        Genimon2->setAutoFillBackground(false);
        Genimon1 = new QLabel(Combat);
        Genimon1->setObjectName("Genimon1");
        Genimon1->setGeometry(QRect(280, 280, 150, 150));
        Genimon1->setAutoFillBackground(false);
        TableauInfo = new QLabel(Combat);
        TableauInfo->setObjectName("TableauInfo");
        TableauInfo->setGeometry(QRect(760, 440, 291, 191));
        TableauInfo->setFont(font);
        TableauInfo->setAutoFillBackground(true);
        TableauInfo->setFrameShape(QFrame::Shape::Box);
        TableauInfo->setLineWidth(3);
        TableauInfo->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);
        BackGround = new QLabel(Combat);
        BackGround->setObjectName("BackGround");
        BackGround->setGeometry(QRect(0, 0, 1280, 720));
        BackGround->setAutoFillBackground(true);
        BackGround->setTextFormat(Qt::TextFormat::PlainText);
        BackGround->setPixmap(QPixmap(QString::fromUtf8(":/Decor/Image_Qt/Decor/AreneCombat.png")));
        BackGround->setScaledContents(true);
        HP1 = new QLabel(Combat);
        HP1->setObjectName("HP1");
        HP1->setGeometry(QRect(280, 440, 150, 31));
        HP1->setFont(font);
        HP1->setAutoFillBackground(true);
        HP1->setFrameShape(QFrame::Shape::Box);
        HP1->setLineWidth(3);
        Nom1 = new QLabel(Combat);
        Nom1->setObjectName("Nom1");
        Nom1->setGeometry(QRect(270, 210, 171, 61));
        Nom1->setFont(font);
        Nom1->setAutoFillBackground(true);
        Nom1->setFrameShape(QFrame::Shape::Box);
        Nom1->setLineWidth(3);
        Nom1->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        Contoles = new QLabel(Combat);
        Contoles->setObjectName("Contoles");
        Contoles->setGeometry(QRect(0, 0, 501, 41));
        QFont font1;
        font1.setPointSize(16);
        font1.setBold(false);
        Contoles->setFont(font1);
        Contoles->setAutoFillBackground(true);
        Contoles->setFrameShape(QFrame::Shape::Box);
        Contoles->setLineWidth(3);
        Nom2 = new QLabel(Combat);
        Nom2->setObjectName("Nom2");
        Nom2->setGeometry(QRect(890, 70, 171, 61));
        Nom2->setFont(font);
        Nom2->setAutoFillBackground(true);
        Nom2->setFrameShape(QFrame::Shape::Box);
        Nom2->setLineWidth(3);
        Nom2->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);
        Alerte = new QLabel(Combat);
        Alerte->setObjectName("Alerte");
        Alerte->setGeometry(QRect(60, 80, 381, 71));
        QFont font2;
        font2.setPointSize(16);
        font2.setBold(true);
        Alerte->setFont(font2);
        Alerte->setAutoFillBackground(false);
        Alerte->setAlignment(Qt::AlignmentFlag::AlignCenter);
        Manche = new QLabel(Combat);
        Manche->setObjectName("Manche");
        Manche->setGeometry(QRect(840, 410, 131, 31));
        Manche->setFont(font);
        Manche->setAutoFillBackground(true);
        Manche->setFrameShape(QFrame::Shape::Box);
        Manche->setLineWidth(3);
        Manche->setAlignment(Qt::AlignmentFlag::AlignCenter);
        Attaque = new QLabel(Combat);
        Attaque->setObjectName("Attaque");
        Attaque->setGeometry(QRect(170, 520, 81, 71));
        Attaque->setAutoFillBackground(false);
        Attaque->setPixmap(QPixmap(QString::fromUtf8(":/Decor/Image_Qt/Decor/Attack.png")));
        Attaque->setScaledContents(true);
        Bloquer = new QLabel(Combat);
        Bloquer->setObjectName("Bloquer");
        Bloquer->setGeometry(QRect(310, 520, 91, 81));
        Bloquer->setAutoFillBackground(false);
        Bloquer->setPixmap(QPixmap(QString::fromUtf8(":/Decor/Image_Qt/Decor/Shield.png")));
        Bloquer->setScaledContents(true);
        Bonus = new QLabel(Combat);
        Bonus->setObjectName("Bonus");
        Bonus->setGeometry(QRect(430, 520, 121, 81));
        Bonus->setAutoFillBackground(false);
        Bonus->setPixmap(QPixmap(QString::fromUtf8(":/Decor/Image_Qt/Decor/Bonus.png")));
        Bonus->setScaledContents(true);
        Nb_attaque = new QLabel(Combat);
        Nb_attaque->setObjectName("Nb_attaque");
        Nb_attaque->setGeometry(QRect(160, 610, 121, 31));
        Nb_attaque->setFont(font);
        Nb_attaque->setAutoFillBackground(true);
        Nb_attaque->setFrameShape(QFrame::Shape::Box);
        Nb_attaque->setLineWidth(3);
        Nb_attaque->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        Nb_bouclier = new QLabel(Combat);
        Nb_bouclier->setObjectName("Nb_bouclier");
        Nb_bouclier->setGeometry(QRect(300, 610, 121, 31));
        Nb_bouclier->setFont(font);
        Nb_bouclier->setAutoFillBackground(true);
        Nb_bouclier->setFrameShape(QFrame::Shape::Box);
        Nb_bouclier->setLineWidth(3);
        Nb_bouclier->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        Nb_bonus = new QLabel(Combat);
        Nb_bonus->setObjectName("Nb_bonus");
        Nb_bonus->setGeometry(QRect(440, 610, 101, 31));
        Nb_bonus->setFont(font);
        Nb_bonus->setAutoFillBackground(true);
        Nb_bonus->setFrameShape(QFrame::Shape::Box);
        Nb_bonus->setLineWidth(3);
        Nb_bonus->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        BackGround->raise();
        Nom1->raise();
        Genimon1->raise();
        Genimon2->raise();
        HP1->raise();
        HP2->raise();
        TableauInfo->raise();
        Contoles->raise();
        Nom2->raise();
        Alerte->raise();
        Manche->raise();
        Attaque->raise();
        Bloquer->raise();
        Bonus->raise();
        Nb_attaque->raise();
        Nb_bouclier->raise();
        Nb_bonus->raise();

        retranslateUi(Combat);

        QMetaObject::connectSlotsByName(Combat);
    } // setupUi

    void retranslateUi(QWidget *Combat)
    {
        Combat->setWindowTitle(QCoreApplication::translate("Combat", "Form", nullptr));
        HP2->setText(QCoreApplication::translate("Combat", "PV: ", nullptr));
        Genimon2->setText(QString());
        Genimon1->setText(QString());
        TableauInfo->setText(QString());
        BackGround->setText(QString());
        HP1->setText(QCoreApplication::translate("Combat", "PV: ", nullptr));
        Nom1->setText(QCoreApplication::translate("Combat", "Nom : \n"
"Degats:", nullptr));
        Contoles->setText(QCoreApplication::translate("Combat", "Attaquer (1)       Bloquer (2)       Bonus (3)       Fuir (4)", nullptr));
        Nom2->setText(QCoreApplication::translate("Combat", "Nom : \n"
"Degats:", nullptr));
        Alerte->setText(QCoreApplication::translate("Combat", "Alerte", nullptr));
        Manche->setText(QCoreApplication::translate("Combat", "Manche #1", nullptr));
        Attaque->setText(QString());
        Bloquer->setText(QString());
        Bonus->setText(QString());
        Nb_attaque->setText(QCoreApplication::translate("Combat", "NbAttaque: 9", nullptr));
        Nb_bouclier->setText(QCoreApplication::translate("Combat", "NbBouclier: 9", nullptr));
        Nb_bonus->setText(QCoreApplication::translate("Combat", "NbBonus: 9", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Combat: public Ui_Combat {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMBAT_H
