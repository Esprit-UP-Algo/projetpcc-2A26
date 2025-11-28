#ifndef GESTION_FOURNISSEUR_H
#define GESTION_FOURNISSEUR_H

#include <QString>
#include <QRegularExpression>
#include <QSqlQuery>
#include <QSqlQueryModel>


#include <QSqlError>
#include "connection.h"

class Gestion_Fournisseur
{
private:
    QString ID,NOM,EMAIL,TEL,CATEGORIE,ADRESSE;


public:
    Gestion_Fournisseur();
    Gestion_Fournisseur(  QString ID,QString NOM,QString EMAIL,QString TEL,QString CATEGORIE,QString ADRESSE);



    //getters
    QString getID() { return ID ;}
    QString getADRESSE() { return ADRESSE ;}
    QString getNOM() { return NOM ;}
    QString getEMAIL() { return EMAIL ;}
    QString getTEL() { return TEL ;}
    QString getCATEGORIE() { return CATEGORIE;}

    //setters
    void setID (QString ID){ this->ID = ID; }
    void setADRESSE (QString ADRESSE){  this->ADRESSE = ADRESSE;}
    void setNOM (QString NOM){ this->NOM = NOM; }
    void setEMAIL (QString EMAIL){ this->EMAIL = EMAIL; }
    void setTEL (QString TEL){  this->TEL = TEL;}
    void setCATEGORIE (QString CATEGORIE){this->CATEGORIE = CATEGORIE;}

    //crud
    bool ajouter_fournisseurs();
    QSqlQueryModel* afficher();
    bool modifier_fournisseurs();
    bool supprimer_fournisseurs(const QString &ID);


    QSqlQueryModel* rechercher_fournisseur(const QString &ID);
    QSqlQueryModel* trier_fournisseurs(const QString &critere);



};

#endif // GESTION_FOURNISSEUR_H
