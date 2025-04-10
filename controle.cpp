#include "controle.h"
#include "./ui_controle.h"
#include <QVBoxLayout>
#include "mainmenu.h"

#include <QSerialPortInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>


Controle::Controle(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::Controle)
    , stackedWidget(new QStackedWidget(this))
    , serialPort(new QSerialPort(this))
    , sendDataTimer(new QTimer(this))
{
    ui->setupUi(this);

    // Créez les différentes pages
    stackedWidget->addWidget(new MainMenu(this)); // Index 0
    stackedWidget->addWidget(new ChoixJoueur(this)); // Index 1
    stackedWidget->addWidget(new Map(this)); // Index 2
    stackedWidget->addWidget(new Capture(this)); // Index 3
    stackedWidget->addWidget(new Combat(this)); // Index 4
    stackedWidget->addWidget(new Genidex(this)); // Index 5
    stackedWidget->addWidget(new HistoRencontre(this)); // Index 6
    stackedWidget->addWidget(new Commande(this)); // Index 7
    stackedWidget->addWidget(new Regle(this)); // Index 8
    stackedWidget->addWidget(new Pause(this)); // Index 9
    stackedWidget->addWidget(new ChoixAction(this)); // Index 10
    setCentralWidget(stackedWidget);

    choixJoueurMenu = qobject_cast<ChoixJoueur*>(stackedWidget->widget(1));
    mapMenu = qobject_cast<Map*>(stackedWidget->widget(2));
    captureMenu = qobject_cast<Capture*>(stackedWidget->widget(3));
    combatMenu = qobject_cast<Combat*>(stackedWidget->widget(4));
    genidexMenu = qobject_cast<Genidex*>(stackedWidget->widget(5));
    histoRencontreMenu = qobject_cast<HistoRencontre*>(stackedWidget->widget(6));
    commandeMenu = qobject_cast<Commande*>(stackedWidget->widget(7));
    regleMenu = qobject_cast<Regle*>(stackedWidget->widget(8));
    pauseMenu = qobject_cast<Pause*>(stackedWidget->widget(9));
    choixActionMenu = qobject_cast<ChoixAction*>(stackedWidget->widget(10));

    //Permet d'envoyer nom joueur de choixJoueur a Map
    connect(choixJoueurMenu, &ChoixJoueur::sendNomsChoisis, mapMenu, &Map::setNomsChoisis);

    connectToArduino();
}

Controle::~Controle()
{
    if (sendDataTimer) {
        sendDataTimer->stop();
        delete sendDataTimer;
    }

    if (serialPort && serialPort->isOpen()) {
        stopReading();
        serialPort->close();
    }

    delete serialPort;
    delete ui;
}

