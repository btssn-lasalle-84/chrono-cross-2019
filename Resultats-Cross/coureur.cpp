/**
* @file Resultats-Cross/coureur.cpp
*
* @brief Définition de la classe Coureur
*
* @author Suzie Turlin
*
* @version 0.1
*
*/

#include "coureur.h"
#include "ihmresultatscross.h"
#include "../BaseDeDonnees/basededonnees.h"


/**
* @brief Coureur
*
* @fn Coureur::Coureur
*
* @param parent QObject Adresse de l'objet Qt parent
*/

Coureur::Coureur(QObject *parent) : QObject(parent)
{
    //**TODO BASE DE DONNEE**//

    BDD = BaseDeDonnees::getInstance();
    if(!BDD->estConnecte())
        BDD->connecter("Resultats-Cross");
    qDebug() << Q_FUNC_INFO << "Etat connexion BDD : " << BDD->estConnecte();


}

Coureur::~Coureur()
{

}

QString Coureur::getNom() const
{
    return nom;
}

QString Coureur::getPrenom() const
{
    return prenom;
}

QString Coureur::getClasse() const
{
    return classe;
}

QString Coureur::getINE() const
{
    return INE;
}

/*QStringList Coureur::getListeCoureurs(QString nom, QString prenom, QString classe, QString INE)
{

}
*/

QString Coureur::formulerRequeteSelect(QString renseignements, QString sources, QString conditions)
{
    QString requete = QString("SELECT %1 FROM %2 WHERE %3").arg(renseignements).arg(sources).arg(conditions);
    qDebug() << Q_FUNC_INFO << "Requête select : " << requete;
    return requete;
}

/*QVector<QString> Coureur::getListeCoureurs(QString Coureur)
{
    QString condition = QString("Nom = '%1'").arg(Coureur);
    QString idCoureur;
    QVector<QString> Coureur;

    bool requeteIdCoureur = BDD->recuperer(this->formulerRequeteSelect("idCoureur", "Coureur", condition), idCoureur);
    qDebug() << Q_FUNC_INFO << "Etat requeteIdCoureur : " << requeteIdCoureur << "\t info : " << idCoureur;

    condition = QString("idCoureur = %1").arg(idCoureur);
    bool requeteNomCoureur = BDD->recuperer(this->formulerRequeteSelect("Nom", "Prenom", condition), Coureur);
    qDebug() << Q_FUNC_INFO << "Etat requeteNomCoureur : " << requeteNomCoureur << "\t info : " << Coureur;
}
*/
