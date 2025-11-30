#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gestion_client.h"
#include "gestion_personnel.h"
#include "gestion_locaux.h"
#include "gestion_fournisseur.h"
#include "gestion_produit.h"
#include "connection.h"
#include "SMS_client.h"
#include "StatisticsWidget.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QRegularExpression>


#include <QPrinter> // Export PDF
#include <QTextDocument>
#include <QFileDialog>
#include <QTextTable>
#include <QTextCursor>
#include <QTextTableFormat>
#include <QTextCharFormat>
#include <QPageSize>
#include <QPageLayout>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,lineEditIDProduit(nullptr)
    , photoPath("")
    , ordonnancePath("")

{
    ui->setupUi(this);
    connect(ui->searchLineEdit_3, &QLineEdit::textChanged,
            this, &MainWindow::on_searchLineEdit_3_textChanged);
    connect(ui->btnExporter_3, &QPushButton::clicked,
            this, &MainWindow::on_btnExporter_3_clicked);
    connect(ui->tableClients, &QTableWidget::doubleClicked, this, &MainWindow::on_tableClients_doubleClicked);

    rafraichirTableauClients();
    verifierInstallationOpenCV();

    // STATISTIQUES
    ui->label_2->setVisible(false);

    // Créer le widget de statistiques à la même position
    m_statsWidget = new StatisticsWidget(this);
    //m_statsWidget->setGeometry(1140, 80, 351, 291);// Même position et taille que l'image
    m_statsWidget->setGeometry(1140, 80, 351, 720); // Nouvelle hauteur

    // Et assurez-vous de cacher le label_3 :
    ui->label_3->setVisible(false);
    connect(ui->stackedWidget_4, &QStackedWidget::currentChanged, this, &MainWindow::onPageChanged);
    connect(ui->stackedWidget, &QStackedWidget::currentChanged, this, &MainWindow::onPageChanged);
    // Initialiser les statistiques
    rafraichirStatistiquesClients();



    // 1. BOUTON UPLOAD PHOTO
    QPushButton *btnUploadPhoto = new QPushButton(ui->frameFicheClient_3);
    btnUploadPhoto->setObjectName("btnUploadPhoto");
    btnUploadPhoto->setGeometry(610, 240, 90, 30);
    btnUploadPhoto->setText("Choisir photo");
    btnUploadPhoto->setStyleSheet("QPushButton {"
                                  "background-color: #41375f;"
                                  "color: white;"
                                  "border-radius: 10px;"
                                  "padding: 5px;"
                                  "font-weight: bold;"
                                  "}"
                                  "QPushButton:hover {"
                                  "background-color: #5a4a82;"
                                  "}");

    // 2. BOUTON UPLOAD ORDONNANCE
    QPushButton *btnUploadOrdonnance = new QPushButton(ui->frameFicheClient_3);
    btnUploadOrdonnance->setObjectName("btnUploadOrdonnance");
    btnUploadOrdonnance->setGeometry(920, 340, 90, 30);
    btnUploadOrdonnance->setText("Choisir fichier");
    btnUploadOrdonnance->setStyleSheet(btnUploadPhoto->styleSheet());

    // 3. CONNEXIONS DES BOUTONS
    connect(btnUploadPhoto, &QPushButton::clicked, this, &MainWindow::on_btnUploadPhoto_clicked);
    connect(btnUploadOrdonnance, &QPushButton::clicked, this, &MainWindow::on_btnUploadOrdonnance_clicked);

    //  CRÉATION DU LINEEDIT ID PRODUIT
    lineEditIDProduit = new QLineEdit(ui->frameFicheClient_3);
    lineEditIDProduit->setObjectName("lineEditIDProduit");
    lineEditIDProduit->setGeometry(790, 390, 201, 31);  // Position où était le textEdit
    lineEditIDProduit->setPlaceholderText("ID du produit acheté");
    lineEditIDProduit->setValidator(new QIntValidator(1, 999999, this));
    lineEditIDProduit->setStyleSheet("color: rgb(0, 0, 0); border: 1px solid gray; border-radius: 5px; padding: 5px;");

    // DÉPLACER LE TEXTEEDIT PLUS BAS POUR FAIRE DE LA PLACE
    ui->textEdit->setGeometry(790, 410, 201, 31);  // On le descend un peu






    // Initialiser le combo de filtrage
    ui->comboProfession_3->clear();
    ui->comboProfession_3->addItem("Tous les filtres");
    ui->comboProfession_3->addItem("Âge: Moins de 30 ans");
    ui->comboProfession_3->addItem("Âge: 30 ans et plus");
    ui->comboProfession_3->addItem("Statut: Nouveau");
    ui->comboProfession_3->addItem("Statut: Ancien");
    ui->comboProfession_3->addItem("Statut: VIP");
    ui->comboProfession_3->addItem("Sexe: Homme");
    ui->comboProfession_3->addItem("Sexe: Femme");

    // Connexions
    //connect(ui->comboProfession_3, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onFiltresChanged);
    connect(ui->searchLineEdit_3, &QLineEdit::textChanged, this, [this]() {
        QString filtre = ui->comboProfession_3->currentText();
        QString recherche = ui->searchLineEdit_3->text().trimmed();
        appliquerFiltreAvecSQL(filtre, recherche);
    });

    connect(ui->comboProfession_3, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onFiltresChanged);

    connect(ui->tableClients, &QTableWidget::itemChanged, this, &MainWindow::onTableItemChanged);
    connect(ui->tablePersonnel, &QTableWidget::itemChanged, this, &MainWindow::onTablePersonnelItemChanged);
    connect(ui->tablePersonnel_2, &QTableWidget::itemChanged, this, &MainWindow::onTableLocauxItemChanged);
    connect(ui->tableClients_2, &QTableWidget::itemChanged, this, &MainWindow::onTableFournisseurItemChanged);
    connect(ui->tablePersonnel_3, &QTableWidget::itemChanged, this, &MainWindow::onTableProduitItemChanged);

    connect(ui->toolButton_client1, &QToolButton::clicked, this, &MainWindow::showClientInterface);
    connect(ui->toolButton_person1, &QToolButton::clicked, this, &MainWindow::showPersonnelInterface);
    connect(ui->toolButton_loc1, &QToolButton::clicked, this, &MainWindow::showLocauxInterface);
    connect(ui->toolButton_fourn1, &QToolButton::clicked, this, &MainWindow::showFournisseurInterface);
    connect(ui->toolButton_prod1, &QToolButton::clicked, this, &MainWindow::showProduitsInterface);

    showClientInterface();

    connect(ui->btnAjouterClient_4, &QPushButton::clicked, [=]() {
        ui->stackedWidget_4->setCurrentIndex(2);
        viderFormulaireClient();
    });
    connect(ui->btnListeClients_4, &QPushButton::clicked, [=]() {
        ui->stackedWidget_4->setCurrentIndex(0);
        rafraichirTableauClients();
    });
    connect(ui->btnAjouterClient_5, &QPushButton::clicked, [=]() {
        ui->stackedWidget_4->setCurrentIndex(2);
        viderFormulaireClient();
    });
    connect(ui->btnListeClients_5, &QPushButton::clicked, [=]() {
        ui->stackedWidget_4->setCurrentIndex(0);
        rafraichirTableauClients();
    });

    connect(ui->btnAjouterPersonnel_3, &QPushButton::clicked, [=]() {
        ui->stackedWidget_3->setCurrentIndex(2);
        viderFormulairePersonnel();
    });
    connect(ui->btnListePersonnel_3, &QPushButton::clicked, [=]() {
        ui->stackedWidget_3->setCurrentIndex(0);
        rafraichirTableauPersonnel();
    });
    connect(ui->btnAjouterClient_2, &QPushButton::clicked, [=]() {
        ui->stackedWidget_3->setCurrentIndex(2);
        viderFormulairePersonnel();
    });
    connect(ui->btnListeClients_2, &QPushButton::clicked, [=]() {
        ui->stackedWidget_3->setCurrentIndex(0);
        rafraichirTableauPersonnel();
    });

    connect(ui->btnAjouterPersonnel_4, &QPushButton::clicked, [=]() {
        ui->stackedWidget_2->setCurrentIndex(2);
        viderFormulaireLocal();
    });
    connect(ui->btnListePersonnel_4, &QPushButton::clicked, [=]() {
        ui->stackedWidget_2->setCurrentIndex(0);
        rafraichirTableauLocaux();
    });
    connect(ui->btnAjouterClient_3, &QPushButton::clicked, [=]() {
        ui->stackedWidget_2->setCurrentIndex(2);
        viderFormulaireLocal();
    });
    connect(ui->btnListeClients_3, &QPushButton::clicked, [=]() {
        ui->stackedWidget_2->setCurrentIndex(0);
        rafraichirTableauLocaux();
    });

    connect(ui->btnAjouterClient_6, &QPushButton::clicked, [=]() {
        ui->stackedWidget_5->setCurrentIndex(2);
        viderFormulaireFournisseur();
    });
    connect(ui->btnListeClients_6, &QPushButton::clicked, [=]() {
        ui->stackedWidget_5->setCurrentIndex(0);
        rafraichirTableauFournisseur();
    });
    connect(ui->btnAjouterClient_7, &QPushButton::clicked, [=]() {
        ui->stackedWidget_5->setCurrentIndex(2);
        viderFormulaireFournisseur();
    });
    connect(ui->btnListeClients_7, &QPushButton::clicked, [=]() {
        ui->stackedWidget_5->setCurrentIndex(0);
        rafraichirTableauFournisseur();
    });

    connect(ui->btnAjouterPersonnel_5, &QPushButton::clicked, [=]() {
        ui->stackedWidget_6->setCurrentIndex(2);
        viderFormulaireProduit();
    });
    connect(ui->btnListePersonnel_5, &QPushButton::clicked, [=]() {
        ui->stackedWidget_6->setCurrentIndex(0);
        rafraichirTableauProduit();
    });
    connect(ui->btnAjouterClient_8, &QPushButton::clicked, [=]() {
        ui->stackedWidget_6->setCurrentIndex(2);
        viderFormulaireProduit();
    });
    connect(ui->btnListeClients_8, &QPushButton::clicked, [=]() {
        ui->stackedWidget_6->setCurrentIndex(0);
        rafraichirTableauProduit();
    });

    connect(ui->btnConfirmer_3, &QPushButton::clicked, this, &MainWindow::on_btnConfirmer_3_clicked);
    connect(ui->btnAnnuler_3, &QPushButton::clicked, this, &MainWindow::on_btnAnnuler_3_clicked);

    connect(ui->btnConfirmer, &QPushButton::clicked, this, &MainWindow::on_btnConfirmerPersonnel_clicked);
    connect(ui->btnAnnuler, &QPushButton::clicked, this, &MainWindow::on_btnAnnulerPersonnel_clicked);

    connect(ui->btnConfirmer_2, &QPushButton::clicked, this, &MainWindow::on_btnConfirmerLocal_clicked);
    connect(ui->btnAnnuler_2, &QPushButton::clicked, this, &MainWindow::on_btnAnnulerLocal_clicked);

    connect(ui->btnConfirmer_4, &QPushButton::clicked, this, &MainWindow::on_btnConfirmerFournisseur_clicked);
    connect(ui->btnAnnuler_4, &QPushButton::clicked, this, &MainWindow::on_btnAnnulerFournisseur_clicked);

    connect(ui->btnConfirmer_5, &QPushButton::clicked, this, &MainWindow::on_btnConfirmerProduit_clicked);
    connect(ui->btnAnnuler_5, &QPushButton::clicked, this, &MainWindow::on_btnAnnulerProduit_clicked);

    connect(ui->lineEditID_3, &QLineEdit::textChanged, this, &MainWindow::validerID);
    connect(ui->lineEditNom_4, &QLineEdit::textChanged, this, &MainWindow::validerNom);
    connect(ui->lineEditPrenom_3, &QLineEdit::textChanged, this, &MainWindow::validerPrenom);
    connect(ui->lineEditPhone_3, &QLineEdit::textChanged, this, &MainWindow::validerTelephone);

    rafraichirTableauClients();
    rafraichirTableauPersonnel();
    rafraichirTableauLocaux();
    rafraichirTableauFournisseur();
    rafraichirTableauProduit();
}

void MainWindow::showClientInterface() {
    ui->stackedWidget->setCurrentWidget(ui->clients);
    ui->stackedWidget_4->setCurrentIndex(0);
}

void MainWindow::showPersonnelInterface() {
    ui->stackedWidget->setCurrentWidget(ui->personnel);
    ui->stackedWidget_3->setCurrentIndex(0);
}

void MainWindow::showLocauxInterface() {
    ui->stackedWidget->setCurrentWidget(ui->locaux);
    ui->stackedWidget_2->setCurrentIndex(0);
}

void MainWindow::showFournisseurInterface() {
    ui->stackedWidget->setCurrentWidget(ui->fournisseur);
    ui->stackedWidget_5->setCurrentIndex(0);
}

