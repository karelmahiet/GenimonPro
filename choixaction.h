#ifndef CHOIXACTION_H
#define CHOIXACTION_H

#include <QWidget>
#include <vector>
#include "genimon.h"

namespace Ui {
class ChoixAction;
}

class ChoixAction : public QWidget
{
    Q_OBJECT

public:
    explicit ChoixAction(QWidget *parent = nullptr);
    ~ChoixAction();

public slots:
    void handleKeyPress(int key);
    void handleArduinoInput(int boutons, int joystick, int accelerometre, int muons);
    void afficherInfoGenimon(Genimon genimonEnCours, int* nbBalles, int* nbCapsuleGuerison, vector<Genimon>* genidex);

private:
    Ui::ChoixAction *ui;
    vector<Genimon> genimonEnCours_trans;
    int* nbBalles_trans;
    int* nbCapsuleGuerison_trans;
    vector<Genimon>* genidex_trans;

    void update();
    int BOUTONS = 0;
    int JOYSTICKS = 0;
    int ACCEL = 0;
    int MUONS = 0;

signals:
    void requestMenuChange(int index);  // Signal pour demander un changement de menu
    void sendInfos(Genimon genimonEnCours, int* nbBalles, int* nbCapsuleGuerison, vector<Genimon>* genidex);
};

#endif // CHOIXACTION_H
