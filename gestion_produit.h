#ifndef GESTION_PRODUIT_H
#define GESTION_PRODUIT_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlError>
#include "connection.h"

class Gestion_Produit
{
public:
    Gestion_Produit();
    Gestion_Produit(int id, const QString &marque, const QString &modele,
                    const QString &type, const QString &couleur, float prix,
                    float remise, int quantite, const QString &matiere,
                    const QString &genre, const QDate &dateAjout,
                    int idClient, int idFournisseur, int idLocal);

    int getId() const;
    QString getMarque() const;
    QString getModele() const;
    QString getType() const;
    QString getCouleur() const;
    float getPrix() const;
    float getRemise() const;
    int getQuantite() const;
    QString getMatiere() const;
    QString getGenre() const;
    QDate getDateAjout() const;
    int getIdClient() const;
    int getIdFournisseur() const;
    int getIdLocal() const;

    bool setId(int id);
    bool setMarque(const QString &marque);
    bool setModele(const QString &modele);
    bool setType(const QString &type);
    bool setCouleur(const QString &couleur);
    bool setPrix(float prix);
    bool setRemise(float remise);
    bool setQuantite(int quantite);
    bool setMatiere(const QString &matiere);
    bool setGenre(const QString &genre);
    bool setDateAjout(const QDate &date);
    bool setIdClient(int idClient);
    bool setIdFournisseur(int idFournisseur);
    bool setIdLocal(int idLocal);

    static bool ajouterProduit(int id, const QString &marque, const QString &modele,
                               const QString &type, const QString &couleur, float prix,
                               float remise, int quantite, const QString &matiere,
                               const QString &genre, const QDate &dateAjout,
                               int idClient, int idFournisseur, int idLocal,
                               QString &erreurMessage);

    static bool supprimerProduit(int id, QString &erreurMessage);
    static QList<Gestion_Produit> chargerTousLesProduits();
    static bool modifierProduit(int id, const QString &marque, const QString &modele,
                                const QString &type, const QString &couleur, float prix,
                                float remise, int quantite, const QString &matiere,
                                const QString &genre, const QDate &dateAjout,
                                int idClient, int idFournisseur, int idLocal,
                                QString &erreurMessage);

    bool isValid() const;
    static bool isValidId(int id);
    static bool isValidMarque(const QString &marque);
    static bool isValidModele(const QString &modele);
    static bool isValidType(const QString &type);
    static bool isValidPrix(float prix);
    static bool isValidQuantite(int quantite);

private:
    int m_id;
    QString m_marque;
    QString m_modele;
    QString m_type;
    QString m_couleur;
    float m_prix;
    float m_remise;
    int m_quantite;
    QString m_matiere;
    QString m_genre;
    QDate m_dateAjout;
    int m_idClient;
    int m_idFournisseur;
    int m_idLocal;
};

#endif
