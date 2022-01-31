#ifndef IHMRESULTATSCROSS_H
#define IHMRESULTATSCROSS_H

/**
*
* @file Resultats-Cross/ihmresultatscross.h
*
* @brief Déclaration de la classe IHMResultatsCross
*
* @author Suzie Turlin
*
* @version 0.1
*
*/

#define TAILLETEXTELABEL 20
#define TAILLETEXTEBUTON 20
#define HAUTEUR_TABLEAU 1

#define COLONNE_INE         0
#define COLONNE_NOM         1
#define COLONNE_PRENOM      2
#define COLONNE_CLASSE      3

#define INFO_COUREUR_INE        0
#define INFO_COUREUR_NOM        1
#define INFO_COUREUR_PRENOM     2
#define INFO_COUREUR_CLASSE     3

#include <QtWidgets> /* tous les widgets de Qt5 */
#include <QMainWindow>
#include <QDebug>

class BaseDeDonnees;
class Coureur;
    /**
    *
    * @class IHMResultatsCross
    *
    * @brief La fenêtre principale de l'application Resultats-Cross
    *
    * @author Suzie Turlin
    *
    * @version 0.1
    *
    */
    class IHMResultatsCross : public QWidget
    {

    Q_OBJECT

    private:
        QStringList nomColonnes;
        BaseDeDonnees *BDD; //!< agrégation BaseDeDonnee
        QTableView *vueListeClassement; //!< Tableau classement
        QStandardItemModel *modeleClassement;
        int nbLignesClassement;
        Coureur *coureur; //!< agrégation coureur
        // les widgets
        QComboBox *cblisteCoureurs; //!< Combobox contenant les différentes coureurs dans la base de données

        QLabel *labelClassement;
        QLabel *labelCoureurs;
        //QPushButton *bAjouter; //!< Bouton Ajouter

        // QLabel *labelNomCoureur;
        // QLabel *labelPrenomCoureur;
        // QLabel *labelINECoureur;

        void listeCoureurs();

    public:
        IHMResultatsCross(QWidget *parent = nullptr);
        ~IHMResultatsCross();
        void classerArrivee();


    private slots:

     void classerArrivee(QStringList classementCoureurs);

};

#endif // IHMRESULTATSCROSS_H




