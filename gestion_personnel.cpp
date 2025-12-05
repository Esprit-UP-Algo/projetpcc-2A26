#include "gestion_personnel.h"
#include <QDebug>
#include <QMessageBox>

Gestion_Personnel::Gestion_Personnel()
{
    m_id = 0;
    m_nom = "";
    m_prenom = "";
    m_mail = "";
    m_adresse = "";
    m_poste = "";
    m_dateEmbauche = QDate::currentDate();
    m_statut = "Actif";
    m_idLocal = 0;
}

Gestion_Personnel::Gestion_Personnel(int id, const QString &nom, const QString &prenom,
                                     const QString &mail, const QString &adresse,
                                     const QString &poste, const QDate &dateEmbauche,
                                     const QString &statut, int idLocal)
{
    setId(id);
    setNom(nom);
    setPrenom(prenom);
    setMail(mail);
    setAdresse(adresse);
    setPoste(poste);
    setDateEmbauche(dateEmbauche);
    setStatut(statut);
    setIdLocal(idLocal);
}

// Getters
int Gestion_Personnel::getId() const { return m_id; }
QString Gestion_Personnel::getNom() const { return m_nom; }
QString Gestion_Personnel::getPrenom() const { return m_prenom; }
QString Gestion_Personnel::getMail() const { return m_mail; }
QString Gestion_Personnel::getAdresse() const { return m_adresse; }
QString Gestion_Personnel::getPoste() const { return m_poste; }
QDate Gestion_Personnel::getDateEmbauche() const { return m_dateEmbauche; }
QString Gestion_Personnel::getStatut() const { return m_statut; }
int Gestion_Personnel::getIdLocal() const { return m_idLocal; }

// Setters
bool Gestion_Personnel::setId(int id) {
    if (!isValidId(id)) return false;
    m_id = id;
    return true;
}

bool Gestion_Personnel::setNom(const QString &nom) {
    if (!isValidNom(nom)) return false;
    m_nom = nom.toUpper().trimmed();
    return true;
}

bool Gestion_Personnel::setPrenom(const QString &prenom) {
    if (!isValidNom(prenom)) return false;
    m_prenom = prenom.trimmed();
    return true;
}

bool Gestion_Personnel::setMail(const QString &mail) {
    if (!isValidMail(mail)) return false;
    m_mail = mail.trimmed();
    return true;
}

bool Gestion_Personnel::setAdresse(const QString &adresse) {
    m_adresse = adresse.trimmed().left(20);
    return true;
}

bool Gestion_Personnel::setPoste(const QString &poste) {
    if (!isValidPoste(poste)) return false;
    m_poste = poste;
    return true;
}

bool Gestion_Personnel::setDateEmbauche(const QDate &date) {
    m_dateEmbauche = date;
    return true;
}

bool Gestion_Personnel::setStatut(const QString &statut) {
    if (!isValidStatut(statut)) return false;
    m_statut = statut;
    return true;
}

bool Gestion_Personnel::setIdLocal(int idLocal) {
    m_idLocal = idLocal;
    return true;
}

// CRUD Operations
bool Gestion_Personnel::ajouterPersonnel(int id, const QString &nom, const QString &prenom,
                                         const QString &mail, const QString &adresse,
                                         const QString &poste, const QDate &dateEmbauche,
                                         const QString &statut, int idLocal,
                                         QString &erreurMessage)
{
    // Validation
    if (!isValidId(id)) { erreurMessage = "ID invalide !"; return false; }
    if (!isValidNom(nom)) { erreurMessage = "Nom invalide !"; return false; }
    if (!isValidNom(prenom)) { erreurMessage = "Prénom invalide !"; return false; }
    if (!isValidMail(mail)) { erreurMessage = "Mail invalide !"; return false; }
    if (!isValidPoste(poste)) { erreurMessage = "Poste invalide !"; return false; }
    if (!isValidStatut(statut)) { erreurMessage = "Statut invalide !"; return false; }

    // Connexion
    Connection c;
    if (!c.createconnect()) {
        erreurMessage = "Connexion échouée !";
        return false;
    }

    QSqlDatabase db = QSqlDatabase::database();

    // Vérifier ID existant
    QSqlQuery check(db);
    check.prepare("SELECT 1 FROM PERSONNELS WHERE ID_PERSONNEL = :id");
    check.bindValue(":id", id);
    if (check.exec() && check.next()) {
        erreurMessage = "Cet ID existe déjà !";
        return false;
    }

    // Insertion
    QSqlQuery query(db);
    query.prepare(
        "INSERT INTO PERSONNELS (ID_PERSONNEL, NOM, PRENOM, MAIL, ADRESSE, "
        "POSTE, DATE_DEMBAUCHE, STATUT, ID_LOCAL) "
        "VALUES (:id, :nom, :prenom, :mail, :adresse, :poste, :date, :statut, :idLocal)"
        );

    query.bindValue(":id", id);
    query.bindValue(":nom", nom.toUpper());
    query.bindValue(":prenom", prenom);
    query.bindValue(":mail", mail);
    query.bindValue(":adresse", adresse.left(20));
    query.bindValue(":poste", poste);
    query.bindValue(":date", dateEmbauche);
    query.bindValue(":statut", statut);
    query.bindValue(":idLocal", idLocal);

    if (query.exec()) {
        erreurMessage = "Personnel ajouté avec succès !";
        return true;
    } else {
        erreurMessage = "Erreur Oracle : " + query.lastError().text();
        return false;
    }
}

