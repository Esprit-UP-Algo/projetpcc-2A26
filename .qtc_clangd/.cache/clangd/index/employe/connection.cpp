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
    db.setDatabaseName("projet_kn");
    db.setUserName("system");
    db.setPassword("oraclekn");

    if (db.open())
        test = true;
    return test;
}
