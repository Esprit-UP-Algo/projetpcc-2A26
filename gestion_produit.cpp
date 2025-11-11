#include "gestion_produit.h"
#include <QDebug>
#include <QMessageBox>

Gestion_Produit::Gestion_Produit()
{
    m_id = 0;
    m_marque = "";
    m_modele = "";
    m_type = "";
    m_couleur = "";
    m_prix = 0.0;
    m_remise = 0.0;
    m_quantite = 0;
    m_matiere = "";
    m_genre = "";
    m_dateAjout = QDate::currentDate();
    m_idClient = 0;
    m_idFournisseur = 0;
    m_idLocal = 0;
}

Gestion_Produit::Gestion_Produit(int id, const QString &marque, const QString &modele,
                                 const QString &type, const QString &couleur, float prix,
                                 float remise, int quantite, const QString &matiere,
                                 const QString &genre, const QDate &dateAjout,
                                 int idClient, int idFournisseur, int idLocal)
{
    setId(id);
    setMarque(marque);
    setModele(modele);
    setType(type);
    setCouleur(couleur);
    setPrix(prix);
    setRemise(remise);
    setQuantite(quantite);
    setMatiere(matiere);
    setGenre(genre);
    setDateAjout(dateAjout);
    setIdClient(idClient);
    setIdFournisseur(idFournisseur);
    setIdLocal(idLocal);
}

// Getters
int Gestion_Produit::getId() const { return m_id; }
QString Gestion_Produit::getMarque() const { return m_marque; }
QString Gestion_Produit::getModele() const { return m_modele; }
QString Gestion_Produit::getType() const { return m_type; }
QString Gestion_Produit::getCouleur() const { return m_couleur; }
float Gestion_Produit::getPrix() const { return m_prix; }
float Gestion_Produit::getRemise() const { return m_remise; }
int Gestion_Produit::getQuantite() const { return m_quantite; }
QString Gestion_Produit::getMatiere() const { return m_matiere; }
QString Gestion_Produit::getGenre() const { return m_genre; }
QDate Gestion_Produit::getDateAjout() const { return m_dateAjout; }
int Gestion_Produit::getIdClient() const { return m_idClient; }
int Gestion_Produit::getIdFournisseur() const { return m_idFournisseur; }
int Gestion_Produit::getIdLocal() const { return m_idLocal; }

// Setters
bool Gestion_Produit::setId(int id) {
    if (!isValidId(id)) return false;
    m_id = id;
    return true;
}

bool Gestion_Produit::setMarque(const QString &marque) {
    if (!isValidMarque(marque)) return false;
    m_marque = marque.trimmed();
    return true;
}

bool Gestion_Produit::setModele(const QString &modele) {
    if (!isValidModele(modele)) return false;
    m_modele = modele.trimmed();
    return true;
}

bool Gestion_Produit::setType(const QString &type) {
    if (!isValidType(type)) return false;
    m_type = type;
    return true;
}

bool Gestion_Produit::setCouleur(const QString &couleur) {
    m_couleur = couleur.trimmed().left(20);
    return true;
}

bool Gestion_Produit::setPrix(float prix) {
    if (!isValidPrix(prix)) return false;
    m_prix = prix;
    return true;
}

bool Gestion_Produit::setRemise(float remise) {
    m_remise = remise;
    return true;
}

bool Gestion_Produit::setQuantite(int quantite) {
    if (!isValidQuantite(quantite)) return false;
    m_quantite = quantite;
    return true;
}

bool Gestion_Produit::setMatiere(const QString &matiere) {
    m_matiere = matiere.trimmed().left(20);
    return true;
}

bool Gestion_Produit::setGenre(const QString &genre) {
    m_genre = genre.trimmed().left(20);
    return true;
}

bool Gestion_Produit::setDateAjout(const QDate &date) {
    m_dateAjout = date;
    return true;
}

bool Gestion_Produit::setIdClient(int idClient) {
    m_idClient = idClient;
    return true;
}

bool Gestion_Produit::setIdFournisseur(int idFournisseur) {
    m_idFournisseur = idFournisseur;
    return true;
}

bool Gestion_Produit::setIdLocal(int idLocal) {
    m_idLocal = idLocal;
    return true;
}

