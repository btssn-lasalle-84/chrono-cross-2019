/**
* @file Gestion-Cross/gestionbdd.cpp
* @brief Définition de la classe GestionBDD
* @author ANDRÉO Michaël
* @version 1.0
*/

#include "gestionbdd.h"

/**
* @brief Constructeur GestionBDD() de la classe GestionBDD
* @fn GestionBDD::GestionBDD()
* @param parent
*/
GestionBDD::GestionBDD(QObject *parent) : QObject(parent)
{
    BDD = BaseDeDonnees::getInstance();
    if(!BDD->estConnecte())
        BDD->connecter("Chrono-Cross");

    qDebug() << Q_FUNC_INFO << "Etat connexion BDD : " << BDD->estConnecte();
}

/**
* @brief Destructeur ~GestionBDD() de la classe GestionBDD()
* @fn GestionBDD::~GestionBDD()
*/
GestionBDD::~GestionBDD()
{
    BaseDeDonnees::detruireInstance();
    qDebug() << Q_FUNC_INFO;
}

QVector<QStringList> GestionBDD::recupererTableBDD(QString nomTable)
{
    table.clear();
    bool etat = BDD->recuperer(QString("SELECT * FROM %1 WHERE 1 ORDER BY INE ASC;").arg(nomTable), table);
    qDebug() << Q_FUNC_INFO << etat;
    return table;
}

QVector<QStringList>GestionBDD::recupererListeCoureursInscrit(QString nomCourse)
{
    QString idCourse;
    bool etat = BDD->recuperer(QString("SELECT idCourse FROM Course WHERE Nom = '%1'").arg(nomCourse), idCourse);

    QVector<QStringList> liste;
    etat = BDD->recuperer(QString("SELECT Coureur.Nom, Coureur.Prenom, Inscrit.NumeroDossard FROM `Inscrit` JOIN Coureur ON Inscrit.idCoureur=Coureur.idCoureur WHERE Inscrit.idCourse = '%1' ORDER BY Inscrit.NumeroDossard ASC;").arg(idCourse), liste);
    qDebug() << Q_FUNC_INFO << etat;
    return liste;
}

QVector<QString> GestionBDD::recupererListeManifestationsInscription(QString INE)
{
    QVector<QString> manifestationInscrit;
    QVector<QString> manifestationNonInscrit;
    bool etat = BDD->recuperer(QString("SELECT Manifestation.Nom FROM `Manifestation` JOIN Course ON Manifestation.idManifestation=Course.idManifestation JOIN Inscrit ON Course.idCourse=Inscrit.idCourse JOIN Coureur ON Inscrit.idCoureur=Coureur.idCoureur WHERE INE = '%1';").arg(INE), manifestationInscrit);

    int nbManifestations = manifestationInscrit.size();
    qDebug() << Q_FUNC_INFO << etat << manifestationInscrit;

    if(etat)
    {
        QString nbManifestationsTotales;
        etat = BDD->recuperer("SELECT COUNT(*) FROM Manifestation;", nbManifestationsTotales);
        if(etat)
        {
            if(QString::number(nbManifestations) == nbManifestationsTotales)
            { // le coureur est inscrit à toutes les courses
                manifestationNonInscrit << "Inscrit(e) à toute les courses disponibles";
                return manifestationNonInscrit;
            }
            else if(nbManifestations == 0)
            { // le coureur n'est inscrit à aucune course
                etat = BDD->recuperer("SELECT Nom FROM Manifestation;",manifestationNonInscrit);
                qDebug()<< Q_FUNC_INFO << manifestationNonInscrit;
                return manifestationNonInscrit;
            }
            else
            { // le coureur est inscrit à au moins une course mais pas toute
                for(int i = 0; i < nbManifestations; i += 1)
                {
                etat = BDD->recuperer(QString("SELECT Nom FROM Manifestation WHERE Nom!='%1' ORDER BY Date ASC").arg(manifestationInscrit[i]), manifestationNonInscrit);
                qDebug()<< Q_FUNC_INFO << manifestationNonInscrit;
                }
                return manifestationNonInscrit;
            }
        }
        else
        {
            qDebug() << Q_FUNC_INFO << "ERREUR";
            return manifestationNonInscrit;
        }
    }
    else
    {
        qDebug() << Q_FUNC_INFO << "ERREUR";
        return manifestationNonInscrit;
    }
}

QVector<QString> GestionBDD::recupererListeCoursesInscription(QString nom, QString sexe)
{
    QVector<QString> listeCourses;
    bool etat = BDD->recuperer(QString("SELECT Course.Nom FROM `Course` JOIN Manifestation ON Manifestation.idManifestation=Course.idManifestation WHERE Manifestation.Nom = '%1' AND Course.Nom LIKE '%%2' ORDER BY HeureDepart ASC;").arg(nom).arg(sexe), listeCourses);
    if(etat)
        return listeCourses;
    else
    {
        qDebug() << Q_FUNC_INFO << "ERREUR";
        return listeCourses;
    }
}

