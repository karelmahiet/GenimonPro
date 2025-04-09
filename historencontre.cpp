#include "historencontre.h"
#include "ui_historencontre.h"
#include <string>

const int maxGenimonPage = 10;

HistoRencontre::HistoRencontre(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HistoRencontre)
{
    ui->setupUi(this);

    borne1 = maxGenimonPage;
    borne2 = maxGenimonPage * 2;
}

HistoRencontre::~HistoRencontre()
{
    delete ui;
}

void HistoRencontre::handleKeyPress(int key) {

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

void HistoRencontre::handleArduinoInput(int boutons, int joystick, int accelerometre, int muons) {

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

    ACCEL = accelerometre;
    MUONS = muons;

    update();
}

void HistoRencontre::update() {
    if (BOUTONS == 4) {
        BOUTONS = 0;
        JOYSTICKS = 0;
        ACCEL = 0;
        MUONS = 0;
        emit requestMenuChange(2); //Passer au menu map
    }

    BOUTONS = 0;
    JOYSTICKS = 0;
    ACCEL = 0;
    MUONS = 0;
}

void HistoRencontre::ecrireHistorique(vector<Genimon> historique)
{
    QString texte1 = "";
    QString texte2 = "";

    if (historique.size() == 0)
    {
        ui->Affichage1->setText("Aucun genimon rencontre");
    }
    else if (historique.size() <= borne1)
    {
        for (int i = 0; i < historique.size(); i++)
        {
            texte1.append(to_string(i + 1) + ") Nom: " + historique[i].getNom() + ", Type: " + historique[i].getType()
                + ", Rarete: " + historique[i].getRarete() + ", PV: " + to_string(historique[i].getPV()) +
                ", Degats: " + to_string(historique[i].getDegats()) + "\n");
        }

        ui->Affichage1->setText(texte1);
    }
    else if (historique.size() <= borne2)
    {
        for (int i = borne1; i < historique.size(); i++)
        {
            texte2.append(to_string(i + 1) + ") Nom: " + historique[i].getNom() + ", Type: " + historique[i].getType()
                + ", Rarete: " + historique[i].getRarete() + ", PV: " + to_string(historique[i].getPV()) +
                ", Degats: " + to_string(historique[i].getDegats()) + "\n");
        }

        ui->Affichage2->setText(texte2);
    }
    else
    {
        //Décalage des pages
        ui->Affichage1->setText(ui->Affichage2->text());

        texte2.append(to_string(borne2 + 1) + ") Nom: " + historique[borne2].getNom() + ", Type: " + historique[borne2].getType()
            + ", Rarete: " + historique[borne2].getRarete() + ", PV: " + to_string(historique[borne2].getPV()) +
            ", Degats: " + to_string(historique[borne2].getDegats()) + "\n");

        ui->Affichage2->setText(texte2);
        borne1 = borne2;
        borne2 = borne2 + maxGenimonPage;
    }
}
