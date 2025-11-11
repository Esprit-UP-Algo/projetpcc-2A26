#include "gestion_fournisseur.h"
#include <QDebug>
#include <QMessageBox>

Gestion_Fournisseur::Gestion_Fournisseur()
{
    m_id = 0;
    m_nomEntreprise = "";
    m_personneContact = "";
    m_adresse = "";
    m_telephone = 0;
    m_mail = "";
    m_categorie = "";
    m_details = "";
    m_noteFiabilite = 0.0;
}

Gestion_Fournisseur::Gestion_Fournisseur(int id, const QString &nomEntreprise,
                                         const QString &personneContact, const QString &adresse,
                                         int telephone, const QString &mail,
                                         const QString &categorie, const QString &details,
                                         float noteFiabilite)
{
    setId(id);
    setNomEntreprise(nomEntreprise);
    setPersonneContact(personneContact);
    setAdresse(adresse);
    setTelephone(telephone);
    setMail(mail);
    setCategorie(categorie);
    setDetails(details);
    setNoteFiabilite(noteFiabilite);
}

// Getters
int Gestion_Fournisseur::getId() const { return m_id; }
QString Gestion_Fournisseur::getNomEntreprise() const { return m_nomEntreprise; }
QString Gestion_Fournisseur::getPersonneContact() const { return m_personneContact; }
QString Gestion_Fournisseur::getAdresse() const { return m_adresse; }
int Gestion_Fournisseur::getTelephone() const { return m_telephone; }
QString Gestion_Fournisseur::getMail() const { return m_mail; }
QString Gestion_Fournisseur::getCategorie() const { return m_categorie; }
QString Gestion_Fournisseur::getDetails() const { return m_details; }
float Gestion_Fournisseur::getNoteFiabilite() const { return m_noteFiabilite; }

// Setters
bool Gestion_Fournisseur::setId(int id) {
    if (!isValidId(id)) return false;
    m_id = id;
    return true;
}

bool Gestion_Fournisseur::setNomEntreprise(const QString &nom) {
    if (!isValidNom(nom)) return false;
    m_nomEntreprise = nom.trimmed();
    return true;
}

bool Gestion_Fournisseur::setPersonneContact(const QString &personne) {
    m_personneContact = personne.trimmed().left(20);
    return true;
}

bool Gestion_Fournisseur::setAdresse(const QString &adresse) {
    m_adresse = adresse.trimmed().left(20);
    return true;
}

bool Gestion_Fournisseur::setTelephone(int telephone) {
    if (!isValidTelephone(telephone)) return false;
    m_telephone = telephone;
    return true;
}

bool Gestion_Fournisseur::setMail(const QString &mail) {
    if (!isValidMail(mail)) return false;
    m_mail = mail.trimmed();
    return true;
}

bool Gestion_Fournisseur::setCategorie(const QString &categorie) {
    if (!isValidCategorie(categorie)) return false;
    m_categorie = categorie;
    return true;
}

bool Gestion_Fournisseur::setDetails(const QString &details) {
    m_details = details.trimmed().left(20);
    return true;
}

bool Gestion_Fournisseur::setNoteFiabilite(float note) {
    m_noteFiabilite = note;
    return true;
}

// CRUD Operations
bool Gestion_Fournisseur::ajouterFournisseur(int id, const QString &nomEntreprise,
                                             const QString &personneContact, const QString &adresse,
                                             int telephone, const QString &mail,
                                             const QString &categorie, const QString &details,
                                             float noteFiabilite, QString &erreurMessage)
{
    // Validation
    if (!isValidId(id)) { erreurMessage = "ID invalide !"; return false; }
    if (!isValidNom(nomEntreprise)) { erreurMessage = "Nom entreprise invalide !"; return false; }
    if (!isValidTelephone(telephone)) { erreurMessage = "Téléphone invalide !"; return false; }
    if (!isValidMail(mail)) { erreurMessage = "Mail invalide !"; return false; }
    if (!isValidCategorie(categorie)) { erreurMessage = "Catégorie invalide !"; return false; }

    // Connexion
    Connection c;
    if (!c.createconnect()) {
        erreurMessage = "Connexion échouée !";
        return false;
    }

    QSqlDatabase db = QSqlDatabase::database();

    // Vérifier ID existant
    QSqlQuery check(db);
    check.prepare("SELECT 1 FROM FOURNISSEUR WHERE ID_FOURNISSEUR = :id");
    check.bindValue(":id", id);
    if (check.exec() && check.next()) {
        erreurMessage = "Cet ID existe déjà !";
        return false;
    }

    // Insertion
    QSqlQuery query(db);
    query.prepare(
        "INSERT INTO FOURNISSEUR (ID_FOURNISSEUR, NOMENTURE, PERSONNE_CNT, ADRESSE, "
        "NUM_TEL, MAIL, CATÉGORIE, DETAILS, NOTE_DE_FIABILITÉ) "
        "VALUES (:id, :nom, :personne, :adresse, :tel, :mail, :categorie, :details, :note)"
        );

    query.bindValue(":id", id);
    query.bindValue(":nom", nomEntreprise);
    query.bindValue(":personne", personneContact.left(20));
    query.bindValue(":adresse", adresse.left(20));
    query.bindValue(":tel", telephone);
    query.bindValue(":mail", mail);
    query.bindValue(":categorie", categorie);
    query.bindValue(":details", details.left(20));
    query.bindValue(":note", noteFiabilite);

    if (query.exec()) {
        erreurMessage = "Fournisseur ajouté avec succès !";
        return true;
    } else {
        erreurMessage = "Erreur Oracle : " + query.lastError().text();
        return false;
    }
}

