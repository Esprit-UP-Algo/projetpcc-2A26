#include "gestion_client.h"
#include "connection.h"
#include <QDebug>
#include <QMessageBox>
#include <QRegularExpression>
#include <QSqlError>

gestion_client::gestion_client()
{
    m_id = 0;
    m_nom = "";
    m_prenom = "";
    m_telephone = 0;
    m_statut = "Nouveau";
    m_sexe = "H";
    m_dateNaissance = QDate::currentDate();
    m_ordonnance = "";
    m_photo = "";
}

gestion_client::gestion_client(int id, const QString &nom, const QString &prenom,
                               int telephone, const QDate &dateNaissance,
                               const QString &statut, const QString &sexe,
                               const QString &ordonnance, const QString &photo)
{
    setId(id);
    setNom(nom);
    setPrenom(prenom);
    setTelephone(telephone);
    setDateNaissance(dateNaissance);
    setStatut(statut);
    setSexe(sexe);
    setOrdonnance(ordonnance);
    setPhoto(photo);
}

int gestion_client::getId() const { return m_id; }
QString gestion_client::getNom() const { return m_nom; }
QString gestion_client::getPrenom() const { return m_prenom; }
int gestion_client::getTelephone() const { return m_telephone; }
QDate gestion_client::getDateNaissance() const { return m_dateNaissance; }
QString gestion_client::getStatut() const { return m_statut; }
QString gestion_client::getSexe() const { return m_sexe; }
QString gestion_client::getOrdonnance() const { return m_ordonnance; }
QString gestion_client::getPhoto() const { return m_photo; }

int gestion_client::getAge() const
{
    QDate today = QDate::currentDate();
    int age = today.year() - m_dateNaissance.year();
    if (today.month() < m_dateNaissance.month() ||
        (today.month() == m_dateNaissance.month() && today.day() < m_dateNaissance.day())) {
        age--;
    }
    return age;
}

bool gestion_client::setId(int id) {
    if (!isValidId(id)) return false;
    m_id = id;
    return true;
}

bool gestion_client::setNom(const QString &nom) {
    if (!isValidNom(nom)) return false;
    m_nom = nom.toUpper().trimmed();
    return true;
}

bool gestion_client::setPrenom(const QString &prenom) {
    if (!isValidPrenom(prenom)) return false;
    m_prenom = prenom.trimmed();
    return true;
}

bool gestion_client::setTelephone(int telephone) {
    if (!isValidTelephone(telephone)) return false;
    m_telephone = telephone;
    return true;
}

bool gestion_client::setDateNaissance(const QDate &date) {
    if (!isValidDateNaissance(date)) return false;
    m_dateNaissance = date;
    return true;
}

bool gestion_client::setStatut(const QString &statut) {
    if (!isValidStatut(statut)) return false;
    m_statut = statut;
    return true;
}

bool gestion_client::setSexe(const QString &sexe) {
    QString s = sexe.trimmed();
    if (s == "Homme") m_sexe = "H";
    else if (s == "Femme") m_sexe = "F";
    else if (s == "H" || s == "F") m_sexe = s;
    else return false;
    return true;
}

bool gestion_client::setOrdonnance(const QString &ordonnance) {
    m_ordonnance = ordonnance.trimmed().left(20);
    return true;
}

bool gestion_client::setPhoto(const QString &photo) {
    m_photo = photo.trimmed().left(20);
    return true;
}

