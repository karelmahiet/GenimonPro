#include "capture.h"
#include "ui_capture.h"
#include <QEasingCurve>
#include <string>

Capture::Capture(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::Capture)
{
    ui->setupUi(this);
    ui->Joueur->setPixmap(QPixmap(":/Decor/Image_Qt/Decor/ChatGPT.png").scaled(520, 470, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->Pokeball->setVisible(false);
    captureBloquee = false;
}

Capture::~Capture()
{
    delete ui;
}

void Capture::handleKeyPress(int key) {

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

void Capture::handleArduinoInput(int boutons, int joystick, int accelerometre, int muons) {

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

void Capture::update() {

    if (BOUTONS == 1) {
        if (*nbBalles_trans > 0 && !captureBloquee)
        {
            int nbRebond = compterRebond();
            animerPokeball(nbRebond);
        }
    }
    else if (BOUTONS == 2) {
        BOUTONS = 0;
        JOYSTICKS = 0;
        ACCEL = 0;
        MUONS = 0;
        emit requestMenuChange(2); //Passer au menu map
        clearFocus();
    }

    BOUTONS = 0;
    JOYSTICKS = 0;
    ACCEL = 0;
    MUONS = 0;
}

void Capture::afficherInfoCapture(Genimon genimonEnCours, int* nbBalles, int* nbCapsuleGuerison, vector<Genimon>* genidex)
{
    ui->Pokeball->setVisible(false);
    ui->Genimon->show();
    captureBloquee = false;
    ui->Info1->setStyleSheet("background-color: white;");
    ui->Genimon->setPixmap(genimonEnCours.imageGenimon.scaled(ui->Genimon->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    QString texte = "Nombre de balle: ";
    texte.append(to_string(*nbBalles));
    ui->Info1->setText(texte);
    ui->Resultat->setText("Resultat: En attente...");
    nbBalles_trans = nbBalles;
    genimonEnCours_trans.clear();
    genimonEnCours_trans.push_back(genimonEnCours);
    genidex_trans = genidex;
}

int Capture::compterRebond()
{
    captureBloquee = true;
    int nbRebond = 1;
    int facteurChance = genimonEnCours_trans[0].getFacteurChance();
    (*nbBalles_trans)--;

    ui->Resultat->setText("Resultat: En attente...");

    int random = rand() % 20;
    if (random >= 0 && random < (8 + facteurChance)) {
        nbRebond++;
        random = rand() % 20;
        if (random >= 0 && random < (10 + facteurChance)) {
            nbRebond++;
            random = rand() % 20;
            if (random >= 0 && random < (12 + facteurChance)) {
                nbRebond++;
            }
        }
    }

    QString texte = "Nombre de balle: ";
    texte.append(to_string(*nbBalles_trans));
    ui->Info1->setText(texte);
    if (*nbBalles_trans <= 0)
    {
        ui->Info1->setStyleSheet("background-color: grey;");
    }

    return nbRebond;
}

void Capture::animerPokeball(int nbRebond) {

    ui->Pokeball->setVisible(true);
    QSequentialAnimationGroup* animationGroup = new QSequentialAnimationGroup();
    QPoint originalPos = QPoint(850, 160);

    //------------Animation de lançage--------------
    QPropertyAnimation* animationL = new QPropertyAnimation(ui->Pokeball, "pos", this);
    animationL->setDuration(1200); // Durée de l'animation
    animationL->setStartValue(QPoint(200, 440)); // Position de départ
    animationL->setEndValue(originalPos); // Position d'arrivée

    // Utiliser un mouvement de courbe parabolique
    animationL->setEasingCurve(QEasingCurve::OutQuad); // Courbe d'accélération de type "rebond"

    animationL->start();

    // Timer pour faire disparaître la Pokéball après l'animation
    connect(animationL, &QPropertyAnimation::finished, this, [=]() {
        animationL->deleteLater();  // Supprimer l'animation après qu'elle soit terminée
        ui->Genimon->hide();
        animationGroup->start();
        });



    //------------Animation de capture--------------
    // Créer un QPropertyAnimation pour animer la position
    QPropertyAnimation* shakeAnim = new QPropertyAnimation(ui->Pokeball, "pos");
    shakeAnim->setDuration(100);
    shakeAnim->setStartValue(originalPos);
    shakeAnim->setEndValue(originalPos + QPoint(10, 0));  // Déplacer à droite

    // Animation pour aller à gauche
    QPropertyAnimation* shakeAnim2 = new QPropertyAnimation(ui->Pokeball, "pos");
    shakeAnim2->setDuration(100);
    shakeAnim2->setStartValue(originalPos + QPoint(10, 0));
    shakeAnim2->setEndValue(originalPos - QPoint(10, 0));  // Déplacer à gauche

    // Animation pour revenir à la position initiale
    QPropertyAnimation* shakeAnim3 = new QPropertyAnimation(ui->Pokeball, "pos");
    shakeAnim3->setDuration(100);
    shakeAnim3->setStartValue(originalPos - QPoint(10, 0));
    shakeAnim3->setEndValue(originalPos);  // Retourner à la position initiale

    // Appliquer une courbe d'accélération pour les animations
    shakeAnim->setEasingCurve(QEasingCurve::OutQuad);
    shakeAnim2->setEasingCurve(QEasingCurve::OutQuad);
    shakeAnim3->setEasingCurve(QEasingCurve::OutQuad);


    QPropertyAnimation* shakeAnim4 = new QPropertyAnimation(ui->Pokeball, "pos");
    shakeAnim4->setDuration(100);
    shakeAnim4->setStartValue(originalPos);
    shakeAnim4->setEndValue(originalPos + QPoint(10, 0));
    QPropertyAnimation* shakeAnim5 = new QPropertyAnimation(ui->Pokeball, "pos");
    shakeAnim5->setDuration(100);
    shakeAnim5->setStartValue(originalPos + QPoint(10, 0));
    shakeAnim5->setEndValue(originalPos - QPoint(10, 0));
    QPropertyAnimation* shakeAnim6 = new QPropertyAnimation(ui->Pokeball, "pos");
    shakeAnim6->setDuration(100);
    shakeAnim6->setStartValue(originalPos - QPoint(10, 0));
    shakeAnim6->setEndValue(originalPos);
    shakeAnim4->setEasingCurve(QEasingCurve::OutQuad);
    shakeAnim5->setEasingCurve(QEasingCurve::OutQuad);
    shakeAnim6->setEasingCurve(QEasingCurve::OutQuad);


    QPropertyAnimation* shakeAnim7 = new QPropertyAnimation(ui->Pokeball, "pos");
    shakeAnim7->setDuration(100);
    shakeAnim7->setStartValue(originalPos);
    shakeAnim7->setEndValue(originalPos + QPoint(10, 0));
    QPropertyAnimation* shakeAnim8 = new QPropertyAnimation(ui->Pokeball, "pos");
    shakeAnim8->setDuration(100);
    shakeAnim8->setStartValue(originalPos + QPoint(10, 0));
    shakeAnim8->setEndValue(originalPos - QPoint(10, 0));
    QPropertyAnimation* shakeAnim9 = new QPropertyAnimation(ui->Pokeball, "pos");
    shakeAnim9->setDuration(100);
    shakeAnim9->setStartValue(originalPos - QPoint(10, 0));
    shakeAnim9->setEndValue(originalPos);
    shakeAnim7->setEasingCurve(QEasingCurve::OutQuad);
    shakeAnim8->setEasingCurve(QEasingCurve::OutQuad);
    shakeAnim9->setEasingCurve(QEasingCurve::OutQuad);



    //------------Animation d'atterissage--------------
    QPropertyAnimation* animationA = new QPropertyAnimation(ui->Pokeball, "pos", this);
    animationA->setDuration(1000); // Durée de l'animation
    animationA->setStartValue(originalPos); // Position de départ
    animationA->setEndValue(originalPos + QPoint(0, 230)); // Position d'arrivée

    animationA->setEasingCurve(QEasingCurve::OutQuad);

    connect(animationA, &QPropertyAnimation::finished, this, [=]() {
        animationA->deleteLater();  // Supprimer l'animation après qu'elle soit terminée
        });



    //------------Construction de l'animation finale--------------
    animationGroup->addPause(1000);
    animationGroup->addAnimation(shakeAnim);
    animationGroup->addAnimation(shakeAnim2);
    animationGroup->addAnimation(shakeAnim3);
    animationGroup->addPause(1500);
    if (nbRebond >= 2)
    {
        animationGroup->addAnimation(shakeAnim4);
        animationGroup->addAnimation(shakeAnim5);
        animationGroup->addAnimation(shakeAnim6);
        animationGroup->addPause(1500);
    }
    if (nbRebond >= 3)
    {
        animationGroup->addAnimation(shakeAnim7);
        animationGroup->addAnimation(shakeAnim8);
        animationGroup->addAnimation(shakeAnim9);
        animationGroup->addPause(1500);
    }

    connect(animationGroup, &QPropertyAnimation::finished, this, [=]() {
        animationGroup->deleteLater();  // Supprimer l'animation après qu'elle soit terminée
        if (nbRebond != 4)
        {
            ui->Pokeball->setVisible(false);
            ui->Genimon->show();
            ui->Resultat->setText("Resultat: Capture echoue");
            captureBloquee = false;
        }
        else
        {
            genidex_trans->push_back(genimonEnCours_trans[0]);
            ui->Resultat->setText("Resultat: Capture reussie!");
            ui->Info1->setStyleSheet("background-color: grey;");
            animationA->start();
        }
        });
}