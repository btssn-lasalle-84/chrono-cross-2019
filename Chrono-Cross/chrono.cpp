/**
*
* @file Chrono-Cross/chrono.cpp
*
* @brief Définition de la classe Chrono
*
* @author Michael Andreo
*
* @version 1.1
*/

#include "chrono.h"
#include "unistd.h"

/**
* @brief Constructeur de la classe Chrono
* @fn Chrono::Chrono
* @param parent QObject Adresse de l'objet Qt parent (0 = pas de parent car c'est la fenêtre principale)
*/
Chrono::Chrono(QObject *parent) : QObject (parent)
{
    port = new QSerialPort(PORT);
    port->setBaudRate(QSerialPort::Baud9600);
    port->setFlowControl(QSerialPort::NoFlowControl);
    port->setParity(QSerialPort::NoParity);
    port->setDataBits(QSerialPort::Data8);
    port->setStopBits(QSerialPort::OneStop);
    port->open(QIODevice::ReadWrite);

    setEtat(ETAT_NONSYNCHRO);

    qDebug() << Q_FUNC_INFO << "Etat port : " << port->isOpen();
}

/**
* @brief Destructeur de la fenêtre principale
* @fn Chrono::~Chrono
*/
Chrono::~Chrono()
{
    port->close();
}

/**
* @brief Méthode reconnecter() de la classe Chrono
* @fn Chrono::reconnecter()
* @details Reconnecter le TAG HEUER
*/
bool Chrono::reconnecter()
{
    if(port->isOpen())
    {
        disconnect(port, SIGNAL(readyRead()), this, SLOT(lireTrame()));
        port->close();
    }
    port->open(QIODevice::ReadWrite);
    qDebug() << Q_FUNC_INFO << "Etat port : " << port->isOpen();
    if(port->isOpen())
    {
        this->creer();
        return true;
    }
    return false;
}

/**
* @brief Méthode decoderTrame() de la classe Chrono
* @fn Chrono::decoderTrame()
* @details Décode les trames émise du TAG HEUER
*/
void Chrono::decoderTrame()
{
    /*
      Liste des trames reçues :
      - "AK X" acquittement avec : X = 'C' accepted, 'F' rejected, 'R' not supported
      - "TS 00:00:00 00/00/01" synchro
      - "&P 003 XX 90 00:00:00 0" paramètre 003 (demande du numéro de course) XX = le numéro de course
      - "TN 1 2     3.71300  365" temps
      - "CL XX" close course XX = le numéro de course terminée
     */

    trame.remove("\r\n");
    qDebug() << Q_FUNC_INFO << "Trame after remove rn:\t" << trame;

    QStringList champsTrame;
    if(trame.startsWith(TRAME_ACQUITTEMENT))
    {
        champsTrame = trame.split(" ", QString::SkipEmptyParts);
        qDebug() << Q_FUNC_INFO << "Trame acquitement :" << champsTrame[1];

        if(champsTrame[1].startsWith("C"))
        {
            //première trame d'acquittement
            if(etat == ETAT_NONSYNCHRO)
            {
                setEtat(ETAT_MODECLOCK);
                emit chronoCreer();
                qDebug() << Q_FUNC_INFO << "AK\tETAT chrono creer! " << etat;
            }
            //deuxieme trame d'acquittement
            else if(etat == ETAT_MODECLOCK)
            {
                setEtat(ETAT_NEWSYNCHRO);
                emit chronoSynchroniser();
                qDebug() << Q_FUNC_INFO << "AK\tETAT Mode clock " << etat;
            }
            //troisieme trame d'acquittement
            else if(etat == ETAT_NEWSYNCHRO)
            {
                setEtat(ETAT_NEWRUN);
                emit classementCree();
                qDebug() << Q_FUNC_INFO << "ETAT NEW SYNCHR " << etat;
            }
            //quatrième trame d'acquittement
            else if(etat == ETAT_NEWRUN)
            {
                setEtat(ETAT_STARTMANUALSYNCHRO);
                emit chronoLance();
                qDebug() << Q_FUNC_INFO << "ETAT NEWRUN " << etat;
            }
            //cinquième trame d'acquittement
            else if(etat == ETAT_STARTMANUALSYNCHRO)
            {
                setEtat(ETAT_CLOSERUN);
                emit courseArretee();
                qDebug() << Q_FUNC_INFO << "ETAT CLOSERUN " << etat;
            }
            else if(etat == ETAT_CLOSERUN)
            {
                setEtat(ETAT_MODEND);
                emit chronoArrete();
                qDebug() << Q_FUNC_INFO << "ETAT MODEND " << etat;
            }
            else if(etat == ETAT_MODEND)
            {
                setEtat(ETAT_NONSYNCHRO);
                emit chronoRecommence();
            }
        }
    }
    else if(trame.startsWith(TRAME_TEMPS))
    {
        /*
            Time (TN) : TN SSSS CC HH:MM:SS.FFFFF DDDDD

        S = Sequential number (0 - 9999) -> ordre arrivée
        C = Channel number (1 - 99) in case of manual entry (M1 - M4) -> numéro cellule détection (1 = départ et 2 = arrivée)
        H = Hours (0 - 23)
        M = Minutes (0 - 59)
        S = Seconds (0 - 59)
        F = decimal part (0 - 99999)
        D = Days (0 - 32767) counting from 01.01.2000 -> non utilisé

        "TN", "1", "1", "4.30700", "365	05FE"
        "TN         1  1        4.30700   365"
        */

        champsTrame = trame.split(" ", QString::SkipEmptyParts);
        qDebug() << Q_FUNC_INFO << "Trame TN" << champsTrame;
        emit nouvelleArrivee(champsTrame[CHAMPS_TRAME_TEMPS]);
    }
    else if(trame.startsWith(TRAME_COURSE_TERMINEE))
    {
        /*
            Closing of a Run (CL) : CL RR
            R = Run number (1 - 99)

            "CL 06	0115"
         */
        champsTrame = trame.split(" ", QString::SkipEmptyParts);
        qDebug() << Q_FUNC_INFO << "Trame CL" << champsTrame;
        QStringList champs = trame.split("\t");
        champsTrame = champs.at(0).split(" ", QString::SkipEmptyParts);
        qDebug() << Q_FUNC_INFO << "Run number" << champsTrame.at(1);
    }
    else if(etat == ETAT_NONSYNCHRO)
    {
        qDebug() << Q_FUNC_INFO << "Etat synchronisation : " << etat;
        this->reconnecter();
    }
}

