#ifndef GESTION_FOURNISSEUR_H
#define GESTION_FOURNISSEUR_H

#include <QString>
#include <QRegularExpression>
#include <QSqlQuery>
#include <QSqlError>
#include "connection.h"

class Gestion_Fournisseur
{
public:
    Gestion_Fournisseur();
    Gestion_Fournisseur(int id, const QString &nomEntreprise,
                        const QString &personneContact, const QString &adresse,
                        int telephone, const QString &mail,
                        const QString &categorie, const QString &details,
                        float noteFiabilite);

    // Getters
    int getId() const;
    QString getNomEntreprise() const;
    QString getPersonneContact() const;
    QString getAdresse() const;
    int getTelephone() const;
    QString getMail() const;
    QString getCategorie() const;
    QString getDetails() const;
    float getNoteFiabilite() const;

    // Setters
    bool setId(int id);
    bool setNomEntreprise(const QString &nom);
    bool setPersonneContact(const QString &personne);
    bool setAdresse(const QString &adresse);
    bool setTelephone(int telephone);
    bool setMail(const QString &mail);
    bool setCategorie(const QString &categorie);
    bool setDetails(const QString &details);
    bool setNoteFiabilite(float note);

    // CRUD
    static bool ajouterFournisseur(int id, const QString &nomEntreprise,
                                   const QString &personneContact, const QString &adresse,
                                   int telephone, const QString &mail,
                                   const QString &categorie, const QString &details,
                                   float noteFiabilite, QString &erreurMessage);

    static bool supprimerFournisseur(int id, QString &erreurMessage);
    static QList<Gestion_Fournisseur> chargerTousLesFournisseurs();
    static bool modifierFournisseur(int id, const QString &nomEntreprise,
                                    const QString &personneContact, const QString &adresse,
                                    int telephone, const QString &mail,
                                    const QString &categorie, const QString &details,
                                    float noteFiabilite, QString &erreurMessage);

    // Validation
    bool isValid() const;
    static bool isValidId(int id);
    static bool isValidNom(const QString &nom);
    static bool isValidMail(const QString &mail);
    static bool isValidTelephone(int telephone);
    static bool isValidCategorie(const QString &categorie);

private:
    int m_id;
    QString m_nomEntreprise;
    QString m_personneContact;
    QString m_adresse;
    int m_telephone;
    QString m_mail;
    QString m_categorie;
    QString m_details;
    float m_noteFiabilite;
};

#endif // GESTION_FOURNISSEUR_H