bool gestion_client::ajouterClient(int id, const QString &nom, const QString &prenom,
                                   int telephone, const QDate &dateNaissance,
                                   const QString &statut, const QString &sexe,
                                   const QString &ordonnance, const QString &photo,
                                   QString &erreurMessage)
{
    if (!isValidId(id)) { erreurMessage = "ID invalide !"; return false; }
    if (!isValidNom(nom)) { erreurMessage = "Nom invalide !"; return false; }
    if (!isValidPrenom(prenom)) { erreurMessage = "Prénom invalide !"; return false; }
    if (!isValidTelephone(telephone)) { erreurMessage = "Téléphone invalide !"; return false; }
    if (!isValidDateNaissance(dateNaissance)) { erreurMessage = "Date invalide !"; return false; }
    if (!isValidStatut(statut)) { erreurMessage = "Statut invalide !"; return false; }

    QString sexeDB;
    if (sexe == "Homme") sexeDB = "H";
    else if (sexe == "Femme") sexeDB = "F";
    else { erreurMessage = "Sexe invalide !"; return false; }

    Connection c;
    if (!c.createconnect()) {
        erreurMessage = "Connexion échouée !";
        return false;
    }

    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        erreurMessage = "Base de données non ouverte !";
        return false;
    }

    {
        QSqlQuery check(db);
        check.prepare("SELECT 1 FROM CLIENT WHERE ID_CLIENT = :id");
        check.bindValue(":id", id);
        if (check.exec() && check.next()) {
            erreurMessage = "Cet ID existe déjà !";
            return false;
        }
        if (!check.isActive()) {
            erreurMessage = "Erreur lors de la vérification ID : " + check.lastError().text();
            return false;
        }
    }

    {
        QSqlQuery query(db);
        query.prepare(
            "INSERT INTO CLIENT (ID_CLIENT, NOM, PRENOM, NUM_TEL, DATE_DE_NAISSANCE, "
            "STATUT, SEXE, ORDONNANCE, PHOTO) "
            "VALUES (:id, :nom, :prenom, :tel, :date, :statut, :sexe, :ordo, :photo)"
            );

        query.bindValue(":id", id);
        query.bindValue(":nom", nom.toUpper());
        query.bindValue(":prenom", prenom);
        query.bindValue(":tel", telephone);
        query.bindValue(":date", dateNaissance);
        query.bindValue(":statut", statut);
        query.bindValue(":sexe", sexeDB);
        query.bindValue(":ordo", ordonnance.left(20));
        query.bindValue(":photo", photo.left(20));

        if (query.exec()) {
            erreurMessage = "Client ajouté avec succès !";
            return true;
        } else {
            erreurMessage = "Erreur Oracle : " + query.lastError().text();
            qDebug() << "SQL Error:" << query.lastError().text();
            qDebug() << "SQL:" << query.lastQuery();
            return false;
        }
    }
}

QList<gestion_client> gestion_client::chargerTousLesClients()
{
    QList<gestion_client> clients;
    Connection c;
    if (!c.createconnect()) return clients;

    QSqlQuery query;
    query.prepare(
        "SELECT ID_CLIENT, NOM, PRENOM, NUM_TEL, DATE_DE_NAISSANCE, "
        "STATUT, SEXE, ORDONNANCE, PHOTO FROM CLIENT ORDER BY NOM, PRENOM"
        );

    if (query.exec()) {
        while (query.next()) {
            gestion_client client;
            client.setId(query.value(0).toInt());
            client.setNom(query.value(1).toString());
            client.setPrenom(query.value(2).toString());
            client.setTelephone(query.value(3).toInt());
            client.setDateNaissance(query.value(4).toDate());
            client.setStatut(query.value(5).toString());
            client.setSexe(query.value(6).toString());
            client.setOrdonnance(query.value(7).toString());
            client.setPhoto(query.value(8).toString());
            if (client.isValid()) clients.append(client);
        }
    }
    return clients;
}