bool Gestion_Fournisseur::supprimerFournisseur(int id, QString &erreurMessage)
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
    query.prepare("DELETE FROM FOURNISSEUR WHERE ID_FOURNISSEUR = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        if (query.numRowsAffected() > 0) {
            erreurMessage = "Fournisseur supprimé avec succès !";
            return true;
        } else {
            erreurMessage = "Aucun fournisseur trouvé avec cet ID !";
            return false;
        }
    } else {
        erreurMessage = "Erreur Oracle : " + query.lastError().text();
        return false;
    }
}

QList<Gestion_Fournisseur> Gestion_Fournisseur::chargerTousLesFournisseurs()
{
    QList<Gestion_Fournisseur> fournisseurs;
    Connection c;
    if (!c.createconnect()) return fournisseurs;

    QSqlQuery query;
    query.prepare(
        "SELECT ID_FOURNISSEUR, NOMENTURE, PERSONNE_CNT, ADRESSE, NUM_TEL, "
        "MAIL, CATÉGORIE, DETAILS, NOTE_DE_FIABILITÉ FROM FOURNISSEUR ORDER BY NOMENTURE"
        );

    if (query.exec()) {
        while (query.next()) {
            Gestion_Fournisseur fournisseur;
            fournisseur.setId(query.value(0).toInt());
            fournisseur.setNomEntreprise(query.value(1).toString());
            fournisseur.setPersonneContact(query.value(2).toString());
            fournisseur.setAdresse(query.value(3).toString());
            fournisseur.setTelephone(query.value(4).toInt());
            fournisseur.setMail(query.value(5).toString());
            fournisseur.setCategorie(query.value(6).toString());
            fournisseur.setDetails(query.value(7).toString());
            fournisseur.setNoteFiabilite(query.value(8).toFloat());
            if (fournisseur.isValid()) fournisseurs.append(fournisseur);
        }
    }
    return fournisseurs;
}

bool Gestion_Fournisseur::modifierFournisseur(int id, const QString &nomEntreprise,
                                              const QString &personneContact, const QString &adresse,
                                              int telephone, const QString &mail,
                                              const QString &categorie, const QString &details,
                                              float noteFiabilite, QString &erreurMessage)
{
    // Validation
    if (!isValidId(id)) { erreurMessage = "ID invalide !"; return false; }
    if (!isValidNom(nomEntreprise)) { erreurMessage = "Nom entreprise invalide !"; return false; }
    if (!isValidTelephone(telephone)) { erreurMessage = "Téléphone invalide !"; return false; }
    if (!isValidMail(mail)) { erreurMessage = "Mail invalide !"; return false; }
    if (!isValidCategorie(categorie)) { erreurMessage = "Catégorie invalide !"; return false; }

    Connection c;
    if (!c.createconnect()) {
        erreurMessage = "Connexion échouée !";
        return false;
    }

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    query.prepare(
        "UPDATE FOURNISSEUR SET NOMENTURE = :nom, PERSONNE_CNT = :personne, "
        "ADRESSE = :adresse, NUM_TEL = :tel, MAIL = :mail, CATÉGORIE = :categorie, "
        "DETAILS = :details, NOTE_DE_FIABILITÉ = :note WHERE ID_FOURNISSEUR = :id"
        );

    query.bindValue(":id", id);
    query.bindValue(":nom", nomEntreprise);
    query.bindValue(":personne", personneContact.left(20));
    query.bindValue(":adresse", adresse.left(20));
    query.bindValue(":tel", telephone);
    query.bindValue(":mail", mail);
    query.bindValue(":categorie", categorie);
    query.bindValue(":details", details.left(20));
    query.bindValue(":note", noteFiabilite);

    if (query.exec()) {
        if (query.numRowsAffected() > 0) {
            erreurMessage = "Fournisseur modifié avec succès !";
            return true;
        } else {
            erreurMessage = "Aucun fournisseur trouvé avec cet ID !";
            return false;
        }
    } else {
        erreurMessage = "Erreur Oracle : " + query.lastError().text();
        return false;
    }
}

// Validation
bool Gestion_Fournisseur::isValidId(int id) { return id > 0; }

bool Gestion_Fournisseur::isValidNom(const QString &nom) {
    return nom.trimmed().length() >= 2 && nom.trimmed().length() <= 20;
}

bool Gestion_Fournisseur::isValidTelephone(int telephone) {
    return telephone >= 10000000 && telephone <= 9999999999;
}

bool Gestion_Fournisseur::isValidMail(const QString &mail) {
    QRegularExpression regex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    return regex.match(mail).hasMatch() && mail.length() <= 20;
}

bool Gestion_Fournisseur::isValidCategorie(const QString &categorie) {
    return categorie == "Lunettes" || categorie == "Lentilles" ||
           categorie == "Services" || categorie == "Accessoires";
}

bool Gestion_Fournisseur::isValid() const {
    return isValidId(m_id) && isValidNom(m_nomEntreprise) &&
           isValidTelephone(m_telephone) && isValidMail(m_mail) &&
           isValidCategorie(m_categorie);
}
