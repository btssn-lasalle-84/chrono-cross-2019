/**
* @file Gestion-Cross/ihmgestioncross.cpp
* @brief Définition de la classe IHMGestionCross
* @author ANDRÉO Michaël
* @version 1.0
*/

#include<ihmgestioncross.h>

/**
* @brief Constructeur de la fenêtre principale
* @fn IHMGestionCross::IHMGestionCross()
* @param parent
*/
IHMGestionCross::IHMGestionCross(QWidget *parent) : QWidget(parent)
{
    qDebug() << Q_FUNC_INFO;

    gestionnaireBDD = new GestionBDD(this);
    nbLignesTableCoureurs = 0;
    QVector<int> valeurDateDefault;
    valeurDateDefault << 2000 << 01 << 01;
    dateDefault.setDate(valeurDateDefault[0], valeurDateDefault[1], valeurDateDefault[2]);
    qDebug() << Q_FUNC_INFO << dateDefault;

    setStyleSheet(QLatin1String("QWidget\n"
    "{\n"
    "	background-color: white;\n"
    "}\n"
    "QPushButton {\n"
    "    background-color: lightgray;\n"
    "    border-width: 1px;\n"
    "    border-color: black;\n"
    "    border-style: solid;\n"
    "    border-radius: 1;\n"
    "    padding: 5px;\n"
    "    min-width: 9ex;\n"
    "    min-height: 2.5ex;\n"
    "}\n"
    "\n"
    "QPushButton:hover:enabled {\n"
    "   background-color: gray;\n"
    "}\n"
    "\n"
    "QPushButton:pressed {\n"
    "    padding-left: 5px;\n"
    "    padding-top: 5px;\n"
    "    background-color: white;\n"
    "}\n"
    "\n"
    "QPushButton:checked {\n"
    "background-color: white;\n"
    "}\n"
    "QComboBox, QLineEdit {\n"
    "    background-color: white;\n"
    "    selection-color: #0a214c; \n"
    "    selection-background-color: white;\n"
    "    border-width: 1px;\n"
    "    padding: 3px;\n"
    "    border-style: solid;\n"
    "    border-color: gray;\n"
    "    border-radius: 5px;\n"
    "}\n"
    "\n"
    "QLineEdit:focus {\n"
    "    border-width: 2px;\n"
    "    padding: 0px;\n"
    "}\n"
    "\n"
    "QComboBox::item:hover {\n"
    "    background-color: white;\n"
    "}\n"
    ""));

    QFont texteButton;
    texteButton.setPointSize(TAILLETEXTEBOUTONTITRE);

    fenetreGestionCross = new QStackedWidget(this);
    fenetreManifestation = new QWidget(this);
    fenetreCourse = new QWidget(this);
    fenetreCoureur = new QWidget(this);

    fenetreGestionCross->addWidget(fenetreManifestation);
    fenetreGestionCross->addWidget(fenetreCourse);
    fenetreGestionCross->addWidget(fenetreCoureur);

    initialiserFenetreCoureur();

    bManifestations = new QPushButton(QString::fromUtf8("Manifestations"), this);
    bManifestations->setCheckable(true);
    bManifestations->setFont(texteButton);

    bCourses = new QPushButton(QString::fromUtf8("Courses"), this);
    bCourses->setCheckable(true);
    bCourses->setFont(texteButton);

    bCoureurs = new QPushButton(QString::fromUtf8("Coureurs"), this);
    bCoureurs->setCheckable(true);
    bCoureurs->setFont(texteButton);

    logoChronoCross = new QLabel(this);
    QPixmap pixmap_img(IMAGECHRONOCROSS);
    logoChronoCross->setPixmap(pixmap_img);

    QHBoxLayout *hBoutons = new QHBoxLayout;
    QHBoxLayout *hLayoutFenetre = new QHBoxLayout;
    QVBoxLayout *mainLayout = new QVBoxLayout;

    hBoutons->addWidget(bManifestations);
    hBoutons->addWidget(bCourses);
    hBoutons->addWidget(bCoureurs);
    hBoutons->addStretch();
    hBoutons->addWidget(logoChronoCross);
    hBoutons->setContentsMargins(0, 0, 0, 40); // G H D B
    hLayoutFenetre->addWidget(fenetreGestionCross);
    mainLayout->addLayout(hBoutons);
    mainLayout->addLayout(hLayoutFenetre);

    setLayout(mainLayout);
    setWindowTitle("Gestion-Cross");
    setContextMenuPolicy(Qt::ActionsContextMenu);

    QAction *actionQuitter = new QAction("&Quitter", this);
    actionQuitter->setShortcut(QKeySequence::Quit);
    addAction(actionQuitter);

    QAction *actionEntrerPAD = new QAction("&Entrer1", this);
    actionEntrerPAD->setShortcut(QKeySequence(Qt::Key_Enter));
    addAction(actionEntrerPAD);

    QAction *actionEntrerRETURN = new QAction("&Entrer2", this);
    actionEntrerRETURN->setShortcut(QKeySequence(Qt::Key_Return));
    addAction(actionEntrerRETURN);

    //Connect
    connect(actionQuitter, SIGNAL(triggered()), this, SLOT(quitter()));
    connect(actionEntrerPAD, SIGNAL(triggered()), this, SLOT(ajouterNouvelleInscription()));
    connect(actionEntrerRETURN, SIGNAL(triggered()), this, SLOT(ajouterNouvelleInscription()));

    connect(bCoureurs, SIGNAL(clicked()), this, SLOT(gererCoureurs()));
    connect(bCourses, SIGNAL(clicked()), this, SLOT(gererCourses()));
    connect(bManifestations, SIGNAL(clicked()), this, SLOT(gererManifestations()));
    connect(bInscrire, SIGNAL(clicked()), this, SLOT(ajouterNouvelleInscription()));
    connect(bGestionNouveau, SIGNAL(clicked()), this, SLOT(passerModeNouveauCoureur()));
    connect(bCreationConfirmer, SIGNAL(clicked()), this, SLOT(creerCoureur()));
    connect(bCreationAnnuler, SIGNAL(clicked()), this, SLOT(annulerNouveauCoureur()));
    connect(bGestionSupprimer, SIGNAL(clicked()), this, SLOT(supprimerCoureur()));
    connect(bGestionModifier, SIGNAL(clicked()), this, SLOT(modifierCoureur()));
    connect(bGestionSupprimerInscription, SIGNAL(clicked()), this, SLOT(supprimerInscrition()));

    connect(vueTableCoureurs, SIGNAL(clicked(QModelIndex)), this, SLOT(selectionnerCoureur(QModelIndex)));
    connect(cbInscriptionListeManifestation, SIGNAL(currentIndexChanged(QString)), this, SLOT(selectionnerManifestation(QString)));
    connect(cbInscriptionListeCourse, SIGNAL(currentIndexChanged(QString)), this, SLOT(selectionnerCourse(QString)));
    connect(gestionnaireBDD, SIGNAL(nouvelInscrit(QStringList)), this, SLOT(mettreAJourTableInscrit(QStringList)));
    connect(gestionnaireBDD, SIGNAL(nouveauCoureur(QStringList)), this, SLOT(ajouterNouveauCoureurTable(QStringList)));
    connect(gestionnaireBDD, SIGNAL(coureurSupprime()), this, SLOT(supprimerCoureurTable()));
    connect(gestionnaireBDD, SIGNAL(coureurModifie()), this, SLOT(modifierCoureurTable()));
    connect(gestionnaireBDD, SIGNAL(inscriptionSupprimee()), this, SLOT(mettreAJourCBParticipe()));

    setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
    showMaximized();

    gererCoureurs();
}