/**
* @brief Méthode creer() de la classe Chrono
* @fn Chrono::creer()
* @details Si le port est ouvert on écrit la trame MODECLOCK
*/
void Chrono::creer()
{
    if(port->isOpen())
    {
        connect(port, SIGNAL(readyRead()), this, SLOT(lireTrame()));
        qDebug() << Q_FUNC_INFO << "MODECLOCK";
        trame = MODECLOCK;
        qDebug() << Q_FUNC_INFO << "trame émise" << trame;
        port->write(trame.toLatin1());
    }
}

/**
* @brief Méthode synchroniser() de la classe Chrono
* @fn Chrono::synchroniser
* @details Si le port est ouvert on écrit la trame NEWSYNCHRO
*/
bool Chrono::synchroniser()
{
    if(!port->isOpen())
        return false;
    qDebug() << Q_FUNC_INFO << "NEWSYNCHRO";
    trame = NEWSYNCHRO;
    int nb = int(port->write(trame.toLatin1()));
    port->waitForReadyRead(TIMEOUT);
    if(nb > 0)
        return true;
    else
        return false;
}

/**
* @brief Méthode creerClassement() de la classe Chrono
* @fn Chrono::creerClassement
* @details Si le port est ouvert on écrit la trame NEWRUN
*/
bool Chrono::creerClassement()
{
    if(!port->isOpen())
        return false;
    qDebug() << Q_FUNC_INFO << "NEWRUN";
    trame = NEWRUN;
    int nb = int(port->write(trame.toLatin1()));
    if(nb > 0)
        return true;
    else
        return false;
}

/**
* @brief Méthode demarrer() de la classe Chrono
* @fn Chrono::demarrer()
* @details Si le port est ouvert on écrit la trame STARTMANUALSYNCHRO
*/
bool Chrono::demarrer()
{
    if(!port->isOpen())
        return false;
    qDebug() << Q_FUNC_INFO << "STARTMANUALSYNCHRO";
    trame = STARTMANUALSYNCHRO;
    qDebug() << Q_FUNC_INFO << "trame" << trame;
    int nb = int(port->write(trame.toLatin1()));
    if(nb > 0)
        return true;
    else
        return false;
}

/**
* @brief Méthode arreterCourse() de la classe Chrono
* @fn Chrono::arreterCourse()
* @details Si le port est ouvert on écrit la trame CLOSERUN
*/
bool Chrono::arreterCourse()
{
    if(!port->isOpen())
        return false;
    qDebug() << Q_FUNC_INFO << "CLOSERUN";
    trame = CLOSERUN;
    qDebug() << Q_FUNC_INFO << "trame" << trame;
    int nb = int(port->write(trame.toLatin1()));
    if(nb > 0)
        return true;
    else
        return false;
}

/**
* @brief Méthode arreterChrono() de la classe Chrono
* @fn Chrono::arreterChrono()
* @details Si le port est ouvert on écrit la trame MODEND
* @return bool
*/
bool Chrono::arreterChrono()
{
    if(!port->isOpen())
        return false;
    qDebug() << Q_FUNC_INFO << "MODEND";
    trame = MODEND;
    qDebug() << Q_FUNC_INFO << "trame" << trame;
    int nb = int(port->write(trame.toLatin1()));
    if(nb > 0)
        return true;
    else
        return false;
}

/**
* @brief Méthode estConnecte() de la classe Chrono
* @fn Chrono::estConnecte()
* @details Retourne l'état de connexion avec le TAG HEUER
*/
bool Chrono::estConnecte()
{
    port->waitForReadyRead(950);
    return port->isOpen();
}

/**
* @brief Méthode lireTrame() de la classe Chrono
* @fn Chrono::lireTrame()
* @details Lit ligne par ligne les trames du TAG HEUER
*/
void Chrono::lireTrame()
{
    while(port->canReadLine())
    {
        donnees += port->readAll();
        usleep(TIMEOUT);
    }

    if(donnees.contains("\r\n"))
    {
        trame = QString(donnees.data());
        decoderTrame();
        donnees.clear();
    }
}

/**
 * @brief Méthode setEtat() de la classe Chrono
 * @fn Chrono::setEtat()
 * @details Permet de changer l'état du chrono
 * @param nouvelEtat
 * @return Retourne l'état du chrono
 */
QString Chrono::setEtat(QString nouvelEtat)
{
    etat = nouvelEtat;
    return etat;
}