// CRUD Operations
bool Gestion_Produit::ajouterProduit(int id, const QString &marque, const QString &modele,
                                     const QString &type, const QString &couleur, float prix,
                                     float remise, int quantite, const QString &matiere,
                                     const QString &genre, const QDate &dateAjout,
                                     int idClient, int idFournisseur, int idLocal,
                                     QString &erreurMessage)
{
    // Validation
    if (!isValidId(id)) { erreurMessage = "ID invalide !"; return false; }
    if (!isValidMarque(marque)) { erreurMessage = "Marque invalide !"; return false; }
    if (!isValidModele(modele)) { erreurMessage = "Modèle invalide !"; return false; }
    if (!isValidType(type)) { erreurMessage = "Type invalide !"; return false; }
    if (!isValidPrix(prix)) { erreurMessage = "Prix invalide !"; return false; }
    if (!isValidQuantite(quantite)) { erreurMessage = "Quantité invalide !"; return false; }

    // Connexion
    Connection c;
    if (!c.createconnect()) {
        erreurMessage = "Connexion échouée !";
        return false;
    }

    QSqlDatabase db = QSqlDatabase::database();

    // Vérifier ID existant
    QSqlQuery check(db);
    check.prepare("SELECT 1 FROM PRODUIT WHERE ID_PRODUIT = :id");
    check.bindValue(":id", id);
    if (check.exec() && check.next()) {
        erreurMessage = "Cet ID existe déjà !";
        return false;
    }

    // Insertion
    QSqlQuery query(db);
    query.prepare(
        "INSERT INTO PRODUIT (ID_PRODUIT, MARQUE, MODELE, TYPE, COULEUR, PRIX, "
        "REMISE, QUANTITÉ, MATIERE, GENRE, DATE_A, ID_CLIENT, ID_FOURNISSEUR, ID_LOCAL) "
        "VALUES (:id, :marque, :modele, :type, :couleur, :prix, :remise, :quantite, "
        ":matiere, :genre, :date, :idClient, :idFournisseur, :idLocal)"
        );

    query.bindValue(":id", id);
    query.bindValue(":marque", marque);
    query.bindValue(":modele", modele);
    query.bindValue(":type", type);
    query.bindValue(":couleur", couleur.left(20));
    query.bindValue(":prix", prix);
    query.bindValue(":remise", remise);
    query.bindValue(":quantite", quantite);
    query.bindValue(":matiere", matiere.left(20));
    query.bindValue(":genre", genre.left(20));
    query.bindValue(":date", dateAjout);
    query.bindValue(":idClient", idClient);
    query.bindValue(":idFournisseur", idFournisseur);
    query.bindValue(":idLocal", idLocal);

    if (query.exec()) {
        erreurMessage = "Produit ajouté avec succès !";
        return true;
    } else {
        erreurMessage = "Erreur Oracle : " + query.lastError().text();
        return false;
    }
}

bool Gestion_Produit::supprimerProduit(int id, QString &erreurMessage)
{
    if (!isValidId(id)) {
        erreurMessage = "ID invalide !";
        return false;
    }

    Connection c;
    if (!c.createconnect()) {
        erreurMessage = "Connexion échouée !";
        return false;
    }

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    query.prepare("DELETE FROM PRODUIT WHERE ID_PRODUIT = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        if (query.numRowsAffected() > 0) {
            erreurMessage = "Produit supprimé avec succès !";
            return true;
        } else {
            erreurMessage = "Aucun produit trouvé avec cet ID !";
            return false;
        }
    } else {
        erreurMessage = "Erreur Oracle : " + query.lastError().text();
        return false;
    }
}

QList<Gestion_Produit> Gestion_Produit::chargerTousLesProduits()
{
    QList<Gestion_Produit> produits;
    Connection c;
    if (!c.createconnect()) return produits;

    QSqlQuery query;
    query.prepare(
        "SELECT ID_PRODUIT, MARQUE, MODELE, TYPE, COULEUR, PRIX, REMISE, "
        "QUANTITÉ, MATIERE, GENRE, DATE_A, ID_CLIENT, ID_FOURNISSEUR, ID_LOCAL "
        "FROM PRODUIT ORDER BY MARQUE, MODELE"
        );

    if (query.exec()) {
        while (query.next()) {
            Gestion_Produit produit;
            produit.setId(query.value(0).toInt());
            produit.setMarque(query.value(1).toString());
            produit.setModele(query.value(2).toString());
            produit.setType(query.value(3).toString());
            produit.setCouleur(query.value(4).toString());
            produit.setPrix(query.value(5).toFloat());
            produit.setRemise(query.value(6).toFloat());
            produit.setQuantite(query.value(7).toInt());
            produit.setMatiere(query.value(8).toString());
            produit.setGenre(query.value(9).toString());
            produit.setDateAjout(query.value(10).toDate());
            produit.setIdClient(query.value(11).toInt());
            produit.setIdFournisseur(query.value(12).toInt());
            produit.setIdLocal(query.value(13).toInt());
            if (produit.isValid()) produits.append(produit);
        }
    }
    return produits;
}