void Controle::keyPressEvent(QKeyEvent* event) {

    if (stackedWidget->currentIndex() == 0) // Menu Main
    {
        switch (event->key()) {
        case Qt::Key_1:
            changeMenu(1); // Aller à ChoixJoueur
            break;
        case Qt::Key_2:
            changeMenu(7); // Aller à Commande
            break;
        case Qt::Key_3:
            changeMenu(8); // Aller à Regle
            break;
        case Qt::Key_4:
            QApplication::quit(); // Quitter
            break;
        default:
            QMainWindow::keyPressEvent(event);
        }
    }
    else if (stackedWidget->currentIndex() == 1) // Menu ChoixJoueur
    {
        if (event->key() == Qt::Key_1 || event->key() == Qt::Key_2 || event->key() == Qt::Key_Tab) {
            emit sendKeyPress(event->key());
        }
        else {
            QMainWindow::keyPressEvent(event); // Comportement par défaut
        }

    }
    else if (stackedWidget->currentIndex() == 2) // Menu Map
    {
        if (event->key() == Qt::Key_1 || event->key() == Qt::Key_2 || event->key() == Qt::Key_3 || event->key() == Qt::Key_4
            || event->key() == Qt::Key_W || event->key() == Qt::Key_A || event->key() == Qt::Key_S || event->key() == Qt::Key_D) {
            emit sendKeyPress(event->key());
        }

    }
    else if (stackedWidget->currentIndex() == 3) // Menu Capture
    {
        if (event->key() == Qt::Key_1 || event->key() == Qt::Key_2) {
            emit sendKeyPress(event->key());
        }
    }
    else if (stackedWidget->currentIndex() == 4) // Menu Combat
    {
        if (event->key() == Qt::Key_1 || event->key() == Qt::Key_2 || event->key() == Qt::Key_3 || event->key() == Qt::Key_4) {
            emit sendKeyPress(event->key());
        }
    }
    else if (stackedWidget->currentIndex() == 5) // Menu Genidex
    {
        if (event->key() == Qt::Key_1 || event->key() == Qt::Key_2 || event->key() == Qt::Key_3 || event->key() == Qt::Key_4 || event->key() == Qt::Key_F || event->key() == Qt::Key_A
            || event->key() == Qt::Key_W || event->key() == Qt::Key_D || event->key() == Qt::Key_S) {
            emit sendKeyPress(event->key());
        }

    }
    else if (stackedWidget->currentIndex() == 6) // Menu HistoRencontre
    {
        if (event->key() == Qt::Key_4) {
            emit sendKeyPress(event->key());
        }

    }
    else if (stackedWidget->currentIndex() == 7) // Menu Commande
    {
        if (event->key() == Qt::Key_4 || event->key() == Qt::Key_H || event->key() == Qt::Key_A
            || event->key() == Qt::Key_W || event->key() == Qt::Key_D || event->key() == Qt::Key_S) {
            emit sendKeyPress(event->key());
        }

    }
    else if (stackedWidget->currentIndex() == 8) // Menu Regle
    {
        if (event->key() == Qt::Key_4) {
            emit sendKeyPress(event->key());
        }

    }
    else if (stackedWidget->currentIndex() == 9) // Menu Pause
    {
        if (event->key() == Qt::Key_1 || event->key() == Qt::Key_2 || event->key() == Qt::Key_3 || event->key() == Qt::Key_4) {
            emit sendKeyPress(event->key());
        }

    }
    else if (stackedWidget->currentIndex() == 10) // Menu ChoixAction
    {
        if (event->key() == Qt::Key_1 || event->key() == Qt::Key_2 || event->key() == Qt::Key_3) {
            emit sendKeyPress(event->key());
        }
    }
}

