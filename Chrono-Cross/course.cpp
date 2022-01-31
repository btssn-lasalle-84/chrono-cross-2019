/**
* @file Chrono-Cross/course.cpp
* @brief Définition de la classe Course
* @author Michael Andréo
* @version 1.1
*/

#include "course.h"

/**
 * @brief Constructeur de la classe Course
 * @fn Course::Course
 * @param parent QObject Adresse de l'objet Qt parent (0 = pas de parent car c'est la fenêtre principale)
 */
Course::Course(QObject *parent) : QObject(parent)
{
    BDD = BaseDeDonnees::getInstance();
    if(!BDD->estConnecte())
        BDD->connecter("Chrono-Cross");
    qDebug() << Q_FUNC_INFO << "Etat connexion BDD : " << BDD->estConnecte();

    monChrono = new Chrono(this);

    connect(monChrono, SIGNAL(chronoCreer()), this, SLOT(aChronoCree()));
    connect(monChrono, SIGNAL(chronoSynchroniser()), this, SLOT(aChronoSynchronise()));
    connect(monChrono, SIGNAL(classementCree()), this, SLOT(aClassementCree()));
    connect(monChrono, SIGNAL(chronoLance()), this, SLOT(aCommencee()));
    connect(monChrono, SIGNAL(courseArretee()), this, SLOT(aClassementArrete()));
    connect(monChrono, SIGNAL(chronoArrete()), this, SLOT(estFinie()));
    connect(monChrono, SIGNAL(nouvelleArrivee(QString)), this, SLOT(traiterArriveeCoureur(QString)));
    connect(monChrono, SIGNAL(chronoRecommence()), this, SLOT(recommencerChrono()));
    connect(this, SIGNAL(arriveeAjouteeBDD(QString, QString)), this, SLOT(getInformationCoureur(QString, QString)));
}

/**
* @brief Destructeur de la fenêtre principale
* @fn Course::~Course
*/
Course::~Course()
{
    BaseDeDonnees::detruireInstance();
    qDebug() << Q_FUNC_INFO;
}

/**
* @brief Méthode formulerRequeteSelect de la classe Course
* @fn Course::formulerRequeteSelect
* @details Méthode qui renvoie la requête SQL formatée avec les arguments demandés.
* @param renseignements QString informations que l'on recherche
* @param sources QString où se trouve l'information recherchée
* @param conditions QString paramètres de recherche
* @return La requête SQL
*/
QString Course::formulerRequeteSelect(QString renseignements, QString sources, QString conditions)
{
    QString requete = QString("SELECT %1 FROM %2 WHERE %3").arg(renseignements).arg(sources).arg(conditions);
    return requete;
}

/**
* @brief Méthode creerChrono() de la classe Course
* @fn Course::creerChrono()
* @details Utilise la méthode creerChrono() de la classe Chrono
*/
void Course::creerChrono()
{
    monChrono->creer();
}

/**
* @brief Méthode preparerChrono() de la classe Course
* @fn Course::preparerChrono()
* @details Méthode qui appelle la méthode synchroniser de la classe Chrono
*/
void Course::preparerChrono()
{
    if(monChrono->synchroniser())
    {
        qDebug() << Q_FUNC_INFO << "SYNCHRO OK";
    }
    else
        qDebug() << Q_FUNC_INFO << "SYNCHRO ERREUR";
}

/**
* @brief Méthode estChronometragePret() de la classe Course
* @fn Course::estChronometragePret()
* @details Méthode qui indique si le chrono est prêt à chronométrer cette course (utilise a métode estConnecte de la classe Chrono)
*/
bool Course::estChronometragePret()
{
    qDebug() << Q_FUNC_INFO << "Etat :\t" << monChrono->estConnecte();
    return monChrono->estConnecte();
}

/**
* @brief Méthode chronometrer de la classe Course
* @fn Course::chronometrer
* @details Méthode qui permet de lancer le chrono de la course
*/
void Course::chronometrer()
{
    if(monChrono->demarrer())
    {
        qDebug() << Q_FUNC_INFO << "Valide";
    }
    else
        qDebug() << Q_FUNC_INFO << "Erreur lancement chrono";
}

