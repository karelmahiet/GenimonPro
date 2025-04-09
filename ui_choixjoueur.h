/********************************************************************************
** Form generated from reading UI file 'choixjoueur.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOIXJOUEUR_H
#define UI_CHOIXJOUEUR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChoixJoueur
{
public:
    QLineEdit *NomChoisi;
    QLabel *BackGround;
    QLabel *Retour;
    QLabel *Description;
    QLabel *Titre;
    QLabel *Continuer;
    QLabel *Nom;

    void setupUi(QWidget *ChoixJoueur)
    {
        if (ChoixJoueur->objectName().isEmpty())
            ChoixJoueur->setObjectName("ChoixJoueur");
        ChoixJoueur->resize(1280, 720);
        NomChoisi = new QLineEdit(ChoixJoueur);
        NomChoisi->setObjectName("NomChoisi");
        NomChoisi->setGeometry(QRect(410, 260, 400, 60));
        QFont font;
        font.setPointSize(16);
        NomChoisi->setFont(font);
        NomChoisi->setMaxLength(20);
        BackGround = new QLabel(ChoixJoueur);
        BackGround->setObjectName("BackGround");
        BackGround->setGeometry(QRect(0, 0, 1280, 720));
        BackGround->setBaseSize(QSize(100, 100));
        BackGround->setAutoFillBackground(true);
        BackGround->setFrameShape(QFrame::Shape::Box);
        BackGround->setTextFormat(Qt::TextFormat::PlainText);
        BackGround->setPixmap(QPixmap(QString::fromUtf8(":/Decor/Image_Qt/Decor/Ciel_menu.jpg")));
        BackGround->setScaledContents(true);
        Retour = new QLabel(ChoixJoueur);
        Retour->setObjectName("Retour");
        Retour->setGeometry(QRect(540, 600, 200, 40));
        Retour->setAutoFillBackground(true);
        Retour->setAlignment(Qt::AlignmentFlag::AlignCenter);
        Description = new QLabel(ChoixJoueur);
        Description->setObjectName("Description");
        Description->setGeometry(QRect(400, 200, 500, 250));
        QFont font1;
        font1.setPointSize(16);
        font1.setBold(true);
        Description->setFont(font1);
        Description->setAutoFillBackground(false);
        Description->setAlignment(Qt::AlignmentFlag::AlignCenter);
        Description->setWordWrap(true);
        Titre = new QLabel(ChoixJoueur);
        Titre->setObjectName("Titre");
        Titre->setGeometry(QRect(19, 20, 1251, 100));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        Titre->setPalette(palette);
        QFont font2;
        font2.setFamilies({QString::fromUtf8("FZShuTi")});
        font2.setPointSize(60);
        font2.setUnderline(false);
        font2.setStrikeOut(false);
        font2.setStyleStrategy(QFont::PreferDefault);
        Titre->setFont(font2);
        Titre->setMouseTracking(false);
        Titre->setContextMenuPolicy(Qt::ContextMenuPolicy::DefaultContextMenu);
        Titre->setAutoFillBackground(false);
        Titre->setTextFormat(Qt::TextFormat::PlainText);
        Titre->setScaledContents(false);
        Titre->setAlignment(Qt::AlignmentFlag::AlignCenter);
        Titre->setWordWrap(false);
        Continuer = new QLabel(ChoixJoueur);
        Continuer->setObjectName("Continuer");
        Continuer->setGeometry(QRect(540, 540, 200, 40));
        Continuer->setAutoFillBackground(true);
        Continuer->setAlignment(Qt::AlignmentFlag::AlignCenter);
        Nom = new QLabel(ChoixJoueur);
        Nom->setObjectName("Nom");
        Nom->setGeometry(QRect(310, 270, 100, 40));
        Nom->setFont(font);
        Nom->setAlignment(Qt::AlignmentFlag::AlignCenter);
        BackGround->raise();
        NomChoisi->raise();
        Retour->raise();
        Description->raise();
        Titre->raise();
        Continuer->raise();
        Nom->raise();

        retranslateUi(ChoixJoueur);

        QMetaObject::connectSlotsByName(ChoixJoueur);
    } // setupUi

    void retranslateUi(QWidget *ChoixJoueur)
    {
        ChoixJoueur->setWindowTitle(QCoreApplication::translate("ChoixJoueur", "Form", nullptr));
        BackGround->setText(QString());
        Retour->setText(QCoreApplication::translate("ChoixJoueur", "Retour (2)", nullptr));
        Description->setText(QCoreApplication::translate("ChoixJoueur", "Description", nullptr));
        Titre->setText(QCoreApplication::translate("ChoixJoueur", "Choix du joueur", nullptr));
        Continuer->setText(QCoreApplication::translate("ChoixJoueur", "Continuer (1)", nullptr));
        Nom->setText(QCoreApplication::translate("ChoixJoueur", "Nom :", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChoixJoueur: public Ui_ChoixJoueur {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOIXJOUEUR_H
