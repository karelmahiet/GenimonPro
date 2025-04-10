#include "pause.h"
#include "ui_pause.h"

Pause::Pause(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::Pause)
{
    ui->setupUi(this);
    ui->Option3->setStyleSheet("background-color: red;");
    ui->Option3->setText("Mode 5a8 (3) : OFF");
    mode5a8Actif = false;
}

Pause::~Pause()
{
    delete ui;
}

void Pause::handleKeyPress(int key) {
    if (key == Qt::Key_1) {
        QApplication::quit(); // Quitter
    }
    else if (key == Qt::Key_2) {
        ui->Option3->setStyleSheet("background-color: red;");
        ui->Option3->setText("Mode 5a8 (3) : OFF");
        mode5a8Actif = false;
        emit reinitialiserJeu();
        emit requestMenuChange(0); //Passer au menu main
        clearFocus();
    }
    else if (key == Qt::Key_3) {
        if (mode5a8Actif)
        {
            mode5a8Actif = false;
            ui->Option3->setStyleSheet("background-color: red;");
            ui->Option3->setText("Mode 5a8 (3) : OFF");
        }
        else
        {
            mode5a8Actif = true;
            ui->Option3->setStyleSheet("background-color: green;");
            ui->Option3->setText("Mode 5a8 (3) : ON");
        }
        emit mode5a8();
    }
    else if (key == Qt::Key_4) {
        emit requestMenuChange(2); //Passer au menu map
    }
}

void Pause::handleArduinoInput(int boutons, int joystick, int accelerometre, int muons) {

    if (boutons == 1) {
        QApplication::quit(); // Quitter
    }
    else if (boutons == 2) {
        ui->Option3->setStyleSheet("background-color: red;");
        ui->Option3->setText("Mode 5a8 (3) : OFF");
        mode5a8Actif = false;
        emit reinitialiserJeu();
        emit requestMenuChange(0); //Passer au menu main
        clearFocus();
    }
    else if (boutons == 3) {
        if (mode5a8Actif)
        {
            mode5a8Actif = false;
            ui->Option3->setStyleSheet("background-color: red;");
            ui->Option3->setText("Mode 5a8 (3) : OFF");
        }
        else
        {
            mode5a8Actif = true;
            ui->Option3->setStyleSheet("background-color: green;");
            ui->Option3->setText("Mode 5a8 (3) : ON");
        }
        emit mode5a8();
    }
    else if (boutons == 4) {
        emit requestMenuChange(2); //Passer au menu map
    }
}
