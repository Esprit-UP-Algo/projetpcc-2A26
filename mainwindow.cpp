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
    ui->tableClients->setRowCount(8);
    QStringList prenoms = {"eya", "eya", "eya", "eya"};
    QStringList noms = {"m", "m", "m", "m"};

    for (int row = 0; row < 4; ++row) {
        ui->tableClients->setItem(row, 0, new QTableWidgetItem(QString::number(row + 1)));
        ui->tableClients->setItem(row, 1, new QTableWidgetItem(noms[row]));
        ui->tableClients->setItem(row, 2, new QTableWidgetItem(prenoms[row]));
        ui->tableClients->setItem(row, 3, new QTableWidgetItem("30"));
        ui->tableClients->setItem(row, 4, new QTableWidgetItem("VIP"));
        ui->tableClients->setItem(row, 5, new QTableWidgetItem("0123456789"));
        ui->tableClients->setItem(row, 6, new QTableWidgetItem("Femme"));
    }

    ui->tableClients->setColumnWidth(7, 180);
    ui->tableClients->setColumnWidth(8, 100);
    for (int row = 0; row < ui->tableClients->rowCount(); ++row) {
        QWidget *widget = new QWidget();
        QHBoxLayout *layout = new QHBoxLayout(widget);

        QPushButton *btnModif = new QPushButton("MOD️");
        QPushButton *btnSupp = new QPushButton("SUP️");
        QPushButton *btnSMS = new QPushButton("📱 SMS");

        // STYLE ACTIVÉ - DÉCOMMENTÉ
        btnModif->setStyleSheet(
            "QPushButton {"
            "    background-color: rgb(0, 0, 124);"
            "    color: white;"
            "    border-radius: 8px;"
            "    padding: 8px 12px;"
            "    border: none;"
            "    font-weight: bold;"
            "    font-size: 8px;"
            "    min-width: 80px;"

            "}"
            "QPushButton:hover {"
            "    background-color: #2980b9;"
            "}"
            );

        // BOUTON SUPPRIMER - Rouge pâle
        btnSupp->setStyleSheet(
                   "QPushButton {"
                   "    background-color: #cd6155;"
                   "    color: white;"
                   "    border-radius: 8px;"
                   "    padding: 8px 12px;"
                   "    border: none;"
                   "    font-weight:bold;"
                   "    font-size: 8px;"
                   "    min-width: 80px;"

                   "}"
                   "QPushButton:hover {"
                   "    background-color: #c0392b;"
                   "}"
            );
        btnSMS->setStyleSheet(
            "QPushButton {"
            "    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #6c5ce7, stop:1 #a29bfe);"
            "    color: white;"
            "    border-radius: 8px;"
            "    padding: 8px 12px;"
            "    border: none;"
            "    font-weight: bold;"
            "    font-size: 8px;"
            "    min-width: 80px;"

            "}"
            "QPushButton:hover {"
             "    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #5a4a82, stop:1 #41375f);"
            "}"
            );



        layout->addWidget(btnModif);
        layout->addWidget(btnSupp);
        layout->setContentsMargins(5, 2, 5, 2);
        layout->setSpacing(8);

        // Utilisez setCellWidget pour écraser le contenu du .ui
        ui->tableClients->setCellWidget(row, 7, widget);
        ui->tableClients->setCellWidget(row, 8, btnSMS);

    }
}


MainWindow::~MainWindow()
{
    delete ui;
}
