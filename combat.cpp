#include "combat.h"
#include "ui_combat.h"
#include <QPixmap>
#include <functional>

Combat::Combat(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::Combat), TransTimer(new QTimer(this))
{
    TransTimer->setSingleShot(true);
    ui->setupUi(this);
    connect(TransTimer, &QTimer::timeout, this, &Combat::combat);
    connect(this, &Combat::signalBonus, this, &Combat::btnBonus);

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

    //qDebug() << "La fen�tre de combat est maintenant affich�e!";
    transition();
    // D�marrer le timer pour ex�cuter la fonction combat apr�s 3 secondes
    TransTimer->start(3000);  // 3000 millisecondes = 3 secondes

    QWidget::showEvent(event);  // N'oublie pas d'appeler la m�thode de base pour conserver le comportement normal
}

void Combat::transition() {

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
}



void Combat::combat() {

    nbBon = 9;
    nbAtt = 9;
    nbBou = 9;

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
    ui->Manche->setVisible(true);
    ui->Attaque->setVisible(true);
    ui->Bloquer->setVisible(true);
    ui->Bonus->setVisible(true);
    initialiserCombat();
}

void Combat::info() {

    ui->Nom1->setText(QString("Nom: %1").arg("Dylan"));// a remplacer par nom classe genimon
    ui->Nom2->setText(QString("Nom: %1").arg("Moi"));// a remplacer par nom classe genimon
}