IHMGestionCross::~IHMGestionCross()
{
    BaseDeDonnees::detruireInstance();
    qDebug() << Q_FUNC_INFO;
}

void IHMGestionCross::initialiserFenetreCoureur()
{
    QFont texteLabelTitre;
    texteLabelTitre.setPointSize(TAILLETEXTETITRE);

    QFont texteLabelGestion;
    texteLabelGestion.setPointSize(TAILLETEXTEGESTION);

    QFont texteLabelInscription;
    texteLabelInscription.setPointSize(TAILLETEXTEINSCRIPTION);

    QFont texteLabelInscriptionMessage;
    texteLabelInscriptionMessage.setPointSize(TAILLETEXTEINSCRIPTION);
    texteLabelInscriptionMessage.setItalic(true);

    QFont texteLabelGestionBouton;
    texteLabelGestionBouton.setPointSize(TAILLETEXTEBOUTONGESTION);

    //Gestion
    labelGestion = new QLabel(QString::fromUtf8("Coureur : "), this);
    labelGestion->setFont(texteLabelTitre);

    labelGestionNom = new QLabel(QString::fromUtf8("Nom : "), this);
    labelGestionNom->setFont(texteLabelGestion);
    lineEditNom = new QLineEdit(this);
    lineEditNom->setFont(texteLabelGestion);
    lineEditNom->setEnabled(false);

    labelGestionPrenom = new QLabel(QString::fromUtf8("Prénom : "), this);
    labelGestionPrenom->setFont(texteLabelGestion);
    lineEditPrenom = new QLineEdit(this);
    lineEditPrenom->setFont(texteLabelGestion);
    lineEditPrenom->setEnabled(false);

    labelGestionDateNaissance = new QLabel(QString::fromUtf8("Date de Naissance : "), this);
    labelGestionDateNaissance->setFont(texteLabelGestion);
    deDateNaissance = new QDateEdit(this);
    deDateNaissance->setFont(texteLabelGestion);
    deDateNaissance->setEnabled(false);

    labelGestionClasse = new QLabel(QString::fromUtf8("Classe : "), this);
    labelGestionClasse->setFont(texteLabelGestion);
    cbGestionClasse = new QComboBox(this);
    cbGestionClasse->setFont(texteLabelGestion);
    cbGestionClasse->setStyleSheet("text-align : center");
    cbGestionClasse->addItem("< Classes >");
    cbGestionClasse->setEnabled(false);

    labelGestionCategorie = new QLabel(QString::fromUtf8("Catégorie : "), this);
    labelGestionCategorie->setFont(texteLabelGestion);
    cbGestionCategorie = new QComboBox(this);
    cbGestionCategorie->addItem("< Catégories >");
    cbGestionCategorie->setFont(texteLabelGestion);
    cbGestionCategorie->setEnabled(false);

    labelGestionINE = new QLabel(QString::fromUtf8("INE : "), this);
    labelGestionINE->setFont(texteLabelGestion);
    lineEditINE = new QLineEdit(this);
    lineEditINE->setFont(texteLabelGestion);
    lineEditINE->setEnabled(false);

    labelGestionSexe = new QLabel(QString::fromUtf8("Sexe : "), this);
    labelGestionSexe->setFont(texteLabelGestion);
    rbGestionSexeF = new QRadioButton("F", this);
    rbGestionSexeF->setFont(texteLabelGestion);
    rbGestionSexeF->setEnabled(false);
    rbGestionSexeM = new QRadioButton("M", this);
    rbGestionSexeM->setFont(texteLabelGestion);
    rbGestionSexeM->setEnabled(false);

    labelGestionParticipe = new QLabel(QString::fromUtf8("Participe à :"), this);
    labelGestionParticipe->setFont(texteLabelGestion);
    cbGestionParticipe = new QComboBox(this);
    cbGestionParticipe->setFont(texteLabelGestion);
    cbGestionParticipe->setEnabled(false);
    bGestionSupprimerInscription = new QPushButton(QString::fromUtf8("Supprimer l'Inscription"), this);
    bGestionSupprimerInscription->setFont(texteLabelGestionBouton);
    bGestionSupprimerInscription->setEnabled(false);

    //Creation
    bCreationConfirmer = new QPushButton(QString::fromUtf8("Confirmer"), this);
    bCreationConfirmer->setFont(texteLabelGestionBouton);
    bCreationConfirmer->setVisible(false);
    bCreationAnnuler = new QPushButton(QString::fromUtf8("Annuler"), this);
    bCreationAnnuler->setFont(texteLabelGestionBouton);
    bCreationAnnuler->setVisible(false);

    //Inscription
    labelInscription = new QLabel(QString::fromUtf8("Inscription : "), this);
    labelInscription->setFont(texteLabelTitre);

    labelInscriptionManifestation = new QLabel(QString::fromUtf8("Manifestation : "), this);
    labelInscriptionManifestation->setFont(texteLabelInscription);
    cbInscriptionListeManifestation = new QComboBox(this);
    cbInscriptionListeManifestation->addItem("< Liste des manifestations >");
    cbInscriptionListeManifestation->setFont(texteLabelInscription);
    cbInscriptionListeManifestation->setEnabled(false);

    bInscrire = new QPushButton(QString::fromUtf8("Inscrire"), this);
    bInscrire->setEnabled(false);
    bInscrire->setFont(texteLabelGestionBouton);

    labelInscriptionCourse = new QLabel(QString::fromUtf8("Course : "), this);
    labelInscriptionCourse->setFont(texteLabelInscription);
    cbInscriptionListeCourse = new QComboBox(this);
    cbInscriptionListeCourse->addItem("< Liste des courses >");
    cbInscriptionListeCourse->setFont(texteLabelInscription);
    cbInscriptionListeCourse->setEnabled(false);

    labelNumeroDossard = new QLabel(QString::fromUtf8("Numéro de dossard : "), this);
    labelNumeroDossard->setFont(texteLabelGestion);
    lineEditNumeroDossard = new QLineEdit(this);
    lineEditNumeroDossard->setFont(texteLabelGestion);
    lineEditNumeroDossard->setEnabled(false);

    labelMessageInscription = new QLabel(this);
    labelMessageInscription->setFont(texteLabelInscriptionMessage);

    //Tableau
    // enregistrement [idCoureur, idCatégorie, idClasse, INE, Nom, Prenom, DateNaissance, Sexe]
    // tableau [nom prenom classe categorie INE datenaissace sexe]

    vueTableCoureurs = new QTableView(this);
    modeleTableCoureurs = new QStandardItemModel();
    vueTableCoureurs->setModel(modeleTableCoureurs);

    QVBoxLayout *tableauLayout = new QVBoxLayout;
    tableauLayout->addWidget(vueTableCoureurs);
    tableauLayout->setContentsMargins(0, 0, 20, 0); // G H D B

    vueTableInscrits = new QTableView(this);
    modeleTableInscrits = new QStandardItemModel();
    vueTableInscrits->setModel(modeleTableInscrits);
    nomColonnesInscrit << "Nom" << QString::fromUtf8("Prénom") << "Dossard";
    modeleTableInscrits->clear();
    vueTableInscrits->setEditTriggers(QAbstractItemView::NoEditTriggers);
    vueTableInscrits->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    vueTableInscrits->verticalHeader()->setHidden(true);
    modeleTableInscrits->setHorizontalHeaderLabels(nomColonnesInscrit);

    QVBoxLayout *tableauInscritsLayout = new QVBoxLayout;
    tableauInscritsLayout->addWidget(vueTableInscrits);

    QHBoxLayout *sexeFMGestionLayout = new QHBoxLayout;
    sexeFMGestionLayout->addWidget(rbGestionSexeF);
    sexeFMGestionLayout->addWidget(rbGestionSexeM);
    sexeFMGestionLayout->addStretch();

    QHBoxLayout *participeLayout = new QHBoxLayout;
    participeLayout->addWidget(cbGestionParticipe);
    participeLayout->addWidget(bGestionSupprimerInscription);

    QVBoxLayout *editGestionLayout = new QVBoxLayout;
    editGestionLayout->addWidget(lineEditNom);
    editGestionLayout->addWidget(lineEditPrenom);
    editGestionLayout->addWidget(deDateNaissance);
    editGestionLayout->addWidget(cbGestionClasse);
    editGestionLayout->addWidget(cbGestionCategorie);
    editGestionLayout->addWidget(lineEditINE);
    editGestionLayout->addLayout(sexeFMGestionLayout);
    editGestionLayout->addLayout(participeLayout);
    editGestionLayout->setContentsMargins(15, 0, 0, 0); // G H D B

    bGestionNouveau = new QPushButton(QString::fromUtf8("Nouveau"), this);
    bGestionNouveau->setEnabled(true);
    bGestionNouveau->setFont(texteLabelGestionBouton);
    bGestionModifier = new QPushButton(QString::fromUtf8("Modifier"), this);
    bGestionModifier->setEnabled(false);
    bGestionModifier->setFont(texteLabelGestionBouton);
    bGestionSupprimer = new QPushButton(QString::fromUtf8("Supprimer"), this);
    bGestionSupprimer->setEnabled(false);
    bGestionSupprimer->setFont(texteLabelGestionBouton);

    QHBoxLayout *gestionLayoutBoutons = new QHBoxLayout;
    gestionLayoutBoutons->addWidget(bGestionNouveau);
    gestionLayoutBoutons->addWidget(bGestionModifier);
    gestionLayoutBoutons->addWidget(bGestionSupprimer);
    gestionLayoutBoutons->addStretch(10);
    gestionLayoutBoutons->addWidget(bCreationConfirmer);
    gestionLayoutBoutons->addWidget(bCreationAnnuler);
    gestionLayoutBoutons->addStretch();

    QVBoxLayout *labelGestionLayout = new QVBoxLayout;
    labelGestionLayout->addWidget(labelGestionNom);
    labelGestionLayout->addWidget(labelGestionPrenom);
    labelGestionLayout->addWidget(labelGestionDateNaissance);
    labelGestionLayout->addWidget(labelGestionClasse);
    labelGestionLayout->addWidget(labelGestionCategorie);
    labelGestionLayout->addWidget(labelGestionINE);
    labelGestionLayout->addWidget(labelGestionSexe);
    labelGestionLayout->addWidget(labelGestionParticipe);
    labelGestionLayout->setContentsMargins(10, 0, 15, 0); // G H D B

    QHBoxLayout *gestionLayout = new QHBoxLayout;
    gestionLayout->addLayout(labelGestionLayout);
    gestionLayout->addLayout(editGestionLayout);
    gestionLayout->setContentsMargins(0, 0, 0, 10);

    QHBoxLayout *inscriptionDossardLayout = new QHBoxLayout;
    inscriptionDossardLayout->addWidget(labelNumeroDossard);
    inscriptionDossardLayout->addWidget(lineEditNumeroDossard);
    inscriptionDossardLayout->addStretch();

    QHBoxLayout *gestionLayoutBouton = new QHBoxLayout;
    gestionLayoutBouton->addWidget(bInscrire);
    gestionLayoutBouton->addStretch();

    QHBoxLayout *inscriptionManifestationLayout = new QHBoxLayout;
    inscriptionManifestationLayout->addWidget(labelInscriptionManifestation);
    inscriptionManifestationLayout->addWidget(cbInscriptionListeManifestation);
    inscriptionManifestationLayout->addStretch();

    QHBoxLayout *inscriptionCourseLayout = new QHBoxLayout;
    inscriptionCourseLayout->addWidget(labelInscriptionCourse);
    inscriptionCourseLayout->addWidget(cbInscriptionListeCourse);
    inscriptionCourseLayout->addStretch();

    QVBoxLayout *inscriptionLayout = new QVBoxLayout;
    inscriptionLayout->addWidget(labelInscription);
    inscriptionLayout->addLayout(inscriptionManifestationLayout);
    inscriptionLayout->addLayout(inscriptionCourseLayout);
    inscriptionLayout->addLayout(inscriptionDossardLayout);
    inscriptionLayout->addLayout(gestionLayoutBouton);
    inscriptionLayout->addLayout(tableauInscritsLayout);
    inscriptionLayout->addWidget(labelMessageInscription);

    QVBoxLayout *gestionInscriptionLayout = new QVBoxLayout;
    gestionInscriptionLayout->addWidget(labelGestion);
    gestionInscriptionLayout->addLayout(gestionLayout);
    gestionInscriptionLayout->addLayout(gestionLayoutBoutons);
    gestionInscriptionLayout->addSpacing(20);
    gestionInscriptionLayout->addLayout(inscriptionLayout);
    gestionInscriptionLayout->setContentsMargins(20, 0, 0, 0); // G H D B

    QHBoxLayout *panneauLayout = new QHBoxLayout;
    panneauLayout->addLayout(tableauLayout);
    panneauLayout->addLayout(gestionInscriptionLayout);
    panneauLayout->setContentsMargins(5, 0, 5, 5); // G H D B
    fenetreCoureur->setLayout(panneauLayout);
}

