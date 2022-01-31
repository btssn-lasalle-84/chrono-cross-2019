#include "ihmresultatscross.h"
#include "../BaseDeDonnees/basededonnees.h"
#include "coureur.h"

/**
*
* @file Resultats-Cross/ihmresultatscross.cpp
*
* @brief Définition de la classe IHMResultatsCross
*
* @author Suzie Turlin
*
* @version 0.1
*
*/

/**
* @brief Constructeur de la fenêtre principale
*
* @fn IHMResultatsCross::IHMResultatsCross
*
* @param parent QObject Adresse de l'objet Qt parent (0 = pas de parent car c'est la fenêtre principale)
*/

IHMResultatsCross::IHMResultatsCross(QWidget *parent) : QWidget(parent)
{
    /**
    * @todo Définir le contenu de l'IHM
    */

    coureur = new Coureur(this);

    BDD = BaseDeDonnees::getInstance();
    if(!BDD->estConnecte())
        BDD->connecter("Resultats-Cross");

    vueListeClassement = new QTableView(this);
    modeleClassement = new QStandardItemModel(1, 4);
    nomColonnes << "Nom" << "Prénom" << "Classe" << "INE";
    modeleClassement->setHorizontalHeaderLabels(nomColonnes);
    vueListeClassement->setModel(modeleClassement);
    vueListeClassement->setEditTriggers(QAbstractItemView::NoEditTriggers);
    vueListeClassement->setFixedSize(this->width(), this->height());

    vueListeClassement->show();

    // les widgets

    // défini la taille du text dans les QPushButtons
    /*QFont texteBouton;
    texteBouton.setPointSize(TAILLETEXTEBUTON);

    bAjouter = new QPushButton(QString::fromUtf8("Démarrer"), this);
    bAjouter->setDefault(false);
    bAjouter->setEnabled(false);
    bAjouter->setFont(texteBouton);*/

   /* cblisteCoureurs = new QComboBox(this);
    cblisteCoureurs->setFixedSize(this->width()*0.66, this->height()*0.08);
    cblisteCoureurs->addItem(("< Séléctionner Coureur >"));*/


    // défini la taille du text des labels
    QFont texteLabel;
    texteLabel.setPointSize(TAILLETEXTELABEL);

    labelClassement = new QLabel(tr("Classement : "), this);
    labelClassement->setFont(texteLabel);
    labelCoureurs = new QLabel(tr("Coureurs : "), this);
    labelCoureurs->setFont(texteLabel);

    QVBoxLayout *classementLayout = new QVBoxLayout;
    classementLayout->addWidget(labelClassement);
    classementLayout->addWidget(vueListeClassement);

    // le positionnement des widgets
    QHBoxLayout *listesLayout = new QHBoxLayout;
    //QHBoxLayout *boutonsLayout = new QHBoxLayout;

    listesLayout->addWidget(cblisteCoureurs);
    listesLayout->addWidget(labelCoureurs);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(listesLayout);

    setLayout(mainLayout);
    setWindowTitle(tr("Résultat-Cross"));
    setContextMenuPolicy(Qt::ActionsContextMenu);


    //boutonsLayout->addWidget(bAjouter);
    //boutonsLayout->setContentsMargins(0, 0, 0, 20); // G H D B

    // Les labels

    // Les connexions

    // connect(bDemarrer, SIGNAL(clicked()), this, SLOT(coureur()));

    showMaximized(); // Fenêtre d'ouverture maximale
}

/**
* @brief Destructeur de la fenêtre principale
*
* @fn IHMResultatsCross::~IHMResultatsCross
*
*/
IHMResultatsCross::~IHMResultatsCross()
{
    BaseDeDonnees::detruireInstance();
    qDebug() << Q_FUNC_INFO;
}


void IHMResultatsCross::classerArrivee(QStringList informationCoureur)
{
    qDebug() << Q_FUNC_INFO << informationCoureur;
    //informationCoureur[Nom, Prenom, Classe, INE]
    // Redimensionner automatiquement la colonne pour occuper l'espace disponible

    vueListeClassement->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    nbLignesClassement = 1 - modeleClassement->rowCount();


    QStandardItem *nom = new QStandardItem(informationCoureur.at(INFO_COUREUR_NOM));
    QStandardItem *prenom = new QStandardItem(informationCoureur.at(INFO_COUREUR_PRENOM));
    QStandardItem *classe = new QStandardItem(informationCoureur.at(INFO_COUREUR_CLASSE));
    QStandardItem *INE = new QStandardItem(informationCoureur.at(INFO_COUREUR_INE));


    modeleClassement->setItem(nbLignesClassement, COLONNE_NOM, nom);
    modeleClassement->setItem(nbLignesClassement, COLONNE_PRENOM, prenom);
    modeleClassement->setItem(nbLignesClassement, COLONNE_CLASSE, classe);
    modeleClassement->setItem(nbLignesClassement, COLONNE_INE, INE);
    nbLignesClassement += 1;
}
/*
void IHMResultatsCross::listeCoureurs()
{
    //QStringList listeCoureurs = coureur->getListeCoureurs();
    int nbCoureurs = listeCoureurs.size();
    qDebug() << Q_FUNC_INFO << nbCoureurs << "\tliste manifestations :\t" << listeCoureurs;
    for(int i = 0; i < nbCoureurs; i += 1)
    {
        cblisteCoureurs->addItem(listeCoureurs[i]);
    }
}
*/
