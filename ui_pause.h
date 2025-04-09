/********************************************************************************
** Form generated from reading UI file 'pause.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAUSE_H
#define UI_PAUSE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Pause
{
public:
    QLabel *BackGround;
    QLabel *Option2;
    QLabel *Option1;
    QLabel *Option3;
    QLabel *Titre;
    QLabel *Option4;

    void setupUi(QWidget *Pause)
    {
        if (Pause->objectName().isEmpty())
            Pause->setObjectName("Pause");
        Pause->resize(1280, 720);
        BackGround = new QLabel(Pause);
        BackGround->setObjectName("BackGround");
        BackGround->setGeometry(QRect(-5, -35, 1300, 800));
        BackGround->setAutoFillBackground(true);
        BackGround->setPixmap(QPixmap(QString::fromUtf8(":/Decor/Image_Qt/Decor/Paysage.png")));
        BackGround->setScaledContents(true);
        Option2 = new QLabel(Pause);
        Option2->setObjectName("Option2");
        Option2->setGeometry(QRect(520, 320, 221, 40));
        QFont font;
        font.setPointSize(12);
        Option2->setFont(font);
        Option2->setAutoFillBackground(true);
        Option2->setAlignment(Qt::AlignmentFlag::AlignCenter);
        Option1 = new QLabel(Pause);
        Option1->setObjectName("Option1");
        Option1->setGeometry(QRect(520, 240, 221, 40));
        Option1->setFont(font);
        Option1->setAutoFillBackground(true);
        Option1->setAlignment(Qt::AlignmentFlag::AlignCenter);
        Option3 = new QLabel(Pause);
        Option3->setObjectName("Option3");
        Option3->setGeometry(QRect(520, 400, 221, 40));
        Option3->setFont(font);
        Option3->setAutoFillBackground(true);
        Option3->setAlignment(Qt::AlignmentFlag::AlignCenter);
        Titre = new QLabel(Pause);
        Titre->setObjectName("Titre");
        Titre->setGeometry(QRect(370, 70, 500, 100));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        Titre->setPalette(palette);
        QFont font1;
        font1.setFamilies({QString::fromUtf8("FZShuTi")});
        font1.setPointSize(50);
        font1.setUnderline(false);
        font1.setStrikeOut(false);
        font1.setStyleStrategy(QFont::PreferDefault);
        Titre->setFont(font1);
        Titre->setMouseTracking(false);
        Titre->setContextMenuPolicy(Qt::ContextMenuPolicy::DefaultContextMenu);
        Titre->setAutoFillBackground(false);
        Titre->setTextFormat(Qt::TextFormat::PlainText);
        Titre->setScaledContents(false);
        Titre->setAlignment(Qt::AlignmentFlag::AlignCenter);
        Titre->setWordWrap(false);
        Option4 = new QLabel(Pause);
        Option4->setObjectName("Option4");
        Option4->setGeometry(QRect(520, 480, 221, 40));
        Option4->setFont(font);
        Option4->setAutoFillBackground(true);
        Option4->setAlignment(Qt::AlignmentFlag::AlignCenter);

        retranslateUi(Pause);

        QMetaObject::connectSlotsByName(Pause);
    } // setupUi

    void retranslateUi(QWidget *Pause)
    {
        Pause->setWindowTitle(QCoreApplication::translate("Pause", "Form", nullptr));
        BackGround->setText(QString());
        Option2->setText(QCoreApplication::translate("Pause", "Reinitialiser le jeu (2)", nullptr));
        Option1->setText(QCoreApplication::translate("Pause", "Sortir du jeu (1)", nullptr));
        Option3->setText(QCoreApplication::translate("Pause", "Mode 5a8 (3) : OFF", nullptr));
        Titre->setText(QCoreApplication::translate("Pause", "Jeu en pause", nullptr));
        Option4->setText(QCoreApplication::translate("Pause", "Revenir au jeu (4)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Pause: public Ui_Pause {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAUSE_H
