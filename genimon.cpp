#include "genimon.h"

Genimon::Genimon(QWidget* parent) : QLabel(parent)
{
    int random = rand() % 8;
    typeNumerique = random;
    setNom();
    if (random == 0) {
        type = "informatique";
        typeSuperieur = "aucunI";
        typeInferieur = "civil";
    }
    else if (random == 1) {
        type = "electrique";
        typeSuperieur = "aucunE";
        typeInferieur = "batiment";
    }
    else if (random == 2) {
        type = "robotique";
        typeSuperieur = "bioTech";
        typeInferieur = "aucunR";
    }
    else if (random == 3) {
        type = "mecanique";
        typeSuperieur = "civil";
        typeInferieur = "bioTech";
    }
    else if (random == 4) {
        type = "civil";
        typeSuperieur = "informatique";
        typeInferieur = "mecanique";
    }
    else if (random == 5) {
        type = "batiment";
        typeSuperieur = "electrique";
        typeInferieur = "chimique";
    }
    else if (random == 6) {
        type = "bioTech";
        typeSuperieur = "mecanique";
        typeInferieur = "robotique";
    }
    else if (random == 7) {
        type = "chimique";
        typeSuperieur = "batiment";
        typeInferieur = "chimique";
    }

    setImage();
    setRarete();
    facteurDegats = degats / 4;
}

