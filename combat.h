#ifndef COMBAT_H
#define COMBAT_H

#include <QWidget>
#include <QTimer>
#include <QProgressBar>
#include "genimon.h"

namespace Ui {
    class Combat;
}

class Combat : public QWidget
{
    Q_OBJECT

public:
    void recevoirInfos(Genimon, int*, int*, std::vector<Genimon>*);
    void updateHealthBarColor(QProgressBar*, int, int);
    void btnAttaquer();
    void btnBouclier();
    void gererCombatTourAdversaire();
    void btnBonus();
    void executerActionsJoueur();
    void initialiserCombat();
    explicit Combat(QWidget* parent = nullptr);
    ~Combat();

public slots:
    void handleKeyPress(int key);
    void handleArduinoInput(int boutons, int joystick, int accelerometre, int muons);

private:
    void executerActionSuivante();
    int* balles = nullptr;
    int nbAtt = 9;
    int nbBou = 9;
    int nbBon = 9;
    int indexActionJoueur = 0;
    Genimon* genimonJoueur;
    Genimon* genimonEnnemi;
    std::vector<Genimon>* genidexDuJoueur;
    std::vector<int> actionsJoueur;
    bool attenteActions = false;

    int nbToursJoueur = 2;
    int nbAttaquesJoueur = 0;
    int nbBoucliersJoueur = 0;
    int nbBonusJoueur = 0;

    int nbToursAdversaire = 2;
    int nbAttaquesAdversaire = 0;
    int nbBoucliersAdversaire = 0;
    int nbBonusAdversaire = 0;

	bool bouclierJoueurActif = false;
	bool bouclierEnnemiActif = false;
    bool tourAdversaireEnCours = false;
	bool combatTermine = false;
    int bonusGagnesCeTour = 0;

    bool defenseActive;
    bool combatCommence;
    Genimon* genimon;
    Ui::Combat* ui;
    QTimer* TransTimer;
    void transition();
    void combat();
    void info();
    void showEvent(QShowEvent* event);
    void setGenimonAdverse(Genimon* genimon);

    void update();
    int BOUTONS = 0;
    int JOYSTICKS = 0;
    int ACCEL = 0;
    int MUONS = 0;

signals:
    void requestMenuChange(int index);  // Signal pour demander un changement de menu
    void signalBonus();
};

#endif // COMBAT_H