void IHMGestionCross::listerManifestations()
{
    QString INE = lineEditINE->text();
    listeManifestations = gestionnaireBDD->recupererListeManifestationsInscription(INE);
    cbInscriptionListeManifestation->clear();

    if(listeManifestations[0] == "Inscrit(e) à toute les courses disponibles")
    {
        cbInscriptionListeManifestation->addItem("Inscrit(e) à toute les courses disponibles");
        cbInscriptionListeManifestation->setEditable(false);
        cbInscriptionListeCourse->addItem("Inscrit(e) à toute les courses disponibles");
        cbInscriptionListeCourse->setEnabled(true);
        cbInscriptionListeCourse->setEditable(false);
        bInscrire->setEnabled(false);
    }
    else
    {
        cbInscriptionListeManifestation->clear();
        cbInscriptionListeManifestation->addItem("< Liste des manifestations >");
        for(int i=0; i < listeManifestations.size(); i++)
        {
            cbInscriptionListeManifestation->addItem(listeManifestations.at(i));
        }
    }
}

void IHMGestionCross::listerCourses(QString nom)
{
    if(listeManifestations[0] != "Inscrit(e) à toute les courses disponibles")
    {
        QString sexe = recupererSexeCoureur();
        listeCourses = gestionnaireBDD->recupererListeCoursesInscription(nom, sexe);
        qDebug() << Q_FUNC_INFO << listeCourses.size() << nom << listeCourses;
        cbInscriptionListeCourse->clear();
        cbInscriptionListeCourse->addItem("< Liste des courses >");
        for(int i=0; i < listeCourses.size(); i++)
        {
            qDebug() << Q_FUNC_INFO << listeCourses.at(i);
            cbInscriptionListeCourse->addItem(listeCourses.at(i));
        }
        cbInscriptionListeCourse->setEnabled(true);
    }
    else
        qDebug() << Q_FUNC_INFO << "Aucune course disponible";
}