/**
* @brief Méthode arreterClassement() de la classe Course
* @fn Course::arreterClassement()
* @details Appelle la méthode arreterClassement () de la classe Chrono
*/
void Course::arreterClassement()
{
    monChrono->arreterCourse();
}

/**
* @brief Méthode arreterChronomètre() de la classe Course
* @fn Course::arreterChrono()
* @details Appelle la méthode arreterChrono() de la classe Chrono
*/
void Course::arreterChrono()
{
    monChrono->arreterChrono();
}

/**
* @brief Méthode verifierDossard() de la classe Course
* @fn Course::verifierDossard()
* @details Permet de verifier si un numéro de dossard est valide, si il est associer à la bonne course et si il n'a pas déjà été utilisé
* @param dossard QString numero de dossard
* @return Renvoi le résultat de la verification sous la forme d'un booléen
*/
int Course::verifierDossard(QString dossard)
{
    // 0 = Invalide , 1 = numéro valide mais mauvaise course , 2 = valide mais dossard déjà entré , 3 = valide
    int verification = 0;

    QString idInscrit;
    QString coureurs;
    QString condition = QString("NumeroDossard = %1").arg(dossard);

    bool retour = BDD->recuperer(this->formulerRequeteSelect("idInscrit", "Inscrit", condition),idInscrit);

    if(retour)
    {
        // le numéro de dossard existe
        verification = 1;
        condition = QString("idCourse = %1 AND idInscrit = %2;").arg(idCourse).arg(idInscrit);
        retour = BDD->recuperer(this->formulerRequeteSelect("*", "Inscrit", condition), coureurs);
        if(!coureurs.isEmpty())
        {
            // le numéro de dossard est enregistré pour la bonne course
            verification = 2;
            coureurs.clear();
            condition = QString("idInscrit = %1").arg(idInscrit);
            retour = BDD->recuperer(this->formulerRequeteSelect("*","Arrivee",condition), coureurs);
            qDebug() << Q_FUNC_INFO << "coureur : " << coureurs << coureurs.isEmpty();
            if(coureurs.isEmpty())
            {
                // le coureur n'a pas déjà franchi la ligne d'arrivée
                verification = 3;
                qDebug() << Q_FUNC_INFO << "Dossard validé";
                return  verification;
            }
            else
            {
                qDebug() << Q_FUNC_INFO << "Dossard valide mais ce dossard a déjà franchi la ligne d'arrivée.";
                return verification;
            }
        }
        else
        {
            qDebug() << Q_FUNC_INFO << "Dossard valide mais pas inscrit pour cette course.";
            return verification;
        }
    }
    else
    {
        qDebug() << Q_FUNC_INFO << "Numéro dossard invalide";
        return verification;
    }
}

/**
 * @brief Méthode convertirTemps() de la classe Course
 * @fn Course::convertirTemps()
 * @details Permet de convertir le temps recu sous le format HH:MM:SS.DDDDD en HH:MM:SS
 * @param tempsMS
 * @return Retourne le temps converti
 */
QString Course::convertirTemps(QString tempsMS)
{
    QString tempsS;
    QString tempsFinal;

    bool tempsConverti = false;
    int i = 0;

    while(!tempsConverti)
    {
        if(tempsMS[i] == '.')
        {
            tempsConverti = true;
        }
        else
        {
            tempsS[i] = tempsMS[i];
            i += 1;
        }
    }

    if(tempsS.length() <2)
    {
        tempsFinal = "00:00:0" + tempsS;
        return tempsFinal;
    }
    else if (tempsS.length() <3)
    {
        tempsFinal = "00:00:" + tempsS;
        return tempsFinal;
    }
    else if (tempsS.length() <5)
    {
        tempsFinal = "00:0" + tempsS;
        return tempsFinal;
    }
    else if (tempsS.length() <6)
    {
        tempsFinal = "00:" + tempsS;
        return tempsFinal;
    }
    else if (tempsS.length() <8)
    {
        tempsFinal = "0" + tempsS;
        return tempsFinal;
    }
    else
        return tempsS;
}