void Controle::changeMenu(int index)
{
    JOYSTICK = 0;
    BOUTTONS = 0;
    ACCELEROMETRE = 0;
    MUONS = 0;

    if (index >= 0 && index < stackedWidget->count()) {
        stackedWidget->setCurrentIndex(index);
    }

    // Deconnecter les liens entres menu avant d'en faire d'autres
    disconnect(this, &Controle::sendKeyPress, choixJoueurMenu, &ChoixJoueur::handleKeyPress);
    disconnect(choixJoueurMenu, &ChoixJoueur::requestMenuChange, this, &Controle::changeMenu);
    disconnect(this, &Controle::sendKeyPress, mapMenu, &Map::handleKeyPress);
    disconnect(mapMenu, &Map::requestMenuChange, this, &Controle::changeMenu);
    disconnect(mapMenu, &Map::sendInfos, choixActionMenu, &ChoixAction::afficherInfoGenimon);
    disconnect(mapMenu, &Map::sendHistorique, histoRencontreMenu, &HistoRencontre::ecrireHistorique);
    disconnect(mapMenu, &Map::sendGenidex, genidexMenu, &Genidex::setGenidex);
    disconnect(this, &Controle::sendKeyPress, captureMenu, &Capture::handleKeyPress);
    disconnect(captureMenu, &Capture::requestMenuChange, this, &Controle::changeMenu);
    disconnect(this, &Controle::sendKeyPress, combatMenu, &Combat::handleKeyPress);
    disconnect(combatMenu, &Combat::requestMenuChange, this, &Controle::changeMenu);
    disconnect(this, &Controle::sendKeyPress, genidexMenu, &Genidex::handleKeyPress);
    disconnect(genidexMenu, &Genidex::requestMenuChange, this, &Controle::changeMenu);
    disconnect(genidexMenu, &Genidex::sendInfos, combatMenu, &Combat::recevoirInfos);
    disconnect(this, &Controle::sendKeyPress, histoRencontreMenu, &HistoRencontre::handleKeyPress);
    disconnect(histoRencontreMenu, &HistoRencontre::requestMenuChange, this, &Controle::changeMenu);
    disconnect(this, &Controle::sendKeyPress, commandeMenu, &Commande::handleKeyPress);
    disconnect(commandeMenu, &Commande::requestMenuChange, this, &Controle::changeMenu);
    disconnect(this, &Controle::sendKeyPress, regleMenu, &Regle::handleKeyPress);
    disconnect(regleMenu, &Regle::requestMenuChange, this, &Controle::changeMenu);
    disconnect(this, &Controle::sendKeyPress, pauseMenu, &Pause::handleKeyPress);
    disconnect(pauseMenu, &Pause::requestMenuChange, this, &Controle::changeMenu);
    disconnect(pauseMenu, &Pause::mode5a8, mapMenu, &Map::gererMode5a8);
    disconnect(this, &Controle::sendKeyPress, choixActionMenu, &ChoixAction::handleKeyPress);
    disconnect(choixActionMenu, &ChoixAction::requestMenuChange, this, &Controle::changeMenu);
    disconnect(choixActionMenu, &ChoixAction::sendInfos, captureMenu, &Capture::afficherInfoCapture);
    disconnect(choixActionMenu, &ChoixAction::sendGenidex, genidexMenu, &Genidex::setGenidex);
    disconnect(choixActionMenu, &ChoixAction::debutPreparationCombat, genidexMenu, &Genidex::debuterPreparationCombat);

    disconnect(this, &Controle::sendManetteInput, choixJoueurMenu, &ChoixJoueur::handleArduinoInput);
    disconnect(this, &Controle::sendManetteInput, mapMenu, &Map::handleArduinoInput);
    disconnect(this, &Controle::sendManetteInput, captureMenu, &Capture::handleArduinoInput);
    disconnect(this, &Controle::sendManetteInput, combatMenu, &Combat::handleArduinoInput);
    disconnect(this, &Controle::sendManetteInput, genidexMenu, &Genidex::handleArduinoInput);
    disconnect(this, &Controle::sendManetteInput, histoRencontreMenu, &HistoRencontre::handleArduinoInput);
    disconnect(this, &Controle::sendManetteInput, commandeMenu, &Commande::handleArduinoInput);
    disconnect(this, &Controle::sendManetteInput, regleMenu, &Regle::handleArduinoInput);
    disconnect(this, &Controle::sendManetteInput, pauseMenu, &Pause::handleArduinoInput);
    disconnect(this, &Controle::sendManetteInput, choixActionMenu, &ChoixAction::handleArduinoInput);
    disconnect(mapMenu, &Map::setSegment, this, &Controle::setSegment);
    disconnect(mapMenu, &Map::setMessage, this, &Controle::setMessage);


    // Relier commande clavier et de changement de menu aux autres menus.
    if (index == 1) {
        choixJoueurMenu->updateQuiz();
        connect(this, &Controle::sendKeyPress, choixJoueurMenu, &ChoixJoueur::handleKeyPress);
        connect(choixJoueurMenu, &ChoixJoueur::requestMenuChange, this, &Controle::changeMenu);
        connect(this, &Controle::sendManetteInput, choixJoueurMenu, &ChoixJoueur::handleArduinoInput);
    }
    else if (index == 2) {
        mapMenu->demarrerMenu();
        connect(this, &Controle::sendKeyPress, mapMenu, &Map::handleKeyPress);
        connect(mapMenu, &Map::requestMenuChange, this, &Controle::changeMenu);
        connect(mapMenu, &Map::sendInfos, choixActionMenu, &ChoixAction::afficherInfoGenimon);
        connect(mapMenu, &Map::sendHistorique, histoRencontreMenu, &HistoRencontre::ecrireHistorique);
        connect(mapMenu, &Map::sendGenidex, genidexMenu, &Genidex::setGenidex);
        connect(this, &Controle::sendManetteInput, mapMenu, &Map::handleArduinoInput);
        connect(mapMenu, &Map::setSegment, this, &Controle::setSegment);
        connect(mapMenu, &Map::setMessage, this, &Controle::setMessage);
    }
    else if (index == 3) {
        connect(this, &Controle::sendKeyPress, captureMenu, &Capture::handleKeyPress);
        connect(captureMenu, &Capture::requestMenuChange, this, &Controle::changeMenu);
        connect(this, &Controle::sendManetteInput, captureMenu, &Capture::handleArduinoInput);
    }
    else if (index == 4) {
        connect(this, &Controle::sendKeyPress, combatMenu, &Combat::handleKeyPress);
        connect(combatMenu, &Combat::requestMenuChange, this, &Controle::changeMenu);
        connect(this, &Controle::sendManetteInput, combatMenu, &Combat::handleArduinoInput);
    }
    else if (index == 5) {
        connect(this, &Controle::sendKeyPress, genidexMenu, &Genidex::handleKeyPress);
        connect(genidexMenu, &Genidex::requestMenuChange, this, &Controle::changeMenu);
        connect(genidexMenu, &Genidex::sendInfos, combatMenu, &Combat::recevoirInfos);
        connect(this, &Controle::sendManetteInput, genidexMenu, &Genidex::handleArduinoInput);
    }
    else if (index == 6) {
        connect(this, &Controle::sendKeyPress, histoRencontreMenu, &HistoRencontre::handleKeyPress);
        connect(histoRencontreMenu, &HistoRencontre::requestMenuChange, this, &Controle::changeMenu);
        connect(this, &Controle::sendManetteInput, histoRencontreMenu, &HistoRencontre::handleArduinoInput);
    }
    else if (index == 7) {
        connect(this, &Controle::sendKeyPress, commandeMenu, &Commande::handleKeyPress);
        connect(commandeMenu, &Commande::requestMenuChange, this, &Controle::changeMenu);
        connect(this, &Controle::sendManetteInput, commandeMenu, &Commande::handleArduinoInput);
    }
    else if (index == 8) {
        connect(this, &Controle::sendKeyPress, regleMenu, &Regle::handleKeyPress);
        connect(regleMenu, &Regle::requestMenuChange, this, &Controle::changeMenu);
        connect(this, &Controle::sendManetteInput, regleMenu, &Regle::handleArduinoInput);
    }
    else if (index == 9) {
        connect(this, &Controle::sendKeyPress, pauseMenu, &Pause::handleKeyPress);
        connect(pauseMenu, &Pause::requestMenuChange, this, &Controle::changeMenu);
        connect(pauseMenu, &Pause::reinitialiserJeu, choixJoueurMenu, &ChoixJoueur::initialiserChoixJoueur);
        connect(pauseMenu, &Pause::reinitialiserJeu, mapMenu, &Map::initialiserMap);
        connect(pauseMenu, &Pause::mode5a8, mapMenu, &Map::gererMode5a8);
        connect(this, &Controle::sendManetteInput, pauseMenu, &Pause::handleArduinoInput);
    }
    else if (index == 10) {
        connect(this, &Controle::sendKeyPress, choixActionMenu, &ChoixAction::handleKeyPress);
        connect(choixActionMenu, &ChoixAction::requestMenuChange, this, &Controle::changeMenu);
        connect(choixActionMenu, &ChoixAction::sendInfos, captureMenu, &Capture::afficherInfoCapture);
        connect(choixActionMenu, &ChoixAction::sendGenidex, genidexMenu, &Genidex::setGenidex);
        connect(choixActionMenu, &ChoixAction::debutPreparationCombat, genidexMenu, &Genidex::debuterPreparationCombat);
        connect(this, &Controle::sendManetteInput, choixActionMenu, &ChoixAction::handleArduinoInput);
    }
}


