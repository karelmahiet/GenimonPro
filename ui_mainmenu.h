/********************************************************************************
** Form generated from reading UI file 'mainmenu.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINMENU_H
#define UI_MAINMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainMenu
{
public:
    QLabel *SousTitre;
    QLabel *Commande;
    QLabel *Regle;
    QLabel *BackGround;
    QLabel *TitreJeu;
    QLabel *Quitter;
    QLabel *Start;

    void setupUi(QWidget *MainMenu)
    {
        if (MainMenu->objectName().isEmpty())
            MainMenu->setObjectName("MainMenu");
        MainMenu->resize(1280, 720);
        SousTitre = new QLabel(MainMenu);
        SousTitre->setObjectName("SousTitre");
        SousTitre->setGeometry(QRect(565, 120, 150, 41));
        QFont font;
        font.setFamilies({QString::fromUtf8("FZShuTi")});
        font.setPointSize(20);
        SousTitre->setFont(font);
        SousTitre->setAlignment(Qt::AlignmentFlag::AlignCenter);
        Commande = new QLabel(MainMenu);
        Commande->setObjectName("Commande");
        Commande->setGeometry(QRect(540, 480, 200, 40));
        Commande->setAutoFillBackground(true);
        Commande->setAlignment(Qt::AlignmentFlag::AlignCenter);
        Regle = new QLabel(MainMenu);
        Regle->setObjectName("Regle");
        Regle->setGeometry(QRect(540, 540, 200, 40));
        Regle->setAutoFillBackground(true);
        Regle->setAlignment(Qt::AlignmentFlag::AlignCenter);
        BackGround = new QLabel(MainMenu);
        BackGround->setObjectName("BackGround");
        BackGround->setGeometry(QRect(0, 0, 1280, 720));
        BackGround->setBaseSize(QSize(100, 100));
        BackGround->setAutoFillBackground(true);
        BackGround->setFrameShape(QFrame::Shape::Box);
        BackGround->setTextFormat(Qt::TextFormat::PlainText);
        BackGround->setPixmap(QPixmap(QString::fromUtf8(":/Decor/Image_Qt/Decor/Ciel_menu.jpg")));
        BackGround->setScaledContents(true);
        TitreJeu = new QLabel(MainMenu);
        TitreJeu->setObjectName("TitreJeu");
        TitreJeu->setGeometry(QRect(390, 20, 500, 100));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        TitreJeu->setPalette(palette);
        QFont font1;
        font1.setFamilies({QString::fromUtf8("FZShuTi")});
        font1.setPointSize(60);
        font1.setUnderline(false);
        font1.setStrikeOut(false);
        font1.setStyleStrategy(QFont::PreferDefault);
        TitreJeu->setFont(font1);
        TitreJeu->setMouseTracking(false);
        TitreJeu->setContextMenuPolicy(Qt::ContextMenuPolicy::DefaultContextMenu);
        TitreJeu->setAutoFillBackground(false);
        TitreJeu->setTextFormat(Qt::TextFormat::PlainText);
        TitreJeu->setScaledContents(false);
        TitreJeu->setAlignment(Qt::AlignmentFlag::AlignCenter);
        TitreJeu->setWordWrap(false);
        Quitter = new QLabel(MainMenu);
        Quitter->setObjectName("Quitter");
        Quitter->setGeometry(QRect(540, 600, 200, 40));
        Quitter->setAutoFillBackground(true);
        Quitter->setAlignment(Qt::AlignmentFlag::AlignCenter);
        Start = new QLabel(MainMenu);
        Start->setObjectName("Start");
        Start->setGeometry(QRect(540, 420, 200, 40));
        Start->setAutoFillBackground(true);
        Start->setAlignment(Qt::AlignmentFlag::AlignCenter);
        BackGround->raise();
        TitreJeu->raise();
        Quitter->raise();
        Start->raise();
        SousTitre->raise();
        Regle->raise();
        Commande->raise();

        retranslateUi(MainMenu);

        QMetaObject::connectSlotsByName(MainMenu);
    } // setupUi

    void retranslateUi(QWidget *MainMenu)
    {
        MainMenu->setWindowTitle(QCoreApplication::translate("MainMenu", "Form", nullptr));
        SousTitre->setText(QCoreApplication::translate("MainMenu", "Vert & or", nullptr));
        Commande->setText(QCoreApplication::translate("MainMenu", "Commandes (2)", nullptr));
        Regle->setText(QCoreApplication::translate("MainMenu", "D\303\251roulement du jeu (3)", nullptr));
        BackGround->setText(QString());
        TitreJeu->setText(QCoreApplication::translate("MainMenu", "Genimon", nullptr));
        Quitter->setText(QCoreApplication::translate("MainMenu", "Quitter le jeu (4)", nullptr));
        Start->setText(QCoreApplication::translate("MainMenu", "Nouvelle partie (1)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainMenu: public Ui_MainMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINMENU_H
