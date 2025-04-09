#include "map.h"
#include "ui_map.h"
#include "combat.h"
#include <QThread>
#include <string>

const int maxGenimon = 15;
const int maxCapsuleGuerison = 9;
const int position_x_ref = 72;
const int position_y_ref = 42;
const int image_x_ref = 680;
const int image_y_ref = 550;

Map::Map(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::Map)
{
    ui->setupUi(this);
    ui->NomPerso->setText(QString("%1").arg(nomJoueur));
    Parent = parent;

    initialiserMap();
}

Map::~Map()
{
    delete ui;
}

void Map::demarrerMenu()
{
    joueur->show();
    spawnTimer1->start(4000);
    spawnTimer2->start(20000);
    estSurMap = true;

    for (int i = 0; i < listeGenimons.count(); i++)
    {
        if (estExterieur && listeGenimons[i]->estExterieur)
        {
            listeGenimons[i]->show();
        }
        else if (!estExterieur && !listeGenimons[i]->estExterieur)
        {
            listeGenimons[i]->show();
        }
    }

    if (capsuleGuerisonActive)
    {
        capsuleGuerison->show();
    }

    outsideMusic->play();
    insideMusic->play();

    qDebug() << "out" << outsideMusic->isPlaying();
    qDebug() << "in" << outsideMusic->isPlaying();
}

void Map::fermerMenu()
{
    joueur->hide();
    estSurMap = false;
    spawnTimer2->stop();

    for (int i = 0; i < listeGenimons.count(); i++)
    {
        listeGenimons[i]->hide();
    }

    if (capsuleGuerisonActive)
    {
        capsuleGuerison->hide();
    }
}