bool Gestion_Personnel::supprimerPersonnel(int id, QString &erreurMessage)
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
    query.prepare("DELETE FROM PERSONNELS WHERE ID_PERSONNEL = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        if (query.numRowsAffected() > 0) {
            erreurMessage = "Personnel supprimé avec succès !";
            return true;
        } else {
            erreurMessage = "Aucun personnel trouvé avec cet ID !";
            return false;
        }
    } else {
        erreurMessage = "Erreur Oracle : " + query.lastError().text();
        return false;
    }
}

QList<Gestion_Personnel> Gestion_Personnel::chargerTousLesPersonnels()
{
    QList<Gestion_Personnel> personnels;
    Connection c;
    if (!c.createconnect()) return personnels;

    QSqlQuery query;
    query.prepare(
        "SELECT ID_PERSONNEL, NOM, PRENOM, MAIL, ADRESSE, POSTE, "
        "DATE_DEMBAUCHE, STATUT, ID_LOCAL FROM PERSONNELS ORDER BY NOM, PRENOM"
        );

    if (query.exec()) {
        while (query.next()) {
            Gestion_Personnel personnel;
            personnel.setId(query.value(0).toInt());
            personnel.setNom(query.value(1).toString());
            personnel.setPrenom(query.value(2).toString());
            personnel.setMail(query.value(3).toString());
            personnel.setAdresse(query.value(4).toString());
            personnel.setPoste(query.value(5).toString());
            personnel.setDateEmbauche(query.value(6).toDate());
            personnel.setStatut(query.value(7).toString());
            personnel.setIdLocal(query.value(8).toInt());
            if (personnel.isValid()) personnels.append(personnel);
        }
    }
    return personnels;
}

bool Gestion_Personnel::modifierPersonnel(int id, const QString &nom, const QString &prenom,
                                          const QString &mail, const QString &adresse,
                                          const QString &poste, const QDate &dateEmbauche,
                                          const QString &statut, int idLocal,
                                          QString &erreurMessage)
{
    // Validation
    if (!isValidId(id)) { erreurMessage = "ID invalide !"; return false; }
    if (!isValidNom(nom)) { erreurMessage = "Nom invalide !"; return false; }
    if (!isValidNom(prenom)) { erreurMessage = "Prénom invalide !"; return false; }
    if (!isValidMail(mail)) { erreurMessage = "Mail invalide !"; return false; }
    if (!isValidPoste(poste)) { erreurMessage = "Poste invalide !"; return false; }
    if (!isValidStatut(statut)) { erreurMessage = "Statut invalide !"; return false; }

    Connection c;
    if (!c.createconnect()) {
        erreurMessage = "Connexion échouée !";
        return false;
    }

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    query.prepare(
        "UPDATE PERSONNELS SET NOM = :nom, PRENOM = :prenom, MAIL = :mail, "
        "ADRESSE = :adresse, POSTE = :poste, DATE_DEMBAUCHE = :date, "
        "STATUT = :statut, ID_LOCAL = :idLocal WHERE ID_PERSONNEL = :id"
        );

    query.bindValue(":id", id);
    query.bindValue(":nom", nom.toUpper());
    query.bindValue(":prenom", prenom);
    query.bindValue(":mail", mail);
    query.bindValue(":adresse", adresse.left(20));
    query.bindValue(":poste", poste);
    query.bindValue(":date", dateEmbauche);
    query.bindValue(":statut", statut);
    query.bindValue(":idLocal", idLocal);

    if (query.exec()) {
        if (query.numRowsAffected() > 0) {
            erreurMessage = "Personnel modifié avec succès !";
            return true;
        } else {
            erreurMessage = "Aucun personnel trouvé avec cet ID !";
            return false;
        }
    } else {
        erreurMessage = "Erreur Oracle : " + query.lastError().text();
        return false;
    }
}

// Validation
bool Gestion_Personnel::isValidId(int id) { return id > 0; }

bool Gestion_Personnel::isValidNom(const QString &nom) {
    return nom.trimmed().length() >= 2 && nom.trimmed().length() <= 20 &&
           QRegularExpression("^[A-Za-zÀ-ÿ\\s\\-' ]+$").match(nom).hasMatch();
}

bool Gestion_Personnel::isValidMail(const QString &mail) {
    QRegularExpression regex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    return regex.match(mail).hasMatch() && mail.length() <= 20;
}

bool Gestion_Personnel::isValidPoste(const QString &poste) {
    return poste == "Responsable" || poste == "Vendeur" ||
           poste == "Manager" || poste == "Opticien";
}

bool Gestion_Personnel::isValidStatut(const QString &statut) {
    return statut == "Actif" || statut == "Inactif";
}

bool Gestion_Personnel::isValid() const {
    return isValidId(m_id) && isValidNom(m_nom) && isValidNom(m_prenom) &&
           isValidMail(m_mail) && isValidPoste(m_poste) && isValidStatut(m_statut);
}
