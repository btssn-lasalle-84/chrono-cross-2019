#ifndef RESULTAT_H
#define RESULTAT_H

#include <QObject>

class BaseDeDonnees;
class Coureur;

class Resultat : public QObject
{
    Q_OBJECT
public:
    explicit Resultat(QObject *parent = nullptr);
    ~Resultat();

private:
    BaseDeDonnees *BDD;  //!< agrégation BaseDeDonnees
    Coureur *coureur; //!< association Coureur

    // void ajouterCoureurAuResultat();


signals:

public slots:

};

#endif // RESULTAT_H
