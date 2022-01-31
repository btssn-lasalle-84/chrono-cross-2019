#ifndef CHRONO_H
#define CHRONO_H

/**
*
* @file Chrono-Cross/chrono.h
*
* @brief Déclaration de la classe Chrono
*
* @author Michael Andréo
*
* @version 1.1
*
*/

#include <QObject>
#include <QDebug>
#include <QtSerialPort/QSerialPort>

// Port dédié au TAG HEUER
#ifdef Q_OS_WIN
#define PORT                    "COM10"
#else
#define PORT                    "/dev/hl975"
#endif

// Procotole THCOM08
// PC -> TAG HEUER
#define MODECLOCK               "#WP 120 5\t01AF\r\n"
#define NEWSYNCHRO              "#WC 007 02 00:00 01/01/01\t048E\r\n"
#define NEWRUN                  "#WC 002\t014C\r\n"
#define STARTMANUALSYNCHRO      "#WC 008 01\t01D3\r\n"
#define CLOSERUN                "#WC 001\t014B\r\n"
#define MODEND                  "#WP 120 3\t01AD\r\n"

// PC <- TAG HEUER
#define TRAME_ACQUITTEMENT      "AK"
#define TRAME_SYNCHRO           "TS"
#define TRAME_PARAMETRES        "&P"
#define TRAME_TEMPS             "TN"
#define TRAME_COURSE_TERMINEE   "CL"

// etat chrono
#define ETAT_NONSYNCHRO         "NONSYNCHRO"
#define ETAT_MODECLOCK          "MODECLOCK"
#define ETAT_NEWSYNCHRO         "NEWSYNCHRO"
#define ETAT_NEWRUN             "NEWRUN"
#define ETAT_STARTMANUALSYNCHRO "STARTMANUAL"
#define ETAT_CLOSERUN           "CLOSERUN"
#define ETAT_MODEND             "MODEND"

#define CHAMPS_TRAME_TEMPS      3

#define TIMEOUT                 100000 // en ms

/**
* @class Chrono
*
* @brief Déclaration de la classe Chrono
*
* @author Michael Andréo
*
* @version 1.1
*
*/
class Chrono : public QObject
{
    Q_OBJECT

private:

    QSerialPort *port; //!< Port RS232 du TAG HEUER
    QByteArray donnees; //!< Données brutes d'une trame THCOM08
    QString trame; //!< Trame THCOM08
    QString etat; //!< État du chronomètre

    bool reconnecter();
    void decoderTrame();
    QString setEtat(QString nouvelEtat);

public:
    Chrono(QObject *parent = nullptr);
    ~Chrono();

    void creer();
    bool synchroniser();
    bool creerClassement();
    bool demarrer();
    bool arreterCourse();
    bool arreterChrono();
    bool estConnecte();

public slots:
    void lireTrame();

signals:
    void chronoCreer();
    void chronoSynchroniser();
    void classementCree();
    void chronoLance();
    void courseArretee();
    void chronoArrete();
    void chronoRecommence();

    void nouvelleArrivee(QString tempsArrivee);
};

#endif // CHRONO_H
