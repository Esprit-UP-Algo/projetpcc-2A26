#include "mainwindow.h"
#include "connection.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;

    if (!c.createconnect()) {
        qDebug() << " Erreur : Base non ouverte !";
     }

    qDebug() << "Base Oracle connectée";

    MainWindow w;
    w.show();
    return a.exec();
}
