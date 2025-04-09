#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <vector>
#include <QVector>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "genimon.h"

namespace Ui {
    class Map;
}

class Map : public QWidget
{
    Q_OBJECT

public:
    explicit Map(QWidget* parent = nullptr);
    ~Map();

    void demarrerMenu();
    void fermerMenu();

public slots:
    void handleKeyPress(int key);
    void handleArduinoInput(int boutons, int joystick, int accelerometre, int muons);
    void setNomsChoisis(const QString& nom, QString nomStarter, int typeChoisi);
    void initialiserMap();
    void gererMode5a8();

private:
    Ui::Map* ui;
    QWidget* Parent;
    QTimer* spawnTimer1;
    QTimer* spawnTimer2;
    QLabel* joueur;
    QLabel* capsuleGuerison;
    QPixmap imageJoueur;
    QMediaPlayer* outsideMusic;
    QMediaPlayer* insideMusic;
    QAudioOutput* outsideOutput;
    QAudioOutput* insideOutput;
    int joueurX;
    int joueurY;
    int position_x;
    int position_y;
    int borne_x_min;
    int borne_y_min;
    int borne_x_max;
    int borne_y_max;

    vector<Genimon> genidex;
    vector<Genimon> historique;
    QVector<Genimon*> listeGenimons;
    int nbBalles;
    int nbCapsuleGuerison;
    bool capsuleGuerisonActive;

    int step;
    bool estExterieur;
    QString nomJoueur;
    bool mode5a8Actif;
    bool estSurMap;

    void gererGenimonMap();
    void gererCapsuleVieMap();
    void showExtFaculte();
    void showIntFaculte();
    void showChoixAction();
    void showGenidex();
    void showHistoRencontre();
    void showPause();
    void ajouterGenimon();
    void retirerGenimon();

    void update();
    int BOUTONS = 0;
    int JOYSTICKS = 0;
    int ACCEL = 0;
    int MUONS = 0;

signals:
    void requestMenuChange(int index);
    void sendInfos(Genimon genimonEnCours, int* nbBalles, int* nbCapsuleGuerison, vector<Genimon>* genidex);
    void sendGenidex(int* nbBalles, int* nbCapsuleGuerison, vector<Genimon>* genidex);
    void sendHistorique(vector<Genimon> historique);
    void setSegment(int seg);
    void setMessage(QString mes);
};

#endif // MAP_H