void MainWindow::showProduitsInterface() {
    ui->stackedWidget->setCurrentWidget(ui->produits);
    ui->stackedWidget_6->setCurrentIndex(0);
}

void MainWindow::on_btnConfirmer_3_clicked()
{
    bool okId, okTel;
    int id = ui->lineEditID_3->text().toInt(&okId);
    QString nom = ui->lineEditNom_4->text().trimmed();
    QString prenom = ui->lineEditPrenom_3->text().trimmed();
    int telephone = ui->lineEditPhone_3->text().toInt(&okTel);

    QDate dateNaissance = QDate::fromString(ui->lineEditDateNaissance_4->text(), "yyyy-MM-dd");
    if (!dateNaissance.isValid()) {
        dateNaissance = QDate::fromString(ui->lineEditDateNaissance_4->text(), "dd/MM/yyyy");
    }
    if (!dateNaissance.isValid()) {
        QMessageBox::warning(this, "Erreur", "Date invalide !");
        return;
    }

    QString statut;
    if (ui->checkNew_2->isChecked()) statut = "Nouveau";
    else if (ui->checkOld_2->isChecked()) statut = "Ancien";
    else if (ui->checkVIP_2->isChecked()) statut = "VIP";
    else { QMessageBox::warning(this, "Erreur", "Choisissez un statut !"); return; }

    QString sexeTexte = ui->comboSexe_2->currentText();
    if (sexeTexte.isEmpty()) { QMessageBox::warning(this, "Erreur", "Choisissez un sexe !"); return; }

    if (!okId || !okTel || id <= 0) {
        QMessageBox::warning(this, "Erreur", "ID et téléphone doivent être numériques !");
        return;
    }
    QString idProduitText = lineEditIDProduit->text().trimmed();  // ⭐⭐ ICI on utilise lineEditIDProduit
    if (!idProduitText.isEmpty()) {
        bool ok;
        int idProduit = idProduitText.toInt(&ok);

        if (ok && idProduit > 0) {
            // Décrémenter la quantité du produit
            decrementerQuantiteProduit(idProduit);

            // Ajouter à l'historique des achats
            QString achat = QString("Produit %1 - %2")
                                .arg(idProduit)
                                .arg(QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm"));
            ui->listachatrecents->addItem(achat);

        } else {
            QMessageBox::warning(this, "ID produit invalide",
                                 "L'ID du produit doit être un nombre positif !");
            return; // Arrêter la confirmation
        }
    }
    // Utiliser directement les variables existantes
    QString photo = "";
    QString ordonnance = "";

    // Gestion de la photo
    if (!photoPath.isEmpty()) {
        photo = copierFichierVersDossierApp(photoPath, "photos_clients", "pho");
        if (photo.isEmpty()) {
            QMessageBox::warning(this, "Erreur", "Échec de la copie de la photo !");
            return;
        }
        if (photo.length() > 20) {
            QMessageBox::warning(this, "Erreur", "Le nom de la photo est trop long pour la base de données.");
            return;
        }
    }

    // Gestion de l'ordonnance
    if (!ordonnancePath.isEmpty()) {
        ordonnance = copierFichierVersDossierApp(ordonnancePath, "ordonnances_clients", "ord");
        if (ordonnance.isEmpty()) {
            QMessageBox::warning(this, "Erreur", "Échec de la copie de l'ordonnance !");
            return;
        }
        if (ordonnance.length() > 20) {
            QMessageBox::warning(this, "Erreur", "Le nom de l'ordonnance est trop long pour la base de données.");
            return;
        }
    }

    // Maintenant les variables 'photo' et 'ordonnance' contiennent les noms des fichiers copiés
    QString erreur;
    bool succes;

    if (ui->lineEditID_3->isEnabled()) {
        // MODE AJOUT
        succes = gestion_client::ajouterClient(
            id, nom, prenom, telephone, dateNaissance,
            statut, sexeTexte, ordonnance, photo, erreur  // ← Utiliser les variables originales
            );
    } else {
        // MODE MODIFICATION
        succes = modifierClientExistant(
            id, nom, prenom, telephone, dateNaissance,
            statut, sexeTexte, ordonnance, photo, erreur  // ← Utiliser les variables originales
            );
    }

    if (succes) {
        QMessageBox::information(this, "Succès", erreur);
        viderFormulaireClient();
        rafraichirTableauClients();
        rafraichirStatistiquesClients();
        ui->stackedWidget_4->setCurrentIndex(0);
    } else {
        QMessageBox::critical(this, "Erreur", erreur);
    }
}


void MainWindow::on_btnAnnuler_3_clicked() {
    viderFormulaireClient();
    ui->stackedWidget_4->setCurrentIndex(0);
}

void MainWindow::on_btnConfirmerPersonnel_clicked()
{
    bool okId;
    int id = ui->lineEditID->text().toInt(&okId);
    QString nom = ui->lineEditNom->text().trimmed();
    QString prenom = ui->lineEditPrenom->text().trimmed();
    QString mail = ui->lineEditNom_2->text().trimmed();
    QString adresse = "";
    QString poste = ui->lineEditDateNaissance->text().trimmed();
    QDate dateEmbauche = QDate::currentDate();
    QString statut = "Actif";
    int idLocal = 0;

    if (!okId || id <= 0) {
        QMessageBox::warning(this, "Erreur", "ID doit être numérique !");
        return;
    }

    QString erreur;
    bool succes = Gestion_Personnel::ajouterPersonnel(
        id, nom, prenom, mail, adresse, poste, dateEmbauche, statut, idLocal, erreur
        );

    if (succes) {
        QMessageBox::information(this, "Succès", erreur);
        viderFormulairePersonnel();
        rafraichirTableauPersonnel();
        ui->stackedWidget_3->setCurrentIndex(0);
    } else {
        QMessageBox::critical(this, "Erreur", erreur);
    }
}

void MainWindow::on_btnAnnulerPersonnel_clicked() {
    viderFormulairePersonnel();
    ui->stackedWidget_3->setCurrentIndex(0);
}

void MainWindow::on_btnConfirmerLocal_clicked()
{
    bool okId, okTel;
    int id = ui->lineEditID_2->text().toInt(&okId);
    QString nom = ui->lineEditNom_3->text().trimmed();
    int telephone = ui->lineEditPhone_2->text().toInt(&okTel);
    QString adresse = ui->lineEditPrenom_2->text().trimmed();
    QString superficie = ui->lineEditDateNaissance_2->text().trimmed();
    QString chiffreAffaires = ui->lineEditDateNaissance_3->text().trimmed();

    QString etat;
    if (ui->checkOld->isChecked()) etat = "Disponible";
    else if (ui->checkNew->isChecked()) etat = "Ouvert";
    else if (ui->checkVIP->isChecked()) etat = "Fermé";
    else { QMessageBox::warning(this, "Erreur", "Choisissez un état !"); return; }

    if (!okId || !okTel || id <= 0) {
        QMessageBox::warning(this, "Erreur", "ID et téléphone doivent être numériques !");
        return;
    }

    QString erreur;
    bool succes = Gestion_Locaux::ajouterLocal(
        id, nom, telephone, adresse, superficie, chiffreAffaires, etat, erreur
        );

    if (succes) {
        QMessageBox::information(this, "Succès", erreur);
        viderFormulaireLocal();
        rafraichirTableauLocaux();
        ui->stackedWidget_2->setCurrentIndex(0);
    } else {
        QMessageBox::critical(this, "Erreur", erreur);
    }
}

void MainWindow::on_btnAnnulerLocal_clicked() {
    viderFormulaireLocal();
    ui->stackedWidget_2->setCurrentIndex(0);
}

void MainWindow::on_btnConfirmerFournisseur_clicked()
{
    bool okId, okTel;
    int id = ui->lineEditID_4->text().toInt(&okId);
    QString nomEntreprise = ui->lineEditNom_5->text().trimmed();
    QString personneContact = ui->lineEditPhone_4->text().trimmed();
    QString adresse = ui->lineEditDateNaissance_5->text().trimmed();
    int telephone = ui->lineEditPhone_5->text().toInt(&okTel);
    QString mail = "";
    QString categorie = ui->comboCategorie->currentText();
    QString details = "";
    float noteFiabilite = 0.0;

    if (!okId || !okTel || id <= 0) {
        QMessageBox::warning(this, "Erreur", "ID et téléphone doivent être numériques !");
        return;
    }

    QString erreur;
    bool succes = Gestion_Fournisseur::ajouterFournisseur(
        id, nomEntreprise, personneContact, adresse, telephone, mail,
        categorie, details, noteFiabilite, erreur
        );

    if (succes) {
        QMessageBox::information(this, "Succès", erreur);
        viderFormulaireFournisseur();
        rafraichirTableauFournisseur();
        ui->stackedWidget_5->setCurrentIndex(0);
    } else {
        QMessageBox::critical(this, "Erreur", erreur);
    }
}

void MainWindow::on_btnAnnulerFournisseur_clicked() {
    viderFormulaireFournisseur();
    ui->stackedWidget_5->setCurrentIndex(0);
}

void MainWindow::on_btnConfirmerProduit_clicked()
{
    bool okId, okPrix, okRemise, okQuantite;
    int id = ui->lineEditID_5->text().toInt(&okId);
    QString marque = ui->lineEditNom_6->text().trimmed();
    QString modele = ui->lineEditPrenom_4->text().trimmed();
    QString type = ui->comboProfession_6->currentText();
    QString couleur = ui->lineEditDateNaissance_6->text().trimmed();
    float prix = ui->lineEditDateNaissance_7->text().toFloat(&okPrix);
    float remise = ui->spinBox_2->text().toFloat(&okRemise);
    int quantite = ui->spinBox->text().toInt(&okQuantite);
    QString matiere = ui->comboProfession_7->currentText();
    QString genre = ui->comboProfession_8->currentText();
    QDate dateAjout = ui->dateEdit->date();
    int idClient = 0;
    int idFournisseur = 0;
    int idLocal = 0;

    if (!okId || !okPrix || !okQuantite || id <= 0) {
        QMessageBox::warning(this, "Erreur", "ID, prix et quantité doivent être numériques !");
        return;
    }

    QString erreur;
    bool succes = Gestion_Produit::ajouterProduit(
        id, marque, modele, type, couleur, prix, remise, quantite,
        matiere, genre, dateAjout, idClient, idFournisseur, idLocal, erreur
        );

    if (succes) {
        QMessageBox::information(this, "Succès", erreur);
        viderFormulaireProduit();
        rafraichirTableauProduit();
        ui->stackedWidget_6->setCurrentIndex(0);
    } else {
        QMessageBox::critical(this, "Erreur", erreur);
    }
}

void MainWindow::on_btnAnnulerProduit_clicked() {
    viderFormulaireProduit();
    ui->stackedWidget_6->setCurrentIndex(0);
}

/*void MainWindow::viderFormulaireClient() {
    ui->lineEditID_3->clear();
    ui->lineEditNom_4->clear();
    ui->lineEditPrenom_3->clear();
    ui->lineEditPhone_3->clear();
    ui->lineEditDateNaissance_4->clear();
    ui->comboSexe_2->setCurrentIndex(0);
    ui->checkNew_2->setChecked(false);
    ui->checkOld_2->setChecked(false);
    ui->checkVIP_2->setChecked(false);
    ui->lineEditID_3->setStyleSheet("");
    ui->lineEditNom_4->setStyleSheet("");
    ui->lineEditPrenom_3->setStyleSheet("");
    ui->lineEditPhone_3->setStyleSheet("");
}*/
void MainWindow::viderFormulaireClient()
{
    ui->lineEditID_3->clear();
    ui->lineEditNom_4->clear();
    ui->lineEditPrenom_3->clear();
    ui->lineEditPhone_3->clear();
    ui->lineEditDateNaissance_4->clear();
    ui->comboSexe_2->setCurrentIndex(0);
    ui->checkNew_2->setChecked(false);
    ui->checkOld_2->setChecked(false);
    ui->checkVIP_2->setChecked(false);
    if (lineEditIDProduit) {
        lineEditIDProduit->clear();
    }
    ui->listachatrecents->clear();
    photoPath = "";
    ordonnancePath = "";

    // Remettre l'image par défaut
    ui->lblphoto->setPixmap(QPixmap(":/new/prefix1/uplode-removebg-preview.png"));
    ui->lineEditPhoto->clear();
    ui->lineEditOrdonnance->clear();


    // Réactiver l'ID pour le prochain ajout
    ui->lineEditID_3->setEnabled(true);

    // Remettre le texte original du bouton
    ui->btnConfirmer_3->setText("confirmer");

    ui->lineEditID_3->setStyleSheet("");
    ui->lineEditNom_4->setStyleSheet("");
    ui->lineEditPrenom_3->setStyleSheet("");
    ui->lineEditPhone_3->setStyleSheet("");
}

void MainWindow::viderFormulairePersonnel() {
    ui->lineEditID->clear();
    ui->lineEditNom->clear();
    ui->lineEditPrenom->clear();
    ui->lineEditNom_2->clear();
    ui->lineEditDateNaissance->clear();
}

void MainWindow::viderFormulaireLocal() {
    ui->lineEditID_2->clear();
    ui->lineEditNom_3->clear();
    ui->lineEditPhone_2->clear();
    ui->lineEditPrenom_2->clear();
    ui->lineEditDateNaissance_2->clear();
    ui->lineEditDateNaissance_3->clear();
    ui->checkOld->setChecked(false);
    ui->checkNew->setChecked(false);
    ui->checkVIP->setChecked(false);
}

void MainWindow::viderFormulaireFournisseur() {
    ui->lineEditID_4->clear();
    ui->lineEditNom_5->clear();
    ui->lineEditPhone_4->clear();
    ui->lineEditDateNaissance_5->clear();
    ui->lineEditPhone_5->clear();
    ui->comboCategorie->setCurrentIndex(0);
}

void MainWindow::viderFormulaireProduit() {
    ui->lineEditID_5->clear();
    ui->lineEditNom_6->clear();
    ui->lineEditPrenom_4->clear();
    ui->comboProfession_6->setCurrentIndex(0);
    ui->lineEditDateNaissance_6->clear();
    ui->lineEditDateNaissance_7->clear();
    ui->spinBox_2->clear();
    ui->spinBox->clear();
    ui->comboProfession_7->setCurrentIndex(0);
    ui->comboProfession_8->setCurrentIndex(0);
    ui->dateEdit->setDate(QDate::currentDate());
}

void MainWindow::rafraichirTableauClients()
{
    // Bloquer les signaux pendant le rafraîchissement
    ui->tableClients->blockSignals(true);

    // Simple sauvegarde de la ligne sélectionnée
    int currentRow = ui->tableClients->currentRow();

    ui->tableClients->setRowCount(0);
    auto clients = gestion_client::chargerTousLesClients();

    ui->tableClients->setColumnCount(8);
    QStringList headers = {"ID", "Nom", "Prénom", "Âge", "Statut", "Téléphone", "Sexe", "Actions"};
    ui->tableClients->setHorizontalHeaderLabels(headers);

    ui->tableClients->setColumnWidth(0, 120);
    ui->tableClients->setColumnWidth(1, 120);
    ui->tableClients->setColumnWidth(2, 120);
    ui->tableClients->setColumnWidth(3, 60);
    ui->tableClients->setColumnWidth(4, 100);
    ui->tableClients->setColumnWidth(5, 120);
    ui->tableClients->setColumnWidth(6, 80);
    ui->tableClients->setColumnWidth(7, 120);

    int row = 0;
    for (const auto &c : clients) {
        ui->tableClients->insertRow(row);

        // ID (non éditable)
        QTableWidgetItem *itemId = new QTableWidgetItem(QString::number(c.getId()));
        itemId->setFlags(itemId->flags() & ~Qt::ItemIsEditable);
        ui->tableClients->setItem(row, 0, itemId);

        // Nom
        ui->tableClients->setItem(row, 1, new QTableWidgetItem(c.getNom()));

        // Prénom
        ui->tableClients->setItem(row, 2, new QTableWidgetItem(c.getPrenom()));

        // Âge (non éditable)
        QTableWidgetItem *itemAge = new QTableWidgetItem(QString::number(c.getAge()));
        itemAge->setFlags(itemAge->flags() & ~Qt::ItemIsEditable);
        ui->tableClients->setItem(row, 3, itemAge);

        // Statut
        ui->tableClients->setItem(row, 4, new QTableWidgetItem(c.getStatut()));

        // Téléphone
        ui->tableClients->setItem(row, 5, new QTableWidgetItem(QString::number(c.getTelephone())));

        // Sexe
        QString sexeTexte = (c.getSexe() == "H") ? "Homme" : "Femme";
        ui->tableClients->setItem(row, 6, new QTableWidgetItem(sexeTexte));

        // Actions
        QWidget *actionsWidget = new QWidget();
        QHBoxLayout *layout = new QHBoxLayout(actionsWidget);
        layout->setContentsMargins(3, 1, 3, 1);
        layout->setSpacing(4);

        QPushButton *btnSupp = new QPushButton("SUP");
        QPushButton *btnSMS  = new QPushButton("SMS");
        btnSupp->setFixedSize(45, 26);
        btnSMS->setFixedSize(45, 26);
        btnSupp->setStyleSheet("background:#e74c3c; color:white; border-radius:4px; font-weight:bold;");
        btnSMS->setStyleSheet("background:#6c5ce7; color:white; border-radius:4px; font-weight:bold;");

        layout->addWidget(btnSupp);
        layout->addWidget(btnSMS);

        int clientId = c.getId();
        int tel = c.getTelephone();

        connect(btnSupp, &QPushButton::clicked, this, [this, clientId]() {
            if (QMessageBox::question(this, "Supprimer",
                                      "Supprimer le client ID <b>" + QString::number(clientId) + "</b> ?",
                                      QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {

                QString err;
                if (gestion_client::supprimerClient(clientId, err)) {
                    QMessageBox::information(this, "Succès", err);
                    rafraichirTableauClients();
                     rafraichirStatistiquesClients();
                } else {
                    QMessageBox::critical(this, "Erreur", err);
                }
            }
        });

        connect(btnSMS, &QPushButton::clicked, this, [this, tel, clientName = c.getPrenom() + " " + c.getNom()]() {
            SMS_client *smsWindow = new SMS_client(this, QString::number(tel), clientName);
            smsWindow->exec();
            smsWindow->deleteLater();
        });
        ui->tableClients->setCellWidget(row, 7, actionsWidget);
        row++;
    }

    // Restaurer la sélection si possible (optionnel)
    if (currentRow >= 0 && currentRow < ui->tableClients->rowCount()) {
        ui->tableClients->setCurrentCell(currentRow, 0);
    }

    ui->tableClients->blockSignals(false);
    ui->tableClients->verticalHeader()->setDefaultSectionSize(40);
}
void MainWindow::rafraichirTableauPersonnel()
{
    ui->tablePersonnel->blockSignals(true);
    ui->tablePersonnel->setRowCount(0);
    auto personnels = Gestion_Personnel::chargerTousLesPersonnels();

    ui->tablePersonnel->setColumnCount(9);
    QStringList headers = {"ID", "Nom", "Prénom", "Mail", "Adresse", "Poste", "Date Embauche", "Statut", "Actions"};
    ui->tablePersonnel->setHorizontalHeaderLabels(headers);

    int row = 0;
    for (const auto &p : personnels) {
        ui->tablePersonnel->insertRow(row);

        QTableWidgetItem *itemId = new QTableWidgetItem(QString::number(p.getId()));
        itemId->setFlags(itemId->flags() & ~Qt::ItemIsEditable);
        ui->tablePersonnel->setItem(row, 0, itemId);

        ui->tablePersonnel->setItem(row, 1, new QTableWidgetItem(p.getNom()));
        ui->tablePersonnel->setItem(row, 2, new QTableWidgetItem(p.getPrenom()));
        ui->tablePersonnel->setItem(row, 3, new QTableWidgetItem(p.getMail()));
        ui->tablePersonnel->setItem(row, 4, new QTableWidgetItem(p.getAdresse()));
        ui->tablePersonnel->setItem(row, 5, new QTableWidgetItem(p.getPoste()));
        ui->tablePersonnel->setItem(row, 6, new QTableWidgetItem(p.getDateEmbauche().toString("dd/MM/yyyy")));
        ui->tablePersonnel->setItem(row, 7, new QTableWidgetItem(p.getStatut()));

        QWidget *actionsWidget = new QWidget();
        QHBoxLayout *layout = new QHBoxLayout(actionsWidget);
        layout->setContentsMargins(3, 1, 3, 1);

        QPushButton *btnSupp = new QPushButton("SUP");
        btnSupp->setFixedSize(45, 26);
        btnSupp->setStyleSheet("background:#e74c3c; color:white; border-radius:4px; font-weight:bold;");

        layout->addWidget(btnSupp);

        int personnelId = p.getId();
        connect(btnSupp, &QPushButton::clicked, this, [this, personnelId]() {
            if (QMessageBox::question(this, "Supprimer", "Supprimer le personnel ID <b>" + QString::number(personnelId) + "</b> ?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
                QString err;
                if (Gestion_Personnel::supprimerPersonnel(personnelId, err)) {
                    QMessageBox::information(this, "OK", err);
                    rafraichirTableauPersonnel();
                } else {
                    QMessageBox::critical(this, "Erreur", err);
                }
            }
        });

        ui->tablePersonnel->setCellWidget(row, 8, actionsWidget);
        row++;
    }

    ui->tablePersonnel->blockSignals(false);
}

void MainWindow::rafraichirTableauLocaux()
{
    ui->tablePersonnel_2->blockSignals(true);
    ui->tablePersonnel_2->setRowCount(0);
    auto locaux = Gestion_Locaux::chargerTousLesLocaux();

    ui->tablePersonnel_2->setColumnCount(8);
    QStringList headers = {"ID", "Nom", "Téléphone", "Adresse", "Superficie", "Chiffre d'affaires", "État", "Actions"};
    ui->tablePersonnel_2->setHorizontalHeaderLabels(headers);

    int row = 0;
    for (const auto &l : locaux) {
        ui->tablePersonnel_2->insertRow(row);

        QTableWidgetItem *itemId = new QTableWidgetItem(QString::number(l.getId()));
        itemId->setFlags(itemId->flags() & ~Qt::ItemIsEditable);
        ui->tablePersonnel_2->setItem(row, 0, itemId);

        ui->tablePersonnel_2->setItem(row, 1, new QTableWidgetItem(l.getNom()));
        ui->tablePersonnel_2->setItem(row, 2, new QTableWidgetItem(QString::number(l.getTelephone())));
        ui->tablePersonnel_2->setItem(row, 3, new QTableWidgetItem(l.getAdresse()));
        ui->tablePersonnel_2->setItem(row, 4, new QTableWidgetItem(l.getSuperficie()));
        ui->tablePersonnel_2->setItem(row, 5, new QTableWidgetItem(l.getChiffreAffaires()));
        ui->tablePersonnel_2->setItem(row, 6, new QTableWidgetItem(l.getEtat()));

        QWidget *actionsWidget = new QWidget();
        QHBoxLayout *layout = new QHBoxLayout(actionsWidget);
        layout->setContentsMargins(3, 1, 3, 1);

        QPushButton *btnSupp = new QPushButton("SUP");
        btnSupp->setFixedSize(45, 26);
        btnSupp->setStyleSheet("background:#e74c3c; color:white; border-radius:4px; font-weight:bold;");

        layout->addWidget(btnSupp);

        int localId = l.getId();
        connect(btnSupp, &QPushButton::clicked, this, [this, localId]() {
            if (QMessageBox::question(this, "Supprimer", "Supprimer le local ID <b>" + QString::number(localId) + "</b> ?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
                QString err;
                if (Gestion_Locaux::supprimerLocal(localId, err)) {
                    QMessageBox::information(this, "OK", err);
                    rafraichirTableauLocaux();
                } else {
                    QMessageBox::critical(this, "Erreur", err);
                }
            }
        });

        ui->tablePersonnel_2->setCellWidget(row, 7, actionsWidget);
        row++;
    }

    ui->tablePersonnel_2->blockSignals(false);
}

void MainWindow::rafraichirTableauFournisseur()
{
    ui->tableClients_2->blockSignals(true);
    ui->tableClients_2->setRowCount(0);
    auto fournisseurs = Gestion_Fournisseur::chargerTousLesFournisseurs();

    ui->tableClients_2->setColumnCount(9);
    QStringList headers = {"ID", "Nom Entreprise", "Personne Contact", "Adresse", "Téléphone", "Mail", "Catégorie", "Note", "Actions"};
    ui->tableClients_2->setHorizontalHeaderLabels(headers);

    int row = 0;
    for (const auto &f : fournisseurs) {
        ui->tableClients_2->insertRow(row);

        QTableWidgetItem *itemId = new QTableWidgetItem(QString::number(f.getId()));
        itemId->setFlags(itemId->flags() & ~Qt::ItemIsEditable);
        ui->tableClients_2->setItem(row, 0, itemId);

        ui->tableClients_2->setItem(row, 1, new QTableWidgetItem(f.getNomEntreprise()));
        ui->tableClients_2->setItem(row, 2, new QTableWidgetItem(f.getPersonneContact()));
        ui->tableClients_2->setItem(row, 3, new QTableWidgetItem(f.getAdresse()));
        ui->tableClients_2->setItem(row, 4, new QTableWidgetItem(QString::number(f.getTelephone())));
        ui->tableClients_2->setItem(row, 5, new QTableWidgetItem(f.getMail()));
        ui->tableClients_2->setItem(row, 6, new QTableWidgetItem(f.getCategorie()));
        ui->tableClients_2->setItem(row, 7, new QTableWidgetItem(QString::number(f.getNoteFiabilite())));

        QWidget *actionsWidget = new QWidget();
        QHBoxLayout *layout = new QHBoxLayout(actionsWidget);
        layout->setContentsMargins(3, 1, 3, 1);

        QPushButton *btnSupp = new QPushButton("SUP");
        btnSupp->setFixedSize(45, 26);
        btnSupp->setStyleSheet("background:#e74c3c; color:white; border-radius:4px; font-weight:bold;");

        layout->addWidget(btnSupp);

        int fournisseurId = f.getId();
        connect(btnSupp, &QPushButton::clicked, this, [this, fournisseurId]() {
            if (QMessageBox::question(this, "Supprimer", "Supprimer le fournisseur ID <b>" + QString::number(fournisseurId) + "</b> ?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
                QString err;
                if (Gestion_Fournisseur::supprimerFournisseur(fournisseurId, err)) {
                    QMessageBox::information(this, "OK", err);
                    rafraichirTableauFournisseur();
                } else {
                    QMessageBox::critical(this, "Erreur", err);
                }
            }
        });

        ui->tableClients_2->setCellWidget(row, 8, actionsWidget);
        row++;
    }

    ui->tableClients_2->blockSignals(false);
}

void MainWindow::rafraichirTableauProduit()
{
    ui->tablePersonnel_3->blockSignals(true);
    ui->tablePersonnel_3->setRowCount(0);
    auto produits = Gestion_Produit::chargerTousLesProduits();

    ui->tablePersonnel_3->setColumnCount(11);
    QStringList headers = {"ID", "Marque", "Modèle", "Type", "Couleur", "Prix", "Remise", "Quantité", "Matière", "Genre", "Actions"};
    ui->tablePersonnel_3->setHorizontalHeaderLabels(headers);

    int row = 0;
    for (const auto &p : produits) {
        ui->tablePersonnel_3->insertRow(row);

        QTableWidgetItem *itemId = new QTableWidgetItem(QString::number(p.getId()));
        itemId->setFlags(itemId->flags() & ~Qt::ItemIsEditable);
        ui->tablePersonnel_3->setItem(row, 0, itemId);

        ui->tablePersonnel_3->setItem(row, 1, new QTableWidgetItem(p.getMarque()));
        ui->tablePersonnel_3->setItem(row, 2, new QTableWidgetItem(p.getModele()));
        ui->tablePersonnel_3->setItem(row, 3, new QTableWidgetItem(p.getType()));
        ui->tablePersonnel_3->setItem(row, 4, new QTableWidgetItem(p.getCouleur()));
        ui->tablePersonnel_3->setItem(row, 5, new QTableWidgetItem(QString::number(p.getPrix())));
        ui->tablePersonnel_3->setItem(row, 6, new QTableWidgetItem(QString::number(p.getRemise())));
        ui->tablePersonnel_3->setItem(row, 7, new QTableWidgetItem(QString::number(p.getQuantite())));
        ui->tablePersonnel_3->setItem(row, 8, new QTableWidgetItem(p.getMatiere()));
        ui->tablePersonnel_3->setItem(row, 9, new QTableWidgetItem(p.getGenre()));

        QWidget *actionsWidget = new QWidget();
        QHBoxLayout *layout = new QHBoxLayout(actionsWidget);
        layout->setContentsMargins(3, 1, 3, 1);

        QPushButton *btnSupp = new QPushButton("SUP");
        btnSupp->setFixedSize(45, 26);
        btnSupp->setStyleSheet("background:#e74c3c; color:white; border-radius:4px; font-weight:bold;");

        layout->addWidget(btnSupp);

        int produitId = p.getId();
        connect(btnSupp, &QPushButton::clicked, this, [this, produitId]() {
            if (QMessageBox::question(this, "Supprimer", "Supprimer le produit ID <b>" + QString::number(produitId) + "</b> ?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
                QString err;
                if (Gestion_Produit::supprimerProduit(produitId, err)) {
                    QMessageBox::information(this, "OK", err);
                    rafraichirTableauProduit();
                } else {
                    QMessageBox::critical(this, "Erreur", err);
                }
            }
        });

        ui->tablePersonnel_3->setCellWidget(row, 10, actionsWidget);
        row++;
    }

    ui->tablePersonnel_3->blockSignals(false);
}

void MainWindow::onTableItemChanged(QTableWidgetItem *item)
{
    if (!item || item->column() == 0 || item->column() == 3 || item->column() == 7)
        return;

    // Bloquer temporairement les signaux pour éviter les boucles
    ui->tableClients->blockSignals(true);

    int row = item->row();
    int col = item->column();

    // Vérifications de sécurité
    if (row >= ui->tableClients->rowCount()) {
        ui->tableClients->blockSignals(false);
        return;
    }

    QTableWidgetItem *idItem = ui->tableClients->item(row, 0);
    if (!idItem) {
        ui->tableClients->blockSignals(false);
        return;
    }

    int id = idItem->text().toInt();
    QString value = item->text().trimmed();

    QString champ;
    QVariant sqlValue;
    bool validationOk = true;
    QString erreurMessage;

    // Validation selon la colonne
    switch (col) {
    case 1: // Nom
        if (!gestion_client::isValidNom(value)) {
            erreurMessage = "Nom invalide ! Doit contenir seulement des lettres, apostrophes ou tirets (2-20 caractères).";
            validationOk = false;
        } else {
            champ = "NOM";
            sqlValue = value.toUpper();
        }
        break;

    case 2: // Prénom
        if (!gestion_client::isValidPrenom(value)) {
            erreurMessage = "Prénom invalide ! Doit contenir seulement des lettres, apostrophes ou tirets (2-20 caractères).";
            validationOk = false;
        } else {
            champ = "PRENOM";
            sqlValue = value;
        }
        break;

    case 4: // Statut
        if (value == "Nouveau" || value == "Ancien" || value == "VIP") {
            champ = "STATUT";
            sqlValue = value;
        } else {
            erreurMessage = "Statut invalide ! Choisir: Nouveau, Ancien ou VIP";
            validationOk = false;
        }
        break;

    case 5: // Téléphone
    {
        bool ok;
        int tel = value.toInt(&ok);
        if (!ok || !gestion_client::isValidTelephone(tel)) {
            erreurMessage = "Téléphone invalide ! Doit être numérique (8-10 chiffres).";
            validationOk = false;
        } else {
            champ = "NUM_TEL";
            sqlValue = tel;
        }
        break;
    }

    case 6: // Sexe
        if (value == "Homme") {
            sqlValue = "H";
            champ = "SEXE";
        } else if (value == "Femme") {
            sqlValue = "F";
            champ = "SEXE";
        } else {
            erreurMessage = "Sexe invalide ! Choisir: Homme ou Femme";
            validationOk = false;
        }
        break;

    default:
        ui->tableClients->blockSignals(false);
        return;
    }

    if (!validationOk) {
        QMessageBox::warning(this, "Erreur de validation", erreurMessage);
        // Rafraîchir pour restaurer l'ancienne valeur
        rafraichirTableauClients();
        ui->tableClients->blockSignals(false);
        return;
    }

    // Mise à jour en base de données
    Connection c;
    if (!c.createconnect()) {
        QMessageBox::critical(this, "Erreur", "Connexion à la base de données échouée !");
        rafraichirTableauClients();
        ui->tableClients->blockSignals(false);
        return;
    }

    QSqlQuery q;
    q.prepare(QString("UPDATE CLIENT SET %1 = :val WHERE ID_CLIENT = :id").arg(champ));
    q.bindValue(":val", sqlValue);
    q.bindValue(":id", id);

    if (q.exec()) {
        // Succès - message optionnel
        // QMessageBox::information(this, "Succès", "Modification enregistrée !");
    } else {
        QMessageBox::critical(this, "Erreur BD", "Échec de la modification : " + q.lastError().text());
        // En cas d'erreur BD, on rafraîchit pour récupérer les données correctes
        rafraichirTableauClients();
    }

    // Réactiver les signaux
    ui->tableClients->blockSignals(false);
}

void MainWindow::onTablePersonnelItemChanged(QTableWidgetItem *item)
{
    if (!item || item->column() == 0 || item->column() == 8) return;

    int row = item->row();
    int col = item->column();
    int id = ui->tablePersonnel->item(row, 0)->text().toInt();
    QString value = item->text().trimmed();

    QString champ;
    QVariant sqlValue;

    switch (col) {
    case 1:
        if (!Gestion_Personnel::isValidNom(value)) {
            QMessageBox::warning(this, "Erreur", "Nom invalide !");
            rafraichirTableauPersonnel();
            return;
        }
        champ = "NOM"; sqlValue = value.toUpper();
        break;
    case 2:
        if (!Gestion_Personnel::isValidNom(value)) {
            QMessageBox::warning(this, "Erreur", "Prénom invalide !");
            rafraichirTableauPersonnel();
            return;
        }
        champ = "PRENOM"; sqlValue = value;
        break;
    case 3:
        if (!Gestion_Personnel::isValidMail(value)) {
            QMessageBox::warning(this, "Erreur", "Mail invalide !");
            rafraichirTableauPersonnel();
            return;
        }
        champ = "MAIL"; sqlValue = value;
        break;
    case 4:
        champ = "ADRESSE"; sqlValue = value.left(20);
        break;
    case 5:
        if (!Gestion_Personnel::isValidPoste(value)) {
            QMessageBox::warning(this, "Erreur", "Poste invalide !");
            rafraichirTableauPersonnel();
            return;
        }
        champ = "POSTE"; sqlValue = value;
        break;
    case 6:
    {
        QDate date = QDate::fromString(value, "dd/MM/yyyy");
        if (!date.isValid()) {
            QMessageBox::warning(this, "Erreur", "Date invalide !");
            rafraichirTableauPersonnel();
            return;
        }
        champ = "DATE_DEMBAUCHE"; sqlValue = date;
    }
    break;
    case 7:
        if (!Gestion_Personnel::isValidStatut(value)) {
            QMessageBox::warning(this, "Erreur", "Statut invalide !");
            rafraichirTableauPersonnel();
            return;
        }
        champ = "STATUT"; sqlValue = value;
        break;
    default: return;
    }

    Connection c;
    if (!c.createconnect()) {
        QMessageBox::critical(this, "Erreur", "Connexion échouée !");
        return;
    }

    QSqlQuery q;
    q.prepare(QString("UPDATE PERSONNELS SET %1 = :val WHERE ID_PERSONNEL = :id").arg(champ));
    q.bindValue(":val", sqlValue);
    q.bindValue(":id", id);

    if (!q.exec()) {
        QMessageBox::critical(this, "Erreur", "Échec : " + q.lastError().text());
        rafraichirTableauPersonnel();
    }
}

void MainWindow::onTableLocauxItemChanged(QTableWidgetItem *item)
{
    if (!item || item->column() == 0 || item->column() == 7) return;

    int row = item->row();
    int col = item->column();
    int id = ui->tablePersonnel_2->item(row, 0)->text().toInt();
    QString value = item->text().trimmed();

    QString champ;
    QVariant sqlValue;

    switch (col) {
    case 1:
        if (!Gestion_Locaux::isValidNom(value)) {
            QMessageBox::warning(this, "Erreur", "Nom invalide !");
            rafraichirTableauLocaux();
            return;
        }
        champ = "NOM"; sqlValue = value;
        break;
    case 2:
        if (!value.toInt() || !Gestion_Locaux::isValidTelephone(value.toInt())) {
            QMessageBox::warning(this, "Erreur", "Téléphone invalide !");
            rafraichirTableauLocaux();
            return;
        }
        champ = "TELEPHONE"; sqlValue = value.toInt();
        break;
    case 3:
        champ = "ADRESSE"; sqlValue = value.left(20);
        break;
    case 4:
        champ = "SUPERFICIE"; sqlValue = value.left(20);
        break;
    case 5:
        champ = "CHIFFRE_DAFFAIRE"; sqlValue = value.left(20);
        break;
    case 6:
        if (!Gestion_Locaux::isValidEtat(value)) {
            QMessageBox::warning(this, "Erreur", "État invalide !");
            rafraichirTableauLocaux();
            return;
        }
        champ = "ETAT_DE_LOCAL"; sqlValue = value;
        break;
    default: return;
    }

    Connection c;
    if (!c.createconnect()) {
        QMessageBox::critical(this, "Erreur", "Connexion échouée !");
        return;
    }

    QSqlQuery q;
    q.prepare(QString("UPDATE LOCAUX SET %1 = :val WHERE ID_LOCAL = :id").arg(champ));
    q.bindValue(":val", sqlValue);
    q.bindValue(":id", id);

    if (!q.exec()) {
        QMessageBox::critical(this, "Erreur", "Échec : " + q.lastError().text());
        rafraichirTableauLocaux();
    }
}

void MainWindow::onTableFournisseurItemChanged(QTableWidgetItem *item)
{
    if (!item || item->column() == 0 || item->column() == 8) return;

    int row = item->row();
    int col = item->column();
    int id = ui->tableClients_2->item(row, 0)->text().toInt();
    QString value = item->text().trimmed();

    QString champ;
    QVariant sqlValue;

    switch (col) {
    case 1:
        if (!Gestion_Fournisseur::isValidNom(value)) {
            QMessageBox::warning(this, "Erreur", "Nom entreprise invalide !");
            rafraichirTableauFournisseur();
            return;
        }
        champ = "NOMENTURE"; sqlValue = value;
        break;
    case 2:
        champ = "PERSONNE_CNT"; sqlValue = value.left(20);
        break;
    case 3:
        champ = "ADRESSE"; sqlValue = value.left(20);
        break;
    case 4:
        if (!value.toInt() || !Gestion_Fournisseur::isValidTelephone(value.toInt())) {
            QMessageBox::warning(this, "Erreur", "Téléphone invalide !");
            rafraichirTableauFournisseur();
            return;
        }
        champ = "NUM_TEL"; sqlValue = value.toInt();
        break;
    case 5:
        if (!Gestion_Fournisseur::isValidMail(value)) {
            QMessageBox::warning(this, "Erreur", "Mail invalide !");
            rafraichirTableauFournisseur();
            return;
        }
        champ = "MAIL"; sqlValue = value;
        break;
    case 6:
        if (!Gestion_Fournisseur::isValidCategorie(value)) {
            QMessageBox::warning(this, "Erreur", "Catégorie invalide !");
            rafraichirTableauFournisseur();
            return;
        }
        champ = "CATÉGORIE"; sqlValue = value;
        break;
    case 7:
    {
        bool ok;
        float note = value.toFloat(&ok);
        if (!ok || note < 0 || note > 10) {
            QMessageBox::warning(this, "Erreur", "Note invalide (0-10) !");
            rafraichirTableauFournisseur();
            return;
        }
        champ = "NOTE_DE_FIABILITÉ"; sqlValue = note;
    }
    break;
    default: return;
    }

    Connection c;
    if (!c.createconnect()) {
        QMessageBox::critical(this, "Erreur", "Connexion échouée !");
        return;
    }

    QSqlQuery q;
    q.prepare(QString("UPDATE FOURNISSEUR SET %1 = :val WHERE ID_FOURNISSEUR = :id").arg(champ));
    q.bindValue(":val", sqlValue);
    q.bindValue(":id", id);

    if (!q.exec()) {
        QMessageBox::critical(this, "Erreur", "Échec : " + q.lastError().text());
        rafraichirTableauFournisseur();
    }
}

void MainWindow::onTableProduitItemChanged(QTableWidgetItem *item)
{
    if (!item || item->column() == 0 || item->column() == 10) return;

    int row = item->row();
    int col = item->column();
    int id = ui->tablePersonnel_3->item(row, 0)->text().toInt();
    QString value = item->text().trimmed();

    QString champ;
    QVariant sqlValue;

    switch (col) {
    case 1:
        if (!Gestion_Produit::isValidMarque(value)) {
            QMessageBox::warning(this, "Erreur", "Marque invalide !");
            rafraichirTableauProduit();
            return;
        }
        champ = "MARQUE"; sqlValue = value;
        break;
    case 2:
        if (!Gestion_Produit::isValidModele(value)) {
            QMessageBox::warning(this, "Erreur", "Modèle invalide !");
            rafraichirTableauProduit();
            return;
        }
        champ = "MODELE"; sqlValue = value;
        break;
    case 3:
        if (!Gestion_Produit::isValidType(value)) {
            QMessageBox::warning(this, "Erreur", "Type invalide !");
            rafraichirTableauProduit();
            return;
        }
        champ = "TYPE"; sqlValue = value;
        break;
    case 4:
        champ = "COULEUR"; sqlValue = value.left(20);
        break;
    case 5:
    {
        bool ok;
        float prix = value.toFloat(&ok);
        if (!ok || !Gestion_Produit::isValidPrix(prix)) {
            QMessageBox::warning(this, "Erreur", "Prix invalide !");
            rafraichirTableauProduit();
            return;
        }
        champ = "PRIX"; sqlValue = prix;
    }
    break;
    case 6:
    {
        bool ok;
        float remise = value.toFloat(&ok);
        if (!ok || remise < 0 || remise > 100) {
            QMessageBox::warning(this, "Erreur", "Remise invalide (0-100) !");
            rafraichirTableauProduit();
            return;
        }
        champ = "REMISE"; sqlValue = remise;
    }
    break;
    case 7:
    {
        bool ok;
        int quantite = value.toInt(&ok);
        if (!ok || !Gestion_Produit::isValidQuantite(quantite)) {
            QMessageBox::warning(this, "Erreur", "Quantité invalide !");
            rafraichirTableauProduit();
            return;
        }
        champ = "QUANTITÉ"; sqlValue = quantite;
    }
    break;
    case 8:
        champ = "MATIERE"; sqlValue = value.left(20);
        break;
    case 9:
        champ = "GENRE"; sqlValue = value.left(20);
        break;
    default: return;
    }

    Connection c;
    if (!c.createconnect()) {
        QMessageBox::critical(this, "Erreur", "Connexion échouée !");
        return;
    }

    QSqlQuery q;
    q.prepare(QString("UPDATE PRODUIT SET %1 = :val WHERE ID_PRODUIT = :id").arg(champ));
    q.bindValue(":val", sqlValue);
    q.bindValue(":id", id);

    if (!q.exec()) {
        QMessageBox::critical(this, "Erreur", "Échec : " + q.lastError().text());
        rafraichirTableauProduit();
    }
}
/*void MainWindow::on_searchLineEdit_3_textChanged(const QString &text)
{
    QString filter = text.trimmed();
    QString filtreActif = ui->comboProfession_3->currentText();

    for (int i = 0; i < ui->tableClients->rowCount(); ++i) {
        bool show = true;

        // 1. Appliquer le filtre actif s'il y en a un
        if (filtreActif != "Tous les filtres") {
            show = ligneCorrespondFiltre(i, filtreActif);
        }

        // 2. Appliquer la recherche textuelle si le filtre n'a pas déjà caché la ligne
        if (show && !filter.isEmpty()) {
            QString id = ui->tableClients->item(i, 0)->text();
            QString nom = ui->tableClients->item(i, 1)->text();
            QString prenom = ui->tableClients->item(i, 2)->text();

            show = id.contains(filter, Qt::CaseInsensitive) ||
                   nom.contains(filter, Qt::CaseInsensitive) ||
                   prenom.contains(filter, Qt::CaseInsensitive);
        }

        ui->tableClients->setRowHidden(i, !show);
    }
}
*/
void MainWindow::on_searchLineEdit_3_textChanged(const QString &text)
{
    QString filter = text.trimmed();

    // Bloquer les signaux pendant le rafraîchissement
    ui->tableClients->blockSignals(true);
    ui->tableClients->setRowCount(0);

    Connection c;
    if (!c.createconnect()) {
        QMessageBox::critical(this, "Erreur", "Connexion échouée !");
        ui->tableClients->blockSignals(false);
        return;
    }

    QSqlQuery query;
    QString sql;

    if (filter.isEmpty()) {
        // Si pas de recherche, charger tous les clients
        sql = "SELECT ID_CLIENT, NOM, PRENOM, NUM_TEL, DATE_DE_NAISSANCE, "
              "STATUT, SEXE FROM CLIENT ORDER BY ID_CLIENT";
        query.prepare(sql);
    } else {
        // Recherche avec LIKE sur ID, Nom et Prénom
        sql = "SELECT ID_CLIENT, NOM, PRENOM, NUM_TEL, DATE_DE_NAISSANCE, "
              "STATUT, SEXE FROM CLIENT "
              "WHERE CAST(ID_CLIENT AS VARCHAR(10)) LIKE :filter "
              "OR UPPER(NOM) LIKE UPPER(:filter) "
              "OR UPPER(PRENOM) LIKE UPPER(:filter) "
              "ORDER BY ID_CLIENT";
        query.prepare(sql);
        query.bindValue(":filter", "%" + filter + "%");
    }

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Échec de la recherche : " + query.lastError().text());
        ui->tableClients->blockSignals(false);
        return;
    }

    // Configuration du tableau
    ui->tableClients->setColumnCount(8);
    QStringList headers = {"ID", "Nom", "Prénom", "Âge", "Statut", "Téléphone", "Sexe", "Actions"};
    ui->tableClients->setHorizontalHeaderLabels(headers);

    ui->tableClients->setColumnWidth(0, 120);
    ui->tableClients->setColumnWidth(1, 120);
    ui->tableClients->setColumnWidth(2, 120);
    ui->tableClients->setColumnWidth(3, 60);
    ui->tableClients->setColumnWidth(4, 100);
    ui->tableClients->setColumnWidth(5, 120);
    ui->tableClients->setColumnWidth(6, 80);
    ui->tableClients->setColumnWidth(7, 120);

    int row = 0;
    while (query.next()) {
        ui->tableClients->insertRow(row);

        int id = query.value(0).toInt();
        QString nom = query.value(1).toString();
        QString prenom = query.value(2).toString();
        int telephone = query.value(3).toInt();
        QDate dateNaissance = query.value(4).toDate();
        QString statut = query.value(5).toString();
        QString sexe = query.value(6).toString();

        // Calculer l'âge
        int age = dateNaissance.daysTo(QDate::currentDate()) / 365;

        // ID (non éditable)
        QTableWidgetItem *itemId = new QTableWidgetItem(QString::number(id));
        itemId->setFlags(itemId->flags() & ~Qt::ItemIsEditable);
        ui->tableClients->setItem(row, 0, itemId);

        // Nom
        ui->tableClients->setItem(row, 1, new QTableWidgetItem(nom));

        // Prénom
        ui->tableClients->setItem(row, 2, new QTableWidgetItem(prenom));

        // Âge (non éditable)
        QTableWidgetItem *itemAge = new QTableWidgetItem(QString::number(age));
        itemAge->setFlags(itemAge->flags() & ~Qt::ItemIsEditable);
        ui->tableClients->setItem(row, 3, itemAge);

        // Statut
        ui->tableClients->setItem(row, 4, new QTableWidgetItem(statut));

        // Téléphone
        ui->tableClients->setItem(row, 5, new QTableWidgetItem(QString::number(telephone)));

        // Sexe
        QString sexeTexte = (sexe == "H") ? "Homme" : "Femme";
        ui->tableClients->setItem(row, 6, new QTableWidgetItem(sexeTexte));

        // Boutons Actions (SUP et SMS)
        QWidget *actionsWidget = new QWidget();
        QHBoxLayout *layout = new QHBoxLayout(actionsWidget);
        layout->setContentsMargins(3, 1, 3, 1);
        layout->setSpacing(4);

        QPushButton *btnSupp = new QPushButton("SUP");
        QPushButton *btnSMS = new QPushButton("SMS");
        btnSupp->setFixedSize(45, 26);
        btnSMS->setFixedSize(45, 26);
        btnSupp->setStyleSheet("background:#e74c3c; color:white; border-radius:4px; font-weight:bold;");
        btnSMS->setStyleSheet("background:#6c5ce7; color:white; border-radius:4px; font-weight:bold;");

        layout->addWidget(btnSupp);
        layout->addWidget(btnSMS);

        connect(btnSupp, &QPushButton::clicked, this, [this, id]() {
            if (QMessageBox::question(this, "Supprimer",
                                      "Supprimer le client ID <b>" + QString::number(id) + "</b> ?",
                                      QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
                QString err;
                if (gestion_client::supprimerClient(id, err)) {
                    QMessageBox::information(this, "Succès", err);
                    on_searchLineEdit_3_textChanged(ui->searchLineEdit_3->text());
                    rafraichirStatistiquesClients();
                } else {
                    QMessageBox::critical(this, "Erreur", err);
                }
            }
        });

        connect(btnSMS, &QPushButton::clicked, this, [this, telephone, clientName = prenom + " " + nom]() {
            SMS_client *smsWindow = new SMS_client(this, QString::number(telephone), clientName);
            smsWindow->exec();
            smsWindow->deleteLater();
        });

        ui->tableClients->setCellWidget(row, 7, actionsWidget);
        row++;
    }

    ui->tableClients->blockSignals(false);
    ui->tableClients->verticalHeader()->setDefaultSectionSize(40);
}
/*void MainWindow::on_btnExporter_3_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Exporter PDF", "clients.pdf", "PDF (*.pdf)");
    if (fileName.isEmpty()) return;

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    printer.setPageSize(QPageSize::A4);
    printer.setPageMargins(QMarginsF(15, 15, 15, 15), QPageLayout::Millimeter);

    QTextDocument doc;

    QTextCursor cursor(&doc);
    cursor.insertHtml("<h1 style='text-align:center;'>Liste des Clients</h1><br>");

    // Compter les lignes visibles
    int visibleRows = 0;
    for (int i = 0; i < ui->tableClients->rowCount(); ++i) {
        if (!ui->tableClients->isRowHidden(i)) visibleRows++;
    }

    QTextTableFormat tableFormat;
    tableFormat.setBorder(1);
    tableFormat.setCellPadding(5);
    tableFormat.setAlignment(Qt::AlignCenter);
    tableFormat.setWidth(QTextLength(QTextLength::PercentageLength, 100));
    // Construction du tableau HTML
    QTextTable *table = cursor.insertTable(visibleRows + 1, 7, tableFormat);

    // En-têtes
    QStringList headers = {"ID", "Nom", "Prénom", "Âge", "Statut", "Téléphone", "Sexe"};
    QTextCharFormat headerFmt;
    headerFmt.setFontWeight(QFont::Bold);
    headerFmt.setBackground(Qt::lightGray);

    for (int col = 0; col < 7; ++col) {
        table->cellAt(0, col).firstCursorPosition().insertText(headers[col], headerFmt);
    }

    // Données
    int pdfRow = 1;
    for (int row = 0; row < ui->tableClients->rowCount(); ++row) {
        if (ui->tableClients->isRowHidden(row)) continue;

        for (int col = 0; col < 7; ++col) {
            QString text = ui->tableClients->item(row, col) ?
                               ui->tableClients->item(row, col)->text() : "";
            table->cellAt(pdfRow, col).firstCursorPosition().insertText(text);
        }
        pdfRow++;
    }

    doc.print(&printer);
    QMessageBox::information(this, "Succès", "PDF exporté avec succès !");
}*/
void MainWindow::on_btnExporter_3_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Exporter PDF", "clients.pdf", "PDF (*.pdf)");
    if (fileName.isEmpty()) return;

    Connection c;
    if (!c.createconnect()) {
        QMessageBox::critical(this, "Erreur", "Connexion échouée !");
        return;
    }

    // Construire la requête SQL selon les filtres actuels
    QString filtreSelectionne = ui->comboProfession_3->currentText();
    QString recherche = ui->searchLineEdit_3->text().trimmed();

    QString sql = "SELECT ID_CLIENT, NOM, PRENOM, NUM_TEL, DATE_DE_NAISSANCE, "
                  "STATUT, SEXE FROM CLIENT WHERE 1=1 ";

    // Ajouter les conditions de filtrage (même logique que appliquerFiltreAvecSQL)
    if (filtreSelectionne == "Âge: Moins de 30 ans") {
        sql += "AND (SYSDATE - DATE_DE_NAISSANCE) / 365 < 30 ";
    }
    else if (filtreSelectionne == "Âge: 30 ans et plus") {
        sql += "AND (SYSDATE - DATE_DE_NAISSANCE) / 365 >= 30 ";
    }
    else if (filtreSelectionne == "Statut: Nouveau") {
        sql += "AND STATUT = 'Nouveau' ";
    }
    else if (filtreSelectionne == "Statut: Ancien") {
        sql += "AND STATUT = 'Ancien' ";
    }
    else if (filtreSelectionne == "Statut: VIP") {
        sql += "AND STATUT = 'VIP' ";
    }
    else if (filtreSelectionne == "Sexe: Homme") {
        sql += "AND SEXE = 'H' ";
    }
    else if (filtreSelectionne == "Sexe: Femme") {
        sql += "AND SEXE = 'F' ";
    }

    // Ajouter la recherche textuelle si présente
    if (!recherche.isEmpty()) {
        sql += "AND (CAST(ID_CLIENT AS VARCHAR(10)) LIKE :recherche "
               "OR UPPER(NOM) LIKE UPPER(:recherche) "
               "OR UPPER(PRENOM) LIKE UPPER(:recherche)) ";
    }

    sql += "ORDER BY ID_CLIENT";

    QSqlQuery query;
    query.prepare(sql);

    if (!recherche.isEmpty()) {
        query.bindValue(":recherche", "%" + recherche + "%");
    }

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Échec de l'exportation : " + query.lastError().text());
        return;
    }

    // Compter les résultats
    int totalClients = 0;
    QVector<QStringList> donnees;

    while (query.next()) {
        totalClients++;

        int id = query.value(0).toInt();
        QString nom = query.value(1).toString();
        QString prenom = query.value(2).toString();
        int telephone = query.value(3).toInt();
        QDate dateNaissance = query.value(4).toDate();
        QString statut = query.value(5).toString();
        QString sexe = query.value(6).toString();

        // Calculer l'âge
        int age = dateNaissance.daysTo(QDate::currentDate()) / 365;
        QString sexeTexte = (sexe == "H") ? "Homme" : "Femme";

        QStringList ligne;
        ligne << QString::number(id)
              << nom
              << prenom
              << QString::number(age)
              << statut
              << QString::number(telephone)
              << sexeTexte;

        donnees.append(ligne);
    }

    if (totalClients == 0) {
        QMessageBox::warning(this, "Aucune donnée", "Aucun client à exporter !");
        return;
    }

    // Créer le PDF
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    printer.setPageSize(QPageSize::A4);
    printer.setPageMargins(QMarginsF(15, 15, 15, 15), QPageLayout::Millimeter);

    QTextDocument doc;
    QTextCursor cursor(&doc);

    // Titre
    cursor.insertHtml("<h1 style='text-align:center;'>Liste des Clients</h1>");

    // Informations sur le filtre
    if (filtreSelectionne != "Tous les filtres" || !recherche.isEmpty()) {
        QString infoFiltre = "<p style='text-align:center; color:#666;'>";
        if (filtreSelectionne != "Tous les filtres") {
            infoFiltre += "Filtre: <b>" + filtreSelectionne + "</b>";
        }
        if (!recherche.isEmpty()) {
            if (filtreSelectionne != "Tous les filtres") infoFiltre += " | ";
            infoFiltre += "Recherche: <b>" + recherche + "</b>";
        }
        infoFiltre += "</p>";
        cursor.insertHtml(infoFiltre);
    }

    cursor.insertHtml("<p style='text-align:center;'>Total: <b>" + QString::number(totalClients) + "</b> client(s)</p><br>");

    // Créer le tableau
    QTextTableFormat tableFormat;
    tableFormat.setBorder(1);
    tableFormat.setCellPadding(5);
    tableFormat.setAlignment(Qt::AlignCenter);
    tableFormat.setWidth(QTextLength(QTextLength::PercentageLength, 100));

    QTextTable *table = cursor.insertTable(totalClients + 1, 7, tableFormat);

    // En-têtes
    QStringList headers = {"ID", "Nom", "Prénom", "Âge", "Statut", "Téléphone", "Sexe"};
    QTextCharFormat headerFmt;
    headerFmt.setFontWeight(QFont::Bold);
    headerFmt.setBackground(Qt::lightGray);

    for (int col = 0; col < 7; ++col) {
        table->cellAt(0, col).firstCursorPosition().insertText(headers[col], headerFmt);
    }

    // Données
    for (int row = 0; row < donnees.size(); ++row) {
        for (int col = 0; col < 7; ++col) {
            table->cellAt(row + 1, col).firstCursorPosition().insertText(donnees[row][col]);
        }
    }

    // Imprimer le PDF
    doc.print(&printer);

    QMessageBox::information(this, "Succès",
                             QString("PDF exporté avec succès !\n%1 client(s) exporté(s).").arg(totalClients));
}
void MainWindow::on_tableClients_doubleClicked(const QModelIndex &index)
{
    int row = index.row();
    int col = index.column();

    // On agit seulement si on double-clique sur la colonne ID (colonne 0)
    if (col != 0) return;

    // Récupérer l'ID du client
    QTableWidgetItem *idItem = ui->tableClients->item(row, 0);
    if (!idItem) return;

    int clientId = idItem->text().toInt();

    // Charger les données du client depuis la base
    chargerEtAfficherClient(clientId);
}


void MainWindow::chargerEtAfficherClient(int id)
{
    // Au lieu d'utiliser rechercherParId, on va chercher dans le tableau directement
    bool clientTrouve = false;
    gestion_client client;

    // Parcourir le tableau pour trouver le client avec cet ID
    for (int row = 0; row < ui->tableClients->rowCount(); ++row) {
        QTableWidgetItem *idItem = ui->tableClients->item(row, 0);
        if (idItem && idItem->text().toInt() == id) {
            // Client trouvé dans le tableau
            clientTrouve = true;

            // Récupérer les données du tableau
            QString nom = ui->tableClients->item(row, 1)->text();
            QString prenom = ui->tableClients->item(row, 2)->text();
            int telephone = ui->tableClients->item(row, 5)->text().toInt();
            QString statut = ui->tableClients->item(row, 4)->text();
            QString sexe = ui->tableClients->item(row, 6)->text();

            // Créer un objet client temporaire (la date sera mise à jour après)
            client.setId(id);
            client.setNom(nom);
            client.setPrenom(prenom);
            client.setTelephone(telephone);
            client.setStatut(statut);
            client.setSexe(sexe);

            break;
        }
    }

    if (!clientTrouve) {
        QMessageBox::warning(this, "Erreur", "Client non trouvé dans le tableau !");
        return;
    }

    // MAINTENANT ON CHARGE LA PHOTO ET L'ORDONNANCE DEPUIS LA BASE 
    Connection c;
    if (c.createconnect()) {
        QSqlQuery query;
        query.prepare("SELECT PHOTO, ORDONNANCE, DATE_DE_NAISSANCE FROM CLIENT WHERE ID_CLIENT = :id");
        query.bindValue(":id", id);

        if (query.exec() && query.next()) {

            // Charger la photo depuis la base
            QString photo = query.value(0).toString();
            if (!photo.isEmpty()) {
                QString photoCheminComplet = "photos_clients/" + photo;
                if (QFile::exists(photoCheminComplet)) {
                    photoPath = photoCheminComplet;
                    afficherPhotoPleinCadre(photoPath);  // ⭐ NOUVELLE LIGNE
                    ui->lineEditPhoto->setText(photo);
                }
            } else {
                // Pas de photo dans la base
                photoPath = "";
                ui->lineEditPhoto->clear();
                ui->lblphoto->setPixmap(QPixmap(":/new/prefix1/uplode-removebg-preview.png"));
            }

            // Charger l'ordonnance depuis la base
            QString ordonnance = query.value(1).toString();
            if (!ordonnance.isEmpty()) {
                ordonnancePath = "ordonnances_clients/" + ordonnance;
                ui->lineEditOrdonnance->setText(ordonnance);
            } else {
                ordonnancePath = "";
                ui->lineEditOrdonnance->clear();
            }

            // Charger la date de naissance depuis la base
           /* QDate dateNaissance = query.value(2).toDate();
            if (dateNaissance.isValid()) {
                ui->lineEditDateNaissance_4->setText(dateNaissance.toString("yyyy-MM-dd"));
            }*/
        }
    }

    // Aller à la page d'ajout/modification
    ui->stackedWidget_4->setCurrentIndex(2);

    // Remplir le formulaire avec les données du client
    ui->lineEditID_3->setText(QString::number(client.getId()));
    ui->lineEditNom_4->setText(client.getNom());
    ui->lineEditPrenom_3->setText(client.getPrenom());
    ui->lineEditPhone_3->setText(QString::number(client.getTelephone()));
    // Note: On ne peut pas récupérer la date de naissance depuis le tableau
    // ui->lineEditDateNaissance_4->setText(client.getDateNaissance().toString("yyyy-MM-dd"));

    // Sexe
    if (client.getSexe() == "H") {
        ui->comboSexe_2->setCurrentText("Homme");
    } else {
        ui->comboSexe_2->setCurrentText("Femme");
    }

    // Statut
    QString statut = client.getStatut();
    ui->checkNew_2->setChecked(statut == "Nouveau");
    ui->checkOld_2->setChecked(statut == "Ancien");
    ui->checkVIP_2->setChecked(statut == "VIP");

    // Désactiver la modification de l'ID
    ui->lineEditID_3->setEnabled(false);
    if (!client.getPhoto().isEmpty()) {
        QString photoCheminComplet = "photos_clients/" + client.getPhoto();
        if (QFile::exists(photoCheminComplet)) {
            photoPath = photoCheminComplet;
            QPixmap pixmap(photoPath);
            if (!pixmap.isNull()) {
                QPixmap scaledPixmap = pixmap.scaled(ui->lblphoto->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                ui->lblphoto->setPixmap(scaledPixmap);
            }
            ui->lineEditPhoto->setText(client.getPhoto());
        }
    }

    if (!client.getPhoto().isEmpty()) {
        QString photoCheminComplet = "photos_clients/" + client.getPhoto();
        if (QFile::exists(photoCheminComplet)) {
            photoPath = photoCheminComplet;
            afficherPhotoPleinCadre(photoPath);  // ⭐ NOUVELLE LIGNE
            ui->lineEditPhoto->setText(client.getPhoto());
        }
    }

    if (!client.getOrdonnance().isEmpty()) {
        ordonnancePath = "ordonnances_clients/" + client.getOrdonnance();
        ui->lineEditOrdonnance->setText(client.getOrdonnance());  // ← Ici aussi
    }


    // Changer le texte du bouton
    ui->btnConfirmer_3->setText("Modifier le client");
}

bool MainWindow::modifierClientExistant(int id, const QString &nom, const QString &prenom,
                                        int telephone, const QDate &dateNaissance,
                                        const QString &statut, const QString &sexe,
                                        const QString &ordonnance, const QString &photo,
                                        QString &erreurMessage)
{
    return gestion_client::modifierClient(id, nom, prenom, telephone, dateNaissance,
                                          statut, sexe, ordonnance, photo, erreurMessage);
}
/*// Fonction principale appelée quand le filtre change
void MainWindow::onFiltresChanged()
{
    QString filtreSelectionne = ui->comboProfession_3->currentText();

    if (filtreSelectionne == "Tous les filtres") {
        reinitialiserFiltres();
    } else {
        appliquerFiltre(filtreSelectionne);
    }
}*/

// Applique un filtre spécifique
/*void MainWindow::appliquerFiltre(const QString &filtre)
{
    int visibleCount = 0;

    for (int i = 0; i < ui->tableClients->rowCount(); ++i) {
        bool visible = ligneCorrespondFiltre(i, filtre);
        ui->tableClients->setRowHidden(i, !visible);

        if (visible) visibleCount++;
    }

    // Optionnel: Afficher le nombre de résultats
    qDebug() << "Filtre" << filtre << ":" << visibleCount << "client(s) trouvé(s)";
}
*/
void MainWindow::onFiltresChanged()
{
    QString filtreSelectionne = ui->comboProfession_3->currentText();
    QString recherche = ui->searchLineEdit_3->text().trimmed();

    appliquerFiltreAvecSQL(filtreSelectionne, recherche);
}

void MainWindow::appliquerFiltreAvecSQL(const QString &filtre, const QString &recherche)
{
    // Bloquer les signaux pendant le rafraîchissement
    ui->tableClients->blockSignals(true);
    ui->tableClients->setRowCount(0);

    Connection c;
    if (!c.createconnect()) {
        QMessageBox::critical(this, "Erreur", "Connexion échouée !");
        ui->tableClients->blockSignals(false);
        return;
    }

    QSqlQuery query;
    QString sql = "SELECT ID_CLIENT, NOM, PRENOM, NUM_TEL, DATE_DE_NAISSANCE, "
                  "STATUT, SEXE FROM CLIENT WHERE 1=1 ";

    // Ajouter les conditions de filtrage
    if (filtre == "Âge: Moins de 30 ans") {
        sql += "AND (SYSDATE - DATE_DE_NAISSANCE) / 365 < 30 ";
    }
    else if (filtre == "Âge: 30 ans et plus") {
        sql += "AND (SYSDATE - DATE_DE_NAISSANCE) / 365 >= 30 ";
    }
    else if (filtre == "Statut: Nouveau") {
        sql += "AND STATUT = 'Nouveau' ";
    }
    else if (filtre == "Statut: Ancien") {
        sql += "AND STATUT = 'Ancien' ";
    }
    else if (filtre == "Statut: VIP") {
        sql += "AND STATUT = 'VIP' ";
    }
    else if (filtre == "Sexe: Homme") {
        sql += "AND SEXE = 'H' ";
    }
    else if (filtre == "Sexe: Femme") {
        sql += "AND SEXE = 'F' ";
    }

    // Ajouter la recherche textuelle si présente
    if (!recherche.isEmpty()) {
        sql += "AND (CAST(ID_CLIENT AS VARCHAR(10)) LIKE :recherche "
               "OR UPPER(NOM) LIKE UPPER(:recherche) "
               "OR UPPER(PRENOM) LIKE UPPER(:recherche)) ";
    }

    sql += "ORDER BY ID_CLIENT";

    query.prepare(sql);

    if (!recherche.isEmpty()) {
        query.bindValue(":recherche", "%" + recherche + "%");
    }

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Échec du filtrage : " + query.lastError().text());
        ui->tableClients->blockSignals(false);
        return;
    }

    // Configuration du tableau
    ui->tableClients->setColumnCount(8);
    QStringList headers = {"ID", "Nom", "Prénom", "Âge", "Statut", "Téléphone", "Sexe", "Actions"};
    ui->tableClients->setHorizontalHeaderLabels(headers);

    ui->tableClients->setColumnWidth(0, 120);
    ui->tableClients->setColumnWidth(1, 120);
    ui->tableClients->setColumnWidth(2, 120);
    ui->tableClients->setColumnWidth(3, 60);
    ui->tableClients->setColumnWidth(4, 100);
    ui->tableClients->setColumnWidth(5, 120);
    ui->tableClients->setColumnWidth(6, 80);
    ui->tableClients->setColumnWidth(7, 120);

    int row = 0;
    int totalClients = 0;

    while (query.next()) {
        totalClients++;
        ui->tableClients->insertRow(row);

        int id = query.value(0).toInt();
        QString nom = query.value(1).toString();
        QString prenom = query.value(2).toString();
        int telephone = query.value(3).toInt();
        QDate dateNaissance = query.value(4).toDate();
        QString statut = query.value(5).toString();
        QString sexe = query.value(6).toString();

        // Calculer l'âge
        int age = dateNaissance.daysTo(QDate::currentDate()) / 365;

        // ID (non éditable)
        QTableWidgetItem *itemId = new QTableWidgetItem(QString::number(id));
        itemId->setFlags(itemId->flags() & ~Qt::ItemIsEditable);
        ui->tableClients->setItem(row, 0, itemId);

        // Nom
        ui->tableClients->setItem(row, 1, new QTableWidgetItem(nom));

        // Prénom
        ui->tableClients->setItem(row, 2, new QTableWidgetItem(prenom));

        // Âge (non éditable)
        QTableWidgetItem *itemAge = new QTableWidgetItem(QString::number(age));
        itemAge->setFlags(itemAge->flags() & ~Qt::ItemIsEditable);
        ui->tableClients->setItem(row, 3, itemAge);

        // Statut
        ui->tableClients->setItem(row, 4, new QTableWidgetItem(statut));

        // Téléphone
        ui->tableClients->setItem(row, 5, new QTableWidgetItem(QString::number(telephone)));

        // Sexe
        QString sexeTexte = (sexe == "H") ? "Homme" : "Femme";
        ui->tableClients->setItem(row, 6, new QTableWidgetItem(sexeTexte));

        // Boutons Actions
        QWidget *actionsWidget = new QWidget();
        QHBoxLayout *layout = new QHBoxLayout(actionsWidget);
        layout->setContentsMargins(3, 1, 3, 1);
        layout->setSpacing(4);

        QPushButton *btnSupp = new QPushButton("SUP");
        QPushButton *btnSMS = new QPushButton("SMS");
        btnSupp->setFixedSize(45, 26);
        btnSMS->setFixedSize(45, 26);
        btnSupp->setStyleSheet("background:#e74c3c; color:white; border-radius:4px; font-weight:bold;");
        btnSMS->setStyleSheet("background:#6c5ce7; color:white; border-radius:4px; font-weight:bold;");

        layout->addWidget(btnSupp);
        layout->addWidget(btnSMS);

        connect(btnSupp, &QPushButton::clicked, this, [this, id, filtre, recherche]() {
            if (QMessageBox::question(this, "Supprimer",
                                      "Supprimer le client ID <b>" + QString::number(id) + "</b> ?",
                                      QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
                QString err;
                if (gestion_client::supprimerClient(id, err)) {
                    QMessageBox::information(this, "Succès", err);
                    appliquerFiltreAvecSQL(filtre, recherche);
                    rafraichirStatistiquesClients();
                } else {
                    QMessageBox::critical(this, "Erreur", err);
                }
            }
        });

        connect(btnSMS, &QPushButton::clicked, this, [this, telephone, clientName = prenom + " " + nom]() {
            SMS_client *smsWindow = new SMS_client(this, QString::number(telephone), clientName);
            smsWindow->exec();
            smsWindow->deleteLater();
        });

        ui->tableClients->setCellWidget(row, 7, actionsWidget);
        row++;
    }

    ui->tableClients->blockSignals(false);
    ui->tableClients->verticalHeader()->setDefaultSectionSize(40);

    // Afficher le nombre de résultats
    qDebug() << "Filtre appliqué:" << filtre << "- Résultats:" << totalClients;
}

// Fonction pour réinitialiser (afficher tous)
void MainWindow::reinitialiserFiltres()
{
    ui->comboProfession_3->setCurrentIndex(0); // "Tous les filtres"
    ui->searchLineEdit_3->clear();
    rafraichirTableauClients();
}
/*// Réinitialise tous les filtres (affiche tous les clients)
void MainWindow::reinitialiserFiltres()
{
    for (int i = 0; i < ui->tableClients->rowCount(); ++i) {
        ui->tableClients->setRowHidden(i, false);
    }

    qDebug() << "Tous les filtres réinitialisés";
}
*/
// Vérifie si une ligne correspond à un filtre donné
bool MainWindow::ligneCorrespondFiltre(int row, const QString &filtre)
{
    // Filtres par âge
    if (filtre == "Âge: Moins de 30 ans") {
        QTableWidgetItem *ageItem = ui->tableClients->item(row, 3);
        return ageItem && ageItem->text().toInt() < 30;
    }
    else if (filtre == "Âge: 30 ans et plus") {
        QTableWidgetItem *ageItem = ui->tableClients->item(row, 3);
        return ageItem && ageItem->text().toInt() >= 30;
    }

    // Filtres par statut
    else if (filtre == "Statut: Nouveau") {
        QTableWidgetItem *statutItem = ui->tableClients->item(row, 4);
        return statutItem && statutItem->text() == "Nouveau";
    }
    else if (filtre == "Statut: Ancien") {
        QTableWidgetItem *statutItem = ui->tableClients->item(row, 4);
        return statutItem && statutItem->text() == "Ancien";
    }
    else if (filtre == "Statut: VIP") {
        QTableWidgetItem *statutItem = ui->tableClients->item(row, 4);
        return statutItem && statutItem->text() == "VIP";
    }

    // Filtres par sexe
    else if (filtre == "Sexe: Homme") {
        QTableWidgetItem *sexeItem = ui->tableClients->item(row, 6);
        return sexeItem && sexeItem->text() == "Homme";
    }
    else if (filtre == "Sexe: Femme") {
        QTableWidgetItem *sexeItem = ui->tableClients->item(row, 6);
        return sexeItem && sexeItem->text() == "Femme";
    }

    return true; // Si filtre non reconnu, afficher la ligne
}

void MainWindow::validerID(const QString &text) {
    bool ok;
    int id = text.toInt(&ok);
    // Vérifier exactement 8 chiffres
    bool valid = ok && text.length() == 8 && id > 0;
    ui->lineEditID_3->setStyleSheet(valid ? "border: 2px solid green;" : "border: 2px solid red; background-color: #FFE6E6;");
}

void MainWindow::validerNom(const QString &text) {
    ui->lineEditNom_4->setStyleSheet(text.isEmpty() || gestion_client::isValidNom(text) ? "border: 2px solid green;" : "border: 2px solid red; background-color: #FFE6E6;");
}

void MainWindow::validerPrenom(const QString &text) {
    ui->lineEditPrenom_3->setStyleSheet(text.isEmpty() || gestion_client::isValidPrenom(text) ? "border: 2px solid green;" : "border: 2px solid red; background-color: #FFE6E6;");
}

void MainWindow::validerTelephone(const QString &text) {
    bool ok;
    int tel = text.toInt(&ok);
    // Vérifier exactement 8 chiffres
    bool valid = ok && text.length() == 8;
    ui->lineEditPhone_3->setStyleSheet(valid ? "border: 2px solid green;" : "border: 2px solid red; background-color: #FFE6E6;");
}
void MainWindow::rafraichirStatistiquesClients()
{
    if (m_statsWidget) {
        m_statsWidget->rafraichirStatistiques();
    }
}
void MainWindow::onPageChanged()
{
    // Vérifier si nous sommes dans la page "Liste des clients"
    bool isClientPage = (ui->stackedWidget->currentWidget() == ui->clients);
    bool isClientListPage = (ui->stackedWidget_4->currentIndex() == 0); // Index 0 = page_7 (liste)

    if (m_statsWidget) {
        m_statsWidget->setVisible(isClientPage && isClientListPage);

        // Rafraîchir les statistiques si on arrive sur la page liste des clients
        if (isClientPage && isClientListPage) {
            rafraichirStatistiquesClients();
        }
    }
}
void MainWindow::decrementerQuantiteProduit(int idProduit)
{
    Connection c;
    if (!c.createconnect()) {
        QMessageBox::critical(this, "Erreur", "Connexion à la base de données échouée !");
        return;
    }

    // Vérifier d'abord si le produit existe
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT QUANTITÉ, MARQUE, MODELE FROM PRODUIT WHERE ID_PRODUIT = :id");
    checkQuery.bindValue(":id", idProduit);

    if (checkQuery.exec() && checkQuery.next()) {
        int quantiteActuelle = checkQuery.value(0).toInt();
        QString marque = checkQuery.value(1).toString();
        QString modele = checkQuery.value(2).toString();

        if (quantiteActuelle > 0) {
            // Décrémenter la quantité
            QSqlQuery updateQuery;
            updateQuery.prepare("UPDATE PRODUIT SET QUANTITÉ = QUANTITÉ - 1 WHERE ID_PRODUIT = :id");
            updateQuery.bindValue(":id", idProduit);

            if (updateQuery.exec()) {
                qDebug() << "Quantité décrémentée pour le produit ID:" << idProduit;

                // Message de confirmation
                QMessageBox::information(this, "Achat enregistré",
                                         QString("Produit acheté avec succès!\n"
                                                 "ID: %1\n"
                                                 "Marque: %2\n"
                                                 "Modèle: %3\n"
                                                 "Nouveau stock: %4")
                                             .arg(idProduit)
                                             .arg(marque)
                                             .arg(modele)
                                             .arg(quantiteActuelle - 1));

                // Mettre à jour l'affichage des produits
                rafraichirTableauProduit();

            } else {
                QMessageBox::critical(this, "Erreur",
                                      "Erreur lors de la mise à jour du stock: " + updateQuery.lastError().text());
            }
        } else {
            QMessageBox::warning(this, "Stock épuisé",
                                 QString("Le produit ID %1 (%2 %3) n'est plus en stock !")
                                     .arg(idProduit)
                                     .arg(marque)
                                     .arg(modele));
        }
    } else {
        QMessageBox::warning(this, "Produit introuvable",
                             QString("Aucun produit trouvé avec l'ID: %1").arg(idProduit));
    }
}

// ⭐⭐ FONCTION : Générer un nom court pour les fichiers

QString MainWindow::genererNomCourt(const QString &cheminOriginal, const QString &prefixe)
{
    if (cheminOriginal.isEmpty()) return "";

    QFileInfo fileInfo(cheminOriginal);
    QString extension = fileInfo.suffix();

    // Générer un nom court : prefixe + timestamp + .ext
    QString nomCourt = QString("%1_%2.%3")
                           .arg(prefixe.left(3))
                           .arg(QDateTime::currentSecsSinceEpoch())
                           .arg(extension.left(3));

    return nomCourt.left(20);
}

// ============================================================================
// ⭐⭐ FONCTION : Copier le fichier vers le dossier de l'app
// ============================================================================
QString MainWindow::copierFichierVersDossierApp(const QString &sourcePath, const QString &dossier, const QString &prefixe)
{
    if (sourcePath.isEmpty()) return "";

    QDir dir;
    if (!dir.exists(dossier)) {
        dir.mkpath(dossier);
    }

    QString nomCourt = genererNomCourt(sourcePath, prefixe);
    QString destinationPath = dossier + "/" + nomCourt;

    if (QFile::copy(sourcePath, destinationPath)) {
        return nomCourt;
    }

    return QString("%1.%2").arg(prefixe.left(3)).arg(QFileInfo(sourcePath).suffix().left(3));
}

/*void MainWindow::on_btnUploadPhoto_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this,
                                                    "Choisir une photo",
                                                    QDir::homePath(),
                                                    "Images (*.png *.jpg *.jpeg *.bmp *.gif)");

    if (!filePath.isEmpty()) {
        // ⭐ VALIDATION DU VISAGE HUMAIN
        QString erreurValidation;
        if (!validerVisageHumain(filePath, erreurValidation)) {
            QMessageBox::warning(this, "Photo invalide", erreurValidation);
            return; // Ne pas accepter la photo
        }

        // ✅ Photo validée !
        QString nomFichier = QFileInfo(filePath).fileName();
        if (nomFichier.length() > 20) {
            QMessageBox::warning(this, "Nom trop long",
                                 "Le nom sera renommé automatiquement.");
        }

        photoPath = filePath;

        // Afficher l'aperçu
        QPixmap pixmap(photoPath);
        if (!pixmap.isNull()) {
            QPixmap scaledPixmap = pixmap.scaled(ui->lblphoto->size(),
                                                 Qt::KeepAspectRatio,
                                                 Qt::SmoothTransformation);
            ui->lblphoto->setPixmap(scaledPixmap);
        }

        QString nomCourt = genererNomCourt(photoPath, "photo");
        ui->lineEditPhoto->setText(nomCourt);

        // Message de confirmation
        QMessageBox::information(this, "✅ Photo validée",
                                 "Visage humain détecté avec succès !\n"
                                 "La photo est acceptée.");
    }
}*/
void MainWindow::on_btnUploadPhoto_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this,
                                                    "Choisir une photo",
                                                    QDir::homePath(),
                                                    "Images (*.png *.jpg *.jpeg *.bmp *.gif)");

    if (!filePath.isEmpty()) {
        QString erreurValidation;
        if (!validerVisageHumain(filePath, erreurValidation)) {
            QMessageBox::warning(this, "Photo invalide", erreurValidation);
            return;
        }

        QString nomFichier = QFileInfo(filePath).fileName();
        if (nomFichier.length() > 20) {
            QMessageBox::warning(this, "Nom trop long",
                                 "Le nom sera renommé automatiquement.");
        }

        photoPath = filePath;

        // ⭐ NOUVELLE LIGNE - SIMPLE ET PROPRE ⭐
        afficherPhotoPleinCadre(photoPath);

        QString nomCourt = genererNomCourt(photoPath, "photo");
        ui->lineEditPhoto->setText(nomCourt);

        QMessageBox::information(this, "✅ Photo validée",
                                 "Visage humain détecté avec succès !\n"
                                 "La photo est acceptée.");
    }
}

// ⭐⭐ FONCTION : Upload de l'ordonnance

void MainWindow::on_btnUploadOrdonnance_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this,
                                                    "Choisir une ordonnance",
                                                    QDir::homePath(),
                                                    "Documents (*.pdf *.png *.jpg *.jpeg);;PDF (*.pdf);;Images (*.png *.jpg *.jpeg)"
                                                    );

    if (!filePath.isEmpty()) {
        QString nomFichier = QFileInfo(filePath).fileName();
        if (nomFichier.length() > 20) {
            QMessageBox::warning(this, "Nom trop long",
                                 "Le nom du fichier est trop long. Il sera renommé automatiquement.");
        }

        ordonnancePath = filePath;
        QString nomCourt = genererNomCourt(ordonnancePath, "ordo");
        ui->lineEditOrdonnance->setText(nomCourt);
    }
}

// ⭐ FONCTION : AFFICHER PHOTO EN PLEIN CADRE (AVEC RECADRAGE)

void MainWindow::afficherPhotoPleinCadre(const QString &cheminPhoto)
{
    // Charger l'image
    QPixmap pixmap(cheminPhoto);

    // Si l'image est invalide, afficher l'image par défaut
    if (pixmap.isNull()) {
        ui->lblphoto->setPixmap(QPixmap(":/new/prefix1/uplode-removebg-preview.png"));
        return;
    }

    // Obtenir la taille du label
    QSize labelSize = ui->lblphoto->size();

    // Calculer les ratios (proportions)
    double imgRatio = (double)pixmap.width() / pixmap.height();
    double labelRatio = (double)labelSize.width() / labelSize.height();

    QPixmap croppedPixmap;

    if (imgRatio > labelRatio) {
        // L'IMAGE EST PLUS LARGE que le cadre
        // → On recadre les côtés gauche/droite
        int newWidth = pixmap.height() * labelRatio;
        int x = (pixmap.width() - newWidth) / 2;  // Centrer horizontalement
        croppedPixmap = pixmap.copy(x, 0, newWidth, pixmap.height());

    } else {
        // L'IMAGE EST PLUS HAUTE que le cadre
        // → On recadre le haut/bas
        int newHeight = pixmap.width() / labelRatio;
        int y = (pixmap.height() - newHeight) / 2;  // Centrer verticalement
        croppedPixmap = pixmap.copy(0, y, pixmap.width(), newHeight);
    }

    // Redimensionner l'image recadrée à la taille exacte du label
    QPixmap scaledPixmap = croppedPixmap.scaled(labelSize,
                                                Qt::IgnoreAspectRatio,
                                                Qt::SmoothTransformation);

    // Afficher l'image
    ui->lblphoto->setPixmap(scaledPixmap);
}

bool MainWindow::validerVisageHumain(const QString &cheminPhoto, QString &erreurMessage)
{
    try {
        cv::Mat image = cv::imread(cheminPhoto.toStdString());
        if (image.empty()) {
            erreurMessage = "❌ Impossible de charger l'image !";
            return false;
        }

        qDebug() << "📷 Image chargée:" << image.cols << "x" << image.rows;

        // Redimensionner doucement
        if (image.rows > 800 || image.cols > 800) {
            cv::resize(image, image, cv::Size(600, 600));
        }
        // CONVERTIR EN NIVEAUX DE GRIS
        cv::Mat grayImage;
        cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);
        cv::equalizeHist(grayImage, grayImage);

        // Charger le détecteur
        cv::CascadeClassifier faceCascade;
        QString cascadePath = QCoreApplication::applicationDirPath() + "/haarcascade_frontalface_default.xml";

        if (!faceCascade.load(cascadePath.toStdString())) {
            erreurMessage = "❌ Fichier de détection introuvable !";
            return false;
        }

        // DÉTECTER LES VISAGES
        std::vector<cv::Rect> faces;

        // Premier essai avec paramètres standards
        faceCascade.detectMultiScale(grayImage, faces, 1.1, 4, 0, cv::Size(60, 60));

        qDebug() << "🔍 Visages détectés (premier passage):" << faces.size();

        // Si aucun visage, essayer avec des paramètres plus sensibles
        if (faces.empty()) {
            faceCascade.detectMultiScale(grayImage, faces, 1.05, 3, 0, cv::Size(40, 40));
            qDebug() << "🔍 Visages détectés (second passage):" << faces.size();
        }

        // ⭐ REFUSER LES MULTIPLES VISAGES
        if (faces.size() > 1) {
            erreurMessage = QString("❌ Photo refusée !\n\n"
                                    "%1 visages détectés.\n\n"
                                    "Une seule personne par photo est autorisée.")
                                .arg(faces.size());
            return false;
        }

        // ⭐ ACCEPTER SI 1 VISAGE DÉTECTÉ (sans filtrage trop strict)
        if (faces.size() == 1) {
            cv::Rect face = faces[0];
            double ratio = (double)face.width / face.height;

            qDebug() << "✅ Visage détecté - Ratio:" << ratio
                     << "Taille:" << face.width << "x" << face.height
                     << "Position:" << face.x << "," << face.y;

            // Vérifications basiques uniquement
            if (ratio < 0.5 || ratio > 2.0) {
                erreurMessage = "❌ Format de visage inhabituel !";
                return false;
            }

            if (face.width < 30 || face.height < 30) {
                erreurMessage = "❌ Visage trop petit !";
                return false;
            }

            qDebug() << "🎉 Photo acceptée - 1 visage détecté";
            return true;
        }

        // ⭐ SI AUCUN VISAGE
        erreurMessage = "❌ Aucun visage détecté !\n\n"
                        "Conseils :\n"
                        "• Photo bien éclairée\n"
                        "• Visage face à la caméra\n"
                        "• Pas trop loin/près\n"
                        "• Fond simple";
        return false;

    } catch (const cv::Exception& e) {
        erreurMessage = QString("❌ Erreur OpenCV : %1").arg(e.what());
        qDebug() << "❌ OpenCV Exception:" << e.what();
        return false;
    } catch (...) {
        erreurMessage = "❌ Erreur inconnue lors de l'analyse";
        return false;
    }
}
void MainWindow::verifierInstallationOpenCV()
{
    qDebug() << "=== VÉRIFICATION OPENCV ===";

    // Vérifier la version
    qDebug() << "Version OpenCV:" << CV_VERSION;

    // Vérifier les chemins des cascades
    QStringList cascadesToCheck = {
        "C:/opencv-mingw/OpenCV-MinGW-Build-OpenCV-4.5.5-x64/etc/haarcascades/",
        "C:/opencv/build/etc/haarcascades/",
        QCoreApplication::applicationDirPath() + "/"
    };

    QStringList cascadeFiles = {
        "haarcascade_frontalface_default.xml",
        "haarcascade_frontalface_alt.xml",
        "haarcascade_frontalface_alt2.xml"
    };

    for (const QString& basePath : cascadesToCheck) {
        qDebug() << "🔍 Checking:" << basePath;
        for (const QString& file : cascadeFiles) {
            QString fullPath = basePath + file;
            if (QFile::exists(fullPath)) {
                qDebug() << "   ✅" << file;
            } else {
                qDebug() << "   ❌" << file << "(manquant)";
            }
        }
    }
    qDebug() << "=== FIN VÉRIFICATION ===";
}
MainWindow::~MainWindow() {
    delete lineEditIDProduit;
    delete ui;
}
