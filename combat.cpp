#include "combat.h"
#include "ui_combat.h"
#include <QPixmap>
#include <functional>
#include "capture.h"
#include <string>

Combat::Combat(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::Combat), TransTimer(new QTimer(this))
{
    TransTimer->setSingleShot(true);
    ui->setupUi(this);
    connect(TransTimer, &QTimer::timeout, this, &Combat::combat);
    connect(this, &Combat::signalBonus, this, &Combat::btnBonus);
	battleMusic = new QMediaPlayer(this);
	battleOutput = new QAudioOutput(this);
	battleMusic->setAudioOutput(battleOutput);
	battleMusic->setSource(QUrl::fromLocalFile("battle.wav"));
	battleMusic->setLoops(QMediaPlayer::Infinite);

    ui->Nb_bonus->setText("NbBonus: 0");
    ui->Nb_attaque->setText("NbAttaques: 0");
    ui->Nb_bouclier->setText("NbBoucliers: 0");
}

Combat::~Combat()
{
    delete TransTimer;
    delete ui;
    //pt
    delete genimonJoueur;
    delete genimonEnnemi;
    delete TransTimer;
    delete ui;
}

void Combat::handleKeyPress(int key) {

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

void Combat::handleArduinoInput(int boutons, int joystick, int accelerometre, int muons) {

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

void Combat::update() {
    if (BOUTONS == 4) {
        BOUTONS = 0;
        JOYSTICKS = 0;
        ACCEL = 0;
        MUONS = 0;
		battleMusic->stop();
        emit requestMenuChange(2); //Passer au menu map
    }
    if (BOUTONS == 1) {
        emit btnAttaquer();
    }
    if (BOUTONS == 2) {
        emit btnBouclier();
    }
    if (BOUTONS == 3) {
        emit signalBonus();
    }

    BOUTONS = 0;
    JOYSTICKS = 0;
    ACCEL = 0;
    MUONS = 0;
}

void Combat::showEvent(QShowEvent* event) {

    //qDebug() << "La fenêtre de combat est maintenant affichée!";
    transition();
    // Démarrer le timer pour exécuter la fonction combat après 3 secondes
    TransTimer->start(3000);

    QWidget::showEvent(event);  // N'oublie pas d'appeler la méthode de base pour conserver le comportement normal
}

void Combat::transition() {
    battleMusic->play();
    ui->BackGround->setPixmap(QPixmap(":/Decor/Image_Qt/Decor/Transition combat.png"));
    ui->Genimon1->move(570, 130);
    ui->Genimon2->move(570, 460);
    ui->Nom1->setVisible(false);
    ui->Nom2->setVisible(false);
    ui->HP1->setVisible(false);
    ui->HP2->setVisible(false);
    ui->TableauInfo->setVisible(false);
    ui->Nb_attaque->setVisible(false);
    ui->Nb_bouclier->setVisible(false);
    ui->Nb_bonus->setVisible(false);
    ui->Manche->setVisible(false);
    ui->Attaque->setVisible(false);
    ui->Bloquer->setVisible(false);
    ui->Bonus->setVisible(false);
    ui->Alerte->setVisible(false);
    ui->Contoles->setVisible(false);
}



void Combat::combat() {
    ui->BackGround->setPixmap(QPixmap(":/Decor/Image_Qt/Decor/AreneCombat.png"));
    ui->Genimon1->move(280, 280);
    ui->Genimon2->move(900, 140);
    ui->Nom1->setVisible(true);
    ui->Nom2->setVisible(true);
    ui->HP1->setVisible(true);
    ui->HP2->setVisible(true);
    ui->TableauInfo->setVisible(true);
    ui->Nb_attaque->setVisible(true);
    ui->Nb_bouclier->setVisible(true);
    ui->Nb_bonus->setVisible(true);
    ui->Manche->setVisible(false);
    ui->Attaque->setVisible(true);
    ui->Bloquer->setVisible(true);
    ui->Bonus->setVisible(true);
	ui->Alerte->setVisible(false);
    ui->Contoles->setVisible(true);
    initialiserCombat();
}

void Combat::recevoirInfos(Genimon ennemi, int* nbBalles, Genimon* joueur) {
    balles = nbBalles;
    genimonEnnemi = new Genimon(ennemi);
    genimonJoueur = joueur;

    //joueur
    ui->Genimon1->setPixmap(genimonJoueur->imageGenimon.scaled(ui->Genimon1->size(), Qt::KeepAspectRatio));
    ui->Nom1->setText(QString().append("Nom: " + genimonJoueur->getNom() + "\nDegats: " + to_string(genimonJoueur->getDegats())));
    int pvActuels = genimonJoueur->getPV();
    int pvMax = genimonJoueur->pvMax;
    ui->HP1->setText("PV : " + QString::number(pvActuels) + " / " + QString::number(pvMax));

    //ennemi
    ui->Genimon2->setPixmap(genimonEnnemi->imageGenimon.scaled(ui->Genimon2->size(), Qt::KeepAspectRatio));
    ui->Nom2->setText(QString().append("Nom: " + genimonEnnemi->getNom() + "\nDegats: " + to_string(genimonEnnemi->getDegats())));
    int pvActuels2 = genimonEnnemi->getPV();
    int pvMax2 = genimonEnnemi->pvMax;
    ui->HP2->setText("PV : " + QString::number(pvActuels2) + " / " + QString::number(pvMax2));
}

void Combat::btnAttaquer()
{
    if (combatTermine || !combatCommence || attenteActions || tourAdversaireEnCours) return;

    if (!genimonJoueur || !genimonEnnemi || genimonJoueur->getPV() <= 0 || genimonEnnemi->getPV() <= 0)
        return;

    if (actionsJoueur.size() < nbToursJoueur)
    {
        actionsJoueur.push_back(1);
        ui->TableauInfo->setText("Action " + QString::number(actionsJoueur.size()) + "/" + QString::number(nbToursJoueur));
        ui->Nb_attaque->setText("NbAttaque: " + QString::number(++nbAtt));
    }

    if (actionsJoueur.size() == nbToursJoueur)
    {
        attenteActions = true;
        executerActionsJoueur();
    }
}

void Combat::btnBouclier()
{
    if (combatTermine || !combatCommence || attenteActions || tourAdversaireEnCours) return;

    if (!genimonJoueur || genimonEnnemi->getPV() <= 0 || genimonJoueur->getPV() <= 0)
        return;

    if (actionsJoueur.size() < nbToursJoueur && bouclierJoueurActif == false)
    {
        actionsJoueur.push_back(2);
        bouclierJoueurActif = true;

        ui->TableauInfo->setText("Action " + QString::number(actionsJoueur.size()) + "/" + QString::number(nbToursJoueur));
        ui->Nb_bouclier->setText("NbBouclier: " + QString::number(++nbBou));
        bouclierJoueurActif = true;
	}
	else if (bouclierJoueurActif == true)
	{
		ui->TableauInfo->setText("Tu as deja un bouclier ! \nChoisi une autre action");
		return;
	}

    if (actionsJoueur.size() == nbToursJoueur)
    {
        attenteActions = true;
        executerActionsJoueur();
    }
}

void Combat::gererCombatTourAdversaire()
{
    if (combatTermine) return;

    tourAdversaireEnCours = true;

    nbAtt = 0;
    nbBou = 0;
    nbBon = 0;
    ui->Nb_bonus->setText("NbBonus: " + QString::number(nbBon));
    ui->Nb_attaque->setText("NbAttaques: " + QString::number(nbAtt));
    ui->Nb_bouclier->setText("NbBoucliers: " + QString::number(nbBou));

    ui->TableauInfo->setText("Tour de " + QString::fromStdString(genimonEnnemi->getNom()));

    QTimer::singleShot(4000, this, [=]() {
        //bonus ennemi
        nbToursAdversaire += nbBonusAdversaire;
        nbBonusAdversaire = 0;

        nbAttaquesAdversaire = 0;
        nbBoucliersAdversaire = 0;

        int actionsRestantes = nbToursAdversaire;

        //actions ennemi
        while (actionsRestantes > 0) {
            int choix = rand() % 3;
            if (choix == 0) {
                nbAttaquesAdversaire++;
            }
            else if (choix == 1) {
                nbBoucliersAdversaire++;
            }
            else {
                if (nbBonusAdversaire < 4)
                    nbBonusAdversaire++;
            }
            actionsRestantes--;
        }

        //active bouclier ennemi
        if (nbBoucliersAdversaire > 0) {
            bouclierEnnemiActif = true;
        }

        QString resume = QString("Actions:\n%1 attaque(s),\n%2 bouclier(s),\n%3 bonus")
            .arg(nbAttaquesAdversaire)
            .arg(nbBoucliersAdversaire)
            .arg(nbBonusAdversaire);
        ui->TableauInfo->setText(resume);

        QTimer::singleShot(4000, this, [=]() {
            int totalDegats = 0;

            for (int i = 1; i <= nbAttaquesAdversaire; i++) {
                if (bouclierJoueurActif) {
                    ui->TableauInfo->setText(QString::fromStdString(genimonJoueur->getNom()) + " bloque une attaque ennemie !");
                    bouclierJoueurActif = false;
                }
                else {
                    totalDegats += genimonEnnemi->getDegats();
                }
            }

            genimonJoueur->varierPV(-totalDegats);
            if (genimonJoueur->getPV() <= 0)
                genimonJoueur->setPV(0);

            ui->HP1->setText("PV : " + QString::number(genimonJoueur->getPV()) + " / " + QString::number(genimonJoueur->pvMax));
            ui->TableauInfo->setText(QString::fromStdString(genimonEnnemi->getNom()) +
                " inflige " + QString::number(totalDegats) + " degats !");

            //check si joueur est mort
            if (genimonJoueur->getPV() <= 0) {
                combatTermine = true;
                QTimer::singleShot(4000, this, [=]() {
                    (*genimonJoueur).setPV(genimonJoueur->getPV());
                    ui->TableauInfo->setText(QString::fromStdString(genimonJoueur->getNom()) + " est K.O. , \ntu as perdu... \n4 = retour a la map");
                    });
                return;
            }

            // Réinitialisation de fin de tour
            nbAttaquesAdversaire = 0;
            nbBoucliersAdversaire = 0;
            nbToursAdversaire = 2;
            bouclierJoueurActif = false;
            tourAdversaireEnCours = false;

            QTimer::singleShot(4000, this, [=]() {
                ui->TableauInfo->setText("A ton tour ! \nTu as " + QString::number(nbToursJoueur) + " actions.");
                });
            });
        });
}

void Combat::btnBonus()
{
    if (combatTermine || !combatCommence || attenteActions || tourAdversaireEnCours) return;

    if (!genimonJoueur || !genimonEnnemi || genimonJoueur->getPV() <= 0)
    {
        ui->TableauInfo->setText(QString::fromStdString(genimonJoueur->getNom()) + " est K.O. Il ne peut pas agir.");
        return;
    }

    if (nbBonusJoueur >= 4)
    {
        ui->TableauInfo->setText("Tu as deja 4 bonus maximum ! \nChoisi une autre action");
        return;
    }

    if (actionsJoueur.size() < nbToursJoueur)
    {
        actionsJoueur.push_back(3);
        ui->TableauInfo->setText("Action " + QString::number(actionsJoueur.size()) + "/" + QString::number(nbToursJoueur));
        ui->Nb_bonus->setText("NbBonus: " + QString::number(++nbBon));
    }

    if (actionsJoueur.size() == nbToursJoueur)
    {
        attenteActions = true;
        executerActionsJoueur();
    }
}

void Combat::executerActionsJoueur()
{
    if (combatTermine) return;
    if (actionsJoueur.empty())
        return;

    indexActionJoueur = 0;
    //check si bot est mort
    if (genimonEnnemi->getPV() <= 0) {
        QTimer::singleShot(4000, this, [=]() {
            ui->TableauInfo->setText(QString::fromStdString(genimonEnnemi->getNom()) + " est K.O. , \ntu as gagne! \n4 = retour a la map");
            });
    }else
    executerActionSuivante();
}

void Combat::executerActionSuivante()
{
    if (combatTermine) return;
    if (indexActionJoueur >= actionsJoueur.size()) {
        //fin tour
        actionsJoueur.clear();

        nbToursJoueur = 2 + bonusGagnesCeTour;
        bonusGagnesCeTour = 0;
        ui->TableauInfo->setText("Fin du tour ! Tu auras " + QString::number(nbToursJoueur) +"\nactions au prochain tour.");

        nbBoucliersJoueur = 0;
        nbAttaquesJoueur = 0;
        attenteActions = false;

        QTimer::singleShot(4000, this, [=]() {
            gererCombatTourAdversaire();
            });
        return;
    }

    int action = actionsJoueur[indexActionJoueur];
    QString nomJoueur = QString::fromStdString(genimonJoueur->getNom());

    if (action == 1) {
        int degats = genimonJoueur->getDegats();
        if (bouclierEnnemiActif) {
            ui->TableauInfo->setText(QString::fromStdString(genimonEnnemi->getNom()) + " bloque ton attaque !");
            bouclierEnnemiActif = false;
        }
        else {
            genimonEnnemi->varierPV(-degats);
            ui->TableauInfo->setText(QString::fromStdString(genimonJoueur->getNom()) +
                " attaque et inflige " + QString::number(degats) + " degats !");
        }

        if (genimonEnnemi->getPV() <= 0) {
            genimonEnnemi->setPV(0);
            ui->HP2->setText("PV : 0 / " + QString::number(genimonEnnemi->pvMax));
            ui->TableauInfo->setText("Bravo ! " + QString::fromStdString(genimonEnnemi->getNom()) + " est K.O. ! \nTu as gagne !");
            actionsJoueur.clear();
            attenteActions = false;
            combatTermine = true;

            QTimer::singleShot(4000, this, [=]() {
                int ballesGagnees = genimonEnnemi->getGainBalles();
                *balles += ballesGagnees;
                (*genimonJoueur).setPV(genimonJoueur->getPV());
                ui->TableauInfo->setText("Tu gagnes " + QString::number(ballesGagnees) + " balles ! \n4 = retour a la map");
                });
            return;
        }

        ui->HP2->setText("PV : " + QString::number(genimonEnnemi->getPV()) + " / " + QString::number(genimonEnnemi->pvMax));
    }

    else if (action == 2) {
        nbBoucliersJoueur++;
        ui->TableauInfo->setText(nomJoueur + " utilise un bouclier !");
    }

    else if (action == 3) {
        bonusGagnesCeTour++;
        ui->TableauInfo->setText(nomJoueur + " accumule un bonus !");
    }

    indexActionJoueur++;

    QTimer::singleShot(4000, this, [=]() {
        executerActionSuivante();
        });
}

void Combat::initialiserCombat()
{
	if (genimonJoueur->getPV() == 0) {
		ui->TableauInfo->setText(QString::fromStdString(genimonJoueur->getNom()) + " semble fatigue... \nPrend la fuite!");
		return;
	}

    //reset
    combatCommence = false;
    nbToursJoueur = 2;
    nbAttaquesJoueur = 0;
    nbBoucliersJoueur = 0;
    nbBonusJoueur = 0;
    nbToursAdversaire = 2;
    nbAttaquesAdversaire = 0;
    nbBoucliersAdversaire = 0;
    nbBonusAdversaire = 0;
    nbAtt = 0;
    nbBou = 0;
    nbBon = 0;
    ui->Nb_bonus->setText("NbBonus: " + QString::number(nbBon));
    ui->Nb_attaque->setText("NbAttaques: " + QString::number(nbAtt));
    ui->Nb_bouclier->setText("NbBoucliers: " + QString::number(nbBou));
    defenseActive = false;
    ui->TableauInfo->clear();
    ui->TableauInfo->setText("Bon combat!");

    //2 sec pile ou face
    QTimer::singleShot(4000, this, [=]() {
        bool joueurCommence = (rand() % 2 == 0);//true = joueur gagne
        ui->TableauInfo->setText("Tirage a pile ou face...");

        QTimer::singleShot(4000, this, [=]() {
            if (joueurCommence) {
                ui->TableauInfo->setText("Resultat : " + QString::fromStdString(genimonJoueur->getNom()) + " commence !");
                QTimer::singleShot(4000, this, [=]() {
                    ui->TableauInfo->setText("A ton tour !\nTu as " + QString::number(nbToursJoueur) + " actions.");
                    combatCommence = true;
                    });
            }
            else {
                ui->TableauInfo->setText("Resultat : " + QString::fromStdString(genimonEnnemi->getNom()) + " commence !");
                QTimer::singleShot(4000, this, [=]() {
                    combatCommence = true;
                    gererCombatTourAdversaire();
                    });
            }
            });
        });
}