bool gestion_client::supprimerClient(int id, QString &erreurMessage)
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
    query.prepare("DELETE FROM OPTIMATECH.CLIENT WHERE ID_CLIENT = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        if (query.numRowsAffected() > 0) {
            erreurMessage = "Client supprimé avec succès !";
            return true;
        } else {
            erreurMessage = "Aucun client trouvé avec cet ID !";
            return false;
        }
    } else {
        erreurMessage = "Erreur Oracle : " + query.lastError().text();
        qDebug() << "SQL Error:" << query.lastError().text();
        return false;
    }
}
bool gestion_client::modifierClient(int id, const QString &nom, const QString &prenom,
                                    int telephone, const QDate &dateNaissance,
                                    const QString &statut, const QString &sexe,
                                    const QString &ordonnance, const QString &photo,
                                    QString &erreurMessage)
{
    // Validation des données
    if (!isValidId(id)) { erreurMessage = "ID invalide !"; return false; }
    if (!isValidNom(nom)) { erreurMessage = "Nom invalide !"; return false; }
    if (!isValidPrenom(prenom)) { erreurMessage = "Prénom invalide !"; return false; }
    if (!isValidTelephone(telephone)) { erreurMessage = "Téléphone invalide !"; return false; }
    if (!isValidDateNaissance(dateNaissance)) { erreurMessage = "Date invalide !"; return false; }

    QString sexeDB;
    if (sexe == "Homme") sexeDB = "H";
    else if (sexe == "Femme") sexeDB = "F";
    else { erreurMessage = "Sexe invalide !"; return false; }

    Connection c;
    if (!c.createconnect()) {
        erreurMessage = "Connexion échouée !";
        return false;
    }

    QSqlDatabase db = QSqlDatabase::database();

    QSqlQuery query(db);
    query.prepare(
        "UPDATE CLIENT SET NOM = :nom, PRENOM = :prenom, NUM_TEL = :tel, "
        "DATE_DE_NAISSANCE = :date, STATUT = :statut, SEXE = :sexe, "
        "ORDONNANCE = :ordo, PHOTO = :photo "
        "WHERE ID_CLIENT = :id"
        );

    query.bindValue(":id", id);
    query.bindValue(":nom", nom.toUpper());
    query.bindValue(":prenom", prenom);
    query.bindValue(":tel", telephone);
    query.bindValue(":date", dateNaissance);
    query.bindValue(":statut", statut);
    query.bindValue(":sexe", sexeDB);
    query.bindValue(":ordo", ordonnance.left(20));
    query.bindValue(":photo", photo.left(20));

    if (query.exec()) {
        erreurMessage = "Client modifié avec succès !";
        return true;
    } else {
        erreurMessage = "Erreur modification : " + query.lastError().text();
        return false;
    }
}

bool gestion_client::isValidId(int id) {
    QString idStr = QString::number(id);
    return id > 0 && idStr.length() == 8;  // Exactement 8 chiffres
}

bool gestion_client::isValidNom(const QString &nom) {
    return nom.trimmed().length() >= 2 && nom.trimmed().length() <= 20 &&
           QRegularExpression("^[A-Za-zÀ-ÿ\\s\\-' ]+$").match(nom).hasMatch();
}
bool gestion_client::isValidPrenom(const QString &prenom) { return isValidNom(prenom); }
bool gestion_client::isValidTelephone(int telephone) {
    QString telStr = QString::number(telephone);
    return telStr.length() == 8;  // Exactement 8 chiffres
}
bool gestion_client::isValidDateNaissance(const QDate &date) {
    if (!date.isValid()) return false;
    int age = QDate::currentDate().year() - date.year();
    if (QDate::currentDate().month() < date.month() ||
        (QDate::currentDate().month() == date.month() && QDate::currentDate().day() < date.day())) age--;
    return age >= 0 && age <= 120;
}
bool gestion_client::isValidStatut(const QString &statut) {
    return statut == "Nouveau" || statut == "Ancien" || statut == "VIP";
}
bool gestion_client::isValidSexe(const QString &sexe) {
    return sexe == "H" || sexe == "F";
}

bool gestion_client::isValid() const {
    return isValidId(m_id) && isValidNom(m_nom) && isValidPrenom(m_prenom) &&
           isValidTelephone(m_telephone) && isValidDateNaissance(m_dateNaissance) &&
           isValidStatut(m_statut) && isValidSexe(m_sexe);
}

QString gestion_client::toString() const {
    return QString("Client[%1, %2 %3, %4 ans, %5]")
    .arg(m_id).arg(m_nom).arg(m_prenom).arg(getAge()).arg(m_statut);
}
