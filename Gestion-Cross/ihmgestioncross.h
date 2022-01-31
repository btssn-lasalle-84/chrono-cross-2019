#ifndef IHMGESTIONCROSS_H
#define IHMGESTIONCROSS_H

/**
* @file Gestion-Cross/ihmgestioncross.h
* @brief Déclaration de la classe IHMGestionCross
* @author Michael Andréo
* @version 1.0
**/

#include <QtWidgets>
#include <QMainWindow>
#include <QDebug>
#include <QDialog>
#include <QLayout>
#include "gestionbdd.h"

#define FENETRE_MANIFESTATION   0
#define FENETRE_COURSE          1
#define FENETRE_COUREUR         2

#define IMAGECHRONOCROSS "../image/icone-chrono-cross.png"

#define TAILLETEXTETITRE            20
#define TAILLETEXTEGESTION          15
#define TAILLETEXTEINSCRIPTION      15
#define TAILLETEXTEBOUTONTITRE      17
#define TAILLETEXTEBOUTONGESTION    13

#define INFO_COUREUR_ID             0
#define INFO_COUREUR_CATEGORIE      1
#define INFO_COUREUR_CLASSE         2
#define INFO_COUREUR_INE            3
#define INFO_COUREUR_NOM            4
#define INFO_COUREUR_PRENOM         5
#define INFO_COUREUR_DATENAISSANCE  6
#define INFO_COUREUR_SEXE           7

#define INFO_COUREURINSCRIT_NOM             0
#define INFO_COUREURINSCRIT_PRENOM          1
#define INFO_COUREURINSCRIT_NUMERODOSSAD    2

#define COLONNE_NOM             0
#define COLONNE_PRENOM          1
#define COLONNE_NUMERODOSSARD   2 // pour le tableau d'inscrit
#define COLONNE_CLASSE          2
#define COLONNE_CATEGORIE       3
#define COLONNE_INE             4
#define COLONNE_DATENAISSANCE   5
#define COLONNE_SEXE            6

class Coureur;

/**
* @class IHMGestionCross
* @brief La fenêtre principale de l'application Gestion-Cross
* @author ANDREO Michaël
* @version 1.0
*/
class IHMGestionCross : public QWidget
{
    Q_OBJECT

private:
    QString etat;
    QString idCoureur;
    GestionBDD *gestionnaireBDD;
    QVector<QString> listeManifestations;
    QVector<QString> listeCourses;
    QVector<QStringList> listeCoureurs;
    QVector<QStringList> listeCoureursInscrit;
    QVector<QStringList> listeClasses;
    QVector<QStringList> listeCategories;
    QVector<QStringList> tableCoureurs;
    int nbLignesTableCoureurs;
    int nbLignesTableInscrit;
    QStringList nomColonnesInscrit;
    QDate dateDefault;

    QStackedWidget *fenetreGestionCross;
    QWidget *fenetreManifestation;
    QWidget *fenetreCourse;
    QWidget *fenetreCoureur;
    QPushButton *bManifestations;
    QPushButton *bCourses;
    QPushButton *bCoureurs;

    // Widgets pour la fenêtre Coureur
    QLabel *labelGestion;
    QLabel *labelInscription;
    QLabel *logoChronoCross;
    QLabel *labelGestionNom;
    QLabel *labelGestionPrenom;
    QLabel *labelGestionDateNaissance;
    QLabel *labelGestionClasse;
    QLabel *labelGestionCategorie;
    QLabel *labelGestionINE;
    QLabel *labelGestionSexe;
    QLabel *labelGestionParticipe;
    QPushButton *bGestionNouveau;
    QPushButton *bCreationConfirmer;
    QPushButton *bCreationAnnuler;
    QPushButton *bGestionModifier;
    QPushButton *bGestionSupprimer;
    QPushButton *bInscrire;
    QDateEdit *deDateNaissance;
    QLineEdit *lineEditNom;
    QLineEdit *lineEditPrenom;
    QComboBox *cbGestionClasse;
    QComboBox *cbGestionCategorie;
    QComboBox *cbGestionParticipe;
    QLineEdit *lineEditINE;
    QRadioButton *rbGestionSexeF;
    QRadioButton *rbGestionSexeM;
    QPushButton *bGestionSupprimerInscription;

    // inscription
    QLabel *labelInscriptionManifestation;
    QComboBox *cbInscriptionListeManifestation;
    QLabel *labelInscriptionCourse;
    QComboBox *cbInscriptionListeCourse;
    QLabel *labelNumeroDossard;
    QLineEdit *lineEditNumeroDossard;
    QTableView *vueTableCoureurs;
    QStandardItemModel *modeleTableCoureurs;
    QStringList nomColonnesCoureur;
    QTableView *vueTableInscrits;
    QStandardItemModel *modeleTableInscrits;
    QLabel *labelMessageInscription;

    QDialog *confirmationDialog;
    QLabel *labelConfirmationDialog;
    QPushButton *bConfirmationDialog;
    QPushButton *bAnnulerDialog;

    void initialiserFenetreCoureur();
    void listerManifestations();
    void listerCourses(QString idManifestation);
    void afficherTable(QString nomTable);
    void viderTableInscrit();
    QString recupererSexeCoureur();
    bool verifierNumeroDossardInscription(QString numeroDossard);
    bool verifierInformationsCreerCoureur(QStringList informations);
    bool verifierInformationsModifierCoureur(QStringList informations);
    void messageErreur(QString message);
    void messageSucces(QString message);
    QVector<int> traiterDateNaissance(QString dateNaissance);
    QStringList recupererChampsGestion();
    void reinitialiserGestionCoureur();

public:
    IHMGestionCross(QWidget *parent = nullptr);
    ~IHMGestionCross();

private slots:
    void gererCoureurs();
    void gererCourses();
    void gererManifestations();
    void selectionnerManifestation(QString nom);
    void selectionnerCourse(QString nom);
    void selectionnerCoureur(QModelIndex index);
    void initialiserConfirmationDialog(QString nomTache);
    void ajouterNouvelleInscription();
    void supprimerInscrition();
    void mettreAJourTableInscrit(QStringList inscription);
    void ajouterNouveauCoureurTable(QStringList informationCoureur);
    void supprimerCoureurTable();
    void modifierCoureurTable();
    void mettreAJourTableCoureur();
    void mettreAJourCBParticipe();
    void passerModeNouveauCoureur();
    void creerCoureur();
    void supprimerCoureur();
    void modifierCoureur();
    void initialiserConfirmationDialog();
    void annulerNouveauCoureur();
    void confirmerDialog();
    void quitterDialog();
    void quitter();

signals:
};

#endif // IHMGESTIONCROSS_H
