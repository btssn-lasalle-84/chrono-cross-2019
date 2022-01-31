#ifndef IHMCHRONOCROSS_H
#define IHMCHRONOCROSS_H

/**
* @file Chrono-Cross/ihmchronocross.h
* @brief Déclaration de la classe IHMChronoCross
* @author Michael Andréo
* @version 1.1
**/

#include <QtWidgets> /* tous les widgets de Qt5 */
#include <QMainWindow>
#include <QDebug>
#include <QTimer>
#include <QDialog>

#define TAILLETEXTELABEL        20
#define TAILLETEXTEBUTON        20
#define TAILLETEXTELISTE        16
#define TAILLETEXTEINFO         18
#define TAILLETEXTESUPPRIMER    15
#define TAILLETEXTECLASSEMENT   12

#define IMAGECHRONOCROSS "../image/icone-chrono-cross.png"
#define CLASSEMENT       0
#define TEMPS            1
#define DOSSARD          2

#define COLONNE_TEMPS       0
#define COLONNE_DOSSARD     1
#define COLONNE_NOM         2
#define COLONNE_PRENOM      3
#define COLONNE_CLASSE      4

#define INFO_COUREUR_TEMPS      0
#define INFO_COUREUR_DOSSARD    1
#define INFO_COUREUR_NOM        2
#define INFO_COUREUR_PRENOM     3
#define INFO_COUREUR_CLASSE     4

#define NUMERO_DOSSARD_INVALIDE         0
#define DOSSARD_VALIDE_COURSE_INVALIDE  1
#define DOSSARD_DEJA_ARRIVE             2
#define DOSSARD_VALIDE                  3

class BaseDeDonnees;
class Course;

/**
  * @class IHMChronoCross
  * @brief La fenêtre principale de l'application Chrono-Cross
  * @author ANDREO Michaël
  * @version 1.1
  */
class IHMChronoCross : public QWidget
{
    Q_OBJECT

private:

    Course *course; //!< agrégation d'une course
    QVector<QStringList> courses; //!< liste des courses pour une manifestation
    QStringList classement; //!< Liste du classement pour une course
    QStringList nomColonnes; //!< Liste de nom des colonnes du classement "Temps, dossard, nom..."
    QStringList tempsArriveesNonClassees; //!< Liste des arrivées non classés
    int nbArriveesNonClassees;
    int nbArriveesClassees;
    int nbCoureurArrive; //!< Nombre de coureurs arrivés
    int nbLignesClassement; //!< nombre de lignes du classement

    bool acquitement;

    long m_valeur; //!< Valeur du chrono
    
    // les widgets
    QComboBox *cbListeManifestations; //!< Combobox contenant les différentes manifesations de la base de donnée
    QComboBox *cbListeCourses; //!< Combobox contenant les différentes course de la base de donnée

    QLabel *labelManifestations; //!< Label contenant le QString "Manifestations : " devant cbListeManifestations
    QLabel *labelListeCourses; //!< Label contenant le QString "Courses : " devant cbListeCourses
    QLabel *labelNumeroDossard; //!< Label contenant le QString "N° dossard : "
    QLabel *labelZoneCourse; //!< Label contenant le texte : Course symbolisant la zone course
    QLabel *labelZoneClassement; //!< Label contenant le texte : Classement symbolisant la zone classement
    QLabel *labelZoneChrono; //!< Label contenant le texte "Chrono : " symbolisant la zone chrono
    QLabel *logoChronoCross; //!< Label contenant l'image du logo Chrono-Cross
    QLabel *labelEtatChrono; //!< Label contenant le texte "Etat : " pour la led chrono
    QLabel *labelLedChrono; //!< Label contenant la LED (état vert, orange ou rouge) qui représente l'état de la connexion avec le TAG HEUER

    QLabel *labelLedCourse; //!< Label contenant la LED (état vert, orange ou rouge) qui représente l'état du chrono, si il est prêt à faire une course
    QLabel *labelEtatCourse; //!< Label contenant le texte "Etat : " pour la led course
    QLabel *labelZoneArrivees; //!< Label contenant le QString "Arrivées : " symbolisant la zone des arrivées non classées
    QLabel *labelMessageDossard; //!< Label du message d'érreur pour les numéros de dossards
    QLabel *labelMessageSupprimer; //!< label contenant le message d'information pour supprimer le premier temps non classée

    //zone information sur les coureurs d'une course
    QLabel *labelNbInscrit; //!< Label contentant le texte "Nombre d'inscrit :"
    QLabel *labelNbArriveesNonClassees ; //!< Label contentant le texte "Nombre d'arrivées non classées :"
    QLabel *labelNbArriveesClassees; //!< Label contentant le texte "Nombre d'arrivées classées :"
    QLCDNumber *QLCDNbArriveesNonClassees; //!< QLCD qui affiche le nombre d'arrivées non classées
    QLCDNumber *QLCDNbArriveesClassees; //!< QLCD qui affiche le nombre d'arrivées classées

    //zone information sur la course
    QLabel *labelNomCourse;
    QLabel *labelDistanceCourse;
    QLabel *labelHeureCourse;

    QLCDNumber *QLCDChrono; //!< QLCD contenant le chrono

    QLineEdit *lineEditNumeroDossard; //!< LineEdit qui permet de rentrer un numéro de dossard

    QPushButton *bSynchroniser; //!< Bouton Synchroniser
    QPushButton *bLancer; //!< Bouton Lancer le chronomètre
    QPushButton *bArreter; //!< Bouton Arreter
    QPushButton *bTerminer; //!< Bouton Terminer
    QPushButton *bAssocier; //!< Bouton Associer

    QTableView *vueTableauClassement; //!< Vue en liste classement
    QStandardItemModel *modeleClassement; //!< Model du classement

    QListView *vueListeTempsArriveesNonClassees; //!< Vue en tableau des temps non classés
    QStringListModel *modeleArriveesNonClassees; //!< Model des arrivées non classés

    QTimer *m_timer; //!< Chrono de l'ihm

    QDialog *confirmationDialog;

    QLabel *labelConfirmationDialog;
    QPushButton *bConfirmationDialog;
    QPushButton *bAnnulerDialog;

    void listerManifestations();
    bool verifierCourseSelectionnee(QString courseSelectionnee);
    void setRouge(QLabel *label);
    void setVert(QLabel *label);
    void setOrange(QLabel *label);
    void reinitialiserInfoCourse();
    void reinitialiserClassement();
    void initialiserConfirmationDialog();
    void personnaliserAffichageArrivee(int nbLignesClassement);
    long getSeconde();
    long getMinute();
    long getHeure();
    void update();


public:
    IHMChronoCross(QWidget *parent = nullptr);
    ~IHMChronoCross();

private slots:
    void listerCourses(QString manifestation);
    void creerCourse(QString nomCourse);
    void initialiserCourse();
    void preparerCourse();
    void parer();
    void lancerCourse();
    void lancerChronoIHM();
    void arreterCourse();
    void arreterChrono();
    void terminerChrono();
    void terminerCourse();
    void commencerNouvelleCourse();

    void ajouterArriveeCoureur(QString tempsArrivee);
    void associerArriveeDossard();
    void classerArrivee(QStringList informationCoureur);

    void quitter();

    void tic();

    void afficherInformationsCourse(QString nomCourse);
    void mettreAJourNbArriveesNonClassees(int nbArrivee);
    void mettreAJourNbArriveesClassees(int nbArrivee);

    void quitterDialog();
    void supprimerPremierTemps();

signals:


};

#endif // IHMCHRONOCROSS_H