void Combat::recevoirInfos(Genimon ennemi, int* nbBalles, int* nbCapsuleGuerison, std::vector<Genimon>* genidex) {
    genidexDuJoueur = genidex;
    balles = nbBalles;
    genimonEnnemi = new Genimon(ennemi);

    if (genidex && !genidex->empty()) {
        genimonJoueur = new Genimon(genidex->at(0));
    }
    else {
        genimonJoueur = nullptr;
        ui->TableauInfo->setText("Vous n'avez aucun Genimon pour combattre!");
        return;
    }
    //joueur
    ui->Genimon1->setPixmap(genimonJoueur->imageGenimon.scaled(ui->Genimon1->size(), Qt::KeepAspectRatio));
    ui->Nom1->setText(QString::fromStdString(genimonJoueur->getNom()));
    int pvActuels = genimonJoueur->getPV();
    int pvMax = genimonJoueur->pvMax;
    ui->HP1->setText("PV : " + QString::number(pvActuels) + " / " + QString::number(pvMax));

    //ennemi
    ui->Genimon2->setPixmap(genimonEnnemi->imageGenimon.scaled(ui->Genimon2->size(), Qt::KeepAspectRatio));
    ui->Nom2->setText(QString::fromStdString(genimonEnnemi->getNom()));
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
        ui->TableauInfo->setText("Action " + QString::number(actionsJoueur.size()) + "/" + QString::number(nbToursJoueur) + ": Attaque");
        ui->Nb_attaque->setText("NbAttaque: " + QString::number(nbAtt -= 1));
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

    if (actionsJoueur.size() < nbToursJoueur)
    {
        actionsJoueur.push_back(2);
        bouclierJoueurActif = true;

        ui->TableauInfo->setText("Action " + QString::number(actionsJoueur.size()) + "/" + QString::number(nbToursJoueur) + ": Bouclier");
        ui->Nb_bouclier->setText("NbBouclier: " + QString::number(nbBou -= 1));
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

    ui->TableauInfo->setText("Tour de " + QString::fromStdString(genimonEnnemi->getNom()));

    QTimer::singleShot(3000, this, [=]() {
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

        QString resume = QString("Actions: %1 attaque(s), %2 bouclier(s), %3 bonus")
            .arg(nbAttaquesAdversaire)
            .arg(nbBoucliersAdversaire)
            .arg(nbBonusAdversaire);
        ui->TableauInfo->setText(resume);

        QTimer::singleShot(3000, this, [=]() {
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
                " attaque et inflige " + QString::number(totalDegats) + " degats !");

            //check si joueur est mort
            if (genimonJoueur->getPV() <= 0) {
                combatTermine = true;
                QTimer::singleShot(4000, this, [=]() {
                    ui->TableauInfo->setText(QString::fromStdString(genimonJoueur->getNom()) + " est K.O. ! (4 = map)");
                    QTimer::singleShot(3000, this, [=]() {
                        nbBon = 9;
                        nbAtt = 9;
                        nbBou = 9;
                        emit requestMenuChange(2);});
                    });
                return;
            }

            // R�initialisation de fin de tour
            nbAttaquesAdversaire = 0;
            nbBoucliersAdversaire = 0;
            nbToursAdversaire = 2;
            bouclierJoueurActif = false;
            tourAdversaireEnCours = false;

            QTimer::singleShot(3000, this, [=]() {
                ui->TableauInfo->setText("A ton tour ! Tu as " + QString::number(nbToursJoueur) + " actions.");
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
        ui->TableauInfo->setText("Tu as d�j� 4 bonus maximum !");
        return;
    }

    if (actionsJoueur.size() < nbToursJoueur)
    {
        actionsJoueur.push_back(3);
        ui->TableauInfo->setText("Action " + QString::number(actionsJoueur.size()) + "/" + QString::number(nbToursJoueur) + ": Bonus");
        ui->Nb_bonus->setText("NbBonus: " + QString::number(nbBon -= 1));
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
        QTimer::singleShot(3000, this, [=]() {
            ui->TableauInfo->setText(QString::fromStdString(genimonEnnemi->getNom()) + " est K.O. ! (4 = map)");
            });
        QTimer::singleShot(3000, this, [=]() {
            nbBon = 9;
            nbAtt = 9;
            nbBou = 9;
            emit requestMenuChange(2);});
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
        ui->TableauInfo->setText("Fin du tour ! Tu auras " + QString::number(nbToursJoueur) + " actions au prochain tour.");

        nbBoucliersJoueur = 0;
        nbAttaquesJoueur = 0;
        attenteActions = false;

        QTimer::singleShot(3000, this, [=]() {
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
        }

        if (genimonEnnemi->getPV() <= 0) {
            genimonEnnemi->setPV(0);
            ui->HP2->setText("PV : 0 / " + QString::number(genimonEnnemi->pvMax));
            ui->TableauInfo->setText("Bravo ! " + QString::fromStdString(genimonEnnemi->getNom()) + " est K.O. !");
            actionsJoueur.clear();
            attenteActions = false;

            QTimer::singleShot(3000, this, [=]() {
                int ballesGagnees = 3 + (rand() % 5);//entre 3 et 7
                *balles += ballesGagnees;
                ui->TableauInfo->setText("Tu gagnes " + QString::number(ballesGagnees) + " balles !");
                });
            QTimer::singleShot(3000, this, [=]() {
                nbBon = 9;
                nbAtt = 9;
                nbBou = 9;
                emit requestMenuChange(2);});
            return;
        }

        ui->TableauInfo->setText(nomJoueur + " attaque et inflige " + QString::number(degats) + " degats !");
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

    QTimer::singleShot(3000, this, [=]() {
        executerActionSuivante();
        });
}

void Combat::initialiserCombat()
{
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
    nbBon = 9;
	nbAtt = 9;
	nbBou = 9;
    ui->Nb_bonus->setText("NbBonus: " + QString::number(nbBon));
    ui->Nb_attaque->setText("NbAttaques: " + QString::number(nbAtt));
    ui->Nb_bouclier->setText("NbBoucliers: " + QString::number(nbBou));
    defenseActive = false;
    ui->TableauInfo->clear();
    ui->TableauInfo->setText("Bon combat!");

    //2 sec pile ou face
    QTimer::singleShot(3000, this, [=]() {
        bool joueurCommence = (rand() % 2 == 0);//true = joueur gagne
        ui->TableauInfo->setText("Tirage a pile ou face...");

        QTimer::singleShot(3000, this, [=]() {
            if (joueurCommence) {
                ui->TableauInfo->setText("Resultat : Tu commences !");
                QTimer::singleShot(3000, this, [=]() {
                    ui->TableauInfo->setText("A ton tour ! Tu as " + QString::number(nbToursJoueur) + " actions.");
                    combatCommence = true;
                    });
            }
            else {
                ui->TableauInfo->setText("Resultat : ennemi commence !");
                QTimer::singleShot(3000, this, [=]() {
                    combatCommence = true;
                    gererCombatTourAdversaire();
                    });
            }
            });
        });
}