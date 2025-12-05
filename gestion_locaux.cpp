#include "gestion_locaux.h"
#include <QDebug>
#include <QMessageBox>

Gestion_Locaux::Gestion_Locaux()
{
    m_id = 0;
    m_nom = "";
    m_telephone = 0;
    m_adresse = "";
    m_superficie = "";
    m_chiffreAffaires = "";
    m_etat = "Disponible";
}

Gestion_Locaux::Gestion_Locaux(int id, const QString &nom, int telephone,
                               const QString &adresse, const QString &superficie,
                               const QString &chiffreAffaires, const QString &etat)
{
    setId(id);
    setNom(nom);
    setTelephone(telephone);
    setAdresse(adresse);
    setSuperficie(superficie);
    setChiffreAffaires(chiffreAffaires);
    setEtat(etat);
}

// Getters
int Gestion_Locaux::getId() const { return m_id; }
QString Gestion_Locaux::getNom() const { return m_nom; }
int Gestion_Locaux::getTelephone() const { return m_telephone; }
QString Gestion_Locaux::getAdresse() const { return m_adresse; }
QString Gestion_Locaux::getSuperficie() const { return m_superficie; }
QString Gestion_Locaux::getChiffreAffaires() const { return m_chiffreAffaires; }
QString Gestion_Locaux::getEtat() const { return m_etat; }

// Setters
bool Gestion_Locaux::setId(int id) {
    if (!isValidId(id)) return false;
    m_id = id;
    return true;
}

bool Gestion_Locaux::setNom(const QString &nom) {
    if (!isValidNom(nom)) return false;
    m_nom = nom.trimmed();
    return true;
}

bool Gestion_Locaux::setTelephone(int telephone) {
    if (!isValidTelephone(telephone)) return false;
    m_telephone = telephone;
    return true;
}

bool Gestion_Locaux::setAdresse(const QString &adresse) {
    m_adresse = adresse.trimmed().left(20);
    return true;
}

bool Gestion_Locaux::setSuperficie(const QString &superficie) {
    m_superficie = superficie.trimmed().left(20);
    return true;
}

bool Gestion_Locaux::setChiffreAffaires(const QString &chiffreAffaires) {
    m_chiffreAffaires = chiffreAffaires.trimmed().left(20);
    return true;
}

bool Gestion_Locaux::setEtat(const QString &etat) {
    if (!isValidEtat(etat)) return false;
    m_etat = etat;
    return true;
}

// CRUD Operations
bool Gestion_Locaux::ajouterLocal(int id, const QString &nom, int telephone,
                                  const QString &adresse, const QString &superficie,
                                  const QString &chiffreAffaires, const QString &etat,
                                  QString &erreurMessage)
{
    // Validation
    if (!isValidId(id)) { erreurMessage = "ID invalide !"; return false; }
    if (!isValidNom(nom)) { erreurMessage = "Nom invalide !"; return false; }
    if (!isValidTelephone(telephone)) { erreurMessage = "Téléphone invalide !"; return false; }
    if (!isValidEtat(etat)) { erreurMessage = "État invalide !"; return false; }

    // Connexion
    Connection c;
    if (!c.createconnect()) {
        erreurMessage = "Connexion échouée !";
        return false;
    }

    QSqlDatabase db = QSqlDatabase::database();

    // Vérifier ID existant
    QSqlQuery check(db);
    check.prepare("SELECT 1 FROM LOCAUX WHERE ID_LOCAL = :id");
    check.bindValue(":id", id);
    if (check.exec() && check.next()) {
        erreurMessage = "Cet ID existe déjà !";
        return false;
    }

    // Insertion
    QSqlQuery query(db);
    query.prepare(
        "INSERT INTO LOCAUX (ID_LOCAL, NOM, TELEPHONE, ADRESSE, SUPERFICIE, "
        "CHIFFRE_DAFFAIRE, ETAT_DE_LOCAL) "
        "VALUES (:id, :nom, :tel, :adresse, :superficie, :ca, :etat)"
        );

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":tel", telephone);
    query.bindValue(":adresse", adresse.left(20));
    query.bindValue(":superficie", superficie.left(20));
    query.bindValue(":ca", chiffreAffaires.left(20));
    query.bindValue(":etat", etat);

    if (query.exec()) {
        erreurMessage = "Local ajouté avec succès !";
        return true;
    } else {
        erreurMessage = "Erreur Oracle : " + query.lastError().text();
        return false;
    }
}