/**
* @brief Méthode afficherTable() de la classe IHMGestionCross
* @fn IHMGestionCross::afficherTable
* @details Récupère la table Coureur de la base de données et l'affiche dans le tableau
* @param nomTable QString
*/
void IHMGestionCross::afficherTable(QString nomTable)
{
    // enregistrement [ idCoureur, idCatégorie, idClasse, INE, Nom, Prenom, DateNaissance, Sexe ]
    // tableau [ nom prenom classe categorie INE datenaissace sexe ]
    tableCoureurs.clear();
    tableCoureurs = gestionnaireBDD->recupererTableBDD(nomTable);
    if(tableCoureurs.size() == 0)
        return;
    QStringList enregistrement;
    int nbEnregistrements = tableCoureurs.count();

    qDebug() << Q_FUNC_INFO << nbEnregistrements;

    for(int i = 0; i < nbEnregistrements; i += 1)
    {
        enregistrement = tableCoureurs[i];
        QStandardItem *nom = new QStandardItem(enregistrement.at(INFO_COUREUR_NOM));
        QStandardItem *prenom = new QStandardItem(enregistrement.at(INFO_COUREUR_PRENOM));
        QStandardItem *classe = new QStandardItem(gestionnaireBDD->recupererInformation("Nom", "Classe", QString("idClasse = %1;").arg(enregistrement[INFO_COUREUR_CLASSE])));

        QStandardItem *categorie = new QStandardItem(gestionnaireBDD->recupererInformation("Nom", "Categorie", QString("idCategorie = %1;").arg(enregistrement[INFO_COUREUR_CATEGORIE])));
        QStandardItem *ine = new QStandardItem(enregistrement.at(INFO_COUREUR_INE));
        QStandardItem *dateNaissance = new QStandardItem(enregistrement.at(INFO_COUREUR_DATENAISSANCE));
        QStandardItem *sexe = new QStandardItem(enregistrement.at(INFO_COUREUR_SEXE));

        modeleTableCoureurs->setItem(i, COLONNE_NOM, nom);
        modeleTableCoureurs->setItem(i, COLONNE_PRENOM, prenom);
        modeleTableCoureurs->setItem(i, COLONNE_CLASSE, classe);
        modeleTableCoureurs->setItem(i, COLONNE_CATEGORIE, categorie);
        modeleTableCoureurs->setItem(i, COLONNE_INE, ine);
        modeleTableCoureurs->setItem(i, COLONNE_DATENAISSANCE, dateNaissance);
        modeleTableCoureurs->setItem(i, COLONNE_SEXE, sexe);

        enregistrement.clear();
    }
    nbLignesTableCoureurs = modeleTableCoureurs->rowCount();
}

void IHMGestionCross::viderTableInscrit()
{
    modeleTableInscrits->clear();
    modeleTableInscrits->setHorizontalHeaderLabels(nomColonnesInscrit);
}

QString IHMGestionCross::recupererSexeCoureur()
{
    if(rbGestionSexeF->isChecked())
        return "F";
    else if(rbGestionSexeM->isChecked())
        return "M";
    else
        return "ERREUR";
}

