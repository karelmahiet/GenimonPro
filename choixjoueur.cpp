#include "choixjoueur.h"
#include "ui_choixjoueur.h"
#include "controle.h"
#include <QKeyEvent>
#include <QDebug>

extern Controle* controle;

ChoixJoueur::ChoixJoueur(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::ChoixJoueur)
{
    ui->setupUi(this);

    ui->Continuer->setStyleSheet("background-color: white; color: black; font-size: 14px;");
    ui->Retour->setStyleSheet("background-color: white; color: black; font-size: 14px;");

    audioOutput = new QAudioOutput(this);
    mediaPlayer = new QMediaPlayer(this);
    mediaPlayer->setSource(QUrl("qrc:/Music/Image_Qt/Music/Blitzkrieg 2022.wav"));
    mediaPlayer->setAudioOutput(audioOutput);
    mediaPlayer->setLoops(QMediaPlayer::Infinite);
    initialiserChoixJoueur();
}

ChoixJoueur::~ChoixJoueur()
{
    delete ui;
}

void ChoixJoueur::initialiserChoixJoueur()
{
    etat = 0;
    typeChoisi = 0;
    nomStarter = "";
    nomJoueur = "";
}

void ChoixJoueur::handleKeyPress(int key) {

    if (etat != 0 && etat != 1) {
        if (key == Qt::Key_1) {
            BOUTONS = 1;
            qDebug() << "Clavier1 (Oui) détecté";
        }
        else if (key == Qt::Key_2) {
            BOUTONS = 2;
            qDebug() << "Clavier2 (Non) détecté";
        }
    }
    else {
        BOUTONS = 0;
    }

    if (etat == 0 && key == Qt::Key_Tab) {
        nomJoueur = ui->NomChoisi->text();
        if (nomJoueur == "")
        {
            nomJoueur = "Joueur";
        }
        ui->NomChoisi->clearFocus();
        ui->NomChoisi->clear();
        qDebug() << "Nom validé par Tab :" << nomJoueur;

        etat = 1;
    }
    else if (etat == 1 && key == Qt::Key_Tab)
    {
        nomStarter = ui->NomChoisi->text();
        if (nomStarter == "")
        {
            nomStarter = "Bombardier";
        }
        ui->NomChoisi->clearFocus();
        ui->NomChoisi->clear();
        qDebug() << "Nom validé par Tab :" << nomStarter;

        etat = 2;
    }
    updateQuiz();
}

void ChoixJoueur::handleArduinoInput(int boutons, int joystick, int accelerometre, int muons) {

    if (etat != 0 && etat != 1) {
        if (boutons == 1) {
            BOUTONS = 1;
            qDebug() << "Clavier1 (Oui) détecté";
        }
        else if (boutons == 2) {
            BOUTONS = 2;
            qDebug() << "Clavier2 (Non) détecté";
        }
    }
    else {
        BOUTONS = 0;
    }

    if (etat == 0 && boutons == 1) {
        nomJoueur = ui->NomChoisi->text();
        if (nomJoueur == "")
        {
            nomJoueur = "Joueur";
        }
        ui->NomChoisi->clearFocus();
        ui->NomChoisi->clear();
        qDebug() << "Nom validé par Tab :" << nomJoueur;

        etat = 1;
    }
    else if (etat == 1 && boutons == 1)
    {
        nomStarter = ui->NomChoisi->text();
        if (nomStarter == "")
        {
            nomStarter = "Genie";
        }
        ui->NomChoisi->clearFocus();
        ui->NomChoisi->clear();
        qDebug() << "Nom validé par Tab :" << nomStarter;

        etat = 2;
    }
    updateQuiz();
}


