#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QTableWidgetItem>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // CONNEXIONS DE LA BARRE LATÉRALE
    connect(ui->toolButton_client1, &QToolButton::clicked, this, &MainWindow::showClientInterface);
    connect(ui->toolButton_person1, &QToolButton::clicked, this, &MainWindow::showPersonnelInterface);
    connect(ui->toolButton_loc1, &QToolButton::clicked, this, &MainWindow::showLocauxInterface);

    // Fournisseurs et Produits - message d'information
    connect(ui->toolButton_fourn1, &QToolButton::clicked, [=]() {
        QMessageBox::information(this, "Fournisseurs", "Interface Fournisseurs en cours de développement...");
    });

    connect(ui->toolButton_prod1, &QToolButton::clicked, [=]() {
        QMessageBox::information(this, "Produits", "Interface Produits en cours de développement...");
    });

    // Interface par défaut - Clients
    showClientInterface();

    connect(ui->btnAjouterClient_4, &QPushButton::clicked, [=]() {
        ui->stackedWidget_4->setCurrentIndex(2);
    });

    connect(ui->btnListeClients_4, &QPushButton::clicked, [=]() {
        ui->stackedWidget_4->setCurrentIndex(0);
    });

    connect(ui->btnAjouterClient_5, &QPushButton::clicked, [=]() {
        ui->stackedWidget_4->setCurrentIndex(2);
    });

    connect(ui->btnListeClients_5, &QPushButton::clicked, [=]() {
        ui->stackedWidget_4->setCurrentIndex(0);
    });

    connect(ui->btnAjouterPersonnel_3, &QPushButton::clicked, [=]() {
        ui->stackedWidget_3->setCurrentIndex(2);
    });

    connect(ui->btnListePersonnel_3, &QPushButton::clicked, [=]() {
        ui->stackedWidget_3->setCurrentIndex(0);
    });

    connect(ui->btnAjouterClient_2, &QPushButton::clicked, [=]() {
        ui->stackedWidget_3->setCurrentIndex(2);
    });

    connect(ui->btnListeClients_2, &QPushButton::clicked, [=]() {
        ui->stackedWidget_3->setCurrentIndex(0);
    });

    connect(ui->btnAjouterPersonnel_4, &QPushButton::clicked, [=]() {
        ui->stackedWidget_2->setCurrentIndex(2);
    });

    connect(ui->btnListePersonnel_4, &QPushButton::clicked, [=]() {
        ui->stackedWidget_2->setCurrentIndex(0);
    });

    connect(ui->btnAjouterClient_3, &QPushButton::clicked, [=]() {
        ui->stackedWidget_2->setCurrentIndex(2);
    });

    connect(ui->btnListeClients_3, &QPushButton::clicked, [=]() {
        ui->stackedWidget_2->setCurrentIndex(0);
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

        ui->tableClients->setCellWidget(row, 7, widget);
        ui->tableClients->setCellWidget(row, 8, btnSMS);
    }

    QTableWidget* tablePersonnel = ui->tablePersonnel;

    // Configuration du tableau
    tablePersonnel->setRowCount(8);

    // Ajuster la largeur des colonnes
    tablePersonnel->verticalHeader()->setDefaultSectionSize(45);
    tablePersonnel->setColumnWidth(7, 60);  // Colonne "Documents"
    tablePersonnel->setColumnWidth(8, 60);  // Colonne "Permissions"
    tablePersonnel->setColumnWidth(9, 90);  // Colonne "Actions"

    // Ajouter des données d'exemple au tableau personnel
    QStringList nomsPersonnel = {"Dupont", "Martin", "Bernard", "Dubois", "Thomas", "Robert", "Richard", "Petit"};
    QStringList prenomsPersonnel = {"Jean", "Marie", "Pierre", "Sophie", "Luc", "Anne", "Paul", "Claire"};
    QStringList roles = {"Responsable", "Vendeur", "Manager", "Opticien", "Vendeur", "Manager", "Opticien", "Responsable"};

    for (int row = 0; row < tablePersonnel->rowCount(); ++row) {
        // Remplir les données du personnel
        tablePersonnel->setItem(row, 0, new QTableWidgetItem(QString::number(row + 1001)));
        tablePersonnel->setItem(row, 1, new QTableWidgetItem(nomsPersonnel[row]));
        tablePersonnel->setItem(row, 2, new QTableWidgetItem(prenomsPersonnel[row]));
        tablePersonnel->setItem(row, 3, new QTableWidgetItem("0123456789"));
        tablePersonnel->setItem(row, 4, new QTableWidgetItem(nomsPersonnel[row].toLower() + "@entreprise.com"));
        tablePersonnel->setItem(row, 5, new QTableWidgetItem(roles[row]));
        tablePersonnel->setItem(row, 6, new QTableWidgetItem("Actif"));

        // Créer une taille de bouton commune pour la cohérence
        QSize buttonSize(30, 30);
        QSize iconSize(20, 20);

        // --- Colonne 7 : DOCUMENTS (centré) ---
        QWidget *docsWidget = new QWidget();
        QHBoxLayout *docsLayout = new QHBoxLayout(docsWidget);
        docsLayout->setContentsMargins(0, 0, 0, 0);
        docsLayout->setAlignment(Qt::AlignCenter);

        QPushButton *btnDocs = new QPushButton();
        btnDocs->setFlat(true);
        btnDocs->setFixedSize(buttonSize);
        btnDocs->setIcon(QIcon(":/icons/clip.png"));
        btnDocs->setIconSize(iconSize);
        btnDocs->setToolTip("Gérer les documents");
        btnDocs->setStyleSheet("QPushButton { background-color: #5D6D7E; border-radius: 8px; border: none; } QPushButton:hover { background-color: #85929E; }");

        docsLayout->addWidget(btnDocs);
        tablePersonnel->setCellWidget(row, 7, docsWidget);

        // --- Colonne 8 : PERMISSIONS (centré) ---
        QWidget *permsWidget = new QWidget();
        QHBoxLayout *permsLayout = new QHBoxLayout(permsWidget);
        permsLayout->setContentsMargins(0, 0, 0, 0);
        permsLayout->setAlignment(Qt::AlignCenter);

        QPushButton *btnPerms = new QPushButton();
        btnPerms->setFlat(true);
        btnPerms->setFixedSize(buttonSize);
        btnPerms->setIcon(QIcon(":/icons/shield.png"));
        btnPerms->setIconSize(iconSize);
        btnPerms->setToolTip("Gérer les permissions");
        btnPerms->setStyleSheet("QPushButton { background-color: #884EA0; border-radius: 8px; border: none; } QPushButton:hover { background-color: #AF7AC5; }");

        permsLayout->addWidget(btnPerms);
        tablePersonnel->setCellWidget(row, 8, permsWidget);

        // --- Colonne 9 : ACTIONS (centré) ---
        QWidget *actionsWidget = new QWidget();
        QHBoxLayout *actionsLayout = new QHBoxLayout(actionsWidget);
        actionsLayout->setContentsMargins(0, 0, 0, 0);
        actionsLayout->setSpacing(8);
        actionsLayout->setAlignment(Qt::AlignCenter);

        QPushButton *btnModif = new QPushButton();
        btnModif->setFlat(true);
        btnModif->setFixedSize(buttonSize);
        btnModif->setIcon(QIcon(":/icons/pencil.png"));
        btnModif->setIconSize(iconSize);
        btnModif->setToolTip("Modifier l'employé");
        btnModif->setStyleSheet("QPushButton { background-color: rgb(0, 0, 124); border-radius: 8px; border: none; } QPushButton:hover { background-color: #2980b9; }");

        QPushButton *btnSupp = new QPushButton();
        btnSupp->setFlat(true);
        btnSupp->setFixedSize(buttonSize);
        btnSupp->setIcon(QIcon(":/icons/trash.png"));
        btnSupp->setIconSize(iconSize);
        btnSupp->setToolTip("Supprimer l'employé");
        btnSupp->setStyleSheet("QPushButton { background-color: #cd6155; border-radius: 8px; border: none; } QPushButton:hover { background-color: #c0392b; }");

        actionsLayout->addWidget(btnModif);
        actionsLayout->addWidget(btnSupp);
        tablePersonnel->setCellWidget(row, 9, actionsWidget);
    }
}

// IMPLÉMENTATION DES SLOTS POUR LA NAVIGATION PRINCIPALE
void MainWindow::showClientInterface()
{
    ui->stackedWidget->setCurrentWidget(ui->clients);
    ui->stackedWidget_4->setCurrentIndex(0);
}

void MainWindow::showPersonnelInterface()
{
    ui->stackedWidget->setCurrentWidget(ui->personnel);
    ui->stackedWidget_3->setCurrentIndex(0);
}

void MainWindow::showLocauxInterface()
{
    ui->stackedWidget->setCurrentWidget(ui->locaux);
    ui->stackedWidget_2->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}
