/********************************************************************************
** Form generated from reading UI file 'map.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAP_H
#define UI_MAP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Map
{
public:
    QLabel *NomPerso;
    QLabel *BackGround;
    QLabel *Contoles;

    void setupUi(QWidget *Map)
    {
        if (Map->objectName().isEmpty())
            Map->setObjectName("Map");
        Map->resize(1280, 720);
        NomPerso = new QLabel(Map);
        NomPerso->setObjectName("NomPerso");
        NomPerso->setGeometry(QRect(0, 669, 211, 51));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        NomPerso->setFont(font);
        NomPerso->setAutoFillBackground(true);
        NomPerso->setFrameShape(QFrame::Shape::Box);
        NomPerso->setLineWidth(3);
        BackGround = new QLabel(Map);
        BackGround->setObjectName("BackGround");
        BackGround->setGeometry(QRect(0, 0, 1280, 720));
        BackGround->setBaseSize(QSize(100, 100));
        BackGround->setAutoFillBackground(true);
        BackGround->setFrameShape(QFrame::Shape::Box);
        BackGround->setTextFormat(Qt::TextFormat::PlainText);
        BackGround->setPixmap(QPixmap(QString::fromUtf8(":/Decor/Image_Qt/Decor/School-Map-withoutPeople-8bit.jpeg")));
        BackGround->setScaledContents(true);
        Contoles = new QLabel(Map);
        Contoles->setObjectName("Contoles");
        Contoles->setGeometry(QRect(0, 0, 411, 41));
        QFont font1;
        font1.setPointSize(16);
        font1.setBold(false);
        Contoles->setFont(font1);
        Contoles->setAutoFillBackground(true);
        Contoles->setFrameShape(QFrame::Shape::Box);
        Contoles->setLineWidth(3);
        BackGround->raise();
        NomPerso->raise();
        Contoles->raise();

        retranslateUi(Map);

        QMetaObject::connectSlotsByName(Map);
    } // setupUi

    void retranslateUi(QWidget *Map)
    {
        Map->setWindowTitle(QCoreApplication::translate("Map", "Form", nullptr));
        NomPerso->setText(QCoreApplication::translate("Map", "Nom perso", nullptr));
        BackGround->setText(QString());
        Contoles->setText(QCoreApplication::translate("Map", "G\303\251nidex (1)       Historique (2)       Pause (3)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Map: public Ui_Map {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAP_H
