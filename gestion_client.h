#ifndef GESTION_CLIENT_H
#define GESTION_CLIENT_H

#include <QString>
#include <QDate>
#include <QList>
#include <QSqlQuery>

class gestion_client
{
public:
    gestion_client();
    gestion_client(int id, const QString &nom, const QString &prenom,
                   int telephone, const QDate &dateNaissance,
                   const QString &statut, const QString &sexe,
                   const QString &ordonnance = "", const QString &photo = "");

    int getId() const;
    QString getNom() const;
    QString getPrenom() const;
    int getTelephone() const;
    QDate getDateNaissance() const;
    QString getStatut() const;
    QString getSexe() const;
    QString getOrdonnance() const;
    QString getPhoto() const;
    int getAge() const;

    bool setId(int id);
    bool setNom(const QString &nom);
    bool setPrenom(const QString &prenom);
    bool setTelephone(int telephone);
    bool setDateNaissance(const QDate &date);
    bool setStatut(const QString &statut);
    bool setSexe(const QString &sexe);
    bool setOrdonnance(const QString &ordonnance);
    bool setPhoto(const QString &photo);

    static bool ajouterClient(int id, const QString &nom, const QString &prenom,
                              int telephone, const QDate &dateNaissance,
                              const QString &statut, const QString &sexe,
                              const QString &ordonnance, const QString &photo,
                              QString &erreurMessage);

    static QList<gestion_client> chargerTousLesClients();
    static bool supprimerClient(int id, QString &erreurMessage);

    static bool isValidId(int id);
    static bool isValidNom(const QString &nom);
    static bool isValidPrenom(const QString &prenom);
    static bool isValidTelephone(int telephone);
    static bool isValidDateNaissance(const QDate &date);
    static bool isValidStatut(const QString &statut);
    static bool isValidSexe(const QString &sexe);
    static bool modifierClient(int id, const QString &nom, const QString &prenom,
                               int telephone, const QDate &dateNaissance,
                               const QString &statut, const QString &sexe,
                               const QString &ordonnance, const QString &photo,
                               QString &erreurMessage);

    bool isValid() const;
    QString toString() const;

private:
    int m_id;
    QString m_nom;
    QString m_prenom;
    int m_telephone;
    QDate m_dateNaissance;
    QString m_statut;
    QString m_sexe;
    QString m_ordonnance;
    QString m_photo;
};

#endif // GESTION_CLIENT_H
