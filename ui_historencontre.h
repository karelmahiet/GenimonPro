/********************************************************************************
** Form generated from reading UI file 'historencontre.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HISTORENCONTRE_H
#define UI_HISTORENCONTRE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HistoRencontre
{
public:
    QLabel *Affichage1;
    QLabel *Affichage2;
    QLabel *BackGround;
    QLabel *Contoles;

    void setupUi(QWidget *HistoRencontre)
    {
        if (HistoRencontre->objectName().isEmpty())
            HistoRencontre->setObjectName("HistoRencontre");
        HistoRencontre->resize(1280, 720);
        Affichage1 = new QLabel(HistoRencontre);
        Affichage1->setObjectName("Affichage1");
        Affichage1->setGeometry(QRect(120, 70, 471, 571));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        Affichage1->setFont(font);
        Affichage1->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);
        Affichage1->setWordWrap(true);
        Affichage2 = new QLabel(HistoRencontre);
        Affichage2->setObjectName("Affichage2");
        Affichage2->setGeometry(QRect(680, 70, 471, 571));
        Affichage2->setFont(font);
        Affichage2->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);
        Affichage2->setWordWrap(true);
        BackGround = new QLabel(HistoRencontre);
        BackGround->setObjectName("BackGround");
        BackGround->setGeometry(QRect(-5, -35, 1300, 800));
        BackGround->setAutoFillBackground(true);
        BackGround->setPixmap(QPixmap(QString::fromUtf8(":/Decor/Image_Qt/Decor/Livre2D_V2.png")));
        BackGround->setScaledContents(true);
        Contoles = new QLabel(HistoRencontre);
        Contoles->setObjectName("Contoles");
        Contoles->setGeometry(QRect(0, 0, 111, 41));
        QFont font1;
        font1.setPointSize(16);
        font1.setBold(false);
        Contoles->setFont(font1);
        Contoles->setAutoFillBackground(true);
        Contoles->setFrameShape(QFrame::Shape::Box);
        Contoles->setLineWidth(3);
        BackGround->raise();
        Affichage1->raise();
        Affichage2->raise();
        Contoles->raise();

        retranslateUi(HistoRencontre);

        QMetaObject::connectSlotsByName(HistoRencontre);
    } // setupUi

    void retranslateUi(QWidget *HistoRencontre)
    {
        HistoRencontre->setWindowTitle(QCoreApplication::translate("HistoRencontre", "Form", nullptr));
        Affichage1->setText(QString());
        Affichage2->setText(QString());
        BackGround->setText(QString());
        Contoles->setText(QCoreApplication::translate("HistoRencontre", "Fermer (4)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HistoRencontre: public Ui_HistoRencontre {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HISTORENCONTRE_H
