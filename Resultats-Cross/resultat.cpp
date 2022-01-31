/**
* @file Resultats-Cross/ihmresultatscross.cpp
*
* @brief Définition de la classe Resultat
*
* @author Suzie Turlin
*
* @version 0.1
*
*/

#include "resultat.h"
#include "../BaseDeDonnees/basededonnees.h"
#include "coureur.h"

/**
* @brief Resultat
* @fn Resultat::Resultat
*
* @param parent QObject Adresse de l'objet Qt parent
*/
Resultat::Resultat(QObject *parent) : QObject(parent)
{
    BDD = BaseDeDonnees::getInstance();
    if(!BDD->estConnecte())
        BDD->connecter("Resultats-Cross");
    qDebug() << Q_FUNC_INFO << "Etat connection BDD : " << BDD->estConnecte();
}

Resultat::~Resultat()
{
    BaseDeDonnees::detruireInstance();
    qDebug() << Q_FUNC_INFO;
}