/**
* @brief Méthode getNbInscrit de la classe Course
* @fn Course::getNbInscrit
* @details Méthode qui renvoie le nombre d'inscrit d'une course d'après son ID depuis la base de donnée.
* @param course string nom d'une course
* @return Le nombre d'inscrit dans une course
*/
int Course::getNbInscrit(QString course)
{
    QString condition = QString("Nom = '%1'").arg(course);
    QString nbInscrit;

    bool retour = BDD->recuperer(this->formulerRequeteSelect("idCourse", "Course", condition), idCourse);

    if(retour)
    {
        retour = BDD->recuperer(QString("SELECT COUNT(*) FROM Inscrit WHERE idCourse = %1").arg(idCourse),nbInscrit);
    }

    int nb = nbInscrit.toInt();
    return nb;
}

/**
* @brief Méthode getDistance() de la classe Course
* @fn Course::getDistance()
* @details Permet de retourner la distance d'une course d'arpsè son nom
* @param course
* @return Retourne la distance d'une course
*/
int Course::getDistance(QString course)
{
    QString condition = QString("Nom = '%1'").arg(course);

    bool retour = BDD->recuperer(this->formulerRequeteSelect("Distance", "Course", condition), distance);
    if(retour)
        return distance.toInt();
    else
        qDebug() << Q_FUNC_INFO << "Erreur";
        return 0;
}

/**
* @brief Méthode getHeure() de la classe Course
* @fn Course::getHeure()
* @details Permet de retourner l'heure de départ d'une course d'après son nom
* @param course
* @return Retourne l'heure de départ d'une course
*/
QString Course::getHeure(QString course)
{
    QString condition = QString("Nom = '%1'").arg(course);

    bool retour = BDD->recuperer(this->formulerRequeteSelect("HeureDepart", "Course", condition), heureDepart);

    if(retour)
        return heureDepart;
    else
        qDebug() << Q_FUNC_INFO << "Erreur";
        return "";
}

/**
* @brief Méthode getNbArrivee() de la classe Course
* @fn Course::getNbArrivee()
* @details Permet de récupérer le nombre de coureur de la table Arrivee
* @return Le nombre d'arrivee
*/
int Course::getNbArrivee()
{
    QString information;
    int nbArrivee;
    bool retour = BDD->recuperer("SELECT COUNT(*) FROM Arrivee WHERE 1;", information);
    if(retour)
    {
        nbArrivee = information.toInt();
        return nbArrivee;
    }
    else
        qDebug() << Q_FUNC_INFO << "Erreur";
        return 0;
}

/**
* @brief Méthode getNomCourse() de la classe Course
* @fn Course::getNomCourse()
* @details Permet de retourner le nom d'une course d'après le numéro de dossard d'un inscrit
* @param dossard
* @return Retourne le nom de la course ou rien selon l'état de la requête SQL
*/
QString Course::getNomCourse(QString dossard)
{
    QString id;
    QString nomCourse;
    QString condition = QString("NumeroDossard = %1;").arg(dossard);
    bool retour = BDD->recuperer(this->formulerRequeteSelect("idCourse", "Inscrit", condition), id);
    if(retour)
    {
        condition = QString("idCourse = %1").arg(id);
        retour = BDD->recuperer(this->formulerRequeteSelect("Nom", "Course", condition), nomCourse);
        if(retour)
            return nomCourse;
        else
        {
            qDebug() << Q_FUNC_INFO << "ERREUR";
            return nomCourse;
        }
    }
    else
    {
        qDebug() << Q_FUNC_INFO << "ERREUR";
        return nomCourse;
    }
}

/**
 * @brief Méthode setIdCourse() de la classe Course
 * @fn Course::setIdCourse()
 * @details Permet d'initialiser l'id de la course
 * @param nomCourse
 */
