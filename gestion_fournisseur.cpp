#include "gestion_fournisseur.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QSqlError>

// ======= Constructeurs ========

Gestion_Fournisseur::Gestion_Fournisseur()
{
    ID = "";
    NOM = "";
    EMAIL = "";
    TEL = "";
    CATEGORIE = "";
    ADRESSE = "";
}

Gestion_Fournisseur::Gestion_Fournisseur(QString ID, QString NOM, QString EMAIL, QString TEL, QString CATEGORIE, QString ADRESSE)
{
    this->ID = ID;
    this->NOM = NOM;
    this->EMAIL = EMAIL;
    this->TEL = TEL;
    this->CATEGORIE = CATEGORIE;
    this->ADRESSE = ADRESSE;
}

// ======= Ajouter ========

bool Gestion_Fournisseur::ajouter_fournisseurs()
{
    QSqlQuery query;
    query.prepare("INSERT INTO FOURNISSEUR (ID, NOM, EMAIL, TEL, CATEGORIE, ADRESSE) "
                  "VALUES (:ID, :NOM, :EMAIL, :TEL, :CATEGORIE, :ADRESSE)");

    query.bindValue(":ID", ID);
    query.bindValue(":NOM", NOM);
    query.bindValue(":EMAIL", EMAIL);
    query.bindValue(":TEL", TEL);
    query.bindValue(":CATEGORIE", CATEGORIE);
    query.bindValue(":ADRESSE", ADRESSE);

    if (query.exec())
    {
        QMessageBox::information(nullptr, QObject::tr("Succès"),
                                 QObject::tr("Fournisseur ajouté avec succès !"));
        return true;
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("Échec d'ajout : %1").arg(query.lastError().text()));
        return false;
    }
}

// ======= Afficher ========

QSqlQueryModel* Gestion_Fournisseur::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT ID, NOM, EMAIL, TEL, CATEGORIE, ADRESSE FROM FOURNISSEUR");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Téléphone"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Catégorie"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Adresse"));

    return model;
}

// ======= Modifier ========

bool Gestion_Fournisseur::modifier_fournisseurs()
{
    QSqlQuery query;
    query.prepare("UPDATE FOURNISSEUR SET NOM = :NOM, EMAIL = :EMAIL, TEL = :TEL, "
                  "CATEGORIE = :CATEGORIE, ADRESSE = :ADRESSE WHERE ID = :ID");

    query.bindValue(":ID", ID);
    query.bindValue(":NOM", NOM);
    query.bindValue(":EMAIL", EMAIL);
    query.bindValue(":TEL", TEL);
    query.bindValue(":CATEGORIE", CATEGORIE);
    query.bindValue(":ADRESSE", ADRESSE);

    if (query.exec())
    {
        QMessageBox::information(nullptr, QObject::tr("Succès"),
                                 QObject::tr("Fournisseur modifié avec succès !"));
        return true;
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("Échec de modification : %1").arg(query.lastError().text()));
        return false;
    }
}

// ======= Supprimer ========

bool Gestion_Fournisseur::supprimer_fournisseurs(const QString &ID)
{
    QSqlQuery query;
    query.prepare("DELETE FROM FOURNISSEUR WHERE ID = :ID");
    query.bindValue(":ID", ID);

    if (query.exec())
    {
        QMessageBox::information(nullptr, QObject::tr("Succès"),
                                 QObject::tr("Fournisseur supprimé !"));
        return true;
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("Échec de suppression : %1").arg(query.lastError().text()));
        return false;
    }
}


QSqlQueryModel* Gestion_Fournisseur::rechercher_fournisseur(const QString &ID)
{
    QSqlQueryModel *model = new QSqlQueryModel();

    QSqlQuery query;
    query.prepare("SELECT ID, NOM, EMAIL, TEL, CATEGORIE, ADRESSE FROM FOURNISSEUR WHERE ID = :ID");
    query.bindValue(":ID", ID);
    query.exec();

    model->setQuery(query);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Téléphone"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Catégorie"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Adresse"));

    return model;
}
QSqlQueryModel* Gestion_Fournisseur::trier_fournisseurs(const QString &critere)
{
    QSqlQueryModel *model = new QSqlQueryModel();

    QString queryStr;

    if (critere == "id") {
        queryStr = "SELECT ID, NOM, EMAIL, TEL, CATEGORIE, ADRESSE FROM FOURNISSEUR ORDER BY ID";
    } else if (critere == "nom") {
        queryStr = "SELECT ID, NOM, EMAIL, TEL, CATEGORIE, ADRESSE FROM FOURNISSEUR ORDER BY NOM";
    } else {
        queryStr = "SELECT ID, NOM, EMAIL, TEL, CATEGORIE, ADRESSE FROM FOURNISSEUR"; // pas de tri
    }

    model->setQuery(queryStr);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Téléphone"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Catégorie"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Adresse"));

    return model;
}

