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

    // NOUVELLES CONNEXIONS - Fournisseurs et Produits
    connect(ui->toolButton_fourn1, &QToolButton::clicked, this, &MainWindow::showFournisseurInterface);
    connect(ui->toolButton_prod1, &QToolButton::clicked, this, &MainWindow::showProduitsInterface);

    // Interface par défaut - Clients
    showClientInterface();

    // Navigation pour Clients
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

    // Navigation pour Personnel
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

    // Navigation pour Locaux
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

    // NOUVELLES CONNEXIONS - Navigation pour Fournisseurs
    connect(ui->btnAjouterClient_6, &QPushButton::clicked, [=]() {
        ui->stackedWidget_5->setCurrentIndex(2);
    });

    connect(ui->btnListeClients_6, &QPushButton::clicked, [=]() {
        ui->stackedWidget_5->setCurrentIndex(0);
    });

    connect(ui->btnAjouterClient_7, &QPushButton::clicked, [=]() {
        ui->stackedWidget_5->setCurrentIndex(2);
    });

    connect(ui->btnListeClients_7, &QPushButton::clicked, [=]() {
        ui->stackedWidget_5->setCurrentIndex(0);
    });

    // NOUVELLES CONNEXIONS - Navigation pour Produits
    connect(ui->btnAjouterPersonnel_5, &QPushButton::clicked, [=]() {
        ui->stackedWidget_6->setCurrentIndex(2);
    });

    connect(ui->btnListePersonnel_5, &QPushButton::clicked, [=]() {
        ui->stackedWidget_6->setCurrentIndex(0);
    });

    connect(ui->btnAjouterClient_8, &QPushButton::clicked, [=]() {
        ui->stackedWidget_6->setCurrentIndex(2);
    });

    connect(ui->btnListeClients_8, &QPushButton::clicked, [=]() {
        ui->stackedWidget_6->setCurrentIndex(0);
    });

    // ========== CONFIGURATION DE LA TABLE CLIENTS ==========
    ui->tableClients->setRowCount(8);
    QStringList prenoms = {"Sophie", "Pierre", "Marie", "Jean", "Laura", "Thomas", "Emma", "Nicolas"};
    QStringList noms = {"Martin", "Dubois", "Bernard", "Moreau", "Petit", "Leroy", "Roux", "Garcia"};

    for (int row = 0; row < 8; ++row) {
        ui->tableClients->setItem(row, 0, new QTableWidgetItem(QString::number(100 + row)));
        ui->tableClients->setItem(row, 1, new QTableWidgetItem(noms[row]));
        ui->tableClients->setItem(row, 2, new QTableWidgetItem(prenoms[row]));
        ui->tableClients->setItem(row, 3, new QTableWidgetItem(QString::number(25 + row)));
        ui->tableClients->setItem(row, 4, new QTableWidgetItem(row % 3 == 0 ? "VIP" : (row % 3 == 1 ? "Fidèle" : "Nouveau")));
        ui->tableClients->setItem(row, 5, new QTableWidgetItem(QString("01234567%1").arg(row)));
        ui->tableClients->setItem(row, 6, new QTableWidgetItem(row % 2 == 0 ? "Homme" : "Femme"));
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

        // Connecter les boutons à des actions
        connect(btnModif, &QPushButton::clicked, [=]() {
            QMessageBox::information(this, "Modification", "Modifier le client: " + noms[row] + " " + prenoms[row]);
        });

        connect(btnSupp, &QPushButton::clicked, [=]() {
            QMessageBox::warning(this, "Suppression", "Supprimer le client: " + noms[row] + " " + prenoms[row]);
        });

        connect(btnSMS, &QPushButton::clicked, [=]() {
            QMessageBox::information(this, "SMS", "Envoyer SMS à: " + noms[row] + " " + prenoms[row]);
        });

        layout->addWidget(btnModif);
        layout->addWidget(btnSupp);
        layout->setContentsMargins(5, 2, 5, 2);
        layout->setSpacing(8);

        ui->tableClients->setCellWidget(row, 7, widget);
        ui->tableClients->setCellWidget(row, 8, btnSMS);
    }

    // ========== CONFIGURATION DE LA TABLE PERSONNEL ==========
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

    // ========== CONFIGURATION DE LA TABLE LOCAUX ==========
    QTableWidget* tableLocaux = ui->tablePersonnel_2;

    // Configuration du tableau
    tableLocaux->setRowCount(8);

    // Ajuster la largeur des colonnes
    tableLocaux->setColumnWidth(0, 80);   // ID
    tableLocaux->setColumnWidth(1, 120);  // Nom
    tableLocaux->setColumnWidth(2, 100);  // Téléphone
    tableLocaux->setColumnWidth(3, 150);  // Adresse
    tableLocaux->setColumnWidth(4, 80);   // Superficie
    tableLocaux->setColumnWidth(5, 120);  // Chiffre d'affaires
    tableLocaux->setColumnWidth(6, 100);  // État
    tableLocaux->setColumnWidth(7, 120);  // Actions

    // Données d'exemple pour les locaux
    QStringList nomsLocaux = {"Optique Centre-Ville", "Vision Plus", "Lunettes & Style", "Optique Modern", "Vision Express", "Optic 2000", "Grand Optical", "Atol Les Opticiens"};
    QStringList telephones = {"01 42 68 53 09", "01 46 27 82 15", "01 48 74 36 91", "01 43 29 67 42", "01 45 78 23 56", "01 47 38 92 74", "01 44 65 39 81", "01 49 72 34 68"};
    QStringList adresses = {"15 Rue de la République, Paris", "28 Avenue des Champs-Élysées, Paris", "7 Place Bellecour, Lyon", "42 Rue du Rhône, Genève", "89 Gran Via, Madrid", "56 Oxford Street, Londres", "23 Kurfürstendamm, Berlin", "12 Via Montenapoleone, Milan"};
    QList<double> superficies = {85.5, 120.0, 65.0, 95.0, 110.0, 75.0, 140.0, 88.0};
    QList<double> chiffresAffaires = {125000.0, 185000.0, 89000.0, 142000.0, 168000.0, 95000.0, 210000.0, 135000.0};
    QStringList etats = {"Ouvert", "Ouvert", "Fermé", "Ouvert", "Disponible", "Ouvert", "Ouvert", "Fermé"};

    for (int row = 0; row < tableLocaux->rowCount(); ++row) {
        // Remplir les données des locaux
        tableLocaux->setItem(row, 0, new QTableWidgetItem(QString::number(2000 + row)));
        tableLocaux->setItem(row, 1, new QTableWidgetItem(nomsLocaux[row]));
        tableLocaux->setItem(row, 2, new QTableWidgetItem(telephones[row]));
        tableLocaux->setItem(row, 3, new QTableWidgetItem(adresses[row]));
        tableLocaux->setItem(row, 4, new QTableWidgetItem(QString::number(superficies[row], 'f', 1) + " m²"));
        tableLocaux->setItem(row, 5, new QTableWidgetItem(QString::number(chiffresAffaires[row], 'f', 0) + " €"));
        tableLocaux->setItem(row, 6, new QTableWidgetItem(etats[row]));

        // Créer les boutons d'action avec les mêmes icônes que la table Produits
        QWidget *actionsWidget = new QWidget();
        QHBoxLayout *actionsLayout = new QHBoxLayout(actionsWidget);
        actionsLayout->setContentsMargins(0, 0, 0, 0);
        actionsLayout->setSpacing(8);
        actionsLayout->setAlignment(Qt::AlignCenter);

        // Créer une taille de bouton commune pour la cohérence
        QSize buttonSize(30, 30);
        QSize iconSize(20, 20);

        // Bouton Modifier (identique à la table Produits)
        QPushButton *btnModif = new QPushButton();
        btnModif->setFlat(true);
        btnModif->setFixedSize(buttonSize);
        btnModif->setIcon(QIcon(":/icons/pencil.png"));
        btnModif->setIconSize(iconSize);
        btnModif->setToolTip("Modifier le local");
        btnModif->setStyleSheet("QPushButton { background-color: rgb(0, 0, 124); border-radius: 8px; border: none; } QPushButton:hover { background-color: #2980b9; }");

        // Bouton Supprimer (identique à la table Produits)
        QPushButton *btnSupp = new QPushButton();
        btnSupp->setFlat(true);
        btnSupp->setFixedSize(buttonSize);
        btnSupp->setIcon(QIcon(":/icons/trash.png"));
        btnSupp->setIconSize(iconSize);
        btnSupp->setToolTip("Supprimer le local");
        btnSupp->setStyleSheet("QPushButton { background-color: #cd6155; border-radius: 8px; border: none; } QPushButton:hover { background-color: #c0392b; }");

        // Connecter les boutons à des actions
        connect(btnModif, &QPushButton::clicked, [=]() {
            QMessageBox::information(this, "Modification", "Modifier le local: " + nomsLocaux[row]);
        });

        connect(btnSupp, &QPushButton::clicked, [=]() {
            QMessageBox::warning(this, "Suppression", "Supprimer le local: " + nomsLocaux[row]);
        });

        actionsLayout->addWidget(btnModif);
        actionsLayout->addWidget(btnSupp);
        tableLocaux->setCellWidget(row, 7, actionsWidget);
    }

    // Ajuster la hauteur des lignes
    tableLocaux->verticalHeader()->setDefaultSectionSize(45);

    // ========== CONFIGURATION DE LA TABLE PRODUITS ==========
    QTableWidget* tableProduits = ui->tablePersonnel_3;

    // Configuration du tableau
    tableProduits->setRowCount(8);

    // Ajuster la largeur des colonnes
    tableProduits->setColumnWidth(0, 80);   // ID Produit
    tableProduits->setColumnWidth(1, 100);  // Marque
    tableProduits->setColumnWidth(2, 100);  // Modèle
    tableProduits->setColumnWidth(3, 80);   // Type
    tableProduits->setColumnWidth(4, 80);   // Couleur
    tableProduits->setColumnWidth(5, 80);   // Prix
    tableProduits->setColumnWidth(6, 80);   // Quantité
    tableProduits->setColumnWidth(7, 100);  // Date d'ajout
    tableProduits->setColumnWidth(8, 120);  // Actions (réduit car seulement 2 boutons)

    // Données d'exemple pour les produits
    QStringList marques = {"Ray-Ban", "Oakley", "Persol", "Gucci", "Prada", "Dior", "Chanel", "Versace"};
    QStringList modeles = {"Aviator", "Frogskins", "PO0649", "GG0286O", "PR16WV", "DIORSTELLAIRE", "CH5348", "VE4285"};
    QStringList types = {"Solaire", "Vue", "Mixte", "Solaire", "Vue", "Mixte", "Solaire", "Lentille"};
    QStringList couleurs = {"Noir", "Tortue", "Brun", "Or", "Argent", "Rose", "Bleu", "Vert"};
    QList<double> prix = {150.0, 120.0, 200.0, 350.0, 280.0, 320.0, 400.0, 85.0};
    QList<int> quantites = {15, 8, 5, 3, 12, 6, 2, 25};
    QStringList dates = {"2024-01-15", "2024-01-20", "2024-02-01", "2024-02-10", "2024-02-15", "2024-03-01", "2024-03-05", "2024-03-10"};

    for (int row = 0; row < tableProduits->rowCount(); ++row) {
        // Remplir les données des produits
        tableProduits->setItem(row, 0, new QTableWidgetItem(QString::number(1000 + row)));
        tableProduits->setItem(row, 1, new QTableWidgetItem(marques[row]));
        tableProduits->setItem(row, 2, new QTableWidgetItem(modeles[row]));
        tableProduits->setItem(row, 3, new QTableWidgetItem(types[row]));
        tableProduits->setItem(row, 4, new QTableWidgetItem(couleurs[row]));
        tableProduits->setItem(row, 5, new QTableWidgetItem(QString::number(prix[row], 'f', 2) + " €"));
        tableProduits->setItem(row, 6, new QTableWidgetItem(QString::number(quantites[row])));
        tableProduits->setItem(row, 7, new QTableWidgetItem(dates[row]));

        // Créer les boutons d'action avec les mêmes icônes que la table Personnel
        QWidget *actionsWidget = new QWidget();
        QHBoxLayout *actionsLayout = new QHBoxLayout(actionsWidget);
        actionsLayout->setContentsMargins(0, 0, 0, 0);
        actionsLayout->setSpacing(8);
        actionsLayout->setAlignment(Qt::AlignCenter);

        // Créer une taille de bouton commune pour la cohérence
        QSize buttonSize(30, 30);
        QSize iconSize(20, 20);

        // Bouton Modifier (identique à la table Personnel)
        QPushButton *btnModif = new QPushButton();
        btnModif->setFlat(true);
        btnModif->setFixedSize(buttonSize);
        btnModif->setIcon(QIcon(":/icons/pencil.png"));
        btnModif->setIconSize(iconSize);
        btnModif->setToolTip("Modifier le produit");
        btnModif->setStyleSheet("QPushButton { background-color: rgb(0, 0, 124); border-radius: 8px; border: none; } QPushButton:hover { background-color: #2980b9; }");

        // Bouton Supprimer (identique à la table Personnel)
        QPushButton *btnSupp = new QPushButton();
        btnSupp->setFlat(true);
        btnSupp->setFixedSize(buttonSize);
        btnSupp->setIcon(QIcon(":/icons/trash.png"));
        btnSupp->setIconSize(iconSize);
        btnSupp->setToolTip("Supprimer le produit");
        btnSupp->setStyleSheet("QPushButton { background-color: #cd6155; border-radius: 8px; border: none; } QPushButton:hover { background-color: #c0392b; }");

        // Connecter les boutons à des actions
        connect(btnModif, &QPushButton::clicked, [=]() {
            QMessageBox::information(this, "Modification", "Modifier le produit: " + marques[row] + " " + modeles[row]);
        });

        connect(btnSupp, &QPushButton::clicked, [=]() {
            QMessageBox::warning(this, "Suppression", "Supprimer le produit: " + marques[row] + " " + modeles[row]);
        });

        actionsLayout->addWidget(btnModif);
        actionsLayout->addWidget(btnSupp);
        tableProduits->setCellWidget(row, 8, actionsWidget);
    }

    // Ajuster la hauteur des lignes
    tableProduits->verticalHeader()->setDefaultSectionSize(45);
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

// NOUVELLES IMPLÉMENTATIONS POUR FOURNISSEURS ET PRODUITS
void MainWindow::showFournisseurInterface()
{
    ui->stackedWidget->setCurrentWidget(ui->fournisseur);
    ui->stackedWidget_5->setCurrentIndex(0);
}

void MainWindow::showProduitsInterface()
{
    ui->stackedWidget->setCurrentWidget(ui->produits);
    ui->stackedWidget_6->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}