void Course::setIdCourse(QString nomCourse)
{
    QString condition = QString("Nom = '%1'").arg(nomCourse);
    bool retour = BDD->recuperer(this->formulerRequeteSelect("idCourse", "Course", condition), idCourse);
    qDebug() << Q_FUNC_INFO << retour;
}

/**
 * @brief Méthode ajouteArriveeBDD() de la classe Course
 * @fn Course::ajouteArriveeBDD
 * @details Permet de récupérer l'es informations 'idInscrit d'un coureur d'après son numéro de dosasrd et l'ajoute à la table Arrivee
 * @param dossard QString
 * @param tempsArrivee QString
 */
void Course::ajouteArriveeBDD(QString dossard, QString tempsArrivee)
{
    QString idInscrit;
    QString condition = QString("NumeroDossard = %1").arg(dossard);

    bool retourId = BDD->recuperer(this->formulerRequeteSelect("idInscrit", "Inscrit", condition),idInscrit);

    bool retour = BDD->executer(QString("INSERT INTO `Arrivee`(`idInscrit`, `Temps`) VALUES (%1,'%2')").arg(idInscrit).arg(tempsArrivee));

    if(retourId)
    {
        if(retour)
        {
            qDebug() << Q_FUNC_INFO << "Ajout ok !";
            emit arriveeAjouteeBDD(dossard, tempsArrivee);
        }
    }
    else
        qDebug() << Q_FUNC_INFO << "Ajout echec !";
}

/**
* @brief Méthode getListeManifestations() de la classe Course
* @details Permet de récupérer la liste des manifestations
* @fn Course::getListeManifestations
* @return Retourne un QStringList listeManifestations contenant toute les manifestations
*/
QStringList Course::getListeManifestations()
{
    QStringList listeManifestations;
    QString i;

    bool retour = BDD->recuperer("SELECT COUNT(*) FROM `Manifestation` WHERE 1", i);

    int j = i.toInt();

    qDebug() << Q_FUNC_INFO << retour << listeManifestations;

    for(int i = 1; i <= j; i += 1)
    {
        QString condition = QString("idManifestation = %1").arg(i);
        retour = BDD->recuperer(this->formulerRequeteSelect("NOM", "Manifestation", condition), listeManifestations);
        qDebug() << Q_FUNC_INFO << retour << "i =" << i << "j =" << j << listeManifestations;
    }
    return  listeManifestations;
}

/**
* @brief Méthode getListeCourses() de la classe Course
* @details Permet de récuperer les listes de courses d'après le nom de la manifestation
* @param manifestation
* @fn Course::getListeCourses
* @return Retourne un vector de QString contenant le nom des courses de la manifestation choisi
*/
QVector<QString> Course::getListeCourses(QString manifestation)
{
    QString condition = QString("Nom = '%1'").arg(manifestation);
    QString idManifestation;
    QVector<QString> courses;

    bool retour = BDD->recuperer(this->formulerRequeteSelect("idManifestation", "Manifestation", condition), idManifestation);
    qDebug() << Q_FUNC_INFO << "Etat requeteIdManifestation : " << retour << "\t info : " << idManifestation;

    condition = QString("`idManifestation` = %1 AND `Etat` = 'ACourir'").arg(idManifestation);
    retour = BDD->recuperer(this->formulerRequeteSelect("Nom", "Course", condition), courses);
    qDebug() << Q_FUNC_INFO << "Etat requeteNomCourses : " << retour << "\t info : " << courses;

/**
*@todo verifier date
**/
/*
QDate date = QDate::currentDate();
qDebug() << "\r\n\r\n" << date << "\r\n\r\n" << "\r\n\r\n";
*/

    return courses;
}

// slots

/**
* @brief SLOT aChronoCree() de la classe Course
* @fn Course::aChronoCree()
* @details Emet le signal chronoCreer
*/
void Course::aChronoCree()
{
    emit chronoCreer();
}

/**
 * @brief SLOT aChronoSynchronise() de la classe Course
 * @fn Course::aChronoSynchronise
 * @details Appelle la méthode creerClassement() de la classe Chrono
 */