QStringList GestionBDD::recupererListeCoursesGestion(QString INE)
{
    QVector<QString> idCourses;
    QStringList nomCourses;
    bool etat = BDD->recuperer(QString("SELECT `Course`.idCourse FROM `Course` JOIN `Inscrit` ON `Course`.idCourse=`Inscrit`.idCourse JOIN `Coureur` ON `Inscrit`.idCoureur=`Coureur`.idCoureur WHERE INE='%1';").arg(INE), idCourses);
    int nbId = idCourses.size();
    qDebug() << Q_FUNC_INFO << etat << "nbID : " << nbId << "IDs : " << idCourses;

    for(int i = 0; i < nbId; i += 1)
    {
        qDebug() << idCourses[i];
        etat = BDD->recuperer(QString("SELECT Nom FROM Course WHERE idCourse = '%1';").arg(idCourses[i]), nomCourses);
    }
    qDebug() << Q_FUNC_INFO << nomCourses;
    return nomCourses;
}

QString GestionBDD::recupererCatergorieCoureur(QString idCategorie)
{
    QString id;
    bool etat = BDD->recuperer(QString("SELECT Nom FROM Categorie WHERE idCategorie = %1;").arg(idCategorie), id);
    if(etat)
        return id;
    else
    {
        qDebug() << Q_FUNC_INFO << "ERREUR";
        return id;
    }
}

QString GestionBDD::recupererClasseCoureur(QString idClasse)
{
    QString id;
    bool etat = BDD->recuperer(QString("SELECT Nom FROM Classe WHERE idClasse = %1;").arg(idClasse), id);
    if(etat)
        return id;
    else
    {
        qDebug() << Q_FUNC_INFO << "ERREUR";
        return id;
    }
}

QString GestionBDD::recupererInformation(QString information, QString nomTable, QString nomEnregistrement)
{
    bool etat = BDD->recuperer(QString("SELECT %1 FROM %2 WHERE %3;").arg(information).arg(nomTable).arg(nomEnregistrement), information);
    if(etat)
        return information;
    else
    {
        qDebug() << Q_FUNC_INFO << "ERREUR";
        return information;
    }
}

QVector<QString> GestionBDD::recupererCategoriesCreation()
{
    QVector<QString> categories;
    bool etat = BDD->recuperer("SELECT DISTINCT Nom FROM Categorie WHERE 1;", categories);
    if(etat)
    {
        return categories;
    }
    else
    {
        qDebug() << Q_FUNC_INFO << "ERREUR";
        return categories;
    }
}

QVector<QString> GestionBDD::recupererClassesCreation()
{
    QVector<QString> classes;
    bool etat = BDD->recuperer("SELECT DISTINCT Nom FROM Classe;", classes);
    if(etat)
    {
        return classes;
    }
    else
    {
        qDebug() << Q_FUNC_INFO << "ERREUR";
        return classes;
    }
}

bool GestionBDD::verifierInformation(QString information, QString table)
{ //information [ 0 info ; 1 table ]
    QStringList info;
    bool etat = BDD->recuperer(QString("SELECT * FROM %1 WHERE %2;").arg(table).arg(information), info);
    return etat;
}

bool GestionBDD::verifierDossard(QString dossard)
{
    QStringList coureurs;
    bool etat = BDD->recuperer(QString("SELECT * FROM Inscrit WHERE NumeroDossard = %1;").arg(dossard), coureurs);
    qDebug() << Q_FUNC_INFO << dossard[0];
    if(etat)
        return false;
    else
        return true;
}

void GestionBDD::ajouterNouveauCoureur(QStringList informationsCoureur)
{
    qDebug() << informationsCoureur;
    QStringList informationsCoureurClassement = informationsCoureur;
    // informationsCoureur [ 0 Categorie , 1 classe , 2 INE , 3 nom ,  4 prenom , 5 dateNaissance , 6 sexe ]
    qDebug() << Q_FUNC_INFO << QString("SELECT idCategorie FROM Categorie WHERE Nom = '%1' AND Sexe = '%2';").arg(informationsCoureur[0]).arg(informationsCoureur[6]);

    bool etat = BDD->recuperer(QString("SELECT idCategorie FROM Categorie WHERE Nom = '%1' AND Sexe = '%2';").arg(informationsCoureur[0]).arg(informationsCoureur[6]), informationsCoureur[0]);

    if(etat)
    {
        qDebug() << Q_FUNC_INFO << QString("SELECT idCLasse FROM Classe WHERE Nom = '%1';").arg(informationsCoureur[1]);

        etat = BDD->recuperer(QString("SELECT idCLasse FROM Classe WHERE Nom = '%1';").arg(informationsCoureur[1]),informationsCoureur[1]);
        if(etat)
        {
            qDebug() << Q_FUNC_INFO << QString("INSERT INTO `Coureur`(`idCoureur`, `idCategorie`, `idClasse`, `INE`, `Nom`, `Prenom`, `DateNaissance`, `Sexe`) VALUES (`idCoureur`,%0,%1,'%2','%3','%4','%5','%6')").arg(informationsCoureur[0]).arg(informationsCoureur[1]).arg(informationsCoureur[2]).arg(informationsCoureur[3]).arg(informationsCoureur[4]).arg(informationsCoureur[5]).arg(informationsCoureur[6]);

            etat = BDD->executer(QString("INSERT INTO `Coureur`(`idCoureur`, `idCategorie`, `idClasse`, `INE`, `Nom`, `Prenom`, `DateNaissance`, `Sexe`) VALUES (`idCoureur`,%0,%1,'%2','%3','%4','%5','%6')").arg(informationsCoureur[0]).arg(informationsCoureur[1]).arg(informationsCoureur[2]).arg(informationsCoureur[3]).arg(informationsCoureur[4]).arg(informationsCoureur[5]).arg(informationsCoureur[6]));
            if(etat)
            {
                qDebug() << Q_FUNC_INFO << "Enregistré(e) avec Succées !";
                emit nouveauCoureur(informationsCoureurClassement);
            }
        }
        else
        {
            qDebug() << Q_FUNC_INFO << "ERREUR";
            informationsCoureurClassement.clear();
        }
    }
    else
    {
        qDebug() << Q_FUNC_INFO << "ERREUR";
        informationsCoureurClassement.clear();
    }
}