Genimon::Genimon(int typeC, string nomC, QWidget* parent) : QLabel(parent)
{
    if (typeC == 0) {
        type = "informatique";
        typeSuperieur = "aucunI";
        typeInferieur = "civil";
        imageGenimon.load(":/Starter/Image_Qt/Starter/Bombardier Info.png");
    }
    else if (typeC == 1) {
        type = "electrique";
        typeSuperieur = "aucunE";
        typeInferieur = "batiment";
        imageGenimon.load(":/Starter/Image_Qt/Starter/Bombardier Elec.png");
    }
    else if (typeC == 2) {
        type = "robotique";
        typeSuperieur = "bioTech";
        typeInferieur = "aucunR";
        imageGenimon.load(":/Starter/Image_Qt/Starter/Bombardier Robot.png");
    }
    else if (typeC == 3) {
        type = "mecanique";
        typeSuperieur = "civil";
        typeInferieur = "bioTech";
        imageGenimon.load(":/Starter/Image_Qt/Starter/Bombardier Mec.png");
    }
    else if (typeC == 4) {
        type = "civil";
        typeSuperieur = "informatique";
        typeInferieur = "mecanique";
        imageGenimon.load(":/Starter/Image_Qt/Starter/Bombardier Civil.png");
    }
    else if (typeC == 5) {
        type = "batiment";
        typeSuperieur = "electrique";
        typeInferieur = "chimique";
        imageGenimon.load(":/Starter/Image_Qt/Starter/Bombardier Batiment.png");
    }
    else if (typeC == 6) {
        type = "bioTech";
        typeSuperieur = "mecanique";
        typeInferieur = "robotique";
        imageGenimon.load(":/Starter/Image_Qt/Starter/Bombardier Bio.png");

    }
    else if (typeC == 7) {
        type = "chimique";
        typeSuperieur = "batiment";
        typeInferieur = "chimique";
        imageGenimon.load(":/Starter/Image_Qt/Starter/Bombardier Chimique.png");
    }

    typeNumerique = typeC;
    nom = nomC;
    rarete = "RARE";
    rareteNumerique = 1;
    facteurChance = 2;
    gainBalles = 15;
    pv = 100 + (rand() % 101); //Entre 100 et 200
    degats = 20 + (rand() % 21); //Entre 20 et 40
    facteurDegats = degats / 4;
    pvMax = pv;

    this->setPixmap(imageGenimon.scaled(120, 70, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    this->setScaledContents(true);
    this->resize(50, 50);
    int chance = rand() % 2;
    if (chance == 0)
    {
        estExterieur = true;
    }
    else
    {
        estExterieur = false;
    }
}

Genimon::Genimon(const Genimon& autre)
{
    position_x = autre.position_x;
    position_y = autre.position_y;
    genimonX = autre.genimonX;
    genimonY = autre.genimonY;
    pvMax = autre.pvMax;
    estExterieur = autre.estExterieur;
    nom = autre.nom;
    rarete = autre.rarete;
    type = autre.type;
    typeNumerique = autre.typeNumerique;
    rareteNumerique = autre.rareteNumerique;
    facteurChance = autre.facteurChance;
    gainBalles = autre.gainBalles;
    imageGenimon = autre.imageGenimon;

    typeSuperieur = autre.typeSuperieur;
    typeInferieur = autre.typeInferieur;
    pv = autre.pv;
    degats = autre.degats;
    facteurDegats = autre.facteurDegats;
}

void Genimon::setNom()
{
    if (typeNumerique == 0) { // informatique
        int random = rand() % 3;
        if (random == 0)
            nom = "Albert";
        else if (random == 1)
            nom = "Jeremie";
        else if (random == 2)
            nom = "Raphael";
    }
    else if (typeNumerique == 1) { // electrique
        int random = rand() % 4;
        if (random == 0)
            nom = "Florian";
        else if (random == 1)
            nom = "JP";
        else if (random == 2)
            nom = "Emy";
        else if (random == 3)
            nom = "Marc-Antoine";
    }
    else if (typeNumerique == 2) { // robotique
        int random = rand() % 4;
        if (random == 0)
            nom = "Alexis";
        else if (random == 1)
            nom = "Melianne";
        else if (random == 2)
            nom = "Elon";
        else if (random == 3)
            nom = "Youssef";
    }
    else if (typeNumerique == 3) { // mecanique
        int random = rand() % 3;
        if (random == 0)
            nom = "Dylan";
        else if (random == 1)
            nom = "Joe";
        else if (random == 2)
            nom = "Luther";
    }
    else if (typeNumerique == 4) { // civil
        int random = rand() % 4;
        if (random == 0)
            nom = "Abdullah";
        else if (random == 1)
            nom = "Catherine";
        else if (random == 2)
            nom = "Marek";
        else if (random == 3)
            nom = "Trudeau";

    }
    else if (typeNumerique == 5) { // batiment
        int random = rand() % 3;
        if (random == 0)
            nom = "Felix";
        else if (random == 1)
            nom = "Trump";
        else if (random == 2)
            nom = "Vincent";
    }
    else if (typeNumerique == 6) { // bioTech
        int random = rand() % 3;
        if (random == 0)
            nom = "Darnley";
        else if (random == 1)
            nom = "MrClean";
        else if (random == 2)
            nom = "Simon";
    }
    else if (typeNumerique == 7) { // chimique
        int random = rand() % 3;
        if (random == 0)
            nom = "Jacob";
        else if (random == 1)
            nom = "Marie";
        else if (random == 2)
            nom = "Karel";
    }
}

void Genimon::setRarete()
{
    int random = rand() % 100;

    if (random < 30)
    {
        rarete = "COMMUN";
        rareteNumerique = 0;
        facteurChance = 4;
        gainBalles = 10;

        pv = 50 + (rand() % 51); //Entre 50 et 100
        degats = 10 + (rand() % 11); //Entre 10 et 20
    }
    else if (random < 60)
    {
        rarete = "RARE";
        rareteNumerique = 1;
        facteurChance = 2;
        gainBalles = 15;

        pv = 100 + (rand() % 101); //Entre 100 et 200
        degats = 20 + (rand() % 21); //Entre 20 et 40
    }
    else if (random < 80)
    {
        rarete = "EPIQUE";
        rareteNumerique = 2;
        facteurChance = 1;
        gainBalles = 20;

        pv = 200 + (rand() % 101); //Entre 200 et 300
        degats = 40 + (rand() % 21); //Entre 40 et 60
    }
    else if (random < 99)
    {
        rarete = "!! LEGENDAIRE !!";
        rareteNumerique = 3;
        facteurChance = 0;
        gainBalles = 25;

        pv = 300 + (rand() % 201); //Entre 300 et 500
        degats = 60 + (rand() % 31); //Entre 60 et 90
    }
    else
    {
        rarete = "*** SECRET ***";
        rareteNumerique = 4;
        facteurChance = 0;
        gainBalles = 30;

        pv = 500 + (rand() % 201); //Entre 500 et 700
        degats = 90 + (rand() % 31); //Entre 90 et 120
    }

    pvMax = pv;
}

void Genimon::setImage()
{
    if (nom == "Florian") {
        imageGenimon.load(":/Elec/Image_Qt/Elec/Flo_finale-removebg-preview.png");
    }
    else if (nom == "Emy") {
        imageGenimon.load(":/Elec/Image_Qt/Elec/Emy_finale-removebg-preview.png");
    }
    else if (nom == "Marc-Antoine") {
        imageGenimon.load(":/Elec/Image_Qt/Elec/Marc-Antoine_finale-removebg-preview.png");
    }
    else if (nom == "JP") {
        imageGenimon.load(":/Elec/Image_Qt/Elec/JP_finale-removebg-preview.png");
    }
    else if (nom == "Albert") {
        imageGenimon.load(":/Info/Image_Qt/Info/ecran_Albert.png");
    }
    else if (nom == "Jeremie") {
        imageGenimon.load(":/Info/Image_Qt/Info/ecran_JeremieV2.png");
    }
    else if (nom == "Raphael") {
        imageGenimon.load(":/Info/Image_Qt/Info/ecran_RaphaelV2.png");
    }
    else if (nom == "Dylan") {
        imageGenimon.load(":/Mec/Image_Qt/Mec/gear_Dylan.png");
    }
    else if (nom == "Joe") {
        imageGenimon.load(":/Mec/Image_Qt/Mec/gear_Joe.png");
    }
    else if (nom == "Luther") {
        imageGenimon.load(":/Mec/Image_Qt/Mec/gear_Luther.png");
    }
    else if (nom == "Abdullah") {
        imageGenimon.load(":/Civil/Image_Qt/Civil/Abdullah_final.png");
    }
    else if (nom == "Catherine") {
        imageGenimon.load(":/Civil/Image_Qt/Civil/Catherine_final.png");
    }
    else if (nom == "Marek") {
        imageGenimon.load(":/Civil/Image_Qt/Civil/Marek_final.png");
    }
    else if (nom == "Trudeau") {
        imageGenimon.load(":/Civil/Image_Qt/Civil/Trudeau_final.png");
    }
    else if (nom == "Jacob") {
        imageGenimon.load(":/Chimie/Image_Qt/Chimique/Erlenmeyer-Jacob.png");
    }
    else if (nom == "Karel") {
        imageGenimon.load(":/Chimie/Image_Qt/Chimique/Erlenmeyer-Karel.png");
    }
    else if (nom == "Marie") {
        imageGenimon.load(":/Chimie/Image_Qt/Chimique/Erlenmeyer-Marie.png");
    }
    else if (nom == "Darnley") {
        imageGenimon.load(":/Bio/Image_Qt/Bio/Virus_Darnley-removebg-preview.png");
    }
    else if (nom == "MrClean") {
        imageGenimon.load(":/Bio/Image_Qt/Bio/Virus_MrClean-removebg-preview.png");
    }
    else if (nom == "Simon") {
        imageGenimon.load(":/Bio/Image_Qt/Bio/Virus_Simon-removebg-preview.png");
    }
    else if (nom == "Felix") {
        imageGenimon.load(":/Batiment/Image_Qt/Batiment/Felix_Finale.png");
    }
    else if (nom == "Trump") {
        imageGenimon.load(":/Batiment/Image_Qt/Batiment/Trump_Finale.png");
    }
    else if (nom == "Vincent") {
        imageGenimon.load(":/Batiment/Image_Qt/Batiment/Vincent_Finale.png");
    }
    else if (nom == "Alexis") {
        imageGenimon.load(":/Robot/Image_Qt/Robot/robot_Alexis.png");
    }
    else if (nom == "Elon") {
        imageGenimon.load(":/Robot/Image_Qt/Robot/robot_Elon.png");
    }
    else if (nom == "Melianne") {
        imageGenimon.load(":/Robot/Image_Qt/Robot/robot_Melianne.png");
    }
    else if (nom == "Youssef") {
        imageGenimon.load(":/Robot/Image_Qt/Robot/robot_Youssef.png");
    }
    else {
        imageGenimon.load(":/Civil/Image_Qt/Civil/Trudeau_final.png");
    }

    this->setPixmap(imageGenimon.scaled(120, 70, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    this->setScaledContents(true);
    this->resize(50, 50);

    int chance = rand() % 2;
    if (chance == 0)
    {
        estExterieur = true;
    }
    else
    {
        estExterieur = false;
    }
}

int Genimon::getTypeNumerique() {
    return typeNumerique;
}

string Genimon::getType() {
    return type;
}

string Genimon::getTypeSuperieur()
{
    return typeSuperieur;
}

string Genimon::getTypeInferieur()
{
    return typeInferieur;
}

string Genimon::getRarete() {
    return rarete;
}

int Genimon::getRareteNumerique() {
    return rareteNumerique;
}

string Genimon::getNom() {
    return nom;
}

int Genimon::getPV() {
    return pv;
}

void Genimon::setPV(int nouveauPV)
{
    pv = nouveauPV;
}

void Genimon::varierPV(int variation)
{
    pv += variation;
    if (pv < 0) pv = 0;
    if (pv > pvMax) pv = pvMax;
}

int Genimon::getDegats() {
    return degats;
}

int Genimon::getFacteurDegats()
{
    return facteurDegats;
}

int Genimon::getFacteurChance()
{
    return facteurChance;
}

int Genimon::getGainBalles()
{
    return gainBalles;
}