void Course::aChronoSynchronise()
{
    if(monChrono->creerClassement())
        qDebug() << Q_FUNC_INFO << "NouveauClassement OK";
    else
        qDebug() << Q_FUNC_INFO << "ERREUR";
}

/**
* @brief SLOT aClassementCree de la classe Course
* @fn Course::aClassementCree
* @details Permet de signaler à la classe IHM que le chronomètre de la course est pret.
*/
void Course::aClassementCree()
{
    qDebug() << Q_FUNC_INFO << "Chrono pret";
    emit chronoCoursePret();
}

/**
* @brief SLOT aCommencee() de la classe Course
* @fn Course::aCommencee()
* @details Emet le signal courseCommence.
*/
void Course::aCommencee()
{
    qDebug() << Q_FUNC_INFO << "Course a commencée";
    emit courseCommence();
}

/**
* @brief SLOT aClassementArrete() de la classe Course
* @fn Course::aClassementArrete()
* @details Emet le signal classementArrete
*/
void Course::aClassementArrete()
{
    qDebug() << Q_FUNC_INFO << "classement est arrété";
    emit classementArrete();
}

/**
* @brief SLOT estFinie() de la classe Course
* @fn Course::estFinie()
* @details Emet le signal courseFinie().
*/
void Course::estFinie()
{
    emit courseFinie();
}

/**
* @brief SLOT recommencerChrono() de la classe Course
* @fn Course::recommencerChrono()
* @details Emet le signal chronoRecommence().
*/
void Course::recommencerChrono()
{
    emit chronoRecommence();
}

/**
* @brief SLOT traiterArriveeCoureur(QString tempsArrivee) de la classe Course
* @fn Course::traiterArriveeCoureur(QString tempsArrivee)
* @param tempsArrivee QString le temps d'arrivée
*/
void Course::traiterArriveeCoureur(QString tempsArrivee)
{
    QString temps = this->convertirTemps(tempsArrivee);
    emit nouveauTempsArrivee(temps);
}

/**
 * @brief SLOT getInformationCoureur(QString dossard, QString tempsArrivee) de la classe Course
 * @fn Course::getInformationCoureur(QString dossard, QString tempsArrivee)
 * @details Récupere les informations d'un coureur d'après son numéro de dossard, puis émet un signal contenant les informations
 * @param dossard
 * @param tempsArrivee
 */
void Course::getInformationCoureur(QString dossard, QString tempsArrivee)
{
    informationCoureurArrive << tempsArrivee << dossard;
    QString idCoureur;
    bool retour;

    qDebug() << Q_FUNC_INFO << "informationCoureurArrive" << informationCoureurArrive;

    QString condition = QString("NumeroDossard = %1").arg(dossard);
    retour = BDD->recuperer(this->formulerRequeteSelect("idCoureur", "Inscrit", condition), idCoureur);
    if(!retour)
        return;

    condition = QString("idCoureur = %1").arg(idCoureur);
    retour = BDD->recuperer(this->formulerRequeteSelect("Nom,Prenom,idClasse","Coureur",condition), informationCoureurArrive);
    if(!retour)
        return;

    condition = QString("idClasse = %1").arg(informationCoureurArrive[INFORMATION_COUREUR_ARRIVEE_CLASSE]);
    retour = BDD->recuperer(this->formulerRequeteSelect("Nom", "Classe", condition), informationCoureurArrive[INFORMATION_COUREUR_ARRIVEE_CLASSE]);
    if(!retour)
        return;

    qDebug() << Q_FUNC_INFO << "idCoureur" << idCoureur << "informationCoureurArrive" << informationCoureurArrive;

    emit informationCoureurRecuperees(informationCoureurArrive);
    informationCoureurArrive.clear();
}

/**
* @brief SLOT setEtat de la classe Course
* @fn Course::setEtat
* @details Change l'état d'une course dans la table Course
* @param etat
* @return L'état de la requête
*/
bool Course::setEtat(QString etat)
{
    bool retour = BDD->executer(QString("UPDATE `Course` SET `Etat`= '%1' WHERE `idCourse` = %2;").arg(etat).arg(idCourse));
    return retour;
}
