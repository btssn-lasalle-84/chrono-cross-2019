#include "ihmgestioncross.h"
#include <QApplication>

/**
 * @file Gestion-Cross/main.cpp
 *
 * @brief Programme principal Gestion-Cross
 *
 * @details Gère des manifestation de courses de Cross
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
    IHMGestionCross w;
    w.show();

    return a.exec();
}
