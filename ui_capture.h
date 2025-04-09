/********************************************************************************
** Form generated from reading UI file 'capture.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAPTURE_H
#define UI_CAPTURE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Capture
{
public:
    QLabel *BackGround;
    QLabel *Genimon;
    QLabel *Joueur;
    QLabel *Info1;
    QLabel *Resultat;
    QLabel *Pokeball;
    QLabel *Contoles;

    void setupUi(QWidget *Capture)
    {
        if (Capture->objectName().isEmpty())
            Capture->setObjectName("Capture");
        Capture->resize(1280, 720);
        BackGround = new QLabel(Capture);
        BackGround->setObjectName("BackGround");
        BackGround->setGeometry(QRect(0, 0, 1280, 720));
        BackGround->setAutoFillBackground(true);
        BackGround->setTextFormat(Qt::TextFormat::PlainText);
        BackGround->setPixmap(QPixmap(QString::fromUtf8(":/Decor/Image_Qt/Decor/AreneCombat.png")));
        BackGround->setScaledContents(true);
        Genimon = new QLabel(Capture);
        Genimon->setObjectName("Genimon");
        Genimon->setGeometry(QRect(800, 50, 300, 300));
        QFont font;
        font.setKerning(true);
        Genimon->setFont(font);
        Genimon->setAutoFillBackground(false);
        Joueur = new QLabel(Capture);
        Joueur->setObjectName("Joueur");
        Joueur->setGeometry(QRect(-20, 330, 411, 371));
        Joueur->setAutoFillBackground(false);
        Info1 = new QLabel(Capture);
        Info1->setObjectName("Info1");
        Info1->setGeometry(QRect(420, 624, 250, 61));
        QFont font1;
        font1.setPointSize(16);
        font1.setBold(true);
        Info1->setFont(font1);
        Info1->setAutoFillBackground(true);
        Info1->setFrameShape(QFrame::Shape::Box);
        Info1->setLineWidth(3);
        Info1->setAlignment(Qt::AlignmentFlag::AlignCenter);
        Resultat = new QLabel(Capture);
        Resultat->setObjectName("Resultat");
        Resultat->setGeometry(QRect(690, 624, 271, 61));
        Resultat->setFont(font1);
        Resultat->setAutoFillBackground(true);
        Resultat->setFrameShape(QFrame::Shape::Box);
        Resultat->setLineWidth(3);
        Pokeball = new QLabel(Capture);
        Pokeball->setObjectName("Pokeball");
        Pokeball->setGeometry(QRect(500, 190, 100, 80));
        Pokeball->setAutoFillBackground(false);
        Pokeball->setPixmap(QPixmap(QString::fromUtf8(":/Decor/Image_Qt/Decor/pokeball1.png")));
        Pokeball->setScaledContents(true);
        Contoles = new QLabel(Capture);
        Contoles->setObjectName("Contoles");
        Contoles->setGeometry(QRect(0, 0, 281, 41));
        QFont font2;
        font2.setPointSize(16);
        font2.setBold(false);
        Contoles->setFont(font2);
        Contoles->setAutoFillBackground(true);
        Contoles->setFrameShape(QFrame::Shape::Box);
        Contoles->setLineWidth(3);

        retranslateUi(Capture);

        QMetaObject::connectSlotsByName(Capture);
    } // setupUi

    void retranslateUi(QWidget *Capture)
    {
        Capture->setWindowTitle(QCoreApplication::translate("Capture", "Form", nullptr));
        BackGround->setText(QString());
        Genimon->setText(QString());
        Joueur->setText(QString());
        Info1->setText(QCoreApplication::translate("Capture", "Nombres de balle: 0", nullptr));
        Resultat->setText(QCoreApplication::translate("Capture", "R\303\251sultat:", nullptr));
        Pokeball->setText(QString());
        Contoles->setText(QCoreApplication::translate("Capture", "Lancer balle (1)       Partir (2)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Capture: public Ui_Capture {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAPTURE_H
