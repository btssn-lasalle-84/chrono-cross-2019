#ifndef COUREUR_H
#define COUREUR_H

/**
*
* @class Coureur
*
* @brief Gérer les coureurs
*
* @author Suzie Turlin
*
* @version 0.1
*
*/

#include <QObject>

class BaseDeDonnees;

class Coureur : public QObject
{
    Q_OBJECT

private:
    QString nom;
    QString prenom;
    QString INE;
    QString classe;
    BaseDeDonnees *BDD; //!< agrégation BaseDeDonnees
    QString formulerRequeteSelect(QString renseignements, QString sources, QString conditions);

public:
    explicit Coureur(QObject *parent = nullptr);
    ~Coureur();

    // TODO faire le constructeur avec les attributs
    QString getNom() const;
    QString getPrenom() const;
    QString getINE() const;
    QString getClasse() const;

    QVector<QString> getListeCoureurs(QString Coureur);

signals:

public slots:
    QStringList getListeCoureurs(QString, QString, QString, QString);
};
#endif // COUREUR_H