void Map::initialiserMap()
{
    joueur = new QLabel(Parent);
    capsuleGuerison = new QLabel(Parent);
    joueurX = image_x_ref;
    joueurY = image_y_ref;
    position_x = position_x_ref;
    position_y = position_y_ref;
    borne_x_min = 0;
    borne_y_min = 0;
    borne_x_max = 123;
    borne_y_max = 53;

    nbBalles = 20;
    nbCapsuleGuerison = 0;
    capsuleGuerisonActive = false;
    step = 10;
    estExterieur = true;
    nomJoueur = "";
    mode5a8Actif = false;
    estSurMap = true;

    ui->BackGround->setPixmap(QPixmap(":/Decor/Image_Qt/Decor/School-Map-withoutPeople-8bit.jpeg"));
    imageJoueur.load(":/Decor/Image_Qt/Decor/ChatGPT.png");
    joueur->setPixmap(imageJoueur.scaled(120, 70, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    joueur->setScaledContents(true);
    joueur->resize(120, 70);
    joueur->move(680, 550);
    joueur->hide();

    capsuleGuerison->setPixmap(QPixmap(":/Decor/Image_Qt/Decor/Coeur.png").scaled(120, 70, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    capsuleGuerison->setScaledContents(true);
    capsuleGuerison->resize(80, 50);
    capsuleGuerison->move(910, 335);
    capsuleGuerison->hide();

    genidex.clear();
    historique.clear();
    listeGenimons.clear();

    //Création de 5 genimons au début de la partie
    for (int i = 0; i < 5; i++)
    {
        ajouterGenimon();
        listeGenimons[i]->hide();
    }

    spawnTimer1 = new QTimer(this);
    connect(spawnTimer1, &QTimer::timeout, this, &Map::gererGenimonMap);
    spawnTimer2 = new QTimer(this);
    connect(spawnTimer2, &QTimer::timeout, this, &Map::gererCapsuleVieMap);

    outsideOutput = new QAudioOutput(this);
    outsideMusic = new QMediaPlayer(this);
    outsideMusic->setSource(QUrl::fromLocalFile("Blitzkrieg 2022.wav"));
    outsideMusic->setAudioOutput(outsideOutput);
    outsideMusic->setLoops(QMediaPlayer::Infinite);
    insideOutput = new QAudioOutput(this);
    insideMusic = new QMediaPlayer(this);
    insideMusic->setSource(QUrl::fromLocalFile("Blitzkrieg_Int.wav"));
    insideMusic->setAudioOutput(insideOutput);
    insideMusic->setLoops(QMediaPlayer::Infinite);
}

void Map::handleKeyPress(int key) {

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

void Map::handleArduinoInput(int boutons, int joystick, int accelerometre, int muons) {

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

void Map::update() {

    if (BOUTONS == 1) {
        BOUTONS = 0;
        JOYSTICKS = 0;
        ACCEL = 0;
        MUONS = 0;
        showGenidex();
    }
    else if (BOUTONS == 2) {
        BOUTONS = 0;
        JOYSTICKS = 0;
        ACCEL = 0;
        MUONS = 0;
        showHistoRencontre();
    }
    else if (BOUTONS == 3) {
        BOUTONS = 0;
        JOYSTICKS = 0;
        ACCEL = 0;
        MUONS = 0;
        showPause();
    }
    else if (JOYSTICKS == 1) {
        if (position_y > borne_y_min) {
            joueurY -= step;
            position_y--;
            joueur->move(joueurX, joueurY);
        }
        else if (estExterieur && position_x >= 69 && position_x <= 79 && position_y == 0)
        {
            showIntFaculte();
            outsideOutput->setVolume(0);
            insideOutput->setVolume(1);
        }
    }
    else if (JOYSTICKS == 4) {
        if (estExterieur)
        {
            if (((position_x > borne_x_min) && (position_x > 21 && position_x <= 105)) || (position_x > borne_x_min && position_y < 10))
            {
                joueurX -= step;
                position_x--;
                joueur->move(joueurX, joueurY);
            }
        }
        else
        {
            if (position_x > borne_x_min)
            {
                joueurX -= step;
                position_x--;
                joueur->move(joueurX, joueurY);
            }
        }
    }
    else if (JOYSTICKS == 3) {
        if (estExterieur)
        {
            if (((position_y < borne_y_max) && (position_x >= 21 && position_x <= 105)) || position_y < 9) {
                joueurY += step;
                position_y++;
                joueur->move(joueurX, joueurY);
            }
        }
        else
        {
            if (position_y < borne_y_max - 6) {
                joueurY += step;
                position_y++;
                joueur->move(joueurX, joueurY);
            }
            else if (position_x >= 61 && position_x <= 79 && position_y == borne_y_max - 6)
            {
                showExtFaculte();
                outsideOutput->setVolume(1);
                insideOutput->setVolume(0);
            }
        }
    }
    else if (JOYSTICKS == 2) {
        if (estExterieur)
        {
            if (((position_x < borne_x_max) && (position_x >= 21 && position_x < 105)) || (position_x < borne_x_max && position_y < 10))
            {
                joueurX += step;
                position_x++;
                joueur->move(joueurX, joueurY);
            }
        }
        else
        {
            if (position_x < borne_x_max)
            {
                joueurX += step;
                position_x++;
                joueur->move(joueurX, joueurY);
            }
        }
    }

    //Détection collisions genimon
    for (int i = 0; i < listeGenimons.count(); i++)
    {
        if ((listeGenimons[i]->position_x - 4 == position_x || listeGenimons[i]->position_x - 5 == position_x)
            && (listeGenimons[i]->position_y - 1 == position_y || listeGenimons[i]->position_y - 2 == position_y))
        {
			insideMusic->pause();
			outsideMusic->pause();
            historique.push_back(*listeGenimons[i]);
            emit sendInfos(*listeGenimons[i], &nbBalles, &nbCapsuleGuerison, &genidex);

            BOUTONS = 0;
            JOYSTICKS = 0;
            ACCEL = 0;
            MUONS = 0;
            showChoixAction();

            listeGenimons[i]->hide();
            listeGenimons.remove(i);
        }
    }

    //Détection collisions capsule de guerison
    if (capsuleGuerisonActive && (position_x == 91 || position_x == 92 ||position_x == 93) && (position_y == 18 || position_y == 19 || position_y == 20))
    {
        capsuleGuerison->hide();
        capsuleGuerisonActive = false;
        nbCapsuleGuerison++;
        emit setSegment(nbCapsuleGuerison);
    }

    BOUTONS = 0;
    JOYSTICKS = 0;
    ACCEL = 0;
    MUONS = 0;
}

void Map::gererGenimonMap()
{
    //Ajouter un genimon
    if (listeGenimons.count() < maxGenimon)
    {
        if (listeGenimons.count() <= maxGenimon / 3)
        {
            ajouterGenimon();
        }
        else
        {
            if ((rand() % 2) == 1)
            {
                ajouterGenimon();
            }
        }
    }

    //Retirer un genimon
    if (listeGenimons.count() >= 10)
    {
        if ((rand() % 5) == 1)
        {
            retirerGenimon();
        }
    }
}

void Map::gererCapsuleVieMap()
{
    if (!capsuleGuerisonActive && nbCapsuleGuerison < maxCapsuleGuerison)
    {
        int choix = rand() % 3;
        if (choix == 0)
        {
            capsuleGuerison->show();
            capsuleGuerisonActive = true;
        }
    }
}

void Map::ajouterGenimon()
{
    Genimon* nouveauGenimon = new Genimon(Parent);
    listeGenimons.append(nouveauGenimon);
    if (nouveauGenimon->estExterieur)
    {
        nouveauGenimon->position_x = 23 + rand() % 81;
        nouveauGenimon->position_y = 5 + rand() % borne_y_max - 5;
    }
    else
    {
        nouveauGenimon->position_x = rand() % borne_x_max;
        nouveauGenimon->position_y = 7 + rand() % borne_y_max - 14;
    }

    while (nouveauGenimon->position_x == position_x && nouveauGenimon->position_y == position_y)
    {
        if (nouveauGenimon->estExterieur)
        {
            nouveauGenimon->position_x = 23 + rand() % 81;
            nouveauGenimon->position_y = 5 + rand() % borne_y_max - 5;
        }
        else
        {
            nouveauGenimon->position_x = rand() % borne_x_max;
            nouveauGenimon->position_y = 7 + rand() % borne_y_max - 14;
        }
    }

    //Position x
    if (nouveauGenimon->position_x == position_x_ref)
    {
        nouveauGenimon->genimonX = image_x_ref;
    }
    else if (nouveauGenimon->position_x < position_x_ref)
    {
        int difference = position_x_ref - nouveauGenimon->position_x;
        nouveauGenimon->genimonX = image_x_ref - (difference * step);
    }
    else if (nouveauGenimon->position_x > position_x_ref)
    {
        int difference = nouveauGenimon->position_x - position_x_ref;
        nouveauGenimon->genimonX = image_x_ref + (difference * step);
    }

    //Position y
    if (nouveauGenimon->position_y == position_y_ref)
    {
        nouveauGenimon->genimonY = image_y_ref;
    }
    else if (nouveauGenimon->position_y < position_y_ref)
    {
        int difference = position_y_ref - nouveauGenimon->position_y;
        nouveauGenimon->genimonY = image_y_ref - (difference * step);
    }
    else if (nouveauGenimon->position_y > position_y_ref)
    {
        int difference = nouveauGenimon->position_y - position_y_ref;
        nouveauGenimon->genimonY = image_y_ref + (difference * step);
    }

    nouveauGenimon->move(nouveauGenimon->genimonX, nouveauGenimon->genimonY);

    if (estSurMap && estExterieur && nouveauGenimon->estExterieur)
    {
        nouveauGenimon->show();
    }
    else if (estSurMap && !estExterieur && !nouveauGenimon->estExterieur)
    {
        nouveauGenimon->show();
    }
}

void Map::retirerGenimon()
{
    int indexRandom = rand() % listeGenimons.count(); //Retire un genimon random
    listeGenimons[indexRandom]->hide();
    listeGenimons.remove(indexRandom);
}

void Map::gererMode5a8()
{
    if (mode5a8Actif)
    {
        mode5a8Actif = false;
        if (estExterieur)
        {
            ui->BackGround->setPixmap(QPixmap(":/Decor/Image_Qt/Decor/School-Map-withoutPeople-8bit.jpeg"));
        }
        else
        {
            ui->BackGround->setPixmap(QPixmap(":/Decor/Image_Qt/Decor/Cafeteria.jpeg"));
        }
    }
    else
    {
        mode5a8Actif = true;
        if (estExterieur)
        {
            ui->BackGround->setPixmap(QPixmap(":/Decor/Image_Qt/Decor/School-Map-8bit_5a8.png"));
        }
        else
        {
            ui->BackGround->setPixmap(QPixmap(":/Decor/Image_Qt/Decor/Cafeteria_5a8.jpeg"));
        }
    }
}

void Map::showExtFaculte()
{
    if (mode5a8Actif)
    {
        ui->BackGround->setPixmap(QPixmap(":/Decor/Image_Qt/Decor/School-Map-8bit_5a8.png"));
    }
    else
    {
        ui->BackGround->setPixmap(QPixmap(":/Decor/Image_Qt/Decor/School-Map-withoutPeople-8bit.jpeg"));
    }
    ui->NomPerso->setVisible(true);

    position_x = 74;
    position_y = 0;
    joueurX = 700;
    joueurY = 130;
    joueur->move(joueurX, joueurY);
    estExterieur = true;

    for (int i = 0; i < listeGenimons.count(); i++)
    {
        if (listeGenimons[i]->estExterieur)
        {
            listeGenimons[i]->show();
        }
        else
        {
            listeGenimons[i]->hide();
        }
    }

    if (capsuleGuerisonActive)
    {
        capsuleGuerison->show();
    }
}

void Map::showIntFaculte()
{
    if (mode5a8Actif)
    {
        ui->BackGround->setPixmap(QPixmap(":/Decor/Image_Qt/Decor/Cafeteria_5a8.jpeg"));
    }
    else
    {
        ui->BackGround->setPixmap(QPixmap(":/Decor/Image_Qt/Decor/Cafeteria.jpeg"));
    }
    ui->NomPerso->setVisible(true);

    position_x = 70;
    position_y = borne_y_max - 6;
    joueurX = 660;
    joueurY = 600;
    joueur->move(joueurX, joueurY);
    estExterieur = false;

    for (int i = 0; i < listeGenimons.count(); i++)
    {
        if (listeGenimons[i]->estExterieur)
        {
            listeGenimons[i]->hide();
        }
        else
        {
            listeGenimons[i]->show();
        }
    }

    if (capsuleGuerisonActive)
    {
        capsuleGuerison->hide();
    }
}

void Map::showChoixAction()
{
    emit requestMenuChange(10); //Passer au menu choixAction
    fermerMenu();
    spawnTimer1->stop();
}

void Map::showGenidex()
{
    emit sendGenidex(&nbBalles, &nbCapsuleGuerison, &genidex);
    emit requestMenuChange(5); //Passer au menu genidex
    fermerMenu();
}

void Map::showHistoRencontre()
{
    emit sendHistorique(historique);
    emit requestMenuChange(6); //Passer au menu histoRencontre
    fermerMenu();
}

void Map::showPause()
{
    emit requestMenuChange(9); //Passer au menu pause
    fermerMenu();
    spawnTimer1->stop();

    outsideMusic->pause();
    insideMusic->pause();

    qDebug() << "out" << outsideMusic->isPlaying();
    qDebug() << "in" << outsideMusic->isPlaying();
}

void Map::setNomsChoisis(const QString& nom, QString nomStarter, int typeChoisi)
{
    nomJoueur = nom;
    ui->NomPerso->setText(QString("%1").arg(nomJoueur));

    genidex.push_back(Genimon(typeChoisi, nomStarter.toStdString(), Parent));
}