void GestionBDD::ajouterNouvelInscrit(QStringList inscription)
{
    // inscription [ idCoureur , idCourse , numeroDossard ]
    qDebug() << Q_FUNC_INFO << inscription;
    bool etat = BDD->executer(QString("INSERT INTO `Inscrit`(`idInscrit`, `idCoureur`, `idCourse`, `NumeroDossard`) VALUES (`idInscrit`,'%1','%2','%3')").arg(inscription[0]).arg(inscription[1]).arg(inscription[2]));
    qDebug() << Q_FUNC_INFO << "Ajout : " << etat;
    if(etat)
    {
        QString idCoureur = inscription[0];
        QString dossard = inscription[2];
        inscription.clear();
        etat = BDD->recuperer(QString("SELECT Nom, Prenom FROM Coureur WHERE idCoureur = '%1';").arg(idCoureur), inscription);
        inscription << dossard;
        qDebug() << Q_FUNC_INFO << inscription;
        emit nouvelInscrit(inscription);
    }
}

void GestionBDD::supprimerCoureur(QString INE)
{
    qDebug() << Q_FUNC_INFO << INE;
    QStringList enregistrement;
    QString idCoureur;
    bool etat = BDD->recuperer(QString("SELECT idCoureur FROM Coureur WHERE INE = '%1';").arg(INE), idCoureur);
    qDebug() << Q_FUNC_INFO << idCoureur;
    etat = BDD->executer(QString("DELETE FROM `Coureur` WHERE `Coureur`.`idCoureur` = '%1';").arg(idCoureur));
    qDebug() << Q_FUNC_INFO << "Suppression : " << etat;
    if(etat)
        emit coureurSupprime();

    etat = BDD->recuperer(QString("SELECT * FROM `Coureur` WHERE idCoureur = '%1';").arg(idCoureur), enregistrement);
    qDebug() << Q_FUNC_INFO << enregistrement;
    if(etat)
        qDebug() << Q_FUNC_INFO << "ERREUR";
}

void GestionBDD::supprimerInscription(QString idCoureur, QString idCourse)
{
    qDebug() << Q_FUNC_INFO << idCoureur << idCourse;
    bool etat = BDD->executer(QString("DELETE FROM `Inscrit` WHERE `Inscrit`.`idCoureur` = '%1' AND `Inscrit`.idCourse = '%2';").arg(idCoureur).arg(idCourse));
    if(etat)
    {
        qDebug() << Q_FUNC_INFO << etat;
        emit inscriptionSupprimee();
    }
    else
        qDebug() << Q_FUNC_INFO << "ERREUR";
}

void GestionBDD::modifierCoureur(QStringList enregistrement)
{
    // enregistrement [ 0 Categorie , 1 classe , 2 INE , 3 nom , 4 prenom , 5 dateNaissance , 6 sexe  , 7 idCoureur]

    qDebug() << Q_FUNC_INFO << enregistrement;
    bool etat = BDD->recuperer(QString("SELECT idCategorie FROM Categorie WHERE Nom = '%1';").arg(enregistrement[0]), enregistrement[0]);
    etat = BDD->recuperer(QString("SELECT idClasse FROM Classe WHERE Nom = '%1';").arg(enregistrement[1]), enregistrement[1]);

    etat = BDD->executer(QString("UPDATE `Coureur` SET `idCategorie`='%1',`idClasse`='%2',`INE`='%3',`Nom`='%4',`Prenom`='%5',`DateNaissance`='%6',`Sexe`='%7' WHERE idCoureur = '%8';").arg(enregistrement[0]).arg(enregistrement[1]).arg(enregistrement[2]).arg(enregistrement[3]).arg(enregistrement[4]).arg(enregistrement[5]).arg(enregistrement[6]).arg(enregistrement[7]));
    qDebug() << Q_FUNC_INFO << "Modification : " << etat;
    if(etat)
        emit coureurModifie();
}
