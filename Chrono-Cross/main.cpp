#include <QApplication>
#include "ihmchronocross.h"

/**
 * @file Chrono-Cross/main.cpp
 *
 * @brief Programme principal Chrono-Cross
 *
 * @details Chronomètre les courses et classe les coureurs à l'arrivée
 *
 * @author ANDREO Michaël <andreo.michael@outlook.fr>
 *
 * @version 1.1
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

    IHMChronoCross w; // instancie la fenêtre principale de l'application
    w.show(); // affiche la fenêtre principale de l'application

    return a.exec(); // exécute l'application
}