//---------- Communication aruino --------------------------------------------------------------------------

void Controle::connectToArduino() {

    // Vérifiez s'il existe des ports série disponibles
    QList<QSerialPortInfo> availablePorts = QSerialPortInfo::availablePorts();

    if (availablePorts.isEmpty()) {
        // Si aucun port série n'est disponible, affichez un message d'erreur à l'utilisateur
        qDebug() << "Erreur, aucun port série disponible. Assurez-vous que l'Arduino est correctement connecté.";
        return;
    }

    bool connected = false;
    foreach(const QSerialPortInfo & info, availablePorts) {
        serialPort->setPort(info);
        serialPort->setBaudRate(QSerialPort::Baud115200);
        serialPort->setDataBits(QSerialPort::Data8);
        serialPort->setParity(QSerialPort::NoParity);
        serialPort->setStopBits(QSerialPort::OneStop);
        serialPort->setFlowControl(QSerialPort::NoFlowControl);

        if (serialPort->open(QIODevice::ReadWrite)) {
            qDebug() << "Connecté à l'Arduino sur le port" << info.portName();
            connected = true;

            connect(serialPort, &QSerialPort::readyRead, this, [this]() {SendToSerial(MESSAGE, SEGMENT);});
            break;  // Sortir dès que la connexion est établie
        }
        else {
            qDebug() << "Échec de la connexion au port" << info.portName();
        }
    }

    if (!connected) {
        // Si la connexion échoue, affichez un message à l'utilisateur
        qDebug() << "Erreur de connexion, Échec de la connexion à l'Arduino. Vérifiez le câble et réessayez.";
    }
}

