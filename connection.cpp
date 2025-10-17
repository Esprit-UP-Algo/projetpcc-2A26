#include "connection.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Source_Projet2A");//inserer le nom de la source de données
db.setUserName("eya");//inserer nom de l'utilisateur
db.setPassword("eya456");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
