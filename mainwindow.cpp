#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Définir la page initiale sur la liste des clients
    ui->stackedWidget->setCurrentIndex(0);

    // Connexions pour la navigation
    connect(ui->btnAjouterClient_3, &QPushButton::clicked, [=]() {
        ui->stackedWidget->setCurrentIndex(2); // Page "Ajouter client"
    });

    connect(ui->btnListeClients_3, &QPushButton::clicked, [=]() {
        ui->stackedWidget->setCurrentIndex(0); // Page "Liste des clients"
    });

    connect(ui->btnAjouterClient_2, &QPushButton::clicked, [=]() {
        ui->stackedWidget->setCurrentIndex(2); // Page "Ajouter client"
    });

    connect(ui->btnListeClients_2, &QPushButton::clicked, [=]() {
        ui->stackedWidget->setCurrentIndex(0); // Page "Liste des clients"
    });


    for (int row = 0; row < ui->tableClients->rowCount(); ++row) {
        QWidget *widget = new QWidget();
        QHBoxLayout *layout = new QHBoxLayout(widget);

        QPushButton *btnModif = new QPushButton("Modifier");
        QPushButton *btnSupp = new QPushButton("🗑️Supp");


        /*btnModif->setStyleSheet(
            "QPushButton {"
            "    background-color: #a55eea;"
            "    color: white;"
            "    border-radius: 8px;"
            "    padding: 6px 10px;"
            "    border: none;"
            "    font-weight: bold;"
            "    font-size: 9px;"
            "    min-width: 60px;"
            "}"
            "QPushButton:hover {"
            "    background-color: #8854d0;"
            "}"
            );


        btnSupp->setStyleSheet(
            "QPushButton {"
            "    background-color: #fd79a8;"
            "    color: white;"
            "    border-radius: 8px;"
            "    padding: 6px 10px;"
            "    border: none;"
            "    font-weight: bold;"
            "    font-size: 9px;"
            "    min-width: 55px;"
            "}"
            "QPushButton:hover {"
            "    background-color: #e84393;"
            "}"
            );*/

        layout->addWidget(btnModif);
        layout->addWidget(btnSupp);
        layout->setContentsMargins(2, 2, 2, 2);
        layout->setSpacing(4);

        ui->tableClients->setCellWidget(row, 7, widget);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
