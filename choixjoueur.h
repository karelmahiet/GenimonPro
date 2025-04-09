#ifndef CHOIXJOUEUR_H
#define CHOIXJOUEUR_H

#include <QWidget>
#include <QMediaPlayer>
#include <QAudioOutput>

namespace Ui {
    class ChoixJoueur;
}

class ChoixJoueur : public QWidget
{
    Q_OBJECT

public:
    explicit ChoixJoueur(QWidget* parent = nullptr);
    ~ChoixJoueur();

    void updateQuiz();

public slots:
    void handleKeyPress(int key);   // Slot pour gérer les touches 1 et 2
    void handleArduinoInput(int boutons, int joystick, int accelerometre, int muons);
    void initialiserChoixJoueur();

private:
    Ui::ChoixJoueur* ui;

    int etat;
    int typeChoisi;
    QString nomStarter;
    QString nomJoueur;
    QMediaPlayer* mediaPlayer;
    QAudioOutput* audioOutput;

    int BOUTONS = 0;
    int JOYSTICKS = 0;
    int ACCEL = 0;
    int MUONS = 0;

signals:
    void requestMenuChange(int index);  // Signal pour demander un changement de menu
    void sendNomsChoisis(const QString& nomJoueur, QString nomStarter, int typeChoisi);
};

#endif // CHOIXJOUEUR_H