bool IHMGestionCross::verifierNumeroDossardInscription(QString numeroDossard)
{
    if(!numeroDossard.isEmpty())
    {
        QString numeroDossard = lineEditNumeroDossard->text();
        if(numeroDossard.length() ==3)
        {
            QString idCourse = gestionnaireBDD->recupererInformation("idCourse", "Course", QString("Nom = '%1'").arg(cbInscriptionListeCourse->currentText()));
            QString conditionMin = QString("%1000").arg(idCourse);
            QString conditionMax = QString("%1099").arg(idCourse);
            if(numeroDossard > conditionMin && numeroDossard < conditionMax)
            {
                if(gestionnaireBDD->verifierDossard(numeroDossard))
                {
                    labelMessageInscription->setStyleSheet("color : #000000");
                    lineEditNumeroDossard->setStyleSheet("color : #000000");
                    labelMessageInscription->clear();
                    return true;
                }
                else
                {
                    messageErreur("Le numéro de dossard n'est pas disponible");
                    return false;
                }
            }
            else
            {
                messageErreur(QString("Le numéro de dossard est érroné, il doit commencer par  : %1 ").arg(idCourse));
                return false;
            }
        }
        else
        {
            messageErreur("Le numéro de dossard ne doit contenir que 3 chiffres");
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool IHMGestionCross::verifierInformationsCreerCoureur(QStringList informations)
{
    // informationsCoureur [ 0 Categorie , 1 classe , 2 INE , 3 nom , 4 prenom , 5 dateNaissance , 6 sexe ]
    if(informations.size() == 7)
    {
        labelMessageInscription->clear();
        for(int i = 0;  i < 7; i += 1)
        {
            if(informations[i].isEmpty())
            {
                qDebug() << Q_FUNC_INFO << "CHAMPS VIDE";
                messageErreur("Creation impossible:\nUn ou plusieurs champs sont vides.");
                return false;
            }
        }
        bool verificationINE = gestionnaireBDD->verifierInformation(QString("INE = '%1'").arg(informations[2]), "Coureur");
        qDebug() << Q_FUNC_INFO << "idCoureur : " << verificationINE;
        if(verificationINE)
        {
            qDebug() << Q_FUNC_INFO << "INE INVALIDE";
            messageErreur("Creation impossible:\nINE invalide.");
            return false;
        }
        qDebug() << Q_FUNC_INFO << "INE VALIDE";
        bool doublon = gestionnaireBDD->verifierInformation(QString("Nom = '%1' AND Prenom = '%2' AND DateNaissance = '%3';").arg(informations[3]).arg(informations[4]).arg(informations[5]), "Coureur");
        if(doublon)
        {
            qDebug() << Q_FUNC_INFO << "INFORMATION INVALIDE";
            messageErreur("Creation impossible :\nNom prenom ou DateNaissance invalide.");
            return false;
        }
        qDebug() << Q_FUNC_INFO << "INFORMATION VALIDE";
        if(cbGestionClasse->currentText() == "< Classes >")
        {
            qDebug() << Q_FUNC_INFO << "CLASSE INVALIDE";
            messageErreur("Creation impossible :\nClasse invalide.");
            return false;
        }
        if(cbGestionCategorie->currentText() == "< Catégories >")
        {
            qDebug() << Q_FUNC_INFO << "CATEGORIE INVALIDE";
            messageErreur("Création impossible:\nCategorie invalide.");
            return false;
        }
        else
        {
            labelMessageInscription->setStyleSheet("color : #000000");
            qDebug() << Q_FUNC_INFO << "CHAMPS OK";
            labelMessageInscription->setText("Création en cours...");
            return true;
        }
    }
    else
    {
        messageErreur("Creation impossible :\nVeuillez remplir le formulaire.");
        return false;
    }
}

bool IHMGestionCross::verifierInformationsModifierCoureur(QStringList informations)
{
    // informationsCoureur [ 0 Categorie , 1 classe , 2 INE , 3 nom , 4 prenom , 5 dateNaissance , 6 sexe , 7 idCoureur]
    qDebug() << Q_FUNC_INFO << informations << informations.size();
    if(informations.size() == 8)
    {
        labelMessageInscription->clear();
        for(int i = 0;  i < 7; i += 1)
        {
            if(informations[i].isEmpty())
            {
                qDebug() << Q_FUNC_INFO << "CHAMPS VIDE";
                messageErreur("Creation impossible:\nUn ou plusieurs champs sont vides.");
                return false;
            }
        }
        bool verificationINE = gestionnaireBDD->verifierInformation(QString("INE = '%1' AND idCoureur != '%2';").arg(informations[2]).arg(informations[7]), "Coureur");
        qDebug() << Q_FUNC_INFO << "idCoureur : " << verificationINE;
        if(verificationINE)
        {
            qDebug() << Q_FUNC_INFO << "INE INVALIDE";
            messageErreur("Creation impossible:\nINE invalide.");
            return false;
        }
        qDebug() << Q_FUNC_INFO << "INE VALIDE";
        bool doublon = gestionnaireBDD->verifierInformation(QString("Nom = '%1' AND Prenom = '%2' AND DateNaissance = '%3' AND idCoureur != '%4';").arg(informations[3]).arg(informations[4]).arg(informations[5]).arg(informations[7]), "Coureur");
        if(doublon)
        {
            qDebug() << Q_FUNC_INFO << "INFORMATION INVALIDE";
            messageErreur("Creation impossible :\nNom prenom ou DateNaissance invalide.");
            return false;
        }
        qDebug() << Q_FUNC_INFO << "INFORMATION VALIDE";
        if(cbGestionClasse->currentText() == "< Classes >")
        {
            qDebug() << Q_FUNC_INFO << "CLASSE INVALIDE";
            messageErreur("Creation impossible :\nClasse invalide.");
            return false;
        }
        qDebug() << Q_FUNC_INFO << "CLASSE VALIDE";
        if(cbGestionCategorie->currentText() == "< Catégories >")
        {
            qDebug() << Q_FUNC_INFO << "CATEGORIE INVALIDE";
            messageErreur("Création impossible:\nCategorie invalide.");
            return false;
        }
        else
        {
            qDebug() << Q_FUNC_INFO << "CATEGORIE VALIDE";
            labelMessageInscription->setStyleSheet("color : #000000");
            qDebug() << Q_FUNC_INFO << "CHAMPS OK";
            labelMessageInscription->setText("Modification en cours...");
            return true;
        }
    }
    else
    {
        messageErreur("Creation impossible :\nVeuillez remplir le formulaire.");
        return false;
    }
}

void IHMGestionCross::messageErreur(QString message)
{
    labelMessageInscription->clear();
    labelMessageInscription->setText(message);
    labelMessageInscription->setStyleSheet("color : #FF0000");
    lineEditNumeroDossard->setStyleSheet("color : #FF0000");
}

void IHMGestionCross::messageSucces(QString message)
{
    labelMessageInscription->clear();
    labelMessageInscription->setStyleSheet("color : #000000");
    labelMessageInscription->setText(QString("Le(La) coureur(euse) a été %1 avec succés !").arg(message));
}

QVector<int> IHMGestionCross::traiterDateNaissance(QString date)
{
    //date : YYYY-MM-DD
    QStringList listDateNaissance = date.split("-", QString::SkipEmptyParts);
    QVector<int> retourDateNaissanceINT;
    retourDateNaissanceINT << listDateNaissance[0].toInt() << listDateNaissance[1].toInt() << listDateNaissance[2].toInt();
    qDebug() << Q_FUNC_INFO << retourDateNaissanceINT;
    return retourDateNaissanceINT;
}

QStringList IHMGestionCross::recupererChampsGestion()
{
    QStringList informationsCoureur;
    informationsCoureur << cbGestionCategorie->currentText();
    informationsCoureur << cbGestionClasse->currentText();
    informationsCoureur << lineEditINE->text();
    informationsCoureur << lineEditNom->text();
    informationsCoureur << lineEditPrenom->text();
    QDate date = deDateNaissance->date();
    QString dateNaissance = date.toString("yyyy-MM-d");
    informationsCoureur << dateNaissance;
    if(rbGestionSexeF->isChecked())
        informationsCoureur << "F";
    if(rbGestionSexeM->isChecked())
        informationsCoureur << "M";
    informationsCoureur[3] = informationsCoureur[3].toUpper();
    informationsCoureur[4] = informationsCoureur[4].toLower();
    informationsCoureur[4][0] = informationsCoureur[4][0].toUpper();
    return informationsCoureur;
}

void IHMGestionCross::reinitialiserGestionCoureur()
{
    etat.clear();
    etat = "Gestion Coureurs";
    vueTableCoureurs->setEnabled(true);
    bGestionNouveau->setEnabled(true);
    bCreationConfirmer->setVisible(false);
    bCreationAnnuler->setVisible(false);
    lineEditNom->clear();
    lineEditNom->setEnabled(false);
    lineEditPrenom->clear();
    lineEditPrenom->setEnabled(false);
    deDateNaissance->setDate(dateDefault);
    deDateNaissance->setEnabled(false);
    cbGestionClasse->clear();
    cbGestionClasse->addItem("< Classes >");
    cbGestionClasse->setEnabled(false);
    cbGestionCategorie->clear();
    cbGestionCategorie->addItem("< Categories >");
    cbGestionCategorie->setEnabled(false);
    cbGestionParticipe->clear();
    cbGestionParticipe->setEnabled(false);
    lineEditINE->clear();
    lineEditINE->setEnabled(false);
    rbGestionSexeF->setEnabled(false);
    rbGestionSexeM->setEnabled(false);
    labelMessageInscription->setStyleSheet("color : #000000");
}

//slots

/**
* @brief SLOT gererCoureurs() de la classe IHMGestionCross
* @fn IHMGestionCross::gererCoureurs()
* @details Permet de changer l'état de l'IHM pour passer en mode "Gestion Coureur" et de changer l'aspect des boutons
*/
void IHMGestionCross::gererCoureurs()
{
    etat.clear();
    etat = "Mode Coureurs";
    if(fenetreGestionCross->currentIndex() == FENETRE_COUREUR)
    {
        bCoureurs->setChecked(true);
        return;
    }
    qDebug() << Q_FUNC_INFO;
    fenetreGestionCross->setCurrentIndex(FENETRE_COUREUR);
    bManifestations->setChecked(false);
    bCourses->setChecked(false);
    bCoureurs->setChecked(true);

    if(nomColonnesCoureur.isEmpty())
        nomColonnesCoureur << "Nom" << QString::fromUtf8("Prénom") << "Classe" << QString::fromUtf8("Catégorie") << "INE" << "Date de Naissance" << "Sexe";
    modeleTableCoureurs->clear();
    vueTableCoureurs->setEditTriggers(QAbstractItemView::NoEditTriggers);
    vueTableCoureurs->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    vueTableCoureurs->verticalHeader()->setHidden(true);
    modeleTableCoureurs->setHorizontalHeaderLabels(nomColonnesCoureur);
    afficherTable("Coureur");
}

/**
* @brief SLOT gererCourses() de la classe IHMGestionCross
* @fn IHMGestionCross::gererCourses()
* @details Permet de changer l'état de l'IHM pour passer en mode "Gestion Course" et de changer l'aspect des boutons
*/
void IHMGestionCross::gererCourses()
{
    etat.clear();
    etat = "Gerer Courses";
    if(fenetreGestionCross->currentIndex() == FENETRE_COURSE)
    {
        bCourses->setChecked(true);
        return;
    }
    qDebug() << Q_FUNC_INFO;
    fenetreGestionCross->setCurrentIndex(FENETRE_COURSE);
    bManifestations->setChecked(false);
    bCourses->setChecked(true);
    bCoureurs->setChecked(false);
}

/**
* @brief SLOT gererManifestations() de la classe IHMGestionCross
* @fn IHMGestionCross::gererManifestations()
* @details Permet de changer l'état de l'IHM pour passer en mode "Gestion Manifestation" et de changer l'aspect des boutons
*/
void IHMGestionCross::gererManifestations()
{
    etat.clear();
    etat = "Gerer Manifestations";
    if(fenetreGestionCross->currentIndex() == FENETRE_MANIFESTATION)
    {
        bManifestations->setChecked(true);
        return;
    }
    qDebug() << Q_FUNC_INFO;
    fenetreGestionCross->setCurrentIndex(FENETRE_MANIFESTATION);
    bManifestations->setChecked(true);
    bCourses->setChecked(false);
    bCoureurs->setChecked(false);
}

void IHMGestionCross::selectionnerManifestation(QString nom)
{
    etat.clear();
    etat = "Inscription Coureur";
    if(nom != "< Liste des manifestations >" && nom != "")
    {
        listeCourses.clear();
        cbInscriptionListeCourse->clear();
        listerCourses(nom);
        return;
    }
    return;
}

void IHMGestionCross::selectionnerCourse(QString nom)
{
    if(nom!="< Liste des courses >" && nom!="")
    {
        if(listeManifestations[0] != "Inscrit(e) à toute les courses disponibles")
        {
            if(!listeCoureursInscrit.isEmpty())
                viderTableInscrit();
            lineEditNumeroDossard->setEnabled(true);
            listeCoureursInscrit = gestionnaireBDD->recupererListeCoureursInscrit(nom);
            int nbCoureursInscrits = listeCoureursInscrit.size();
            for(int i = 0; i < nbCoureursInscrits; i += 1)
            {
                QStringList enregistrement = listeCoureursInscrit[i];
                QStandardItem *nom = new QStandardItem(enregistrement.at(INFO_COUREURINSCRIT_NOM));
                QStandardItem *prenom = new QStandardItem(enregistrement.at(INFO_COUREURINSCRIT_PRENOM));
                QStandardItem *numeroDossard = new QStandardItem(enregistrement.at(INFO_COUREURINSCRIT_NUMERODOSSAD));

                modeleTableInscrits->setItem(i, COLONNE_NOM, nom);
                modeleTableInscrits->setItem(i, COLONNE_PRENOM, prenom);
                modeleTableInscrits->setItem(i, COLONNE_NUMERODOSSARD, numeroDossard);

                QString idCourse = gestionnaireBDD->recupererInformation("idCourse", "Course", QString("Nom = '%1'").arg(cbInscriptionListeCourse->currentText()));

                labelMessageInscription->setText(QString("Pour inscrire un(e) coureur(euse)\nVeuillez entrer un numéro de dossard disponible entre %1001 et %1099").arg(idCourse));
            }
            bInscrire->setEnabled(true);
            QString idCourse = gestionnaireBDD->recupererInformation("idCourse", "Course", QString("Nom = '%1'").arg(cbInscriptionListeCourse->currentText()));

            qDebug() << Q_FUNC_INFO << idCourse;

            lineEditNumeroDossard->setText(idCourse);
        }
        else
        {
            lineEditNumeroDossard->setEnabled(false);
        }
    }
}

void IHMGestionCross::initialiserConfirmationDialog(QString nomTache)
{
    confirmationDialog = new QDialog(this);
    labelConfirmationDialog = new QLabel (tr("Etes vous sûr de vouloir %1 ce(cette) coureur(coureuse) ?").arg(nomTache));
    bConfirmationDialog = new QPushButton (QString::fromUtf8("Confirmer"));
    bAnnulerDialog = new QPushButton (QString::fromUtf8("Annuler"));

    QHBoxLayout *boutonLayout = new QHBoxLayout;
    boutonLayout->addWidget(bConfirmationDialog);
    boutonLayout->addWidget(bAnnulerDialog);
    boutonLayout->setContentsMargins(0, 0, 0, 5); // G H D B

    QVBoxLayout *mainDialogLayout = new QVBoxLayout;
    mainDialogLayout->addWidget(labelConfirmationDialog);
    mainDialogLayout->addLayout(boutonLayout);
    mainDialogLayout->setContentsMargins(10, 10, 10, 10); // G H D B

    setWindowTitle(tr("Confirmation"));

    connect(bAnnulerDialog, SIGNAL(clicked()), this, SLOT(quitterDialog()));
    if(nomTache == "supprimer")
    {
        QString INE = lineEditINE->text();
        connect(bConfirmationDialog, SIGNAL(clicked()), gestionnaireBDD, SLOT(supprimerCoureur()));
    }
/*    else if(nomTache == "modifier")
        connect(bConfirmationDialog, SIGNAL(clicked()), this, SLOT();
  */
    confirmationDialog->setLayout(mainDialogLayout);
    confirmationDialog->exec();
}

void IHMGestionCross::selectionnerCoureur(QModelIndex index)
{
    etat.clear();
    etat = "Gestion Coureurs";

    if(cbInscriptionListeCourse->currentText() != "< Liste des courses >")
    {
        modeleTableInscrits->clear();
        cbInscriptionListeCourse->clear();
        cbInscriptionListeCourse->addItem("< Liste des courses >");
        lineEditNumeroDossard->clear();
        lineEditNumeroDossard->setEnabled(false);
    }
    bGestionSupprimerInscription->setEnabled(true);
    labelMessageInscription->clear();
    labelMessageInscription->setStyleSheet("color : #000000");
    lineEditNumeroDossard->setStyleSheet("color : #000000");
    bGestionModifier->setEnabled(true);
    bGestionSupprimer->setEnabled(true);
    lineEditNom->setText(tableCoureurs.at(index.row()).at(INFO_COUREUR_NOM));
    lineEditNom->setEnabled(true);
    lineEditPrenom->setText(tableCoureurs.at(index.row()).at(INFO_COUREUR_PRENOM));
    lineEditPrenom->setEnabled(true);
    lineEditINE->setText(tableCoureurs.at(index.row()).at(INFO_COUREUR_INE));
    lineEditINE->setEnabled(true);
    deDateNaissance->setEnabled(true);

    idCoureur = gestionnaireBDD->recupererInformation("idCoureur", "Coureur", QString("INE = '%1';").arg(tableCoureurs.at(index.row()).at(INFO_COUREUR_INE)));

    qDebug() << Q_FUNC_INFO << "id : " << idCoureur;

    QString dateNaissance = tableCoureurs.at(index.row()).at(INFO_COUREUR_DATENAISSANCE);
    QVector<int> dates = traiterDateNaissance(dateNaissance);
    QDate date(dates[0], dates[1], dates[2]);
    qDebug() << Q_FUNC_INFO << date;
    deDateNaissance->setDate(date);

    QString categorie = gestionnaireBDD->recupererInformation("Nom", "Categorie", QString("idCategorie = %1;").arg(tableCoureurs.at(index.row()).at(INFO_COUREUR_CATEGORIE)));
    cbGestionCategorie->clear();
    cbGestionCategorie->addItem(categorie);
    cbGestionCategorie->setEnabled(true);

    QString classe = gestionnaireBDD->recupererInformation("Nom", "Classe", QString("idClasse = %1;").arg(tableCoureurs.at(index.row()).at(INFO_COUREUR_CLASSE)));
    cbGestionClasse->setEnabled(true);
    cbGestionClasse->clear();
    cbGestionClasse->addItem(classe);

    rbGestionSexeF->setEnabled(true);
    rbGestionSexeM->setEnabled(true);
    cbGestionParticipe->setEnabled(true);
    cbGestionParticipe->setEditable(false);
    cbGestionParticipe->clear();
    cbInscriptionListeManifestation->setEnabled(true);

    if(tableCoureurs.at(index.row()).at(INFO_COUREUR_SEXE) == "F")
        rbGestionSexeF->setChecked(true);
    else
        rbGestionSexeM->setChecked(true);

    QString INE = lineEditINE->text();
    QStringList nomCoursesInscrit = gestionnaireBDD->recupererListeCoursesGestion(INE);

    for(int i = 0; i < nomCoursesInscrit.size(); i += 1)
    {
        cbGestionParticipe->addItem(nomCoursesInscrit[i]);
    }

    listerManifestations();
}

void IHMGestionCross::ajouterNouvelleInscription()
{

    QString numeroDossard = lineEditNumeroDossard->text();
    if(verifierNumeroDossardInscription(numeroDossard))
    {
        qDebug() << Q_FUNC_INFO << "Dossad valide";
        QStringList inscription;
        QString nomCourse = cbInscriptionListeCourse->currentText();
        QString idCourse = gestionnaireBDD->recupererInformation("idCourse", "Course", QString("Nom = '%1'").arg(nomCourse));
        QString idCoureur = gestionnaireBDD->recupererInformation("idCoureur", "Coureur", QString("Nom = '%1'").arg(lineEditNom->text()));
        qDebug() << Q_FUNC_INFO << "Inscription :\tidCoureur : " << idCoureur << "\tidCourse : " << idCourse << "\tnumero : " << numeroDossard;
        inscription << idCoureur << idCourse << numeroDossard;
        gestionnaireBDD->ajouterNouvelInscrit(inscription);
        lineEditNumeroDossard->clear();
        messageSucces("inscrit(e)");
        listerManifestations();
        listerCourses("*");
        cbGestionParticipe->addItem(nomCourse);
    }
    else
        qDebug() << Q_FUNC_INFO << "Dossard invalide";
}

void IHMGestionCross::supprimerInscrition()
{
    etat.clear();
    etat = "Suppression Inscription";
    initialiserConfirmationDialog();

}

void IHMGestionCross::mettreAJourTableInscrit(QStringList inscription)
{
    QStandardItem *nom = new QStandardItem(inscription.at(INFO_COUREURINSCRIT_NOM));
    QStandardItem *prenom = new QStandardItem(inscription.at(INFO_COUREURINSCRIT_PRENOM));
    QStandardItem *numeroDossard = new QStandardItem(inscription.at(INFO_COUREURINSCRIT_NUMERODOSSAD));

    nbLignesTableInscrit = modeleTableInscrits->rowCount();
    qDebug() << Q_FUNC_INFO << nbLignesTableInscrit;

    modeleTableInscrits->setItem(nbLignesTableInscrit, COLONNE_NOM, nom);
    modeleTableInscrits->setItem(nbLignesTableInscrit, COLONNE_PRENOM, prenom);
    modeleTableInscrits->setItem(nbLignesTableInscrit, COLONNE_NUMERODOSSARD, numeroDossard);
}

void IHMGestionCross::ajouterNouveauCoureurTable(QStringList informationsCoureur)
{
    qDebug() << Q_FUNC_INFO << informationsCoureur;
    // informationsCoureur [ 0 categorie , 1 classe , 2 ine , 3 nom , 4 prenom , 5 datenaissance , 6 sexe ]
    if(nbLignesTableCoureurs != modeleTableCoureurs->rowCount())
        nbLignesTableCoureurs = modeleTableCoureurs->rowCount();
    modeleTableCoureurs->insertRow(nbLignesTableCoureurs);

    messageSucces("créé(e)");

    QStandardItem *categorie = new QStandardItem(informationsCoureur.at(0));
    QStandardItem *classe  = new QStandardItem(informationsCoureur.at(1));
    QStandardItem *ine  = new QStandardItem(informationsCoureur.at(2));
    QStandardItem *nom  = new QStandardItem(informationsCoureur.at(3));
    QStandardItem *prenom  = new QStandardItem(informationsCoureur.at(4));
    QStandardItem *dateNaissance  = new QStandardItem(informationsCoureur.at(5));
    QStandardItem *sexe  = new QStandardItem(informationsCoureur.at(6));

    modeleTableCoureurs->setItem(nbLignesTableCoureurs, COLONNE_NOM, nom);
    modeleTableCoureurs->setItem(nbLignesTableCoureurs, COLONNE_PRENOM, prenom);
    modeleTableCoureurs->setItem(nbLignesTableCoureurs, COLONNE_CLASSE, classe);
    modeleTableCoureurs->setItem(nbLignesTableCoureurs, COLONNE_CATEGORIE, categorie);
    modeleTableCoureurs->setItem(nbLignesTableCoureurs, COLONNE_INE, ine);
    modeleTableCoureurs->setItem(nbLignesTableCoureurs, COLONNE_DATENAISSANCE, dateNaissance);
    modeleTableCoureurs->setItem(nbLignesTableCoureurs, COLONNE_SEXE, sexe);

    modeleTableCoureurs->sort(4,Qt::SortOrder::AscendingOrder);
    mettreAJourTableCoureur();

}

void IHMGestionCross::mettreAJourTableCoureur()
{
    tableCoureurs.clear();
    tableCoureurs = gestionnaireBDD->recupererTableBDD("Coureur");
    qDebug() << Q_FUNC_INFO;
}

void IHMGestionCross::mettreAJourCBParticipe()
{
    cbGestionParticipe->clear();
    qDebug() << Q_FUNC_INFO << cbGestionParticipe->size();
    QString INE = lineEditINE->text();
    QStringList nomCoursesInscrit = gestionnaireBDD->recupererListeCoursesGestion(INE);
    for(int i = 0; i < nomCoursesInscrit.size(); i += 1)
    {
        cbGestionParticipe->addItem(nomCoursesInscrit[i]);
    }
    listerManifestations();
    listerCourses(cbInscriptionListeManifestation->currentText());
    cbInscriptionListeCourse->setEnabled(false);
}

void IHMGestionCross::supprimerCoureurTable()
{
    messageSucces("supprimé(e)");
    reinitialiserGestionCoureur();
    afficherTable("Coureur");
    mettreAJourTableCoureur();
}

void IHMGestionCross::modifierCoureurTable()
{
    messageSucces("modifié(e)");
    afficherTable("Coureur");
    mettreAJourTableCoureur();
}

void IHMGestionCross::passerModeNouveauCoureur()
{
    etat.clear();
    etat = "Nouveau Coureur";
    vueTableCoureurs->setEnabled(false);
    bGestionModifier->setEnabled(false);
    bGestionNouveau->setEnabled(false);
    cbInscriptionListeCourse->setEnabled(false);
    cbInscriptionListeManifestation->setEnabled(false);
    bGestionSupprimer->setEnabled(false);
    bCreationConfirmer->setVisible(true);
    bCreationAnnuler->setVisible(true);
    rbGestionSexeF->setEnabled(true);
    rbGestionSexeM->setEnabled(true);
    cbGestionParticipe->clear();
    lineEditNom->setEnabled(true);
    lineEditNom->clear();
    lineEditPrenom->setEnabled(true);
    lineEditPrenom->clear();
    lineEditINE->setEnabled(true);
    lineEditINE->clear();
    deDateNaissance->setEnabled(true);
    deDateNaissance->setDate(dateDefault);
    cbGestionClasse->setEnabled(true);
    cbGestionClasse->clear();
    cbGestionClasse->addItem("< Classes >");
    cbGestionCategorie->setEnabled(true);
    cbGestionCategorie->clear();
    cbGestionCategorie->addItem("< Catégories >");
    QVector<QString> categories;
    categories = gestionnaireBDD->recupererCategoriesCreation();
    QVector<QString> classes;
    classes = gestionnaireBDD->recupererClassesCreation();
    bGestionSupprimerInscription->setEnabled(false);

    for(int i = 0; i < classes.size(); i += 1)
    {
        cbGestionClasse->addItem(classes[i]);
    }

    for(int i = 0; i < categories.size(); i += 1)
    {
        cbGestionCategorie->addItem(categories[i]);
    }
}

void IHMGestionCross::creerCoureur()
{
    QStringList informationsCoureur; // informationsCoureur [ 0 Categorie , 1 classe , 2 INE , 3 nom ,  4 prenom , 5 dateNaissance , 6 sexe ]
    informationsCoureur = recupererChampsGestion();
    qDebug() << Q_FUNC_INFO << informationsCoureur;

    if(verifierInformationsCreerCoureur(informationsCoureur))
    {
        qDebug() << Q_FUNC_INFO << "OK";
        gestionnaireBDD->ajouterNouveauCoureur(informationsCoureur);
        reinitialiserGestionCoureur();
    }
    else
    {
        qDebug() << Q_FUNC_INFO << "ERREUR";
    }
}

void IHMGestionCross::annulerNouveauCoureur()
{
    reinitialiserGestionCoureur();
}

void IHMGestionCross::supprimerCoureur()
{
    etat.clear();
    etat = "Suppression Coureur";
    initialiserConfirmationDialog();
}

void IHMGestionCross::modifierCoureur()
{
    etat.clear();
    etat = "Modification Coureur";
    initialiserConfirmationDialog();
}

void IHMGestionCross::initialiserConfirmationDialog()
{
    confirmationDialog = new QDialog(this);
    if(etat == "Suppression Coureur")
        labelConfirmationDialog = new QLabel (tr("Etes vous sûr de vouloir supprimer le Coureur selectionné ?"));
    else if(etat == "Modification Coureur")
        labelConfirmationDialog = new QLabel(tr("Etes vous sûr de vouloir modifier le Coureur selectionné ?"));
    else if(etat == "Suppression Inscription")
        labelConfirmationDialog = new QLabel(tr("Etes vous sûr de vouloir supprimer l'inscription à cette course du Coureur selectionné ?"));
    bConfirmationDialog = new QPushButton (QString::fromUtf8("Confirmer"));
    bAnnulerDialog = new QPushButton (QString::fromUtf8("Annuler"));

    QHBoxLayout *boutonLayout = new QHBoxLayout;
    boutonLayout->addWidget(bConfirmationDialog);
    boutonLayout->addWidget(bAnnulerDialog);
    boutonLayout->setContentsMargins(0, 0, 0, 5); // G H D B

    QVBoxLayout *mainDialogLayout = new QVBoxLayout;
    mainDialogLayout->addWidget(labelConfirmationDialog);
    mainDialogLayout->addLayout(boutonLayout);
    mainDialogLayout->setContentsMargins(10, 10, 10, 10); // G H D B

    setWindowTitle(tr("Confirmation"));

    connect(bAnnulerDialog, SIGNAL(clicked()), this, SLOT(quitterDialog()));
    connect(bConfirmationDialog, SIGNAL(clicked()), this, SLOT(confirmerDialog()));
    qDebug() << Q_FUNC_INFO;

    confirmationDialog->setLayout(mainDialogLayout);
    confirmationDialog->exec();
}

void IHMGestionCross::confirmerDialog()
{
    if(etat == "Suppression Coureur")
    {
        QString INE = lineEditINE->text();
        qDebug() << Q_FUNC_INFO << "SUPPRESSION DEMANDÉ" << INE;
        gestionnaireBDD->supprimerCoureur(INE);
    }
    else if(etat == "Modification Coureur")
    {
        QStringList informationsCoureur = recupererChampsGestion();
        informationsCoureur << idCoureur;
        if(verifierInformationsModifierCoureur(informationsCoureur))
        {
            informationsCoureur << idCoureur;
            qDebug() << Q_FUNC_INFO << "MODIFICATION DEMANDÉ";
            gestionnaireBDD->modifierCoureur(informationsCoureur);
        }
    }
    else if(etat == "Suppression Inscription")
    {
        QString idCoureur = gestionnaireBDD->recupererInformation("idCoureur", "Coureur", QString("INE = '%1'").arg(lineEditINE->text()));
 //       QString idInscrit = gestionnaireBDD->recupererInformation("idInscrit", "Inscrit", QString("idCoureur = '%1'").arg(idCoureur));
        qDebug() << Q_FUNC_INFO << cbGestionParticipe->currentText();
        QString idCourse = gestionnaireBDD->recupererInformation("idCourse", "Course", QString("Nom = '%1'").arg(cbGestionParticipe->currentText()));
        qDebug() << Q_FUNC_INFO << "SUPPRESSION INSCRIPTION";
        gestionnaireBDD->supprimerInscription(idCoureur, idCourse);

    }
    confirmationDialog->close();
}

/**
* @brief SLOT quitterDialog() de la classe IHMChronoCross
* @fn IHMChronoCross::quitterDialog()
* @details Permet de fermer la page dialog Confirmation
*/
void IHMGestionCross::quitterDialog()
{
    confirmationDialog->close();
    reinitialiserGestionCoureur();
    qDebug() << Q_FUNC_INFO;
}

/**
* @brief SLOT quitter() de la classe IHMGestionCross
* @fn IHMGestionCross::quitter()
* @details  Action qui ferme la page
*/
void IHMGestionCross::quitter()
{
    close();
}


