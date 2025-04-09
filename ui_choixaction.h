/********************************************************************************
** Form generated from reading UI file 'choixaction.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOIXACTION_H
#define UI_CHOIXACTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChoixAction
{
public:
    QLabel *BackGround;
    QLabel *Genimon;
    QLabel *Attaque;
    QLabel *Capturer;
    QLabel *Fuir;
    QLabel *Description;
    QLabel *Titre;

    void setupUi(QWidget *ChoixAction)
    {
        if (ChoixAction->objectName().isEmpty())
            ChoixAction->setObjectName("ChoixAction");
        ChoixAction->resize(1280, 720);
        BackGround = new QLabel(ChoixAction);
        BackGround->setObjectName("BackGround");
        BackGround->setGeometry(QRect(0, 0, 1280, 720));
        BackGround->setBaseSize(QSize(100, 100));
        BackGround->setAutoFillBackground(true);
        BackGround->setFrameShape(QFrame::Shape::Box);
        BackGround->setTextFormat(Qt::TextFormat::PlainText);
        BackGround->setPixmap(QPixmap(QString::fromUtf8(":/Decor/Image_Qt/Decor/AreneCombat.png")));
        BackGround->setScaledContents(true);
        Genimon = new QLabel(ChoixAction);
        Genimon->setObjectName("Genimon");
        Genimon->setGeometry(QRect(240, 50, 400, 400));
        Genimon->setAutoFillBackground(false);
        Attaque = new QLabel(ChoixAction);
        Attaque->setObjectName("Attaque");
        Attaque->setGeometry(QRect(110, 570, 301, 71));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        Attaque->setFont(font);
        Attaque->setAutoFillBackground(true);
        Attaque->setFrameShape(QFrame::Shape::Box);
        Attaque->setLineWidth(3);
        Attaque->setAlignment(Qt::AlignmentFlag::AlignCenter);
        Capturer = new QLabel(ChoixAction);
        Capturer->setObjectName("Capturer");
        Capturer->setGeometry(QRect(480, 570, 311, 71));
        Capturer->setFont(font);
        Capturer->setAutoFillBackground(true);
        Capturer->setFrameShape(QFrame::Shape::Box);
        Capturer->setLineWidth(3);
        Capturer->setAlignment(Qt::AlignmentFlag::AlignCenter);
        Fuir = new QLabel(ChoixAction);
        Fuir->setObjectName("Fuir");
        Fuir->setGeometry(QRect(860, 570, 301, 71));
        Fuir->setFont(font);
        Fuir->setAutoFillBackground(true);
        Fuir->setFrameShape(QFrame::Shape::Box);
        Fuir->setLineWidth(3);
        Fuir->setAlignment(Qt::AlignmentFlag::AlignCenter);
        Description = new QLabel(ChoixAction);
        Description->setObjectName("Description");
        Description->setGeometry(QRect(720, 180, 251, 161));
        QFont font1;
        font1.setPointSize(16);
        font1.setBold(false);
        Description->setFont(font1);
        Description->setAutoFillBackground(true);
        Description->setFrameShape(QFrame::Shape::Box);
        Description->setLineWidth(3);
        Description->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);
        Description->setWordWrap(true);
        Titre = new QLabel(ChoixAction);
        Titre->setObjectName("Titre");
        Titre->setGeometry(QRect(770, 140, 141, 41));
        Titre->setFont(font);
        Titre->setAutoFillBackground(true);
        Titre->setFrameShape(QFrame::Shape::Box);
        Titre->setLineWidth(3);
        Titre->setAlignment(Qt::AlignmentFlag::AlignCenter);

        retranslateUi(ChoixAction);

        QMetaObject::connectSlotsByName(ChoixAction);
    } // setupUi

    void retranslateUi(QWidget *ChoixAction)
    {
        ChoixAction->setWindowTitle(QCoreApplication::translate("ChoixAction", "Form", nullptr));
        BackGround->setText(QString());
        Genimon->setText(QString());
        Attaque->setText(QCoreApplication::translate("ChoixAction", "Attraper (1)", nullptr));
        Capturer->setText(QCoreApplication::translate("ChoixAction", "Combattre (2)", nullptr));
        Fuir->setText(QCoreApplication::translate("ChoixAction", "Fuir (3)", nullptr));
        Description->setText(QString());
        Titre->setText(QCoreApplication::translate("ChoixAction", "Description", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChoixAction: public Ui_ChoixAction {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOIXACTION_H
