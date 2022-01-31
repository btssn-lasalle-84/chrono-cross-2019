#ifndef COURSE_H
#define COURSE_H

/**
* @file Chrono-Cross/course.h
* @brief Déclaration de la classe Course
* @author Michael Andréo
* @version 1.1
*/

#include <QObject>
#include <QDebug>
#include <QDate>
#include "chrono.h"
#include "../BaseDeDonnees/basededonnees.h"

#define INFORMATION_COUREUR_ARRIVEE_CLASSE 4

/**
* @class Course
* @brief Déclaration de la classe Course
* @author Michael Andréo
* @version 1.1
*/

class BaseDeDonnees;
class Chrono;

class Course : public QObject
{
    Q_OBJECT

private:
    BaseDeDonnees *BDD; //!< agrégation BaseDeDonnees
    Chrono *monChrono; //!< association Chrono

    QString idCourse; //!< Identifiant de la course
    QString distance; //!< Distance de la course
    QString heureDepart; //!< L'heure de départ de la course    
    QStringList informationCoureurArrive; //!< Informations d'un coure

    QString formulerRequeteSelect(QString renseignements, QString sources, QString conditions);


public:
    Course(QObject *parent = nullptr);
    ~Course();

    void creerChrono();
    void preparerChrono();
    bool estChronometragePret();
    void chronometrer();
    void arreterClassement();
    void arreterChrono();

    int  verifierDossard(QString dossard);
    QString convertirTemps(QString tempsMS);

    int getNbInscrit(QString course);
    int getDistance(QString course);
    QString getHeure(QString course);
    int getNbArrivee();
    QString getNomCourse(QString dossard);
    void setIdCourse(QString nomCourse);

    void ajouteArriveeBDD(QString dossard, QString tempsArrivee);

    QStringList getListeManifestations();
    QVector<QString> getListeCourses(QString manifestation);

public slots:
    void aChronoCree();
    void aChronoSynchronise();
    void aClassementCree();
    void aCommencee();
    void aClassementArrete();
    void estFinie();
    void recommencerChrono();

    void traiterArriveeCoureur(QString tempsArrivee);
    void getInformationCoureur(QString dossard, QString tempsARrivee);

    bool setEtat(QString etat);

signals:
    void chronoCreer();
    void chronoCoursePret();
    void courseCommence();
    void classementArrete();
    void courseFinie();
    void chronoRecommence();

    void nouveauTempsArrivee(QString tempsArrivee);

    void arriveeAjouteeBDD(QString dossard, QString tempsArrivee);
    void informationCoureurRecuperees(QStringList informationCoureur);
};

#endif // COURSE_H