void Controle::startReading() {
    // Commence à lire les données série
    if (!serialPort->isOpen()) {
        connectToArduino();
        qDebug() << "Commence à lire les données série";
    }
    else {
        qDebug() << "Communication deja fonctionnelle";
    }
}

void Controle::stopReading() {
    if (serialPort->isOpen()) {
        serialPort->close();
        qDebug() << "Arrete à lire les données série";
    }
}

void Controle::RcvFromSerial() {
    static QByteArray buffer;  // Tampon pour accumuler les données
    QJsonObject jsonObject;

    // Lire les données du port série
    buffer.append(serialPort->readAll());

    // Parcourir le tampon et chercher des messages JSON complets
    while (true) {
        int startIndex = buffer.indexOf('{');  // Cherche le début d'un message JSON
        int endIndex = buffer.indexOf('}');    // Cherche la fin d'un message JSON
        buffer = buffer.trimmed();

        if (startIndex != -1 && endIndex != -1 && endIndex > startIndex) {
            QByteArray jsonData = buffer.mid(startIndex, endIndex - startIndex + 1);  // Extraire le message JSON complet
            buffer.remove(0, endIndex + 1);  // Supprimer ce message du tampon

            // Analyse du JSON
            QJsonDocument doc = QJsonDocument::fromJson(jsonData);
            if (doc.isNull()) {
                qDebug() << "Erreur : Le JSON est mal formé.";
                continue;  // Passer au prochain message si celui-ci est mal formé
            }

            // Traitement du message JSON
            if (doc.isObject()) {
                jsonObject = doc.object();
                //qDebug() << "Données reçues:" << jsonObject;
                // Traitement des données JSON ici
            }
        }
        else {
            break;  // Sortir si aucun message JSON complet n'est trouvé
        }
    }

    if (jsonObject.contains("boutton")) {
        BOUTTONS = jsonObject["boutton"].toInt();
    }
    if (jsonObject.contains("JoyPosition")) {
        JOYSTICK = jsonObject["JoyPosition"].toInt();
    }

    if (jsonObject.contains("AccCountZ")) {
        ACCELEROMETRE = jsonObject["AccCountZ"].toInt();
    }

    if (jsonObject.contains("muons")) {
        MUONS = jsonObject["muons"].toInt();
    }

    if (stackedWidget->currentIndex() == 0) // Menu Main
    {
        switch (BOUTTONS) {
        case 1:
            changeMenu(1); // Aller à ChoixJoueur
            break;
        case 2:
            changeMenu(7); // Aller à Commande
            break;
        case 3:
            changeMenu(8); // Aller à Regle
            break;
        case 4:
            QApplication::quit(); // Quitter
            break;
        default:
            break;
        }
    }

    if (envoi)
    {
        emit sendManetteInput(BOUTTONS, JOYSTICK, ACCELEROMETRE, MUONS);
        envoi = false;
    }
    else
    {
        envoi = true;
    }
}



void Controle::SendToSerial(const QString& message, int segment) {

    if (serialPort->isOpen()) {
        QJsonObject jsonObject;

        if (lastSend == 0) {
            jsonObject["messageLCD"] = message;
            lastSend = 1;
        }
        else if (lastSend == 1) {
            jsonObject["nbSeg"] = segment;
            lastSend = 1;
        }


        // Convertir l'objet JSON en QByteArray
        QJsonDocument doc(jsonObject);
        QByteArray jsonData = doc.toJson(QJsonDocument::Compact);
        // Ajouter un caractère de nouvelle ligne à la fin
        jsonData.append('\n');  // Ajoute le caractère de nouvelle ligne

        //qDebug() << "Octets envoyés au port série (hex) : " << jsonData.toHex();

        // Envoyer le message JSON via le port série
        if (serialPort->isOpen()) {
            serialPort->write(jsonData);
            //qDebug() << "Message envoyé à l'Arduino:" << QString::fromUtf8(jsonData).simplified();
        }
        else {
            qDebug() << "Erreur : Port série non ouvert.";
        }

        // Attendre une réponse de l'Arduino avant de continuer
        serialPort->waitForReadyRead(150);
        RcvFromSerial();
    }

}


void Controle::setSegment(int seg)
{
    SEGMENT = seg;
}

void Controle::setMessage(QString mes)
{
    MESSAGE = mes;
}