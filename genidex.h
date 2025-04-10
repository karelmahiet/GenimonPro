#ifndef GENIDEX_H
#define GENIDEX_H

#include <QWidget>
#include <genimon.h>

namespace Ui {
class Genidex;
}

class Genidex : public QWidget
{
    Q_OBJECT

public:
    explicit Genidex(QWidget *parent = nullptr);
    ~Genidex();

public slots:
    void handleKeyPress(int key);
    void handleArduinoInput(int boutons, int joystick, int accelerometre, int muons);
    void setGenidex(int* nbBalles, int* nbCapsuleGuerison, vector<Genimon>* genidex);
    void debuterPreparationCombat(Genimon genimonEnnemi);

private:
    Ui::Genidex *ui;
    void showGenimon();
    void showListGenimon();
    void highlight();

    bool estListe = true;
    int selectionGenimon = 0; //0 a 7
    bool preparationCombat = false;
    int* nbCapsuleGuerison_trans;
    vector<Genimon>* genidex_trans;

    Genimon* genimonJoueur;
    int* NbBalles;
    vector<Genimon> genimonEnnemi;

    void update();
    int BOUTONS = 0;
    int JOYSTICKS = 0;
    int ACCEL = 0;
    int MUONS = 0;

signals:
    void requestMenuChange(int index);  // Signal pour demander un changement de menu
    void sendInfos(Genimon genimonEnnemi, int* nbBalles, Genimon* genimonJoueur);
};

#endif // GENIDEX_H
