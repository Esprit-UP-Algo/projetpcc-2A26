#ifndef GESTION_PERSONNEL_H
#define GESTION_PERSONNEL_H

#include <QString>
#include <QDate>
#include <QRegularExpression>
#include <QSqlQuery>
#include <QSqlError>
#include "connection.h"

class Gestion_Personnel
{
public:
    Gestion_Personnel();
    Gestion_Personnel(int id, const QString &nom, const QString &prenom,
                      const QString &mail, const QString &adresse,
                      const QString &poste, const QDate &dateEmbauche,
                      const QString &statut, int idLocal);

    // Getters
    int getId() const;
    QString getNom() const;
    QString getPrenom() const;
    QString getMail() const;
    QString getAdresse() const;
    QString getPoste() const;
    QDate getDateEmbauche() const;
    QString getStatut() const;
    int getIdLocal() const;

    // Setters
    bool setId(int id);
    bool setNom(const QString &nom);
    bool setPrenom(const QString &prenom);
    bool setMail(const QString &mail);
    bool setAdresse(const QString &adresse);
    bool setPoste(const QString &poste);
    bool setDateEmbauche(const QDate &date);
    bool setStatut(const QString &statut);
    bool setIdLocal(int idLocal);

    // CRUD
    static bool ajouterPersonnel(int id, const QString &nom, const QString &prenom,
                                 const QString &mail, const QString &adresse,
                                 const QString &poste, const QDate &dateEmbauche,
                                 const QString &statut, int idLocal,
                                 QString &erreurMessage);

    static bool supprimerPersonnel(int id, QString &erreurMessage);
    static QList<Gestion_Personnel> chargerTousLesPersonnels();
    static bool modifierPersonnel(int id, const QString &nom, const QString &prenom,
                                  const QString &mail, const QString &adresse,
                                  const QString &poste, const QDate &dateEmbauche,
                                  const QString &statut, int idLocal,
                                  QString &erreurMessage);

    // Validation
    bool isValid() const;
    static bool isValidId(int id);
    static bool isValidNom(const QString &nom);
    static bool isValidMail(const QString &mail);
    static bool isValidPoste(const QString &poste);
    static bool isValidStatut(const QString &statut);

private:
    int m_id;
    QString m_nom;
    QString m_prenom;
    QString m_mail;
    QString m_adresse;
    QString m_poste;
    QDate m_dateEmbauche;
    QString m_statut;
    int m_idLocal;
};

#endif // GESTION_PERSONNEL_H