bool Gestion_Locaux::supprimerLocal(int id, QString &erreurMessage)
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
    query.prepare("DELETE FROM LOCAUX WHERE ID_LOCAL = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        if (query.numRowsAffected() > 0) {
            erreurMessage = "Local supprimé avec succès !";
            return true;
        } else {
            erreurMessage = "Aucun local trouvé avec cet ID !";
            return false;
        }
    } else {
        erreurMessage = "Erreur Oracle : " + query.lastError().text();
        return false;
    }
}

QList<Gestion_Locaux> Gestion_Locaux::chargerTousLesLocaux()
{
    QList<Gestion_Locaux> locaux;
    Connection c;
    if (!c.createconnect()) return locaux;

    QSqlQuery query;
    query.prepare(
        "SELECT ID_LOCAL, NOM, TELEPHONE, ADRESSE, SUPERFICIE, "
        "CHIFFRE_DAFFAIRE, ETAT_DE_LOCAL FROM LOCAUX ORDER BY NOM"
        );

    if (query.exec()) {
        while (query.next()) {
            Gestion_Locaux local;
            local.setId(query.value(0).toInt());
            local.setNom(query.value(1).toString());
            local.setTelephone(query.value(2).toInt());
            local.setAdresse(query.value(3).toString());
            local.setSuperficie(query.value(4).toString());
            local.setChiffreAffaires(query.value(5).toString());
            local.setEtat(query.value(6).toString());
            if (local.isValid()) locaux.append(local);
        }
    }
    return locaux;
}

bool Gestion_Locaux::modifierLocal(int id, const QString &nom, int telephone,
                                   const QString &adresse, const QString &superficie,
                                   const QString &chiffreAffaires, const QString &etat,
                                   QString &erreurMessage)
{
    // Validation
    if (!isValidId(id)) { erreurMessage = "ID invalide !"; return false; }
    if (!isValidNom(nom)) { erreurMessage = "Nom invalide !"; return false; }
    if (!isValidTelephone(telephone)) { erreurMessage = "Téléphone invalide !"; return false; }
    if (!isValidEtat(etat)) { erreurMessage = "État invalide !"; return false; }

    Connection c;
    if (!c.createconnect()) {
        erreurMessage = "Connexion échouée !";
        return false;
    }

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    query.prepare(
        "UPDATE LOCAUX SET NOM = :nom, TELEPHONE = :tel, ADRESSE = :adresse, "
        "SUPERFICIE = :superficie, CHIFFRE_DAFFAIRE = :ca, ETAT_DE_LOCAL = :etat "
        "WHERE ID_LOCAL = :id"
        );

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":tel", telephone);
    query.bindValue(":adresse", adresse.left(20));
    query.bindValue(":superficie", superficie.left(20));
    query.bindValue(":ca", chiffreAffaires.left(20));
    query.bindValue(":etat", etat);

    if (query.exec()) {
        if (query.numRowsAffected() > 0) {
            erreurMessage = "Local modifié avec succès !";
            return true;
        } else {
            erreurMessage = "Aucun local trouvé avec cet ID !";
            return false;
        }
    } else {
        erreurMessage = "Erreur Oracle : " + query.lastError().text();
        return false;
    }
}

// Validation
bool Gestion_Locaux::isValidId(int id) { return id > 0; }

bool Gestion_Locaux::isValidNom(const QString &nom) {
    return nom.trimmed().length() >= 2 && nom.trimmed().length() <= 20;
}

bool Gestion_Locaux::isValidTelephone(int telephone) {
    return telephone >= 10000000 && telephone <= 9999999999;
}

bool Gestion_Locaux::isValidEtat(const QString &etat) {
    return etat == "Disponible" || etat == "Ouvert" || etat == "Fermé";
}

bool Gestion_Locaux::isValid() const {
    return isValidId(m_id) && isValidNom(m_nom) &&
           isValidTelephone(m_telephone) && isValidEtat(m_etat);
}
