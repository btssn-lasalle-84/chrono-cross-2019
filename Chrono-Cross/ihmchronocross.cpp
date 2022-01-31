#include "ihmchronocross.h"
#include "../BaseDeDonnees/basededonnees.h"
#include "course.h"

/**
* @file Chrono-Cross/ihmchronocross.cpp
* @brief Définition de la classe IHMChronoCross
* @author ANDRÉO Michaël
* @version 1.1
*/

/**
* @brief Constructeur de la fenêtre principale
* @fn IHMChronoCross::IHMChronoCross
* @param parent QObject Adresse de l'objet Qt parent (0 = pas de parent car c'est la fenêtre principale)
*/
IHMChronoCross::IHMChronoCross(QWidget *parent) : QWidget(parent)
{

    course = new Course(this);

    nbCoureurArrive = course->getNbArrivee();
    nbArriveesNonClassees = 0;
    nbArriveesClassees =0;

    m_valeur = long(1.33);
    m_timer = new QTimer(this);

    // défini la taille du text
    QFont texteLabel;
    texteLabel.setPointSize(TAILLETEXTELABEL);

    QFont texteListe;
    texteListe.setPointSize(TAILLETEXTELISTE);

    QFont texteInformation;
    texteInformation.setPointSize(TAILLETEXTEINFO);

    QFont texteMessageSupprimer;
    texteMessageSupprimer.setPointSize(TAILLETEXTESUPPRIMER);

    // les widgets
    cbListeManifestations = new QComboBox(this);
    cbListeManifestations->setFixedSize(this->width()*0.66, this->height()*0.08);
    cbListeManifestations->addItem(("< Séléctionner une Manifestation >"));
    cbListeManifestations->setFont(texteListe);

    cbListeCourses = new QComboBox(this);
    cbListeCourses->setFixedSize(this->width()*0.66, this->height()*0.08);
    cbListeCourses->addItem(("< Séléctionner une Course >"));
    cbListeCourses->setFont(texteListe);

    labelManifestations = new QLabel(tr("Manifestations : "), this);
    labelManifestations->setFont(texteLabel);
    labelListeCourses = new QLabel(tr("Courses : "), this);
    labelListeCourses->setFont(texteLabel);
    labelZoneCourse = new QLabel(tr("Course "), this);
    labelZoneCourse->setFont(texteLabel);
    labelNumeroDossard = new QLabel(tr("N° dossard : "), this);
    labelNumeroDossard->setFont(texteLabel);
    labelZoneClassement = new QLabel(tr("Classement : "), this);
    labelZoneClassement->setFont(texteLabel);
    labelZoneArrivees = new QLabel(tr("Arrivées : "), this);
    labelZoneArrivees->setFont(texteLabel);
    labelZoneChrono = new QLabel(tr("Chrono "), this);
    labelZoneChrono->setFont(texteLabel);
    labelMessageDossard = new QLabel(tr(""));
    labelMessageDossard->setFont(texteLabel);
    labelNbInscrit = new QLabel(tr("Inscrits : "), this);
    labelNbInscrit->setFont(texteInformation);
    labelNbArriveesNonClassees = new QLabel(tr("Non classées: "), this);
    labelNbArriveesNonClassees->setFont(texteInformation);
    labelNbArriveesClassees = new QLabel(tr("Classées: "), this);
    labelNbArriveesClassees->setFont(texteInformation);
    labelNomCourse = new QLabel(tr("Nom : "), this);
    labelNomCourse->setFont(texteInformation);
    labelDistanceCourse = new QLabel(tr("Distance : "), this);
    labelDistanceCourse->setFont(texteInformation);
    labelHeureCourse = new QLabel(tr("Heure : "), this);
    labelHeureCourse->setFont(texteInformation);

    labelEtatChrono = new QLabel(tr("Etat : "),this);
    labelEtatChrono->setFont(texteInformation);
    labelLedChrono = new QLabel(this);
    setRouge(labelLedChrono);

    labelEtatCourse = new QLabel(tr("Etat : "),this);
    labelEtatCourse->setFont(texteInformation);
    labelLedCourse = new QLabel(this);
    setRouge(labelLedCourse);

    labelMessageSupprimer = new QLabel(tr(""), this);
    labelMessageSupprimer->setFont(texteMessageSupprimer);

    QLCDNbArriveesNonClassees = new QLCDNumber(this);
    QLCDNbArriveesNonClassees->setDigitCount(2);
    QLCDNbArriveesNonClassees->display("--");
    QLCDNbArriveesClassees = new QLCDNumber(this);
    QLCDNbArriveesClassees->setDigitCount(2);
    QLCDNbArriveesClassees->display("--");
    QLCDChrono = new QLCDNumber(this);
    QLCDChrono->setDigitCount(8);
    QLCDChrono->display("--:--:--");
    QLCDChrono->setFixedSize(this->width()*1.5, this->height()*0.5);

    logoChronoCross  = new QLabel(this);
    QPixmap pixmap_img(IMAGECHRONOCROSS);
    logoChronoCross->setPixmap(pixmap_img);

    // défini la taille du text dans les QPushButtons
    QFont texteBouton;
    texteBouton.setPointSize(TAILLETEXTEBUTON);

    bSynchroniser = new QPushButton(QString::fromUtf8("Synchroniser"), this);
    bSynchroniser->setDefault(false);
    bSynchroniser->setEnabled(false);
    bSynchroniser->setFont(texteBouton);

    bLancer = new  QPushButton(QString::fromUtf8("Lancer"), this);
    bLancer->setDefault(false);
    bLancer->setEnabled(false);
    bLancer->setFont(texteBouton);

    bArreter = new QPushButton(QString::fromUtf8("Arrêter"), this);
    bArreter->setDefault(false);    
    bArreter->setEnabled(false);
    bArreter->setFont(texteBouton);

    bTerminer = new QPushButton(QString::fromUtf8("Terminer"), this);
    bTerminer->setDefault(false);
    bTerminer->setEnabled(false);
    bTerminer->setFont(texteBouton);

    bAssocier = new QPushButton(QString::fromUtf8("Associer"), this);
    bAssocier->setEnabled(false);
    bAssocier->setFont(texteBouton);

    lineEditNumeroDossard = new QLineEdit(this);
    lineEditNumeroDossard->setFont(texteLabel);
    lineEditNumeroDossard->setEnabled(false);

    vueTableauClassement = new QTableView(this);
    modeleClassement = new QStandardItemModel(0, 5);
    nomColonnes << "Temps" << "Numéro de Dossard" << "Nom" << "Prenom" << "Classe";
    modeleClassement->setHorizontalHeaderLabels(nomColonnes);
    vueTableauClassement->setModel(modeleClassement);
    vueTableauClassement->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Redimensionner automatiquement la colonne pour occuper l'espace disponible
    vueTableauClassement->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    nbLignesClassement = modeleClassement->rowCount();

    vueListeTempsArriveesNonClassees = new QListView(this);
    modeleArriveesNonClassees = new QStringListModel(classement);
    vueListeTempsArriveesNonClassees->setModel(modeleArriveesNonClassees);
    vueListeTempsArriveesNonClassees->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QAction *actionQuitter = new QAction("&Quitter", this);
    actionQuitter->setShortcut(QKeySequence(QKeySequence::Quit)); //Ctrl+Q
    addAction(actionQuitter);

    QAction *actionEntrerPAD = new QAction("&Entrer1", this);
    actionEntrerPAD->setShortcut(QKeySequence(Qt::Key_Enter));
    addAction(actionEntrerPAD);

    QAction *actionEntrerRETURN = new QAction("&Entrer2", this);
    actionEntrerRETURN->setShortcut(QKeySequence(Qt::Key_Return));
    addAction(actionEntrerRETURN);

    // le positionnement
    QHBoxLayout *listesLayout = new QHBoxLayout;
    listesLayout->addWidget(labelManifestations);
    listesLayout->addWidget(cbListeManifestations);
    listesLayout->addStretch();
    listesLayout->addWidget(labelListeCourses);
    listesLayout->addWidget(cbListeCourses);
    listesLayout->addStretch();
    listesLayout->addWidget(logoChronoCross);
    listesLayout->addStretch();
    listesLayout->setContentsMargins(0, 0, 0, 20); // G H D B

    QVBoxLayout *classementLayout = new QVBoxLayout;
    classementLayout->addWidget(labelZoneClassement);
    classementLayout->addWidget(vueTableauClassement);

    QHBoxLayout *etatLedCourseLayout = new QHBoxLayout;
    etatLedCourseLayout->addWidget(labelEtatCourse);
    etatLedCourseLayout->addWidget(labelLedCourse);

    QHBoxLayout *infoCourseLayout = new QHBoxLayout;
    infoCourseLayout->addWidget(labelZoneCourse);
    infoCourseLayout->addLayout(etatLedCourseLayout);
    infoCourseLayout->addStretch();
    infoCourseLayout->addWidget(labelNomCourse);
    infoCourseLayout->addStretch();
    infoCourseLayout->addWidget(labelDistanceCourse);
    infoCourseLayout->addStretch();
    infoCourseLayout->addWidget(labelHeureCourse);
    infoCourseLayout->addStretch();
    infoCourseLayout->addWidget(labelNbInscrit);
    infoCourseLayout->addStretch();


    QHBoxLayout *boutonCourseLayout = new QHBoxLayout;
    boutonCourseLayout->addStretch();
    boutonCourseLayout->addWidget(bSynchroniser);
    boutonCourseLayout->addStretch();
    boutonCourseLayout->addWidget(bTerminer);
    boutonCourseLayout->addStretch();
    boutonCourseLayout->setContentsMargins(0, 5, 0, 0); // G H D B

    QVBoxLayout *courseLayout = new QVBoxLayout;
    courseLayout->addStretch();
    courseLayout->addLayout(infoCourseLayout);
    courseLayout->addLayout(boutonCourseLayout);

    QHBoxLayout *etatLedChronoLayout = new QHBoxLayout;
    etatLedChronoLayout->addWidget(labelEtatChrono);
    etatLedChronoLayout->addWidget(labelLedChrono);

    QHBoxLayout *QLCDChronoLayout = new QHBoxLayout;
    QLCDChronoLayout->addWidget(QLCDChrono);
    QLCDChronoLayout->setContentsMargins(0, 0, 0, 0); // G H D B

    QHBoxLayout *infoBoutonChronoLayout = new QHBoxLayout;
    infoBoutonChronoLayout->addWidget(labelZoneChrono);
    infoBoutonChronoLayout->addLayout(etatLedChronoLayout);
    infoBoutonChronoLayout->addWidget(bLancer);
    infoBoutonChronoLayout->addStretch();
    infoBoutonChronoLayout->addWidget(bArreter);
    infoBoutonChronoLayout->addStretch();
    infoBoutonChronoLayout->setContentsMargins(0, 0, 0, 20); // G H D B

    QHBoxLayout *dossardLayout = new QHBoxLayout;
    dossardLayout->addWidget(labelNumeroDossard);
    dossardLayout->addWidget(lineEditNumeroDossard);
    dossardLayout->addWidget(bAssocier);
    dossardLayout->setContentsMargins(0, 10, 0, 0); // G H D B
    dossardLayout->addStretch();

    QHBoxLayout *infoArriveesLayout = new QHBoxLayout;
    infoArriveesLayout->addWidget(labelZoneArrivees);
    infoArriveesLayout->addStretch();
    infoArriveesLayout->addWidget(labelNbArriveesNonClassees);
    infoArriveesLayout->addWidget(QLCDNbArriveesNonClassees);
    infoArriveesLayout->addStretch();
    infoArriveesLayout->addWidget(labelNbArriveesClassees);
    infoArriveesLayout->addWidget(QLCDNbArriveesClassees);
    infoArriveesLayout->addStretch();

    QVBoxLayout *arriveesLayout = new QVBoxLayout;
    arriveesLayout->addLayout(infoArriveesLayout);
    arriveesLayout->addWidget(vueListeTempsArriveesNonClassees);
    arriveesLayout->setContentsMargins(0, 0, 0, 10); // G H D B

    QVBoxLayout *messageDossardLayout = new QVBoxLayout;
    messageDossardLayout->addStretch();
    messageDossardLayout->addWidget(labelMessageDossard);
    messageDossardLayout->addStretch();

    QVBoxLayout *chronoLayout = new QVBoxLayout;
    chronoLayout->addLayout(courseLayout);
    chronoLayout->addLayout(QLCDChronoLayout);
    chronoLayout->addLayout(infoBoutonChronoLayout);
    chronoLayout->addLayout(arriveesLayout);
    chronoLayout->addWidget(labelMessageSupprimer);
    chronoLayout->addLayout(dossardLayout);
    chronoLayout->addLayout(messageDossardLayout);

    QHBoxLayout *panneauLayout = new QHBoxLayout;
    panneauLayout->addLayout(classementLayout);
    panneauLayout->addLayout(chronoLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(listesLayout);
    mainLayout->addLayout(panneauLayout);

    setLayout(mainLayout);
    setWindowTitle(tr("Chrono-Cross"));
    setContextMenuPolicy(Qt::ActionsContextMenu);

    // les connexions
    connect(actionQuitter, SIGNAL(triggered()), this, SLOT(quitter()));
    connect(actionEntrerPAD, SIGNAL(triggered()), this, SLOT(associerArriveeDossard()));
    connect(actionEntrerRETURN, SIGNAL(triggered()), this, SLOT(associerArriveeDossard()));

    connect(bSynchroniser, SIGNAL(clicked()), this, SLOT(preparerCourse()));
    connect(bLancer, SIGNAL(clicked()), this, SLOT(lancerCourse()));
    connect(bAssocier, SIGNAL(clicked()), this, SLOT(associerArriveeDossard()));
    connect(bArreter, SIGNAL(clicked()), this, SLOT(arreterCourse()));
    connect(bTerminer, SIGNAL(clicked()), this, SLOT(terminerCourse()));

    connect(course, SIGNAL(chronoCreer()), this, SLOT(initialiserCourse()));
    connect(course, SIGNAL(chronoCoursePret()), this, SLOT(parer()));
    connect(course, SIGNAL(courseCommence()), this, SLOT(lancerChronoIHM()));
    connect(course, SIGNAL(classementArrete()), this, SLOT(arreterChrono()));
    connect(course, SIGNAL(courseFinie()), this, SLOT(terminerChrono()));

    connect(course, SIGNAL(nouveauTempsArrivee(QString)), this, SLOT(ajouterArriveeCoureur(QString)));

    connect(course, SIGNAL(informationCoureurRecuperees(QStringList)), this, SLOT(classerArrivee(QStringList)));
    connect(course, SIGNAL(chronoRecommence()), this, SLOT(commencerNouvelleCourse()));

    connect(cbListeManifestations, SIGNAL(currentIndexChanged(QString)), this, SLOT(listerCourses(QString)));

    connect(cbListeCourses, SIGNAL(currentIndexChanged(QString)), this, SLOT(afficherInformationsCourse(QString)));
    connect(cbListeCourses, SIGNAL(currentIndexChanged(QString)), this, SLOT(creerCourse(QString)));

    connect(m_timer, SIGNAL(timeout()), this, SLOT(tic()));

    listerManifestations();

    setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
    showMaximized();
}

/**
* @brief Destructeur de la fenêtre principale
* @fn IHMChronoCross::~IHMChronoCross()
*/
IHMChronoCross::~IHMChronoCross()
{
    BaseDeDonnees::detruireInstance();
    qDebug() << Q_FUNC_INFO;
}

/**
* @brief Méthode listerManifestations() de la Classe IHMChronoCross
* @fn IHMChronoCross::listerManifestations()
* @details Lister les manifestations à venir
*/
void IHMChronoCross::listerManifestations()
{
    QStringList listeManifestation = course->getListeManifestations();
    int nbManifestations = listeManifestation.size();
    for(int i = 0; i < nbManifestations; i += 1)
    {
        cbListeManifestations->addItem(listeManifestation[i]);
    }
}

/**
* @brief Méthode verifierCourseSelectionnee() de la classe IHMChronoCross
* @fn IHMChronoCross::verifierCourseSelectionnee()
* @details
* @param courseSelectionnee
* @return
*/
bool IHMChronoCross::verifierCourseSelectionnee(QString courseSelectionnee)
{
    if(!courseSelectionnee.isEmpty())
    {
        if(courseSelectionnee != "< Séléctionner une Course >")
        {
            return true;
        }
        else
            return false;
    }
    else
        return false;
}

/**
* @brief Méthode setRouge() de la classe IHMChronoCross
* @fn IHMChronoCross::setRouge()
* @details Initialise l'image ledRouge
* @param label de l'image
*/
void IHMChronoCross::setRouge(QLabel *label)
{
    QImage image;
    image.load(":/images/rouge.png");
    QPixmap pixmap = QPixmap::fromImage(image);
    label->setPixmap(pixmap);
}

/**
* @brief Méthode setVert() de la classe IHMChronoCross
* @fn IHMChronoCross::setVert()
* @details Initialise l'image ledVerte
* @param label de l'image
*/
void IHMChronoCross::setVert(QLabel *label)
{
    QImage image;
    image.load(":/images/vert.png");
    QPixmap pixmap = QPixmap::fromImage(image);
    label->setPixmap(pixmap);
}

/**
* @brief Méthode setOrange() de la classe IHMChronoCross
* @fn IHMChronoCross::setOrange()
* @details Initialise l'image ledOrange
* @param label de l'image
*/
void IHMChronoCross::setOrange(QLabel *label)
{
    QImage image;
    image.load(":/images/orange.png");
    QPixmap pixmap = QPixmap::fromImage(image);
    label->setPixmap(pixmap);
}

/**
 * @brief Méthode reinitialiserInfoCourse() de la classe IHMChronoCross
 * @fn IHMChronoCross::reinitialiserInfoCourse()
 * @details Permet de réinitialiser les informations de la course sur l'IHM
 */
void IHMChronoCross::reinitialiserInfoCourse()
{
    labelNomCourse->setText("Nom :");
    labelDistanceCourse->setText("Distance :");
    labelHeureCourse->setText("Heure :");
    labelNbInscrit->setText("Inscrits :");

    QLCDNbArriveesClassees->display("--");
    QLCDNbArriveesNonClassees->display("--");
}

/**
 * @brief Méthode reinitialiserClassement() de la classe IHMChronoCross
 * @fn IHMChronoCross::reinitialiserClassement()
 * @details vide le classement mais conserve l'entête des colonnes
 */
void IHMChronoCross::reinitialiserClassement()
{
        modeleClassement->clear();
        modeleClassement->setHorizontalHeaderLabels(nomColonnes);
}

/**
* @brief Méthode initialiserConfirmationDialog() de la classe IHMChronoCross
* @fn IHMChronoCross::initialiserConfirmationDialog()
* @details Initialise la page dialog de confirmation pour la suppression d'un temps
*/
void IHMChronoCross::initialiserConfirmationDialog()
{
    QString temps = tempsArriveesNonClassees.front();
    confirmationDialog = new QDialog(this);
    labelConfirmationDialog = new QLabel (tr("Etes vous sûr de vouloir supprimer le temps %1 ?").arg(temps));
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
    connect(bConfirmationDialog, SIGNAL(clicked()), this, SLOT(supprimerPremierTemps()));
    qDebug() << Q_FUNC_INFO;

    confirmationDialog->setLayout(mainDialogLayout);
    confirmationDialog->exec();
}

/**
 * @brief Méthode personnaliserAffichageArrivee() de la classe IHMChronoCross
 * @fn IHMChronoCross::personnaliserAffichageArrivee()
 * @details Personnalise les trois premières lignes du classement en or argent et bronze
 * @param nbLignesClassement
 */
void IHMChronoCross::personnaliserAffichageArrivee(int nbLignesClassement)
{
    QFont texteClassement;
    texteClassement.setPointSize(TAILLETEXTECLASSEMENT);
    texteClassement.setBold(true);

    switch(nbLignesClassement)
    {
        case 0:
            for(int i = 0; i < 5; i+=1)
            {
                QStandardItem *item = modeleClassement->item(nbLignesClassement, i);
                item->setBackground(QColor(255,223,0));
                item->setFont(texteClassement);
            }
        break;

        case 1:
            for(int i = 0; i < 5; i+=1)
            {
                QStandardItem *item = modeleClassement->item(nbLignesClassement, i);
                item->setBackground(QColor(192,192,192));
                item->setFont(texteClassement);
            }
        break;

        case 2:
            for(int i = 0; i < 5; i+=1)
            {
                QStandardItem *item = modeleClassement->item(nbLignesClassement, i);
                item->setBackground(QColor(205,127,50));
                item->setFont(texteClassement);
            }
        break;

    }
}

/**
 * @brief Méthode getSeconde() de la classe IHMChronoCross
 * @fn IHMChronoCross::getSeconde
 * @return Retourne la valeur de m_valeur pour les secondes
 */
long IHMChronoCross::getSeconde()
{
    return (m_valeur / 10) % 60;
}

/**
 * @brief Méthode getMinute() de la classe IHMChronoCross
 * @fn IHMChronoCross::getMinute
 * @return Retourne la valeur de m_valeur pour les Minutes
 */
long IHMChronoCross::getMinute()
{
    return (m_valeur % 36000) / 600;
}

/**
 * @brief Méthode getHeure() de la classe IHMChronoCross
 * @fn IHMChronoCross::getHeure
 * @return Retourne la valeur de m_valeur pour les heures
 */
long IHMChronoCross::getHeure()
{
    return m_valeur / 36000;
}

/**
 * @brief Méthode update() de la classe IHMChronoCross
 * @fn IHMChronoCross::update
 * @details Permet de mettre à jour l'horloge interne de l'IHM
 */
void IHMChronoCross::update()
{
    QString heure, minute, seconde;

    if (getHeure() < 10)
    {
        heure = "0" + QString::number(getHeure());
    }
    else heure = QString::number(getHeure());

    if (getMinute() < 10)
    {
        minute = "0" + QString::number(getMinute());
    }
    else minute = QString::number(getMinute());

    if (getSeconde() < 10)
    {
        seconde = "0" + QString::number(getSeconde());
    }
    else seconde = QString::number(getSeconde());

    if (getHeure() == 24)
    {
        m_valeur = 0;
    }

    QString text = heure + ":" + minute + ":" + seconde;
    QLCDChrono->display(text);
}

// public

/**
* @brief Méthode listerCourses() de la Classe IHMChronoCross
* @fn IHMChronoCross::listerCourses()
* @details Liste et d'affiche les courses à venir à partir d'une manifestation séléctionnée
*/
void IHMChronoCross::listerCourses(QString manifestation)
{
    QVector<QString> listeCourses = course->getListeCourses(manifestation);
    int nbCourses = listeCourses.size();

    //si l'utilisateur change de manifestation on vide la liste course
    if(cbListeCourses->count() != 0)
    {
        cbListeCourses->clear();
        cbListeCourses->addItem(tr("< Séléctionner une Course >"));
    }

    for(int i = 0; i < nbCourses; i += 1)
    {
        cbListeCourses->addItem(listeCourses[i]);
    }
}

/**
* @brief Méthode creerCourse() de la classe IHMChronoCross
* @fn IHMChronoCross::creerCourse()
* @details Si l'utilisateur a selectionner une course valide, utilise la méthode creerChrono() de la classe Course
*/
void IHMChronoCross::creerCourse(QString nomCourse)
{
    qDebug() << Q_FUNC_INFO << verifierCourseSelectionnee(nomCourse);
    if(verifierCourseSelectionnee(nomCourse))
        course->creerChrono();
}

/**
* @brief SLOT initialiserCourse() de la classe IHMChrono-Cross
* @fn IHMChronoCross::initialiserCourse()
* @details Si le chronomètre est pret alors on initialse l'état de la course dans la BDD à "prete", on change la led et on affiche le bouton Synchroniser
*/
void IHMChronoCross::initialiserCourse()
{
    if(course->estChronometragePret())
    {
        course->setEtat("Prete");
        setOrange(labelLedChrono);
        bSynchroniser->setEnabled(true);
    }
    else
        qDebug() << Q_FUNC_INFO << "Erreur";
}

/**
* @brief Slots preparerCourse() de la classe IHMChronoCross
* @fn IHMChronoCross::preparerCourse()
* @details Utilise la méthode preparerChrono() de la classe Course
*/
void IHMChronoCross::preparerCourse()
{
    qDebug() << Q_FUNC_INFO << "\nbDemarrer\n";
    course->preparerChrono();
}

/**
* @brief Private SLOT parer() de la classe IHMChronoCross
* @fn IHMChronoCross::parer()
* @details Affiche la led Orange pour la course, on désactive le bouton synchroniser et on active le bouton lancer
*/
void IHMChronoCross::parer()
{
    setOrange(labelLedCourse);
    bSynchroniser->setEnabled(false);
    bLancer->setEnabled(true);
}

/**
* @brief SLOT lancerCourse() de la classe IHMChronoCross
* @fn IHMChronoCross::lancerCourse()
* @details  Change l'état de la course dans la BDD en passant en mode EnCours et utilise la méthode chronometrer de la classe Course.
*/
void IHMChronoCross::lancerCourse()
{
    course->chronometrer();
    course->setEtat("EnCours");
}

/**
* @brief SLOTS lancerChronoIHM() de la classe IHMChronoCross
* @fn IHMChronoCross::lancerChronoIHM()
* @details Permet d'initialiser le QLCDChrono, d'activer le bouton Arreter et de désactiver le bouton Chronometrer. On passe les leds à l'état vert.
*/
void IHMChronoCross::lancerChronoIHM()
{
    QLCDChrono->display("00:00:00");
    m_timer->start(100);
    setVert(labelLedCourse);
    setVert(labelLedChrono);
    bLancer->setEnabled(false);
    bArreter->setEnabled(true);
}

/**
* @brief SLOT arreterCourse() de la Classe IHMChronoCross
* @fn IHMChronoCross::arreterCourse
* @details Permet d'appeler la méthode arreterClassement() de la classe Course. On désactive le bouton arreter. On passe la course à l'état "Arretee" la led course passe au rouge.
*/
void IHMChronoCross::arreterCourse()
{
   course->arreterClassement();
   course->setEtat("Arretee");
   setRouge(labelLedCourse);
   m_timer->stop();
   bArreter->setEnabled(false);
   labelMessageDossard->clear();
}

/**
* @brief SLOT arreterChrono() de la classe IHMChronoCross
* @fn IHMChronoCross::arreterChrono
* @details appele la méthode arreterChrono() de la classe Course
*/
void IHMChronoCross::arreterChrono()
{
    course->arreterChrono();
}

/**
* @brief SLOT terminerChrono() de la classe IHMChronoCross
* @fn IHMChronoCross::terminerChrono
* @details  Permet de désactiver le QLCD et d'activer le bouton terminer
*/
void IHMChronoCross::terminerChrono()
{
    QLCDChrono->display("--:--:--");
    m_timer->stop();
    bTerminer->setEnabled(true);
}

/**
* @brief Private SLOT terminerCourse() de la classe IHMChronoCross
* @fn IHMChronoCross::terminerCourse
* @details Permet de passer la led chrono à l'état rouge et réinitialser les informations course affiché
*/
void IHMChronoCross::terminerCourse()
{
   setRouge(labelLedChrono);
   course->setEtat("Terminee");
   reinitialiserInfoCourse();
   reinitialiserClassement();
   nbArriveesNonClassees = 0;
   nbLignesClassement = 0;
   nbArriveesClassees = 0;
   nbCoureurArrive = 0;
   m_valeur = 0;
   qDebug() << Q_FUNC_INFO << "on recommence";
}

/**
* @brief SLOT commencerNouvelleCourse() de la classe IHMChronoCross
* @fn IHMChronoCross::commencerNouvelleCourse()
* @details Reinitialise le QLCDChrono pour lancer une nouvelle course.
*/
void IHMChronoCross::commencerNouvelleCourse()
{
    modeleClassement->clear();
    modeleClassement->setHorizontalHeaderLabels(nomColonnes);
    vueTableauClassement->setModel(modeleClassement);
}

/**
* @brief SLOT ajouterArriveeCoureur(QString tempsArrivee) de la classe IHMChronoCross
* @fn IHMChronoCross::ajouterArriveeCoureur(QString tempsArrivee)
* @details  Permet de récupérer la trame des coureurs, stocker les performances dans une variable et les afficher dans l'espace Arrivées non classées.
*/
void IHMChronoCross::ajouterArriveeCoureur(QString tempsArrivee)
{
    bAssocier->setEnabled(true);
    lineEditNumeroDossard->setEnabled(true);
    lineEditNumeroDossard->setFocus();

    labelMessageSupprimer->setText("Pour supprimer le premier temps non classées \nVeuillez entrer le numéro de dossard 0000 puis confirmer.");

    // on ajoute le tempsArrivee au QStringList tempsArriveesNonClassees
    tempsArriveesNonClassees.push_back(tempsArrivee);

    this->mettreAJourNbArriveesNonClassees(1);

    int nbLignesListArriveesNonClassees = modeleArriveesNonClassees->rowCount();
    modeleArriveesNonClassees->insertRow(nbLignesListArriveesNonClassees);
    QModelIndex index = modeleArriveesNonClassees->index(nbLignesListArriveesNonClassees);
    modeleArriveesNonClassees->setData(index, QString(tempsArrivee));
}

/**
* @brief SLOT associerArriveeDossard() de la classe IHMChronoCross
* @fn IHMChronoCross::associerArriveeDossard()
* @details  Selon le nombre entré dans le lineEdit on peut supprimer le premier temps de la liste des temps non classées et associer un temps et un dossard après vérification
*/
void IHMChronoCross::associerArriveeDossard()
{
    if(!tempsArriveesNonClassees.empty())
    {
        QString dossard = lineEditNumeroDossard->text();
        if(dossard != "0000")
        {
            QString tempsArrivee = tempsArriveesNonClassees.front();
            qDebug() << Q_FUNC_INFO << "Temps arrivee : " <<tempsArrivee;
            if(tempsArrivee != "")
            {
                int verification = course->verifierDossard(dossard);
                if(verification != NUMERO_DOSSARD_INVALIDE)
                {
                    if(verification == DOSSARD_VALIDE_COURSE_INVALIDE)
                    {
                    // numéro de dossard valide mais inscrit pour une autre course
                        QString nomCourseInvalide = cbListeCourses->currentText();
                        QString nomCourseValire = course->getNomCourse(dossard);
                        labelMessageDossard->setStyleSheet("color : #FF0000");
                        labelMessageDossard->setText(QString("Numéro de dossard %1 : valide mais non-inscrit à la course %2.\nLe dossard %1 est inscrit pour la course %3.").arg(dossard).arg(nomCourseInvalide).arg(nomCourseValire));
                        lineEditNumeroDossard->clear();
                    }
                    else if(verification == DOSSARD_DEJA_ARRIVE)
                    {
                        // numéro de dossard valide mais le coureur a déjà franchi la ligne d'arrivée
                            QString nomCourse = cbListeCourses->currentText();
                            labelMessageDossard->setStyleSheet("color : #FF0000");
                            labelMessageDossard->setText(QString("Numéro de dossard %1 : valide mais le coureur a déjà franchi la ligne d'arrivée.").arg(dossard).arg(nomCourse));
                            lineEditNumeroDossard->clear();
                    }
                    else if(verification == DOSSARD_VALIDE)
                    {
                        if(labelMessageDossard->styleSheet() == "color : #FF0000")
                            labelMessageDossard->setStyleSheet("color : #000000");

                        mettreAJourNbArriveesNonClassees(-1);
                        mettreAJourNbArriveesClassees(1);

                        course->ajouteArriveeBDD(dossard, tempsArrivee);

                        labelMessageDossard->setText(QString("Numéro de dossard %1 : validé\nLe temps %2 est associé au dossard %1").arg(dossard).arg(tempsArrivee));

                        //enléve le premier temps et vide le lineEditeNumeroDossard
                        modeleArriveesNonClassees->removeRows(0,1);
                        tempsArriveesNonClassees.pop_front();
                        lineEditNumeroDossard->clear();
                    }
                }
                else
                {
                    labelMessageDossard->setStyleSheet("color : #FF0000");
                    labelMessageDossard->setText(QString("Numéro de dossard %1 : invalide").arg(dossard));
                    lineEditNumeroDossard->clear();
                }
            }
            else
            {
                qDebug() << Q_FUNC_INFO << "Aucun numéro entré";
                labelMessageDossard->setText("Aucun numéro de dossard entré");
            }

        }
        else
        {
            lineEditNumeroDossard->clear();
            this->initialiserConfirmationDialog();
            qDebug() << Q_FUNC_INFO << "DEMANDE DE SUPPRESSION DU PREMIER TEMPS";
        }
    }
}

/**
* @brief SLOT classerArrivee() de la classe IHMChronoCross
* @param informationCoureur
* @fn IHMChronoCross::classerArrivee
* @details Permet de classer les arrivées dans le tableau classement, pour les 3 premiers temps on utilise la méthode personnaliserAffichageArrivee()
*/
void IHMChronoCross::classerArrivee(QStringList informationCoureur)
{
    qDebug() << Q_FUNC_INFO << informationCoureur;
    //informationCoureur[ temps, dossard, Nom, Prenom, Classe]

    QStandardItem *temps = new QStandardItem(informationCoureur.at(INFO_COUREUR_TEMPS));
    QStandardItem *dossard = new QStandardItem(informationCoureur.at(INFO_COUREUR_DOSSARD));
    QStandardItem *nom = new QStandardItem(informationCoureur.at(INFO_COUREUR_NOM));
    QStandardItem *prenom = new QStandardItem(informationCoureur.at(INFO_COUREUR_PRENOM));
    QStandardItem *classe = new QStandardItem(informationCoureur.at(INFO_COUREUR_CLASSE));

    modeleClassement->setItem(nbLignesClassement, COLONNE_TEMPS, temps);
    modeleClassement->setItem(nbLignesClassement, COLONNE_DOSSARD, dossard);
    modeleClassement->setItem(nbLignesClassement, COLONNE_NOM, nom);
    modeleClassement->setItem(nbLignesClassement, COLONNE_PRENOM, prenom);
    modeleClassement->setItem(nbLignesClassement, COLONNE_CLASSE, classe);

    qDebug() << Q_FUNC_INFO << nbLignesClassement;

    if(nbLignesClassement < 3)
        personnaliserAffichageArrivee(nbLignesClassement);

    nbLignesClassement += 1;
}

/**
* @brief SLOT quitter() de la classe IHMChronoCross
* @fn IHMChronoCross::quitter()
* @details  Action permet de fermer la page
*/
void IHMChronoCross::quitter()
{
    close();
}

/**
* @brief Méthode tic() de la classe IHMChronoCross
* @fn IHMChronoCross::tic
* @details Ajoute un au chrono interne de l'IHM et utilise la méthode update
*/
void IHMChronoCross::tic()
{
    m_valeur++;
    update();
}

/**
* @brief SLOT afficherInformationsCourse() de la classe IHMChronoCross
* @fn IHMChronoCross::afficherInformationsCourse()
* @details Affiche les informations d'une course
* @param nomCourse
*/
void IHMChronoCross::afficherInformationsCourse(QString nomCourse)
{
    //information course
    if(nomCourse != "" )
    {
        if(nomCourse != "< Séléctionner une Course >")
        {
            // nom
            labelNomCourse->setText(QString("Nom : %1").arg(nomCourse));

            // distance
            int distance = course->getDistance(nomCourse);
            labelDistanceCourse->setText(QString("Distance : %1").arg(distance));

            // heure
            QString heure = course->getHeure(nomCourse);
            labelHeureCourse->setText(QString("Heure : %1").arg(heure));

            //setID
            course->setIdCourse(nomCourse);
        }
    }

    //information coureur course
    int nbInscrit = 0;
    if(nomCourse != "" )
    {
        if(nomCourse != "< Séléctionner une Course >")
        {
            nbInscrit = course->getNbInscrit(nomCourse);
            qDebug() << Q_FUNC_INFO << "nbInscrits : " << nbInscrit;
            labelNbInscrit->setText(QString("Inscrits : %1").arg(nbInscrit));
            QLCDNbArriveesClassees->display("00");
            QLCDNbArriveesNonClassees->display("00");
        }
    }
}

/**
 * @brief SOT mettreAJourNbArriveesNonClassees() de la classe IHMChronoCross
 * @fn IHMChronoCross::mettreAJourNbArriveesNonClassees()
 * @details Permet de mettre à jour le nombre d'arrivées non classées
 * @param nbArrivee
 */
void IHMChronoCross::mettreAJourNbArriveesNonClassees(int nbArrivee)
{
    nbArriveesNonClassees += nbArrivee;
    if(nbArriveesNonClassees < 10)
    {
        QString strNbArriveesNonClassees = QString::number(nbArriveesNonClassees);
        strNbArriveesNonClassees = "0" + strNbArriveesNonClassees;
        QLCDNbArriveesNonClassees->display(strNbArriveesNonClassees);
    }
    else
        QLCDNbArriveesNonClassees->display(nbArriveesNonClassees);
}

/**
 * @brief SLOT mettreAJourNbArriveesClassees() de la classe IHMChronoCross
 * @fn IHMChronoCross::mettreAJourNbArriveesClassees()
 * @details Permet de mettre à jour le nombre d'arrivées non classées
 * @param nbArrivee
 */
void IHMChronoCross::mettreAJourNbArriveesClassees(int nbArrivee)
{
    nbCoureurArrive += nbArrivee;
    nbArriveesClassees = nbCoureurArrive;
    if(nbArriveesClassees < 10)
    {
        QString strNbArriveesClassees = QString::number(nbArriveesClassees);
        strNbArriveesClassees = "0" + strNbArriveesClassees;
        QLCDNbArriveesClassees->display(strNbArriveesClassees);
        qDebug() << Q_FUNC_INFO << "nbArriveesClassees : " << nbArriveesClassees;
    }
    else
        QLCDNbArriveesClassees->display(nbArriveesClassees);
        qDebug() << Q_FUNC_INFO << "nbArriveesClassees : " << nbArriveesClassees;
}

/**
* @brief SLOT quitterDialog() de la classe IHMChronoCross
* @fn IHMChronoCross::quitterDialog()
* @details Permet de fermer la page dialog Confirmation
*/
void IHMChronoCross::quitterDialog()
{
    confirmationDialog->close();
    qDebug() << Q_FUNC_INFO;
}

/**
* @brief SLOT supprimerPremierTemps() de la classe IHMChronoCross
* @fn IHMChronoCross::supprimerPremierTemps()
* @details Permet de supprimer le permier temps de la liste des temps non classées.
*/
void IHMChronoCross::supprimerPremierTemps()
{
    modeleArriveesNonClassees->removeRows(0,1);
    tempsArriveesNonClassees.pop_front();
    confirmationDialog->close();
    this->mettreAJourNbArriveesNonClassees(-1);
}
