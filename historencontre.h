#ifndef HISTORENCONTRE_H
#define HISTORENCONTRE_H

#include <QWidget>
#include <vector>
#include "genimon.h"

namespace Ui {
class HistoRencontre;
}

class HistoRencontre : public QWidget
{
    Q_OBJECT

public:
    explicit HistoRencontre(QWidget *parent = nullptr);
    ~HistoRencontre();

public slots:
    void handleKeyPress(int key);
    void handleArduinoInput(int boutons, int joystick, int accelerometre, int muons);
    void ecrireHistorique(vector<Genimon> historique);

private:
    Ui::HistoRencontre *ui;

    int borne1;
    int borne2;

    void update();
    int BOUTONS = 0;
    int JOYSTICKS = 0;
    int ACCEL = 0;
    int MUONS = 0;

signals:
    void requestMenuChange(int index);  // Signal pour demander un changement de menu
};

#endif // HISTORENCONTRE_H