bool Gestion_Produit::modifierProduit(int id, const QString &marque, const QString &modele,
                                      const QString &type, const QString &couleur, float prix,
                                      float remise, int quantite, const QString &matiere,
                                      const QString &genre, const QDate &dateAjout,
                                      int idClient, int idFournisseur, int idLocal,
                                      QString &erreurMessage)
{
    // Validation
    if (!isValidId(id)) { erreurMessage = "ID invalide !"; return false; }
    if (!isValidMarque(marque)) { erreurMessage = "Marque invalide !"; return false; }
    if (!isValidModele(modele)) { erreurMessage = "Modèle invalide !"; return false; }
    if (!isValidType(type)) { erreurMessage = "Type invalide !"; return false; }
    if (!isValidPrix(prix)) { erreurMessage = "Prix invalide !"; return false; }
    if (!isValidQuantite(quantite)) { erreurMessage = "Quantité invalide !"; return false; }

    Connection c;
    if (!c.createconnect()) {
        erreurMessage = "Connexion échouée !";
        return false;
    }

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    query.prepare(
        "UPDATE PRODUIT SET MARQUE = :marque, MODELE = :modele, TYPE = :type, "
        "COULEUR = :couleur, PRIX = :prix, REMISE = :remise, QUANTITÉ = :quantite, "
        "MATIERE = :matiere, GENRE = :genre, DATE_A = :date, ID_CLIENT = :idClient, "
        "ID_FOURNISSEUR = :idFournisseur, ID_LOCAL = :idLocal WHERE ID_PRODUIT = :id"
        );

    query.bindValue(":id", id);
    query.bindValue(":marque", marque);
    query.bindValue(":modele", modele);
    query.bindValue(":type", type);
    query.bindValue(":couleur", couleur.left(20));
    query.bindValue(":prix", prix);
    query.bindValue(":remise", remise);
    query.bindValue(":quantite", quantite);
    query.bindValue(":matiere", matiere.left(20));
    query.bindValue(":genre", genre.left(20));
    query.bindValue(":date", dateAjout);
    query.bindValue(":idClient", idClient);
    query.bindValue(":idFournisseur", idFournisseur);
    query.bindValue(":idLocal", idLocal);

    if (query.exec()) {
        if (query.numRowsAffected() > 0) {
            erreurMessage = "Produit modifié avec succès !";
            return true;
        } else {
            erreurMessage = "Aucun produit trouvé avec cet ID !";
            return false;
        }
    } else {
        erreurMessage = "Erreur Oracle : " + query.lastError().text();
        return false;
    }
}

// Validation
bool Gestion_Produit::isValidId(int id) { return id > 0; }

bool Gestion_Produit::isValidMarque(const QString &marque) {
    return marque.trimmed().length() >= 2 && marque.trimmed().length() <= 20;
}

bool Gestion_Produit::isValidModele(const QString &modele) {
    return modele.trimmed().length() >= 1 && modele.trimmed().length() <= 20;
}

bool Gestion_Produit::isValidType(const QString &type) {
    return type == "Solaire" || type == "Vue" || type == "Mixte" || type == "Lentille";
}

bool Gestion_Produit::isValidPrix(float prix) {
    return prix >= 0;
}

bool Gestion_Produit::isValidQuantite(int quantite) {
    return quantite >= 0;
}

bool Gestion_Produit::isValid() const {
    return isValidId(m_id) && isValidMarque(m_marque) && isValidModele(m_modele) &&
           isValidType(m_type) && isValidPrix(m_prix) && isValidQuantite(m_quantite);
}