void ChoixJoueur::updateQuiz() {

    switch (etat) {
    case 0:
        ui->Titre->setText("Votre nom ?");
        ui->NomChoisi->setFocus();
        ui->Nom->setVisible(true);
        ui->NomChoisi->setVisible(true);
        ui->Description->setVisible(false);
        ui->Retour->setVisible(false);
        ui->Continuer->setText("Continuer (Tab)");
        break;
    case 1:
        ui->Titre->setText("Nom de votre premier Genimon?");
        ui->NomChoisi->setFocus();
        ui->Retour->setVisible(false);
        break;
    case 2:
        ui->Titre->setText("Quiz de personnalité");
        ui->Description->setText("Pour déterminer le type de votre premier Genimon, répondez à ce quiz pour qu'il puisse "
            "vous représenter. Voulez-vous répondre au quiz? Sinon un type aléatoire sera choisi.");
        ui->Nom->setVisible(false);
        ui->NomChoisi->setVisible(false);
        ui->Description->setVisible(true);
        ui->Retour->setVisible(true);
        ui->Continuer->setText("Oui (1)");
        ui->Retour->setText("Non (2)");

        if (BOUTONS == 1) {
            BOUTONS = 0;
            etat = 4;
            updateQuiz();
        }
        else if (BOUTONS == 2) {
            BOUTONS = 0;
            etat = 3;
            ui->Description->setText("Quiz non répondu. Un type aléatoire a été choisi.");
            typeChoisi = rand() % 8;
            updateQuiz();
        }
        break;

    case 3:
        ui->Continuer->setText("Débuter de la partie (1)");
        ui->Retour->setVisible(false);

        if (BOUTONS == 1)
        {
            BOUTONS = 0;
            emit sendNomsChoisis(nomJoueur, nomStarter, typeChoisi);
            emit requestMenuChange(2); //Passer au menu map
        }
        break;

    case 4:
        ui->Description->setText("Est-ce que 80% est une mauvaise note ?");
        if (BOUTONS == 1) {
            BOUTONS = 0;
            etat = 5;
            updateQuiz();
        }
        else if (BOUTONS == 2) {
            BOUTONS = 0;
            etat = 7;
            updateQuiz();
        }
        break;

    case 5:
        ui->Description->setText("Est-ce que la physique c'est cool ?");
        if (BOUTONS == 1) {
            BOUTONS = 0;
            ui->Description->setText("Félicitations tu es un génie robotique! Tu as terminé le quiz.");
            typeChoisi = 2;
            etat = 3;
            updateQuiz();
        }
        else if (BOUTONS == 2) {
            BOUTONS = 0;
            etat = 6;
            updateQuiz();
        }
        break;

    case 6:
        ui->Description->setText("Est-ce que des trucs morts c'est cool ?");
        if (BOUTONS == 1) {
            BOUTONS = 0;
            ui->Description->setText("Félicitations tu es un génie biotech! Tu as terminé le quiz.");
            typeChoisi = 6;
            etat = 3;
            updateQuiz();
        }
        else if (BOUTONS == 2) {
            BOUTONS = 0;
            ui->Description->setText("Félicitations tu es un génie chimique! Tu as terminé le quiz.");
            typeChoisi = 7;
            etat = 3;
            updateQuiz();
        }
        break;

    case 7:
        ui->Description->setText("Est-ce que tu penses que les ordinateurs fonctionnent avec de l'essence ?");
        if (BOUTONS == 1) {
            BOUTONS = 0;
            ui->Description->setText("Hmmm, intéressant... Tu es un génie mécanique. Félicitations ! Tu as terminé le quiz.");
            typeChoisi = 3;
            etat = 3;
            updateQuiz();
        }
        else if (BOUTONS == 2) {
            BOUTONS = 0;
            etat = 8;
            updateQuiz();
        }
        break;

    case 8:
        ui->Description->setText("Est-ce que tu sais ce que c'est un Amplis-Op ?");
        if (BOUTONS == 1) {
            BOUTONS = 0;
            etat = 9;
            updateQuiz();
        }
        else if (BOUTONS == 2) {
            BOUTONS = 0;
            etat = 10;
            updateQuiz();
        }
        break;

    case 9:
        ui->Description->setText("Est-ce qu'il te font peur ?");
        if (BOUTONS == 1) {
            BOUTONS = 0;
            ui->Description->setText("Félicitations tu es un génie informatique! Tu as terminé le quiz.");
            typeChoisi = 0;
            etat = 3;
            updateQuiz();
        }
        else if (BOUTONS == 2) {
            BOUTONS = 0;
            ui->Description->setText("Félicitations tu es un génie électrique! Tu as terminé le quiz.");
            typeChoisi = 1;
            etat = 3;
            updateQuiz();
        }
        break;

    case 10:
        ui->Description->setText("Est-ce que tu es basique ?");
        if (BOUTONS == 1) {
            BOUTONS = 0;
            ui->Description->setText("Félicitations tu es un génie civil! Tu as terminé le quiz.");
            typeChoisi = 4;
            etat = 3;
            updateQuiz();
        }
        else if (BOUTONS == 2) {
            BOUTONS = 0;
            ui->Description->setText("Félicitations tu es un génie du bâtiment! Tu as terminé le quiz.");
            typeChoisi = 5;
            etat = 3;
            updateQuiz();
        }
        break;

    default:
        break;
    }
}
