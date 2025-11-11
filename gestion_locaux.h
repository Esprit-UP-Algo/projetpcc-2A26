#ifndef GESTION_LOCAUX_H
#define GESTION_LOCAUX_H

#include <QString>
#include <QRegularExpression>
#include <QSqlQuery>
#include <QSqlError>
#include "connection.h"

class Gestion_Locaux
{
public:
    Gestion_Locaux();
    Gestion_Locaux(int id, const QString &nom, int telephone,
                   const QString &adresse, const QString &superficie,
                   const QString &chiffreAffaires, const QString &etat);

    // Getters
    int getId() const;
    QString getNom() const;
    int getTelephone() const;
    QString getAdresse() const;
    QString getSuperficie() const;
    QString getChiffreAffaires() const;
    QString getEtat() const;

    // Setters
    bool setId(int id);
    bool setNom(const QString &nom);
    bool setTelephone(int telephone);
    bool setAdresse(const QString &adresse);
    bool setSuperficie(const QString &superficie);
    bool setChiffreAffaires(const QString &chiffreAffaires);
    bool setEtat(const QString &etat);

    // CRUD
    static bool ajouterLocal(int id, const QString &nom, int telephone,
                             const QString &adresse, const QString &superficie,
                             const QString &chiffreAffaires, const QString &etat,
                             QString &erreurMessage);

    static bool supprimerLocal(int id, QString &erreurMessage);
    static QList<Gestion_Locaux> chargerTousLesLocaux();
    static bool modifierLocal(int id, const QString &nom, int telephone,
                              const QString &adresse, const QString &superficie,
                              const QString &chiffreAffaires, const QString &etat,
                              QString &erreurMessage);

    // Validation
    bool isValid() const;
    static bool isValidId(int id);
    static bool isValidNom(const QString &nom);
    static bool isValidTelephone(int telephone);
    static bool isValidEtat(const QString &etat);

private:
    int m_id;
    QString m_nom;
    int m_telephone;
    QString m_adresse;
    QString m_superficie;
    QString m_chiffreAffaires;
    QString m_etat;
};

#endif // GESTION_LOCAUX_H
