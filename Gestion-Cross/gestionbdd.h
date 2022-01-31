#ifndef GESTIONBDD_H
#define GESTIONBDD_H

/**
* @file Gestion-Cross/gestionbdd.h
* @brief Déclaration de la classe GestionBDD
* @author Michael Andréo
* @version 1.0
*/

#include <QObject>
#include <QDebug>
#include "../BaseDeDonnees/basededonnees.h"

/**
* @class GestionBDD
* @brief Déclaration de la classe GestionBDD
* @author ANDREo Michaël
* @version 1.0
*/

class GestionBDD : public QObject
{
    Q_OBJECT

private:
    BaseDeDonnees *BDD;
    QVector<QStringList> table;


public:
    GestionBDD(QObject *parent = nullptr);
    ~GestionBDD();

    QVector<QString> recupererListeManifestationsInscription(QString INE);
    QVector<QString> recupererListeCoursesInscription(QString nom, QString sexe);
    QStringList recupererListeCoursesGestion(QString INE);
    QVector<QStringList> recupererListeCoureursInscrit(QString nomCourse);
    QVector<QStringList> recupererTableBDD(QString table);
    QString recupererCatergorieCoureur(QString idCategorie);
    QString recupererClasseCoureur(QString idClasse);
    QString recupererInformation(QString info, QString nomTable, QString nomEnregistrement);
    QVector<QString> recupererCategoriesCreation();
    QVector<QString> recupererClassesCreation();
    bool verifierCreation(QStringList enregistrement);
    bool verifierInformation(QString information, QString table);
    void ajouterNouveauCoureur(QStringList enregistrement);
    bool verifierModification(QStringList enregistrement);
    void modifierEnregistrement(QStringList enregistrement);
    bool verifierDossard(QString dossard);
    void ajouterNouvelInscrit(QStringList inscription);
    void supprimerCoureur(QString INE);
    void supprimerInscription(QString idInscrit, QString nomCourse);
    void modifierCoureur(QStringList enregistrement);

public slots:

signals:
    void nouvelInscrit(QStringList inscription);
    void nouveauCoureur(QStringList informationsCoureurClassement);
    void coureurSupprime();
    void inscriptionSupprimee();
    void coureurModifie();
};

#endif // GESTIONBDD_H
