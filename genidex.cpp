#include "genidex.h"
#include "ui_genidex.h"
#include <string>

Genidex::Genidex(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::Genidex)
{
    ui->setupUi(this);
    ui->Alerte->setStyleSheet("color: red;");
}

Genidex::~Genidex()
{
    delete ui;
}

void Genidex::handleKeyPress(int key) {

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

void Genidex::handleArduinoInput(int boutons, int joystick, int accelerometre, int muons) {

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

void Genidex::update() {
    if (BOUTONS == 1 && estListe && selectionGenimon < genidex_trans->size())
    {
        if (!preparationCombat)
        {
            estListe = false;
            showGenimon();
        }
        else
        {
            BOUTONS = 0;
            JOYSTICKS = 0;
            ACCEL = 0;
            MUONS = 0;
            preparationCombat = false;
            emit sendInfos(genimonEnnemi[0], NbBalles, &(*genidex_trans)[selectionGenimon]);
            emit requestMenuChange(4); //Passer au menu combat
        }
    }
    else if (BOUTONS == 1 && !estListe && *nbCapsuleGuerison_trans > 0 &&
            (*genidex_trans)[selectionGenimon].getPV() < (*genidex_trans)[selectionGenimon].pvMax)
    {
        //Guerison du genimon
        (*genidex_trans)[selectionGenimon].setPV((*genidex_trans)[selectionGenimon].pvMax);
        (*nbCapsuleGuerison_trans) -= 1;

        ui->Info2->setText("Nombre de capsules de guerison: " + QString().append((to_string(*nbCapsuleGuerison_trans))));
        if (*nbCapsuleGuerison_trans > 0)
        {
            ui->Info2->setStyleSheet("background-color: white;");
        }
        else
        {
            ui->Info2->setStyleSheet("background-color: grey;");
        }

        showGenimon();
    }
    else if (BOUTONS == 4 && estListe)
    {
        BOUTONS = 0;
        JOYSTICKS = 0;
        ACCEL = 0;
        MUONS = 0;
        emit requestMenuChange(2); //Passer au menu Map
    }
    else if (BOUTONS == 4 && !estListe)
    {
        estListe = true;
        showListGenimon();
    }

    if (JOYSTICKS == 1 && selectionGenimon > 0)
    {
        selectionGenimon -= 1;
        highlight();
    }
    else if (JOYSTICKS == 3 && selectionGenimon < 7)
    {
        selectionGenimon += 1;
        highlight();
    }
    else if (JOYSTICKS == 4 && selectionGenimon >= 2)
    {
        selectionGenimon -= 2;
        highlight();
    }
    else if (JOYSTICKS == 2 && selectionGenimon <= 5)
    {
        selectionGenimon += 2;
        highlight();
    }

    BOUTONS = 0;
    JOYSTICKS = 0;
    ACCEL = 0;
    MUONS = 0;
}

void Genidex::debuterPreparationCombat(Genimon GenimonEnnemi)
{
    preparationCombat = true;
    genimonEnnemi.clear();
    genimonEnnemi.push_back(GenimonEnnemi);
    ui->Contoles1->setVisible(false);
    ui->Contoles3->setVisible(true);
    ui->Info1->setVisible(false);
    ui->Info2->setVisible(false);
}

void Genidex::setGenidex(int* nbBalles, int* nbCapsuleGuerison, vector<Genimon>* genidex)
{
    ui->Genimon1->clear();
    ui->Genimon2->clear();
    ui->Genimon3->clear();
    ui->Genimon4->clear();
    ui->Genimon5->clear();
    ui->Genimon6->clear();
    ui->Genimon7->clear();
    ui->Genimon8->clear();
    ui->Nom1->setText("Nom: ");
    ui->Nom2->setText("Nom: ");
    ui->Nom3->setText("Nom: ");
    ui->Nom4->setText("Nom: ");
    ui->Nom5->setText("Nom: ");
    ui->Nom6->setText("Nom: ");
    ui->Nom7->setText("Nom: ");
    ui->Nom8->setText("Nom: ");

    genidex_trans = genidex;
    nbCapsuleGuerison_trans = nbCapsuleGuerison;
    ui->Info1->setText("Nombre de balles: " + QString().append((to_string(*nbBalles))));
    ui->Info2->setText("Nombre de capsules de guerison: " + QString().append((to_string(*nbCapsuleGuerison))));
    selectionGenimon = 0;
    estListe = true;
    showListGenimon();
    highlight();

    if (*nbCapsuleGuerison > 0)
    {
        ui->Info2->setStyleSheet("background-color: white;");
    }
    else
    {
        ui->Info2->setStyleSheet("background-color: grey;");
    }

    NbBalles = nbBalles;
}


void Genidex::showGenimon()
{
    ui->Genimon->setVisible(true);
    ui->Description->setVisible(true);
    ui->Contoles2->setVisible(true);

    ui->Contoles1->setVisible(false);

    if (*nbCapsuleGuerison_trans <= 0 || (*genidex_trans)[selectionGenimon].getPV() >= (*genidex_trans)[selectionGenimon].pvMax)
    {
        ui->Alerte->setVisible(true);
    }

    ui->Genimon1->setVisible(false);
    ui->Genimon2->setVisible(false);
    ui->Genimon3->setVisible(false);
    ui->Genimon4->setVisible(false);
    ui->Genimon5->setVisible(false);
    ui->Genimon6->setVisible(false);
    ui->Genimon7->setVisible(false);
    ui->Genimon8->setVisible(false);

    ui->Nom1->setVisible(false);
    ui->Nom2->setVisible(false);
    ui->Nom3->setVisible(false);
    ui->Nom4->setVisible(false);
    ui->Nom5->setVisible(false);
    ui->Nom6->setVisible(false);
    ui->Nom7->setVisible(false);
    ui->Nom8->setVisible(false);


    ui->Genimon->setPixmap((*genidex_trans)[selectionGenimon].imageGenimon.scaled(ui->Genimon->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->Description->setText(QString().append("Nom: " + (*genidex_trans)[selectionGenimon].getNom()
                    + "\nType: " + (*genidex_trans)[selectionGenimon].getType()
                    + "\nRarete: " + (*genidex_trans)[selectionGenimon].getRarete()
                    + "\nPV max: " + to_string((*genidex_trans)[selectionGenimon].pvMax)
                    + "\nPV: " + to_string((*genidex_trans)[selectionGenimon].getPV())
                    + "\nDegats: " + to_string((*genidex_trans)[selectionGenimon].getDegats())));
}

void Genidex::showListGenimon()
{
    ui->Genimon->setVisible(false);
    ui->Description->setVisible(false);
    ui->Contoles2->setVisible(false);
    ui->Contoles3->setVisible(false);

    ui->Contoles1->setVisible(true);
    ui->Alerte->setVisible(false);
    ui->Info1->setVisible(true);
    ui->Info2->setVisible(true);

    ui->Genimon1->setVisible(true);
    ui->Genimon2->setVisible(true);
    ui->Genimon3->setVisible(true);
    ui->Genimon4->setVisible(true);
    ui->Genimon5->setVisible(true);
    ui->Genimon6->setVisible(true);
    ui->Genimon7->setVisible(true);
    ui->Genimon8->setVisible(true);

    ui->Nom1->setVisible(true);
    ui->Nom2->setVisible(true);
    ui->Nom3->setVisible(true);
    ui->Nom4->setVisible(true);
    ui->Nom5->setVisible(true);
    ui->Nom6->setVisible(true);
    ui->Nom7->setVisible(true);
    ui->Nom8->setVisible(true);

    int nbGenimon = genidex_trans->size();
    if (nbGenimon == 1)
    {
        ui->Genimon1->setPixmap((*genidex_trans)[0].imageGenimon.scaled(ui->Genimon1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->Nom1->setText("Nom: " + QString().append((*genidex_trans)[0].getNom()));
    }
    else if (nbGenimon == 2)
    {
        ui->Genimon1->setPixmap((*genidex_trans)[0].imageGenimon.scaled(ui->Genimon1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->Genimon2->setPixmap((*genidex_trans)[1].imageGenimon.scaled(ui->Genimon2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

        ui->Nom1->setText("Nom: " + QString().append((*genidex_trans)[0].getNom()));
        ui->Nom2->setText("Nom: " + QString().append((*genidex_trans)[1].getNom()));
    }
    else if (nbGenimon == 3)
    {
        ui->Genimon1->setPixmap((*genidex_trans)[0].imageGenimon.scaled(ui->Genimon1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->Genimon2->setPixmap((*genidex_trans)[1].imageGenimon.scaled(ui->Genimon2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->Genimon3->setPixmap((*genidex_trans)[2].imageGenimon.scaled(ui->Genimon3->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

        ui->Nom1->setText("Nom: " + QString().append((*genidex_trans)[0].getNom()));
        ui->Nom2->setText("Nom: " + QString().append((*genidex_trans)[1].getNom()));
        ui->Nom3->setText("Nom: " + QString().append((*genidex_trans)[2].getNom()));
    }
    else if (nbGenimon == 4)
    {
        ui->Genimon1->setPixmap((*genidex_trans)[0].imageGenimon.scaled(ui->Genimon1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->Genimon2->setPixmap((*genidex_trans)[1].imageGenimon.scaled(ui->Genimon2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->Genimon3->setPixmap((*genidex_trans)[2].imageGenimon.scaled(ui->Genimon3->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->Genimon4->setPixmap((*genidex_trans)[3].imageGenimon.scaled(ui->Genimon4->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

        ui->Nom1->setText("Nom: " + QString().append((*genidex_trans)[0].getNom()));
        ui->Nom2->setText("Nom: " + QString().append((*genidex_trans)[1].getNom()));
        ui->Nom3->setText("Nom: " + QString().append((*genidex_trans)[2].getNom()));
        ui->Nom4->setText("Nom: " + QString().append((*genidex_trans)[3].getNom()));
    }
    else if (nbGenimon == 5)
    {
        ui->Genimon1->setPixmap((*genidex_trans)[0].imageGenimon.scaled(ui->Genimon1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->Genimon2->setPixmap((*genidex_trans)[1].imageGenimon.scaled(ui->Genimon2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->Genimon3->setPixmap((*genidex_trans)[2].imageGenimon.scaled(ui->Genimon3->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->Genimon4->setPixmap((*genidex_trans)[3].imageGenimon.scaled(ui->Genimon4->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->Genimon5->setPixmap((*genidex_trans)[4].imageGenimon.scaled(ui->Genimon5->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

        ui->Nom1->setText("Nom: " + QString().append((*genidex_trans)[0].getNom()));
        ui->Nom2->setText("Nom: " + QString().append((*genidex_trans)[1].getNom()));
        ui->Nom3->setText("Nom: " + QString().append((*genidex_trans)[2].getNom()));
        ui->Nom4->setText("Nom: " + QString().append((*genidex_trans)[3].getNom()));
        ui->Nom5->setText("Nom: " + QString().append((*genidex_trans)[4].getNom()));
    }
    else if (nbGenimon == 6)
    {
        ui->Genimon1->setPixmap((*genidex_trans)[0].imageGenimon.scaled(ui->Genimon1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->Genimon2->setPixmap((*genidex_trans)[1].imageGenimon.scaled(ui->Genimon2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->Genimon3->setPixmap((*genidex_trans)[2].imageGenimon.scaled(ui->Genimon3->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->Genimon4->setPixmap((*genidex_trans)[3].imageGenimon.scaled(ui->Genimon4->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->Genimon5->setPixmap((*genidex_trans)[4].imageGenimon.scaled(ui->Genimon5->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->Genimon6->setPixmap((*genidex_trans)[5].imageGenimon.scaled(ui->Genimon6->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

        ui->Nom1->setText("Nom: " + QString().append((*genidex_trans)[0].getNom()));
        ui->Nom2->setText("Nom: " + QString().append((*genidex_trans)[1].getNom()));
        ui->Nom3->setText("Nom: " + QString().append((*genidex_trans)[2].getNom()));
        ui->Nom4->setText("Nom: " + QString().append((*genidex_trans)[3].getNom()));
        ui->Nom5->setText("Nom: " + QString().append((*genidex_trans)[4].getNom()));
        ui->Nom6->setText("Nom: " + QString().append((*genidex_trans)[5].getNom()));
    }
    else if (nbGenimon == 7)
    {
        ui->Genimon1->setPixmap((*genidex_trans)[0].imageGenimon.scaled(ui->Genimon1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->Genimon2->setPixmap((*genidex_trans)[1].imageGenimon.scaled(ui->Genimon2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->Genimon3->setPixmap((*genidex_trans)[2].imageGenimon.scaled(ui->Genimon3->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->Genimon4->setPixmap((*genidex_trans)[3].imageGenimon.scaled(ui->Genimon4->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->Genimon5->setPixmap((*genidex_trans)[4].imageGenimon.scaled(ui->Genimon5->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->Genimon6->setPixmap((*genidex_trans)[5].imageGenimon.scaled(ui->Genimon6->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->Genimon7->setPixmap((*genidex_trans)[6].imageGenimon.scaled(ui->Genimon7->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

        ui->Nom1->setText("Nom: " + QString().append((*genidex_trans)[0].getNom()));
        ui->Nom2->setText("Nom: " + QString().append((*genidex_trans)[1].getNom()));
        ui->Nom3->setText("Nom: " + QString().append((*genidex_trans)[2].getNom()));
        ui->Nom4->setText("Nom: " + QString().append((*genidex_trans)[3].getNom()));
        ui->Nom5->setText("Nom: " + QString().append((*genidex_trans)[4].getNom()));
        ui->Nom6->setText("Nom: " + QString().append((*genidex_trans)[5].getNom()));
        ui->Nom7->setText("Nom: " + QString().append((*genidex_trans)[6].getNom()));
    }
    else if (nbGenimon == 8)
    {
        ui->Genimon1->setPixmap((*genidex_trans)[0].imageGenimon.scaled(ui->Genimon1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->Genimon2->setPixmap((*genidex_trans)[1].imageGenimon.scaled(ui->Genimon2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->Genimon3->setPixmap((*genidex_trans)[2].imageGenimon.scaled(ui->Genimon3->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->Genimon4->setPixmap((*genidex_trans)[3].imageGenimon.scaled(ui->Genimon4->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->Genimon5->setPixmap((*genidex_trans)[4].imageGenimon.scaled(ui->Genimon5->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->Genimon6->setPixmap((*genidex_trans)[5].imageGenimon.scaled(ui->Genimon6->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->Genimon7->setPixmap((*genidex_trans)[6].imageGenimon.scaled(ui->Genimon7->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->Genimon8->setPixmap((*genidex_trans)[7].imageGenimon.scaled(ui->Genimon8->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

        ui->Nom1->setText("Nom: " + QString().append((*genidex_trans)[0].getNom()));
        ui->Nom2->setText("Nom: " + QString().append((*genidex_trans)[1].getNom()));
        ui->Nom3->setText("Nom: " + QString().append((*genidex_trans)[2].getNom()));
        ui->Nom4->setText("Nom: " + QString().append((*genidex_trans)[3].getNom()));
        ui->Nom5->setText("Nom: " + QString().append((*genidex_trans)[4].getNom()));
        ui->Nom6->setText("Nom: " + QString().append((*genidex_trans)[5].getNom()));
        ui->Nom7->setText("Nom: " + QString().append((*genidex_trans)[6].getNom()));
        ui->Nom8->setText("Nom: " + QString().append((*genidex_trans)[7].getNom()));
    }
}

void Genidex::highlight()
{
    // Réinitialiser l'état de tous les Genimons (enlever le highlight)
    for (int i = 1; i <= 8; ++i) {
        QLabel* genimonLabel = this->findChild<QLabel*>(QString("Genimon%1").arg(i));
        if (genimonLabel) {
            genimonLabel->setStyleSheet("");  // Réinitialiser le style
        }
    }

    // Appliquer un style de highlight (bordure rouge) au Genimon sélectionné
    QLabel* selectedGenimonLabel = this->findChild<QLabel*>(QString("Genimon%1").arg(selectionGenimon + 1));  // +1 car Genimon1 est le premier
    if (selectedGenimonLabel) {
        selectedGenimonLabel->setStyleSheet("background-color: lightblue;");
    }
}
