#include "choixaction.h"
#include "ui_choixaction.h"

ChoixAction::ChoixAction(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChoixAction)
{
    ui->setupUi(this);
}

ChoixAction::~ChoixAction()
{
    delete ui;
}

void ChoixAction::afficherInfoGenimon(Genimon genimonEnCours, int* nbBalles, int* nbCapsuleGuerison, vector<Genimon>* genidex)
{
    QString texte = "";
    ui->Genimon->setPixmap(genimonEnCours.imageGenimon.scaled(ui->Genimon->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    texte.append("Nom: " + genimonEnCours.getNom() + "\nType: " + genimonEnCours.getType() + "\nRarete: " + genimonEnCours.getRarete()
        + "\nPV: " + to_string(genimonEnCours.getPV()) + "\nDegats: " + to_string(genimonEnCours.getDegats()));
    ui->Description->setText(texte);

    genimonEnCours_trans.clear();
    genimonEnCours_trans.push_back(genimonEnCours);
    nbBalles_trans = nbBalles;
    nbCapsuleGuerison_trans = nbCapsuleGuerison;
    genidex_trans = genidex;
    
    if (*nbBalles_trans > 0)
    { 
        ui->Attaque->setStyleSheet("background-color: white;");
    }
    else
    {
        ui->Attaque->setStyleSheet("background-color: grey;");
    }

    if (genidex_trans->size() > 0)
    {
        ui->Capturer->setStyleSheet("background-color: white;");
    }
    else
    {
        ui->Capturer->setStyleSheet("background-color: grey;");
    }
}

void ChoixAction::handleKeyPress(int key) {
    if (key == Qt::Key_1) {
        BOUTONS = 1;
    }
    else if (key == Qt::Key_2) {
        BOUTONS = 2;
    }
    else if (key == Qt::Key_3) {
        BOUTONS = 3;
    }
    else if (key == Qt::Key_4) {
        BOUTONS = 4;
    }

    if (key == Qt::Key_W) {
        JOYSTICKS = 1;
    }
    else if (key == Qt::Key_D) {
        JOYSTICKS = 2;
    }
    else if (key == Qt::Key_S) {
        JOYSTICKS = 3;
    }
    else if (key == Qt::Key_A) {
        JOYSTICKS = 4;
    }
    else {
        JOYSTICKS = 0;
    }

    update();
}

void ChoixAction::handleArduinoInput(int boutons, int joystick, int accelerometre, int muons) {

    if (boutons == 1) {
        BOUTONS = 1;
    }
    else if (boutons == 2) {
        BOUTONS = 2;
    }
    else if (boutons == 3) {
        BOUTONS = 3;
    }
    else if (boutons == 4) {
        BOUTONS = 4;
    }

    if (joystick == 1) {
        JOYSTICKS = 1;
    }
    else if (joystick == 2) {
        JOYSTICKS = 2;
    }
    else if (joystick == 3) {
        JOYSTICKS = 3;
    }
    else if (joystick == 4) {
        JOYSTICKS = 4;
    }

    update();
}

void ChoixAction::update() {

    if (BOUTONS == 1) {
        if (*nbBalles_trans > 0)
        {
            BOUTONS = 0;
            JOYSTICKS = 0;
            ACCEL = 0;
            MUONS = 0;
            emit sendInfos(genimonEnCours_trans[0], nbBalles_trans, nbCapsuleGuerison_trans, genidex_trans);
            emit requestMenuChange(3); //Passer au menu capture
            clearFocus();
        }
    }
    else if (BOUTONS == 2) {
        if (genidex_trans->size() > 0)
        {
            BOUTONS = 0;
            JOYSTICKS = 0;
            ACCEL = 0;
            MUONS = 0;
            emit sendInfos(genimonEnCours_trans[0], nbBalles_trans, nbCapsuleGuerison_trans, genidex_trans);
            emit requestMenuChange(4); //Passer au menu combat
            clearFocus();
        }
    }
    else if (BOUTONS == 3) {
        BOUTONS = 0;
        JOYSTICKS = 0;
        ACCEL = 0;
        MUONS = 0;
        emit requestMenuChange(2); //Passer au menu map
        clearFocus();
    }

    BOUTONS = 0;
    JOYSTICKS = 0;
    ACCEL = 0;
    MUONS = 0;
}
