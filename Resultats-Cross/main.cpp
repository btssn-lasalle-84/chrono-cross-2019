#include <QApplication>
#include "ihmresultatscross.h"

/**
 * @file Resultats-Cross/main.cpp
 *
 * @brief Programme principal Resultats-Cross (Raspberry Pi + Écran)
 *
 * @details Affiche en temps-réel le classement à l'arrivée d'une course
 *
 * @author TURLIN Suzie <suzie.turlin@gmail.com>
 *
 * @version 0.1
 *
 * @fn main(int argc, char *argv[])
 * @param argc
 * @param argv[]
 * @return int
 *
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    IHMResultatsCross w; // instancie la fenêtre principale de l'application
    w.show(); // affiche la fenêtre principale de l'application

    return a.exec(); // exécute l'application
}
