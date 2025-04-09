#include "commande.h"
#include "ui_commande.h"

Commande::Commande(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Commande)
{
    ui->setupUi(this);
    ui->ClavierW->setStyleSheet("background-color: red;");
    ui->ClavierA->setStyleSheet("background-color: red;");
    ui->ClavierS->setStyleSheet("background-color: red;");
    ui->ClavierD->setStyleSheet("background-color: red;");
    ui->ClavierH->setStyleSheet("background-color: red;");
}

Commande::~Commande()
{
    delete ui;
}

void Commande::handleKeyPress(int key) {
    if (key == Qt::Key_4) {
        emit requestMenuChange(0); //Passer au menu principal
        clearFocus();
    }

    if (key == Qt::Key_W) {
        ui->ClavierW->setStyleSheet("background-color: green;");
    }
    else {
        ui->ClavierW->setStyleSheet("background-color: red;");
    }

    if (key == Qt::Key_A) {
        ui->ClavierA->setStyleSheet("background-color: green;");
    }
    else {
        ui->ClavierA->setStyleSheet("background-color: red;");
    }

    if (key == Qt::Key_D) {
        ui->ClavierD->setStyleSheet("background-color: green;");
    }
    else {
        ui->ClavierD->setStyleSheet("background-color: red;");
    }

    if (key == Qt::Key_S) {
        ui->ClavierS->setStyleSheet("background-color: green;");
    }
    else {
        ui->ClavierS->setStyleSheet("background-color: red;");
    }

    if (key == Qt::Key_H) {
        ui->ClavierH->setStyleSheet("background-color: green;");
    }
    else {
        ui->ClavierH->setStyleSheet("background-color: red;");
    }
}

void Commande::handleArduinoInput(int boutons, int joystick, int accelerometre, int muons) {


    if (boutons == 1) {
        ui->ManetteB1->setStyleSheet("background-color: green;");
    }
    else {
        ui->ManetteB1->setStyleSheet("background-color: red;");
    }
    if (boutons == 2) {
        ui->ManetteB2->setStyleSheet("background-color: green;");
    }
    else {
        ui->ManetteB2->setStyleSheet("background-color: red;");
    }
    if (boutons == 3) {
        ui->ManetteB3->setStyleSheet("background-color: green;");
    }
    else {
        ui->ManetteB3->setStyleSheet("background-color: red;");
    }
    if (boutons == 4) {
        ui->ManetteB4->setStyleSheet("background-color: green;");
        emit requestMenuChange(0); //Passer au menu principal
        clearFocus();
    }
    else {
        ui->ManetteB4->setStyleSheet("background-color: red;");
    }


    if (joystick == 1) {
        ui->ManetteJoy->setText(QString("EtatJoystick : %1").arg("HAUT"));
    }
    else if (joystick == 2) {
        ui->ManetteJoy->setText(QString("EtatJoystick : %1").arg("DROITE"));
    }
    else if (joystick == 3) {
        ui->ManetteJoy->setText(QString("EtatJoystick : %1").arg("BAS"));
    }
    else if (joystick == 4) {
        ui->ManetteJoy->setText(QString("EtatJoystick : %1").arg("GAUCHE"));
    }

    ui->Accel->setText(QString("Accel : %1").arg(accelerometre));
    ui->Muon->setText(QString("Muons : %1").arg(muons));
}
