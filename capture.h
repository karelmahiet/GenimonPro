#ifndef CAPTURE_H
#define CAPTURE_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QTimer>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "genimon.h"

namespace Ui {
    class Capture;
}

class Capture : public QWidget
{
    Q_OBJECT

public:
    explicit Capture(QWidget* parent = nullptr);
    ~Capture();

public slots:
    void handleKeyPress(int key);
    void handleArduinoInput(int boutons, int joystick, int accelerometre, int muons);
    void afficherInfoCapture(Genimon genimonEnCours, int* nbBalles, int* nbCapsuleGuerison, vector<Genimon>* genidex);

private:
    Ui::Capture* ui;
    vector<Genimon> genimonEnCours_trans;
    int* nbBalles_trans;
    vector<Genimon>* genidex_trans;
    bool captureBloquee;
	QMediaPlayer* CatchPlayer;
	QAudioOutput* CatchOutput;
	QMediaPlayer* WobblePlayer;
	QAudioOutput* WobbleOutput;
	QMediaPlayer* EscapePlayer;
	QAudioOutput* EscapeOutput;
	QMediaPlayer* ThrowPlayer;
	QAudioOutput* ThrowOutput;
    QMediaPlayer* battleMusic;
    QAudioOutput* battleOutput;

    void animerPokeball(int nbRebond);
    int compterRebond();

    void update();
    int BOUTONS = 0;
    int JOYSTICKS = 0;
    int ACCEL = 0;
    int MUONS = 0;

signals:
    void requestMenuChange(int index);  // Signal pour demander un changement de menu
};

#endif // CAPTURE_H
