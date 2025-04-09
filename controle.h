#ifndef CONTROLE_H
#define CONTROLE_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QKeyEvent>
#include <QSerialPort>
#include <QTimer>

#include "capture.h"
#include "choixjoueur.h"
#include "combat.h"
#include "commande.h"
#include "genidex.h"
#include "historencontre.h"
#include "map.h"
#include "regle.h"
#include "pause.h"
#include "choixaction.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Controle;
}
QT_END_NAMESPACE

class Controle : public QMainWindow
{
    Q_OBJECT

public:
    Controle(QWidget *parent = nullptr);
    ~Controle();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::Controle *ui;
    QStackedWidget *stackedWidget;
    QSerialPort* serialPort;
    QTimer* sendDataTimer;

    ChoixJoueur* choixJoueurMenu;
    Map* mapMenu;
    Capture* captureMenu;
    Combat* combatMenu;
    Genidex* genidexMenu;
    HistoRencontre* histoRencontreMenu;
    Commande* commandeMenu;
    Regle* regleMenu;
    Pause* pauseMenu;
    ChoixAction* choixActionMenu;

    void changeMenu(int index);
    void setSegment(int seg);
    void setMessage(QString mes);

    void connectToArduino();
    void startReading();
    void stopReading();
    void RcvFromSerial();
    void SendToSerial(const QString& message, int segment);

    int JOYSTICK = 0;
    int BOUTTONS = 0;
    int ACCELEROMETRE = 0;
    int MUONS = 0;
    QString MESSAGE = "Je communique";
    int SEGMENT = 0;
    bool lastSend = 0;

signals:
    void sendKeyPress(int key); // Signal pour envoyer les touches clavier
    void sendManetteInput(int bouton, int joystick, int accel, int muons); // Signal pour envoyer les touches manettes
};
#endif // CONTROLE_H
