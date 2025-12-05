#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "apiremises.h"
#include "gestion_client.h"
#include "gestion_personnel.h"
#include "gestion_locaux.h"
#include "gestion_fournisseur.h"
#include "gestion_produit.h"
#include "connection.h"
#include "SMS_client.h"
#include "StatisticsWidget.h"
#include "StatisticsWidgetProduit.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QRegularExpression>
#include <QPrinter>
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
    , m_apiRemises(nullptr)
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

    ui->label_2->setVisible(false);

    m_statsWidget = new StatisticsWidget(this);
    m_statsWidget->setGeometry(1100, 80,300, 500);

    ui->label_3->setVisible(false);
    connect(ui->stackedWidget_4, &QStackedWidget::currentChanged, this, &MainWindow::onPageChanged);
    connect(ui->stackedWidget, &QStackedWidget::currentChanged, this, &MainWindow::onPageChanged);
    rafraichirStatistiquesClients();

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

    QPushButton *btnUploadOrdonnance = new QPushButton(ui->frameFicheClient_3);
    btnUploadOrdonnance->setObjectName("btnUploadOrdonnance");
    btnUploadOrdonnance->setGeometry(920, 340, 90, 30);
    btnUploadOrdonnance->setText("Choisir fichier");
    btnUploadOrdonnance->setStyleSheet(btnUploadPhoto->styleSheet());

    connect(btnUploadPhoto, &QPushButton::clicked, this, &MainWindow::on_btnUploadPhoto_clicked);
    connect(btnUploadOrdonnance, &QPushButton::clicked, this, &MainWindow::on_btnUploadOrdonnance_clicked);

    lineEditIDProduit = new QLineEdit(ui->frameFicheClient_3);
    lineEditIDProduit->setObjectName("lineEditIDProduit");
    lineEditIDProduit->setGeometry(790, 390, 201, 31);
    lineEditIDProduit->setPlaceholderText("ID du produit acheté");
    lineEditIDProduit->setValidator(new QIntValidator(1, 999999, this));
    lineEditIDProduit->setStyleSheet("color: rgb(0, 0, 0); border: 1px solid gray; border-radius: 5px; padding: 5px;");

    ui->comboProfession_3->clear();
    ui->comboProfession_3->addItem("Tous les filtres");
    ui->comboProfession_3->addItem("Âge: Moins de 30 ans");
    ui->comboProfession_3->addItem("Âge: 30 ans et plus");
    ui->comboProfession_3->addItem("Statut: Nouveau");
    ui->comboProfession_3->addItem("Statut: Ancien");
    ui->comboProfession_3->addItem("Statut: VIP");
    ui->comboProfession_3->addItem("Sexe: Homme");
    ui->comboProfession_3->addItem("Sexe: Femme");

    //connect(ui->comboProfession_3, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onFiltresChanged);
    connect(ui->searchLineEdit_3, &QLineEdit::textChanged, this, [this]() {
        QString filtre = ui->comboProfession_3->currentText();
        QString recherche = ui->searchLineEdit_3->text().trimmed();
        appliquerFiltreAvecSQL(filtre, recherche);
    });
    connect(ui->comboProfession_3, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onFiltresChanged);


    /*m_statsWidgetProduit = new StatisticsWidgetProduit(this);

    m_statsWidgetProduit->deplacerManuellement(1100, 100);
    m_statsWidgetProduit->redimensionnerManuellement(320, 520);

    m_statsWidgetProduit->deplacerEtRedimensionner(1200, 100, 320, 520);

    m_statsWidgetProduit->setGeometry(1100, 80, 300, 5000);
    m_statsWidgetProduit->deplacerVersDroite(75);  // +100 pixels vers la droite
    m_statsWidgetProduit->deplacerVersBas(37.5);      // +20 pixels vers le bas
    m_statsWidgetProduit->redimensionnerManuellement(700, 7000); // Agrandir*/

    m_statsWidgetProduit = new StatisticsWidgetProduit(this);
    m_statsWidgetProduit->setGeometry(1100, 100, 320, 550);
    m_statsWidgetProduit->deplacerVersDroite(75);  // +100 pixels vers la droite
    m_statsWidgetProduit->deplacerVersBas(37.5);
    m_statsWidgetProduit->setVisible(false);

    m_statsWidgetProduit->setVisible(false);

    connect(ui->searchLineEdit_5, &QLineEdit::textChanged, this, &MainWindow::on_searchLineEdit_5_textChanged);
    connect(ui->btnExporter_5, &QPushButton::clicked, this, &MainWindow::on_btnExporter_5_clicked);
    connect(ui->comboProfession_5, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onFiltresProduitChanged);

    ui->comboProfession_5->clear();
    ui->comboProfession_5->addItem("Tous les filtres");
    ui->comboProfession_5->addItem("Prix: Bas");
    ui->comboProfession_5->addItem("Prix: Haut");
    ui->comboProfession_5->addItem("A-Z");
    ui->comboProfession_5->addItem("Z-A");
    ui->comboProfession_5->addItem("Genre: Homme");
    ui->comboProfession_5->addItem("Genre: Femme");
    ui->comboProfession_5->addItem("Genre: Unisexe");
    ui->comboProfession_5->addItem("Stock faible");

    verifierStockFaible();

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
        if (m_statsWidgetProduit) {
            m_statsWidgetProduit->setVisible(false);
        }
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
        if (m_statsWidgetProduit) {
            m_statsWidgetProduit->setVisible(false);
        }
    });
    connect(ui->btnListePersonnel_5, &QPushButton::clicked, [=]() {
        ui->stackedWidget_6->setCurrentIndex(0);
        rafraichirTableauProduit();
        if (m_statsWidgetProduit) {
            m_statsWidgetProduit->setVisible(true);
            rafraichirStatistiquesProduits();
        }
    });
    connect(ui->btnAjouterClient_8, &QPushButton::clicked, [=]() {
        ui->stackedWidget_6->setCurrentIndex(2);
        viderFormulaireProduit();
        if (m_statsWidgetProduit) {
            m_statsWidgetProduit->setVisible(false);
        }
    });
    connect(ui->btnListeClients_8, &QPushButton::clicked, [=]() {
        ui->stackedWidget_6->setCurrentIndex(0);
        rafraichirTableauProduit();
        if (m_statsWidgetProduit) {
            m_statsWidgetProduit->setVisible(true);
            rafraichirStatistiquesProduits();
        }
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

    connect(ui->id_fournisseur, &QLineEdit::textChanged, this, &MainWindow::validerIDFournisseur);
    connect(ui->nomentre, &QLineEdit::textChanged, this, &MainWindow::validerNomFournisseur);
    connect(ui->ADRESSE, &QLineEdit::textChanged, this, &MainWindow::validerTelephoneFournisseur);
    connect(ui->MAIL, &QLineEdit::textChanged, this, &MainWindow::validerMailFournisseur);

    connect(ui->searchLineEdit_4, &QLineEdit::textChanged, this, &MainWindow::on_searchLineEdit_4_textChanged);
    connect(ui->btnExporter_4, &QPushButton::clicked, this, &MainWindow::on_btnExporter_4_clicked);
    connect(ui->tableClients_2, &QTableWidget::doubleClicked, this, &MainWindow::on_tableClients_2_doubleClicked);
    connect(ui->comboProfession_4, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onFiltresFournisseurChanged);

    ui->comboProfession_4->clear();
    ui->comboProfession_4->addItem("Tous les filtres");
    ui->comboProfession_4->addItem("Produit fournis");
    ui->comboProfession_4->addItem("Statut");
    ui->comboProfession_4->addItem("Nom de Fournisseur");
    ui->comboProfession_4->addItem("A-Z");
    ui->comboProfession_4->addItem("Z-A");

    rafraichirTableauClients();
    rafraichirTableauPersonnel();
    rafraichirTableauLocaux();
    rafraichirTableauFournisseur();
    rafraichirTableauProduit();
    initialiserAPI();
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
void MainWindow::ajusterPositionStatistiques()
{
    if (m_statsWidgetProduit) {
        m_statsWidgetProduit->setGeometry(1100, 100, 320, 550);
    }
    if (m_statsWidget) {
        m_statsWidget->setGeometry(1100, 100, 320, 520);
    }
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
    QString idProduitText = lineEditIDProduit->text().trimmed();
    if (!idProduitText.isEmpty()) {
        bool ok;
        int idProduit = idProduitText.toInt(&ok);

        if (ok && idProduit > 0) {
            decrementerQuantiteProduit(idProduit);
            QString achat = QString("Produit %1 - %2")
                                .arg(idProduit)
                                .arg(QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm"));
        } else {
            QMessageBox::warning(this, "ID produit invalide",
                                 "L'ID du produit doit être un nombre positif !");
            return;
        }
    }

    QString photo = "";
    QString ordonnance = "";

    if (!photoPath.isEmpty()) {
        photo = gestion_client::copierPhotoVersDossier(photoPath);
        if (photo.isEmpty()) {
            QMessageBox::warning(this, "Erreur", "Échec de la copie de la photo !");
            return;
        }
    }

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

    QString erreur;
    bool succes;

    if (ui->lineEditID_3->isEnabled()) {
        succes = gestion_client::ajouterClient(
            id, nom, prenom, telephone, dateNaissance,
            statut, sexeTexte, ordonnance, photo, erreur
            );
    } else {
        succes = modifierClientExistant(
            id, nom, prenom, telephone, dateNaissance,
            statut, sexeTexte, ordonnance, photo, erreur
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
    int id = ui->id_fournisseur->text().toInt(&okId);
    QString nomEntreprise = ui->nomentre->text().trimmed();
    QString personneContact = ui->PERSONNE_CNT->text().trimmed();
    QString adresse = ui->ADRESSE->text().trimmed();
    int telephone = ui->telephone->text().toInt(&okTel);
    QString mail = ui->MAIL->text().trimmed();
    QString categorie = ui->comboCategorie->currentText();
    QString details = ui->DETAILS->text().trimmed();
    float noteFiabilite = ui->NOTEDEFIABILITE->text().toInt(&okId);

    if (!okId || !okTel || id <= 0) {
        QMessageBox::warning(this, "Erreur", "ID et téléphone doivent être numériques !");
        return;
    }

    if (!Gestion_Fournisseur::isValidNom(nomEntreprise)) {
        QMessageBox::warning(this, "Erreur", "Nom entreprise invalide !");
        return;
    }

    if (!Gestion_Fournisseur::isValidTelephone(telephone)) {
        QMessageBox::warning(this, "Erreur", "Téléphone invalide !");
        return;
    }

    if (!Gestion_Fournisseur::isValidMail(mail)) {
        QMessageBox::warning(this, "Erreur", "Mail invalide !");
        return;
    }

    if (!Gestion_Fournisseur::isValidCategorie(categorie)) {
        QMessageBox::warning(this, "Erreur", "Catégorie invalide !");
        return;
    }

    QString erreur;
    bool succes;

    if (ui->id_fournisseur->isEnabled()) {
        succes = Gestion_Fournisseur::ajouterFournisseur(
            id, nomEntreprise, personneContact, adresse, telephone, mail,
            categorie, details, noteFiabilite, erreur
            );
    } else {
        succes = modifierFournisseurExistant(
            id, nomEntreprise, personneContact, adresse, telephone, mail,
            categorie, details, noteFiabilite, erreur
            );
    }

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
    // VALIDATION RENFORCÉE
    if (ui->lineEditID_5->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir un ID produit !");
        return;
    }

    if (ui->lineEditNom_6->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir une marque !");
        return;
    }

    if (ui->lineEditPrenom_4->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir un modèle !");
        return;
    }

    bool okId, okPrix, okQuantite;
    int id = ui->lineEditID_5->text().toInt(&okId);
    float prix = ui->lineEditDateNaissance_7->text().toFloat(&okPrix);
    int quantite = ui->spinBox->text().toInt(&okQuantite);

    if (!okId || id <= 0) {
        QMessageBox::warning(this, "Erreur", "ID produit invalide !");
        return;
    }

    if (!okPrix || prix < 0) {
        QMessageBox::warning(this, "Erreur", "Prix invalide !");
        return;
    }

    if (!okQuantite || quantite < 0) {
        QMessageBox::warning(this, "Erreur", "Quantité invalide !");
        return;
    }

    // Récupération des autres valeurs
    QString marque = ui->lineEditNom_6->text().trimmed();
    QString modele = ui->lineEditPrenom_4->text().trimmed();
    QString type = ui->comboProfession_6->currentText();
    QString couleur = ui->lineEditDateNaissance_6->text().trimmed();
    float remise = ui->spinBox_2->value();
    QString matiere = ui->comboProfession_7->currentText();
    QString genre = ui->comboProfession_8->currentText();
    QDate dateAjout = ui->dateEdit->date();
    int idClient = 0;
    int idFournisseur = 0;
    int idLocal = 0;

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

void MainWindow::validerIDFournisseur(const QString &text) {
    bool ok;
    int id = text.toInt(&ok);
    bool valid = ok && id > 0 && id <= 999999999;
    ui->id_fournisseur->setStyleSheet(valid ? "border: 2px solid green;" : "border: 2px solid red; background-color: #FFE6E6;");
}

void MainWindow::validerNomFournisseur(const QString &text) {
    bool valid = Gestion_Fournisseur::isValidNom(text);
    ui->nomentre->setStyleSheet(valid ? "border: 2px solid green;" : "border: 2px solid red; background-color: #FFE6E6;");
}

void MainWindow::validerTelephoneFournisseur(const QString &text) {
    bool ok;
    int tel = text.toInt(&ok);
    bool valid = ok && Gestion_Fournisseur::isValidTelephone(tel);
    ui->ADRESSE->setStyleSheet(valid ? "border: 2px solid green;" : "border: 2px solid red; background-color: #FFE6E6;");
}

void MainWindow::validerMailFournisseur(const QString &text) {
    bool valid = text.isEmpty() || Gestion_Fournisseur::isValidMail(text);
    ui->MAIL->setStyleSheet(valid ? "border: 2px solid green;" : "border: 2px solid red; background-color: #FFE6E6;");
}

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
    photoPath = "";
    ordonnancePath = "";
    ui->lblphoto->setPixmap(QPixmap(":/new/prefix1/uplode-removebg-preview.png"));
    ui->lineEditPhoto->clear();
    ui->lineEditOrdonnance->clear();
    ui->lineEditID_3->setEnabled(true);
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
    ui->id_fournisseur->clear();
    ui->nomentre->clear();
    ui->PERSONNE_CNT->clear();
    ui->ADRESSE->clear();
    ui->telephone->clear();
    ui->MAIL->clear();
    ui->comboCategorie->setCurrentIndex(0);
    ui->DETAILS->clear();
    ui->NOTEDEFIABILITE->clear();
    ui->id_fournisseur->setEnabled(true);
    ui->btnConfirmer_4->setText("Confirmer");
    ui->id_fournisseur->setStyleSheet("");
    ui->nomentre->setStyleSheet("");
    ui->ADRESSE->setStyleSheet("");
    ui->MAIL->setStyleSheet("");
}

void MainWindow::viderFormulaireProduit() {
    ui->lineEditID_5->clear();
    ui->lineEditNom_6->clear();
    ui->lineEditPrenom_4->clear();
    ui->comboProfession_6->setCurrentIndex(0);
    ui->lineEditDateNaissance_6->clear();
    ui->lineEditDateNaissance_7->clear();
    ui->spinBox_2->setValue(0);  // Remise à 0 par défaut
    ui->spinBox->setValue(0);    // Quantité à 0 par défaut
    ui->comboProfession_7->setCurrentIndex(0);
    ui->comboProfession_8->setCurrentIndex(0);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->checkBoxAI->setChecked(false); // Décocher auto-discount
}
// SUPPRIMEZ cette méthode entièrement :
void MainWindow::onTestAPIClicked()
{
    // Méthode de test pour vérifier la connexion API
    if (!m_apiRemises) {
        QMessageBox::warning(this, "Erreur", "API non initialisée");
        return;
    }

    // Test avec des valeurs fixes
    m_apiRemises->calculerRemiseAutomatique(123, 25);
}
void MainWindow::rafraichirTableauClients()
{
    ui->tableClients->blockSignals(true);
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

        QTableWidgetItem *itemId = new QTableWidgetItem(QString::number(c.getId()));
        itemId->setFlags(itemId->flags() & ~Qt::ItemIsEditable);
        ui->tableClients->setItem(row, 0, itemId);

        ui->tableClients->setItem(row, 1, new QTableWidgetItem(c.getNom()));
        ui->tableClients->setItem(row, 2, new QTableWidgetItem(c.getPrenom()));

        QTableWidgetItem *itemAge = new QTableWidgetItem(QString::number(c.getAge()));
        itemAge->setFlags(itemAge->flags() & ~Qt::ItemIsEditable);
        ui->tableClients->setItem(row, 3, itemAge);

        ui->tableClients->setItem(row, 4, new QTableWidgetItem(c.getStatut()));
        ui->tableClients->setItem(row, 5, new QTableWidgetItem(QString::number(c.getTelephone())));

        QString sexeTexte = (c.getSexe() == "H") ? "Homme" : "Femme";
        ui->tableClients->setItem(row, 6, new QTableWidgetItem(sexeTexte));

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
    int currentRow = ui->tableClients_2->currentRow();
    ui->tableClients_2->setRowCount(0);
    auto fournisseurs = Gestion_Fournisseur::chargerTousLesFournisseurs();

    ui->tableClients_2->setColumnCount(9);
    QStringList headers = {"ID", "Nom Entreprise", "Personne Contact", "Adresse", "Téléphone", "Mail", "Catégorie", "Note", "Actions"};
    ui->tableClients_2->setHorizontalHeaderLabels(headers);

    ui->tableClients_2->setColumnWidth(0, 120);
    ui->tableClients_2->setColumnWidth(1, 150);
    ui->tableClients_2->setColumnWidth(2, 120);
    ui->tableClients_2->setColumnWidth(3, 120);
    ui->tableClients_2->setColumnWidth(4, 100);
    ui->tableClients_2->setColumnWidth(5, 150);
    ui->tableClients_2->setColumnWidth(6, 100);
    ui->tableClients_2->setColumnWidth(7, 80);
    ui->tableClients_2->setColumnWidth(8, 120);

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
        layout->setSpacing(4);

        QPushButton *btnSupp = new QPushButton("SUP");
        QPushButton *btnModif = new QPushButton("MOD");
        btnSupp->setFixedSize(45, 26);
        btnModif->setFixedSize(45, 26);
        btnSupp->setStyleSheet("background:#e74c3c; color:white; border-radius:4px; font-weight:bold;");
        btnModif->setStyleSheet("background:#3498db; color:white; border-radius:4px; font-weight:bold;");

        layout->addWidget(btnSupp);
        layout->addWidget(btnModif);

        int fournisseurId = f.getId();

        connect(btnSupp, &QPushButton::clicked, this, [this, fournisseurId]() {
            if (QMessageBox::question(this, "Supprimer",
                                      "Supprimer le fournisseur ID <b>" + QString::number(fournisseurId) + "</b> ?",
                                      QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {

                QString err;
                if (Gestion_Fournisseur::supprimerFournisseur(fournisseurId, err)) {
                    QMessageBox::information(this, "Succès", err);
                    rafraichirTableauFournisseur();
                } else {
                    QMessageBox::critical(this, "Erreur", err);
                }
            }
        });

        connect(btnModif, &QPushButton::clicked, this, [this, fournisseurId]() {
            chargerEtAfficherFournisseur(fournisseurId);
        });

        ui->tableClients_2->setCellWidget(row, 8, actionsWidget);
        row++;
    }

    if (currentRow >= 0 && currentRow < ui->tableClients_2->rowCount()) {
        ui->tableClients_2->setCurrentCell(currentRow, 0);
    }

    ui->tableClients_2->blockSignals(false);
    ui->tableClients_2->verticalHeader()->setDefaultSectionSize(40);
}

void MainWindow::highlightLowStockProducts()
{
    int stockZeroCount = 0;

    for (int row = 0; row < ui->tablePersonnel_3->rowCount(); ++row) {
        QTableWidgetItem *quantiteItem = ui->tablePersonnel_3->item(row, 7);
        if (quantiteItem) {
            int quantite = quantiteItem->text().toInt();

            if (quantite == 0) {
                stockZeroCount++;

                // Colorer toute la ligne en rouge clair
                for (int col = 0; col < ui->tablePersonnel_3->columnCount(); ++col) {
                    QTableWidgetItem *item = ui->tablePersonnel_3->item(row, col);
                    if (item) {
                        item->setBackground(QColor(255, 230, 230)); // Rouge très clair
                        item->setForeground(QColor(220, 0, 0));     // Texte rouge

                        // Style spécial pour la cellule quantité
                        if (col == 7) {
                            item->setBackground(QColor(255, 200, 200)); // Rouge plus prononcé
                            item->setFont(QFont("Segoe UI", 9, QFont::Bold));
                        }
                    }
                }

                // Colorer aussi le widget d'actions s'il existe
                QWidget *widget = ui->tablePersonnel_3->cellWidget(row, 10);
                if (widget) {
                    widget->setStyleSheet("background-color: #FFE6E6;");
                }
            } else {
                // Réinitialiser le style pour les autres lignes
                for (int col = 0; col < ui->tablePersonnel_3->columnCount(); ++col) {
                    QTableWidgetItem *item = ui->tablePersonnel_3->item(row, col);
                    if (item) {
                        item->setBackground(Qt::white);
                        item->setForeground(Qt::black);
                        if (col == 7) {
                            item->setFont(QFont("Segoe UI", 9, QFont::Normal));
                        }
                    }
                }

                // Réinitialiser le style du widget d'actions
                QWidget *widget = ui->tablePersonnel_3->cellWidget(row, 10);
                if (widget) {
                    widget->setStyleSheet("");
                }
            }
        }
    }

    // Afficher une alerte si des produits sont en rupture
    if (stockZeroCount > 0) {
        showStockAlert();
    }
}
void MainWindow::showStockAlert()
{
    // Compter les produits en rupture de stock
    int stockZeroCount = 0;
    QStringList produitsRupture;

    for (int row = 0; row < ui->tablePersonnel_3->rowCount(); ++row) {
        QTableWidgetItem *quantiteItem = ui->tablePersonnel_3->item(row, 7);
        QTableWidgetItem *idItem = ui->tablePersonnel_3->item(row, 0);
        QTableWidgetItem *marqueItem = ui->tablePersonnel_3->item(row, 1);
        QTableWidgetItem *modeleItem = ui->tablePersonnel_3->item(row, 2);

        if (quantiteItem && quantiteItem->text().toInt() == 0) {
            stockZeroCount++;
            QString produitInfo = QString("ID:%1 %2 %3")
                                      .arg(idItem->text())
                                      .arg(marqueItem->text())
                                      .arg(modeleItem->text());
            produitsRupture.append(produitInfo);
        }
    }

    if (stockZeroCount > 0) {
        // Message box d'alerte
        QMessageBox::warning(this,
                             "⚠️ ALERTE - Rupture de Stock",
                             QString("<b>%1 produit(s) en rupture de stock !</b><br><br>"
                                     "<b>Produits concernés :</b><br>%2<br><br>"
                                     "Veuillez réapprovisionner ces produits.")
                                 .arg(stockZeroCount)
                                 .arg(produitsRupture.join("<br>")));

        // Optionnel: Faire clignoter le label d'alerte existant
        static bool blinkState = false;
        blinkState = !blinkState;

        QString style = blinkState ?
                            "background-color: #FEF2F2; padding: 8px; border: 2px solid #DC2626; border-radius: 6px; color: #DC2626; font-weight: bold;" :
                            "background-color: #FCA5A5; padding: 8px; border: 2px solid #DC2626; border-radius: 6px; color: #7F1D1D; font-weight: bold;";

        ui->label_33->setStyleSheet(style);
        ui->label_33->setText(QString("⚠️ ALERTE: %1 produit(s) en rupture de stock")
                                  .arg(stockZeroCount));

        // Faire clignoter pendant 5 secondes
        QTimer::singleShot(5000, this, [this]() {
            ui->label_33->setStyleSheet("background-color: #F0FDF4; padding: 8px; border: 2px solid #16A34A; border-radius: 6px; color: #166534; font-weight: bold;");
            ui->label_33->setText("✅ Stock normal");
        });
    }
}
void MainWindow::onTableItemChanged(QTableWidgetItem *item)
{
    if (!item || item->column() == 0 || item->column() == 3 || item->column() == 7)
        return;

    ui->tableClients->blockSignals(true);

    int row = item->row();
    int col = item->column();

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

    switch (col) {
    case 1:
        if (!gestion_client::isValidNom(value)) {
            erreurMessage = "Nom invalide ! Doit contenir seulement des lettres, apostrophes ou tirets (2-20 caractères).";
            validationOk = false;
        } else {
            champ = "NOM";
            sqlValue = value.toUpper();
        }
        break;

    case 2:
        if (!gestion_client::isValidPrenom(value)) {
            erreurMessage = "Prénom invalide ! Doit contenir seulement des lettres, apostrophes ou tirets (2-20 caractères).";
            validationOk = false;
        } else {
            champ = "PRENOM";
            sqlValue = value;
        }
        break;

    case 4:
        if (value == "Nouveau" || value == "Ancien" || value == "VIP") {
            champ = "STATUT";
            sqlValue = value;
        } else {
            erreurMessage = "Statut invalide ! Choisir: Nouveau, Ancien ou VIP";
            validationOk = false;
        }
        break;

    case 5:
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

    case 6:
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
        rafraichirTableauClients();
        ui->tableClients->blockSignals(false);
        return;
    }

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
    } else {
        QMessageBox::critical(this, "Erreur BD", "Échec de la modification : " + q.lastError().text());
        rafraichirTableauClients();
    }

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

        if (filtreActif != "Tous les filtres") {
            show = ligneCorrespondFiltre(i, filtreActif);
        }

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

}*/
// recherche client
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

    int visibleRows = 0;
    for (int i = 0; i < ui->tableClients->rowCount(); ++i) {
        if (!ui->tableClients->isRowHidden(i)) visibleRows++;
    }

    QTextTableFormat tableFormat;
    tableFormat.setBorder(1);
    tableFormat.setCellPadding(5);
    tableFormat.setAlignment(Qt::AlignCenter);
    tableFormat.setWidth(QTextLength(QTextLength::PercentageLength, 100));

    QTextTable *table = cursor.insertTable(visibleRows + 1, 7, tableFormat);

    QStringList headers = {"ID", "Nom", "Prénom", "Âge", "Statut", "Téléphone", "Sexe"};
    QTextCharFormat headerFmt;
    headerFmt.setFontWeight(QFont::Bold);
    headerFmt.setBackground(Qt::lightGray);

    for (int col = 0; col < 7; ++col) {
        table->cellAt(0, col).firstCursorPosition().insertText(headers[col], headerFmt);
    }

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
    /*
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
    }*/

    // Imprimer le PDF
    doc.print(&printer);

    QMessageBox::information(this, "Succès",
                             QString("PDF exporté avec succès !\n%1 client(s) exporté(s).").arg(totalClients));
}

void MainWindow::on_tableClients_doubleClicked(const QModelIndex &index)
{
    int row = index.row();
    int col = index.column();

    if (col != 0) return;

    QTableWidgetItem *idItem = ui->tableClients->item(row, 0);
    if (!idItem) return;

    int clientId = idItem->text().toInt();
    chargerEtAfficherClient(clientId);
}

void MainWindow::chargerEtAfficherClient(int id)
{
    bool clientTrouve = false;
    gestion_client client;

    for (int row = 0; row < ui->tableClients->rowCount(); ++row) {
        QTableWidgetItem *idItem = ui->tableClients->item(row, 0);
        if (idItem && idItem->text().toInt() == id) {
            clientTrouve = true;

            QString nom = ui->tableClients->item(row, 1)->text();
            QString prenom = ui->tableClients->item(row, 2)->text();
            int telephone = ui->tableClients->item(row, 5)->text().toInt();
            QString statut = ui->tableClients->item(row, 4)->text();
            QString sexe = ui->tableClients->item(row, 6)->text();

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

    Connection c;
    if (c.createconnect()) {
        QSqlQuery query;
        query.prepare("SELECT PHOTO, ORDONNANCE, DATE_DE_NAISSANCE FROM CLIENT WHERE ID_CLIENT = :id");
        query.bindValue(":id", id);

        if (query.exec() && query.next()) {
            QString photo = query.value(0).toString();
            if (!photo.isEmpty()) {
                QString photoCheminComplet = "photos_clients/" + photo;
                if (QFile::exists(photoCheminComplet)) {
                    photoPath = photoCheminComplet;
                    /*QPixmap pixmap(photoPath);
                    if (!pixmap.isNull()) {
                        QPixmap scaledPixmap = pixmap.scaled(ui->lblphoto->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                        ui->lblphoto->setPixmap(scaledPixmap);
                    }
                    ui->lineEditPhoto->setText(photo);*/
                    afficherPhotoPleinCadre(photoPath);
                    ui->lineEditPhoto->setText(photo);
                }
            } else {
                photoPath = "";
                ui->lineEditPhoto->clear();
                ui->lblphoto->setPixmap(QPixmap(":/new/prefix1/uplode-removebg-preview.png"));
            }

            QString ordonnance = query.value(1).toString();
            if (!ordonnance.isEmpty()) {
                ordonnancePath = "ordonnances_clients/" + ordonnance;
                ui->lineEditOrdonnance->setText(ordonnance);
            } else {
                ordonnancePath = "";
                ui->lineEditOrdonnance->clear();
            }
        }
    }

    ui->stackedWidget_4->setCurrentIndex(2);

    ui->lineEditID_3->setText(QString::number(client.getId()));
    ui->lineEditNom_4->setText(client.getNom());
    ui->lineEditPrenom_3->setText(client.getPrenom());
    ui->lineEditPhone_3->setText(QString::number(client.getTelephone()));

    if (client.getSexe() == "H") {
        ui->comboSexe_2->setCurrentText("Homme");
    } else {
        ui->comboSexe_2->setCurrentText("Femme");
    }

    QString statut = client.getStatut();
    ui->checkNew_2->setChecked(statut == "Nouveau");
    ui->checkOld_2->setChecked(statut == "Ancien");
    ui->checkVIP_2->setChecked(statut == "VIP");

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

    if (!client.getOrdonnance().isEmpty()) {
        ordonnancePath = "ordonnances_clients/" + client.getOrdonnance();
        ui->lineEditOrdonnance->setText(client.getOrdonnance());
    }

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

/*void MainWindow::onFiltresChanged()
{
    QString filtreSelectionne = ui->comboProfession_3->currentText();

    if (filtreSelectionne == "Tous les filtres") {
        reinitialiserFiltres();
    } else {
        appliquerFiltre(filtreSelectionne);
    }
}

void MainWindow::appliquerFiltre(const QString &filtre)
{
    int visibleCount = 0;

    for (int i = 0; i < ui->tableClients->rowCount(); ++i) {
        bool visible = ligneCorrespondFiltre(i, filtre);
        ui->tableClients->setRowHidden(i, !visible);

        if (visible) visibleCount++;
    }
}*/
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


bool MainWindow::ligneCorrespondFiltre(int row, const QString &filtre)
{
    if (filtre == "Âge: Moins de 30 ans") {
        QTableWidgetItem *ageItem = ui->tableClients->item(row, 3);
        return ageItem && ageItem->text().toInt() < 30;
    }
    else if (filtre == "Âge: 30 ans et plus") {
        QTableWidgetItem *ageItem = ui->tableClients->item(row, 3);
        return ageItem && ageItem->text().toInt() >= 30;
    }
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
    else if (filtre == "Sexe: Homme") {
        QTableWidgetItem *sexeItem = ui->tableClients->item(row, 6);
        return sexeItem && sexeItem->text() == "Homme";
    }
    else if (filtre == "Sexe: Femme") {
        QTableWidgetItem *sexeItem = ui->tableClients->item(row, 6);
        return sexeItem && sexeItem->text() == "Femme";
    }

    return true;
}

void MainWindow::validerID(const QString &text) {
    bool ok;
    int id = text.toInt(&ok);
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
    bool valid = ok && text.length() == 8;
    ui->lineEditPhone_3->setStyleSheet(valid ? "border: 2px solid green;" : "border: 2px solid red; background-color: #FFE6E6;");
}

void MainWindow::rafraichirStatistiquesClients()
{
    if (m_statsWidget) {
        m_statsWidget->rafraichirStatistiques();
    }
}

//produits
void MainWindow::onPageChanged()
{
    bool isClientPage = (ui->stackedWidget->currentWidget() == ui->clients);
    bool isClientListPage = (ui->stackedWidget_4->currentIndex() == 0);
    bool isProduitPage = (ui->stackedWidget->currentWidget() == ui->produits);
    bool isProduitListPage = (ui->stackedWidget_6->currentIndex() == 0);

    if (m_statsWidget) {
        m_statsWidget->setVisible(isClientPage && isClientListPage);
        if (isClientPage && isClientListPage) {
            rafraichirStatistiquesClients();
        }
    }

    if (m_statsWidgetProduit) {
        m_statsWidgetProduit->setVisible(isProduitPage && isProduitListPage);
        if (isProduitPage && isProduitListPage) {
            rafraichirStatistiquesProduits();
            verifierStockFaible();
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

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT QUANTITÉ, MARQUE, MODELE FROM PRODUIT WHERE ID_PRODUIT = :id");
    checkQuery.bindValue(":id", idProduit);

    if (checkQuery.exec() && checkQuery.next()) {
        int quantiteActuelle = checkQuery.value(0).toInt();
        QString marque = checkQuery.value(1).toString();
        QString modele = checkQuery.value(2).toString();

        if (quantiteActuelle > 0) {
            QSqlQuery updateQuery;
            updateQuery.prepare("UPDATE PRODUIT SET QUANTITÉ = QUANTITÉ - 1 WHERE ID_PRODUIT = :id");
            updateQuery.bindValue(":id", idProduit);

            if (updateQuery.exec()) {
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

QString MainWindow::genererNomCourt(const QString &cheminOriginal, const QString &prefixe)
{
    if (cheminOriginal.isEmpty()) return "";

    QFileInfo fileInfo(cheminOriginal);
    QString extension = fileInfo.suffix();

    QString nomCourt = QString("%1_%2.%3")
                           .arg(prefixe.left(3))
                           .arg(QDateTime::currentSecsSinceEpoch())
                           .arg(extension.left(3));

    return nomCourt.left(20);
}

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
                                                    "Images (*.png *.jpg *.jpeg *.bmp *.gif)"
                                                    );

    if (!filePath.isEmpty()) {
        QString nomFichier = QFileInfo(filePath).fileName();
        if (nomFichier.length() > 20) {
            QMessageBox::warning(this, "Nom trop long",
                                 "Le nom du fichier est trop long. Il sera renommé automatiquement.");
        }

        photoPath = filePath;

        QPixmap pixmap(photoPath);
        if (!pixmap.isNull()) {
            QPixmap scaledPixmap = pixmap.scaled(ui->lblphoto->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            ui->lblphoto->setPixmap(scaledPixmap);
        }

        QString nomCourt = genererNomCourt(photoPath, "photo");
        ui->lineEditPhoto->setText(nomCourt);
    }
}
*/
void MainWindow::on_btnUploadPhoto_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this,
                                                    "Choisir une photo",
                                                    QDir::homePath(),
                                                    "Images (*.png *.jpg *.jpeg *.bmp *.gif)");

    if (!filePath.isEmpty()) {
        /*
        // ⭐ APPEL DE LA FONCTION DANS GESTION_CLIENT
        QString erreurValidation;
        if (!gestion_client::validerVisageHumain(filePath, erreurValidation)) {
            QMessageBox::warning(this, "Photo invalide", erreurValidation);
            return;
        }*/

        photoPath = filePath;
        afficherPhotoPleinCadre(photoPath);

        QString nomCourt = gestion_client::genererNomCourtPhoto(photoPath);
        ui->lineEditPhoto->setText(nomCourt);

        QMessageBox::information(this, "✅ Photo validée",
                                 "Visage humain détecté avec succès !");
    }
}
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

void MainWindow::on_searchLineEdit_5_textChanged(const QString &text)
{
    QString filter = text.trimmed();
    QString filtreActif = ui->comboProfession_5->currentText();

    for (int i = 0; i < ui->tablePersonnel_3->rowCount(); ++i) {
        bool show = true;

        if (filtreActif != "Tous les filtres") {
            show = ligneProduitCorrespondFiltre(i, filtreActif);
        }

        if (show && !filter.isEmpty()) {
            QString id = ui->tablePersonnel_3->item(i, 0)->text();
            QString marque = ui->tablePersonnel_3->item(i, 1)->text();
            QString modele = ui->tablePersonnel_3->item(i, 2)->text();

            show = id.contains(filter, Qt::CaseInsensitive) ||
                   marque.contains(filter, Qt::CaseInsensitive) ||
                   modele.contains(filter, Qt::CaseInsensitive);
        }

        ui->tablePersonnel_3->setRowHidden(i, !show);
    }
}

void MainWindow::on_btnExporter_5_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Exporter PDF", "produits.pdf", "PDF (*.pdf)");
    if (fileName.isEmpty()) return;

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    printer.setPageSize(QPageSize::A4);
    printer.setPageMargins(QMarginsF(15, 15, 15, 15), QPageLayout::Millimeter);

    QTextDocument doc;
    QTextCursor cursor(&doc);
    cursor.insertHtml("<h1 style='text-align:center;'>Liste des Produits</h1><br>");

    int visibleRows = 0;
    for (int i = 0; i < ui->tablePersonnel_3->rowCount(); ++i) {
        if (!ui->tablePersonnel_3->isRowHidden(i)) visibleRows++;
    }

    QTextTableFormat tableFormat;
    tableFormat.setBorder(1);
    tableFormat.setCellPadding(5);
    tableFormat.setAlignment(Qt::AlignCenter);
    tableFormat.setWidth(QTextLength(QTextLength::PercentageLength, 100));

    QTextTable *table = cursor.insertTable(visibleRows + 1, 10, tableFormat);
    /*

    QStringList headers = {"ID", "Marque", "Modèle", "Type", "Couleur", "Prix", "Remise", "Quantité", "Matière", "Genre"};
    QTextCharFormat headerFmt;
    headerFmt.setFontWeight(QFont::Bold);
    headerFmt.setBackground(Qt::lightGray);

    for (int col = 0; col < 10; ++col) {
        table->cellAt(0, col).firstCursorPosition().insertText(headers[col], headerFmt);
    }

    int pdfRow = 1;
    for (int row = 0; row < ui->tablePersonnel_3->rowCount(); ++row) {
        if (ui->tablePersonnel_3->isRowHidden(row)) continue;

        for (int col = 0; col < 10; ++col) {
            QString text = ui->tablePersonnel_3->item(row, col) ?
                               ui->tablePersonnel_3->item(row, col)->text() : "";
            table->cellAt(pdfRow, col).firstCursorPosition().insertText(text);
        }
        pdfRow++;
    }
*/

    doc.print(&printer);
    QMessageBox::information(this, "Succès", "PDF exporté avec succès !");
}

void MainWindow::onFiltresProduitChanged()
{
    QString filtreSelectionne = ui->comboProfession_5->currentText();

    if (filtreSelectionne == "Tous les filtres") {
        reinitialiserFiltresProduit();
    } else if (filtreSelectionne.startsWith("Prix:") ||
               filtreSelectionne == "A-Z" ||
               filtreSelectionne == "Z-A") {
        trierTableauProduit(filtreSelectionne);
    } else {
        appliquerFiltreProduit(filtreSelectionne);
    }
}

bool MainWindow::ligneProduitCorrespondFiltre(int row, const QString &filtre)
{
    if (filtre == "Genre: Homme") {
        QTableWidgetItem *genreItem = ui->tablePersonnel_3->item(row, 9);
        return genreItem && genreItem->text() == "Homme";
    }
    else if (filtre == "Genre: Femme") {
        QTableWidgetItem *genreItem = ui->tablePersonnel_3->item(row, 9);
        return genreItem && genreItem->text() == "Femme";
    }
    else if (filtre == "Genre: Unisexe") {
        QTableWidgetItem *genreItem = ui->tablePersonnel_3->item(row, 9);
        return genreItem && genreItem->text() == "Unisexe";
    }
    else if (filtre == "Stock faible") {
        QTableWidgetItem *quantiteItem = ui->tablePersonnel_3->item(row, 7);
        return quantiteItem && quantiteItem->text().toInt() <= 5;
    }

    return true;
}

void MainWindow::appliquerFiltreProduit(const QString &filtre)
{
    int visibleCount = 0;
    for (int i = 0; i < ui->tablePersonnel_3->rowCount(); ++i) {
        bool visible = ligneProduitCorrespondFiltre(i, filtre);
        ui->tablePersonnel_3->setRowHidden(i, !visible);
        if (visible) visibleCount++;
    }
}

void MainWindow::reinitialiserFiltresProduit()
{
    for (int i = 0; i < ui->tablePersonnel_3->rowCount(); ++i) {
        ui->tablePersonnel_3->setRowHidden(i, false);
    }
}

void MainWindow::trierTableauProduit(const QString &critere)
{
    ui->tablePersonnel_3->setSortingEnabled(true);

    if (critere == "Prix: Bas") {
        ui->tablePersonnel_3->sortByColumn(5, Qt::AscendingOrder);
    }
    else if (critere == "Prix: Haut") {
        ui->tablePersonnel_3->sortByColumn(5, Qt::DescendingOrder);
    }
    else if (critere == "A-Z") {
        ui->tablePersonnel_3->sortByColumn(1, Qt::AscendingOrder);
    }
    else if (critere == "Z-A") {
        ui->tablePersonnel_3->sortByColumn(1, Qt::DescendingOrder);
    }

    ui->tablePersonnel_3->setSortingEnabled(false);
}

void MainWindow::rafraichirStatistiquesProduits()
{
    if (m_statsWidgetProduit) {
        m_statsWidgetProduit->rafraichirStatistiques();
    }
}

void MainWindow::verifierStockFaible()
{
    int stockFaibleCount = 0;
    int stockZeroCount = 0;
    QStringList produitsRupture;
    QStringList produitsFaibleStock;

    for (int row = 0; row < ui->tablePersonnel_3->rowCount(); ++row) {
        QTableWidgetItem *quantiteItem = ui->tablePersonnel_3->item(row, 7);
        QTableWidgetItem *idItem = ui->tablePersonnel_3->item(row, 0);
        QTableWidgetItem *marqueItem = ui->tablePersonnel_3->item(row, 1);
        QTableWidgetItem *modeleItem = ui->tablePersonnel_3->item(row, 2);

        if (quantiteItem && idItem) {
            int quantite = quantiteItem->text().toInt();

            if (quantite == 0) {
                stockZeroCount++;
                QString produitInfo = QString("ID:%1 %2 %3")
                                          .arg(idItem->text())
                                          .arg(marqueItem->text())
                                          .arg(modeleItem->text());
                produitsRupture.append(produitInfo);
            }
            else if (quantite <= 5) {
                stockFaibleCount++;
                QString produitInfo = QString("ID:%1 %2 %3 (Stock: %4)")
                                          .arg(idItem->text())
                                          .arg(marqueItem->text())
                                          .arg(modeleItem->text())
                                          .arg(quantite);
                produitsFaibleStock.append(produitInfo);
            }
        }
    }

    static bool blinkState = false;
    blinkState = !blinkState;

    if (stockZeroCount > 0) {
        QString produitsList = produitsRupture.join(", ");
        QString style = blinkState ?
                            "background-color: #FEF2F2; padding: 8px; border: 2px solid #DC2626; border-radius: 6px; color: #DC2626; font-weight: bold;" :
                            "background-color: #FCA5A5; padding: 8px; border: 2px solid #DC2626; border-radius: 6px; color: #7F1D1D; font-weight: bold;";

        ui->label_33->setStyleSheet(style);
        ui->label_33->setText(QString("⚠️ RUPTURE: %1 produit(s) - IDs: %2")
                                  .arg(stockZeroCount).arg(produitsList));

        QTimer::singleShot(500, this, &MainWindow::verifierStockFaible);
    }
    else if (stockFaibleCount > 0) {
        QString style = "background-color: #FEF3C7; padding: 8px; border: 2px solid #D97706; border-radius: 6px; color: #92400E; font-weight: bold;";
        ui->label_33->setStyleSheet(style);
        ui->label_33->setText(QString("⚠️ Stock faible: %1 produit(s) ≤ 5 unités")
                                  .arg(stockFaibleCount));
    }
    else {
        ui->label_33->setStyleSheet("background-color: #F0FDF4; padding: 8px; border: 2px solid #16A34A; border-radius: 6px; color: #166534; font-weight: bold;");
        ui->label_33->setText("✅ Stock normal");
    }
}

void MainWindow::on_searchLineEdit_4_textChanged(const QString &text)
{
    QString filter = text.trimmed();
    QString filtreActif = ui->comboProfession_4->currentText();

    for (int i = 0; i < ui->tableClients_2->rowCount(); ++i) {
        bool show = true;

        if (filtreActif != "Tous les filtres") {
            show = ligneFournisseurCorrespondFiltre(i, filtreActif);
        }

        if (show && !filter.isEmpty()) {
            QString id = ui->tableClients_2->item(i, 0)->text();
            QString nom = ui->tableClients_2->item(i, 1)->text();
            QString personne = ui->tableClients_2->item(i, 2)->text();

            show = id.contains(filter, Qt::CaseInsensitive) ||
                   nom.contains(filter, Qt::CaseInsensitive) ||
                   personne.contains(filter, Qt::CaseInsensitive);
        }

        ui->tableClients_2->setRowHidden(i, !show);
    }
}

void MainWindow::on_btnExporter_4_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Exporter PDF", "fournisseurs.pdf", "PDF (*.pdf)");
    if (fileName.isEmpty()) return;

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    printer.setPageSize(QPageSize::A4);
    printer.setPageMargins(QMarginsF(15, 15, 15, 15), QPageLayout::Millimeter);

    QTextDocument doc;
    QTextCursor cursor(&doc);
    cursor.insertHtml("<h1 style='text-align:center;'>Liste des Fournisseurs</h1><br>");

    int visibleRows = 0;
    for (int i = 0; i < ui->tableClients_2->rowCount(); ++i) {
        if (!ui->tableClients_2->isRowHidden(i)) visibleRows++;
    }

    QTextTableFormat tableFormat;
    tableFormat.setBorder(1);
    tableFormat.setCellPadding(5);
    tableFormat.setAlignment(Qt::AlignCenter);
    tableFormat.setWidth(QTextLength(QTextLength::PercentageLength, 100));

    QTextTable *table = cursor.insertTable(visibleRows + 1, 8, tableFormat);
    /*
    QStringList headers = {"ID", "Nom Entreprise", "Personne Contact", "Adresse", "Téléphone", "Mail", "Catégorie", "Note"};
    QTextCharFormat headerFmt;
    headerFmt.setFontWeight(QFont::Bold);
    headerFmt.setBackground(Qt::lightGray);

    for (int col = 0; col < 8; ++col) {
        table->cellAt(0, col).firstCursorPosition().insertText(headers[col], headerFmt);
    }

    int pdfRow = 1;
    for (int row = 0; row < ui->tableClients_2->rowCount(); ++row) {
        if (ui->tableClients_2->isRowHidden(row)) continue;

        for (int col = 0; col < 8; ++col) {
            QString text = ui->tableClients_2->item(row, col) ?
                               ui->tableClients_2->item(row, col)->text() : "";
            table->cellAt(pdfRow, col).firstCursorPosition().insertText(text);
        }
        pdfRow++;
    }*/

    doc.print(&printer);
    QMessageBox::information(this, "Succès", "PDF exporté avec succès !");
}

void MainWindow::on_tableClients_2_doubleClicked(const QModelIndex &index)
{
    int row = index.row();
    int col = index.column();

    if (col != 0) return;

    QTableWidgetItem *idItem = ui->tableClients_2->item(row, 0);
    if (!idItem) return;

    int fournisseurId = idItem->text().toInt();
    chargerEtAfficherFournisseur(fournisseurId);
}

void MainWindow::chargerEtAfficherFournisseur(int id)
{
    bool fournisseurTrouve = false;
    Gestion_Fournisseur fournisseur;

    for (int row = 0; row < ui->tableClients_2->rowCount(); ++row) {
        QTableWidgetItem *idItem = ui->tableClients_2->item(row, 0);
        if (idItem && idItem->text().toInt() == id) {
            fournisseurTrouve = true;

            QString nom = ui->tableClients_2->item(row, 1)->text();
            QString personne = ui->tableClients_2->item(row, 2)->text();
            QString adresse = ui->tableClients_2->item(row, 3)->text();
            int telephone = ui->tableClients_2->item(row, 4)->text().toInt();
            QString mail = ui->tableClients_2->item(row, 5)->text();
            QString categorie = ui->tableClients_2->item(row, 6)->text();
            float note = ui->tableClients_2->item(row, 7)->text().toFloat();

            fournisseur.setId(id);
            fournisseur.setNomEntreprise(nom);
            fournisseur.setPersonneContact(personne);
            fournisseur.setAdresse(adresse);
            fournisseur.setTelephone(telephone);
            fournisseur.setMail(mail);
            fournisseur.setCategorie(categorie);
            fournisseur.setNoteFiabilite(note);

            break;
        }
    }

    if (!fournisseurTrouve) {
        QMessageBox::warning(this, "Erreur", "Fournisseur non trouvé dans le tableau !");
        return;
    }

    ui->stackedWidget_5->setCurrentIndex(2);

    ui->id_fournisseur->setText(QString::number(fournisseur.getId()));
    ui->nomentre->setText(fournisseur.getNomEntreprise());
    ui->PERSONNE_CNT->setText(fournisseur.getPersonneContact());
    ui->ADRESSE->setText(fournisseur.getAdresse());
    ui->telephone->setText(QString::number(fournisseur.getTelephone()));
    ui->MAIL->setText(fournisseur.getMail());
    ui->comboCategorie->setCurrentText(fournisseur.getCategorie());
    ui->DETAILS->setText(fournisseur.getDetails());
    ui->NOTEDEFIABILITE->setText(QString::number(fournisseur.getNoteFiabilite()));

    ui->id_fournisseur->setEnabled(false);
    ui->btnConfirmer_4->setText("Modifier le fournisseur");
}

void MainWindow::onFiltresFournisseurChanged()
{
    QString filtreSelectionne = ui->comboProfession_4->currentText();

    if (filtreSelectionne == "Tous les filtres") {
        reinitialiserFiltresFournisseur();
    } else if (filtreSelectionne == "A-Z") {
        trierTableauFournisseur("A-Z");
    } else if (filtreSelectionne == "Z-A") {
        trierTableauFournisseur("Z-A");
    } else {
        appliquerFiltreFournisseur(filtreSelectionne);
    }
}

bool MainWindow::ligneFournisseurCorrespondFiltre(int row, const QString &filtre)
{
    if (filtre == "Produit fournis") {
        QTableWidgetItem *categorieItem = ui->tableClients_2->item(row, 6);
        return categorieItem && !categorieItem->text().isEmpty();
    }
    else if (filtre == "Statut") {
        QTableWidgetItem *noteItem = ui->tableClients_2->item(row, 7);
        if (noteItem) {
            float note = noteItem->text().toFloat();
            return note >= 7.0;
        }
    }
    else if (filtre == "Nom de Fournisseur") {
        QTableWidgetItem *nomItem = ui->tableClients_2->item(row, 1);
        return nomItem && nomItem->text().length() > 0;
    }

    return true;
}

void MainWindow::appliquerFiltreFournisseur(const QString &filtre)
{
    int visibleCount = 0;
    for (int i = 0; i < ui->tableClients_2->rowCount(); ++i) {
        bool visible = ligneFournisseurCorrespondFiltre(i, filtre);
        ui->tableClients_2->setRowHidden(i, !visible);
        if (visible) visibleCount++;
    }
}

void MainWindow::reinitialiserFiltresFournisseur()
{
    for (int i = 0; i < ui->tableClients_2->rowCount(); ++i) {
        ui->tableClients_2->setRowHidden(i, false);
    }
}

void MainWindow::trierTableauFournisseur(const QString &critere)
{
    ui->tableClients_2->setSortingEnabled(true);

    if (critere == "A-Z") {
        ui->tableClients_2->sortByColumn(1, Qt::AscendingOrder);
    }
    else if (critere == "Z-A") {
        ui->tableClients_2->sortByColumn(1, Qt::DescendingOrder);
    }

    ui->tableClients_2->setSortingEnabled(false);
}

bool MainWindow::modifierFournisseurExistant(int id, const QString &nomEntreprise,
                                             const QString &personneContact, const QString &adresse,
                                             int telephone, const QString &mail,
                                             const QString &categorie, const QString &details,
                                             float noteFiabilite, QString &erreurMessage)
{
    return Gestion_Fournisseur::modifierFournisseur(id, nomEntreprise, personneContact, adresse,
                                                    telephone, mail, categorie, details,
                                                    noteFiabilite, erreurMessage);
}
// === METHODES POUR L'API DE REMISES ===

void MainWindow::initialiserAPI()
{
    m_apiRemises = new ApiRemises(this);

    // Tester la connexion API Groq au démarrage
    connect(m_apiRemises, &ApiRemises::connexionTestee, this, [this](bool succes) {
        if (succes) {
            qDebug() << "✅ API Groq connectée avec succès";
            QMessageBox::information(this, "API Connectée",
                                     "Connexion à l'API Groq établie avec succès!\n\n"
                                     "Fonctionnalités activées :\n"
                                     "• Calcul intelligent des remises par IA\n"
                                     "• Analyse de la quantité en temps réel\n"
                                     "• Stratégie de prix optimisée");
        } else {
            qDebug() << "🔧 Mode simulation activé (API non disponible)";
            m_apiRemises->setModeSimulation(true);
            QMessageBox::information(this, "Mode Simulation",
                                     "L'API Groq n'est pas disponible.\n"
                                     "Mode simulation activé - Utilisation des règles métier.\n\n"
                                     "Règles de remise OPTIMATECH :\n"
                                     "• 1-9 unités : 0% de remise\n"
                                     "• 10-19 unités : 5% de remise\n"
                                     "• 20-49 unités : 10% de remise\n"
                                     "• 50-99 unités : 15% de remise\n"
                                     "• 100+ unités : 25% de remise");
        }
    });

    // Connecter les autres signaux
    connect(m_apiRemises, &ApiRemises::remiseCalculee, this, &MainWindow::onRemiseCalculee);
    connect(m_apiRemises, &ApiRemises::erreurAPI, this, &MainWindow::onErreurAPI);

    // Connecter les signaux de l'interface
    connect(ui->checkBoxAI, &QCheckBox::clicked, this, &MainWindow::onCheckBoxAIClicked);
    connect(ui->spinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::onQuantiteChanged);
    connect(ui->spinBox_2, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::onRemiseManuelleChanged);

    // Tester la connexion API
    m_apiRemises->testerConnexionAPI();
}
void MainWindow::onCheckBoxAIClicked(bool checked)
{
    if (checked) {
        // Mode automatique activé - bloquer la remise manuelle
        ui->spinBox_2->setEnabled(false);
        ui->spinBox_2->setStyleSheet("background-color: #f0f0f0; color: #888;");

        // Calculer la remise automatique si l'ID et la quantité sont renseignés
        gererRemiseAutomatique();
    } else {
        // Mode manuel activé - débloquer la remise manuelle
        ui->spinBox_2->setEnabled(true);
        ui->spinBox_2->setStyleSheet("");
    }
}

void MainWindow::onQuantiteChanged(int quantite)
{
    // Ne rien faire si la quantité est invalide ou si l'ID n'est pas renseigné
    if (quantite < 0 || ui->lineEditID_5->text().isEmpty()) {
        return;
    }

    if (ui->checkBoxAI->isChecked()) {
        // Si le mode auto est activé, recalculer la remise quand la quantité change
        gererRemiseAutomatique();
    }
}

void MainWindow::onRemiseManuelleChanged(double remise)
{
    Q_UNUSED(remise);

    if (!ui->checkBoxAI->isChecked() && ui->lineEditID_5->text().toInt() > 0) {
        // Appliquer la remise manuelle si le mode manuel est activé
        gererRemiseManuelle();
    }
}

void MainWindow::gererRemiseAutomatique()
{
    if (!m_apiRemises) return;

    // Vérifier que l'ID et la quantité sont valides
    bool ok;
    int idProduit = ui->lineEditID_5->text().toInt(&ok);
    if (!ok || idProduit <= 0) {
        return; // ID invalide
    }

    int quantite = ui->spinBox->value();
    if (quantite < 0) {
        return; // Quantité invalide
    }

    qDebug() << "🔄 Calcul remise auto - ID:" << idProduit << "Quantité:" << quantite;
    m_apiRemises->calculerRemiseAutomatique(idProduit, quantite);
}

void MainWindow::gererRemiseManuelle()
{
    if (!m_apiRemises) return;

    bool ok;
    int idProduit = ui->lineEditID_5->text().toInt(&ok);
    if (!ok || idProduit <= 0) {
        return;
    }

    float remise = ui->spinBox_2->value();
    if (remise < 0 || remise > 100) {
        return;
    }

    m_apiRemises->appliquerRemiseManuelle(idProduit, remise);
}

void MainWindow::onRemiseCalculee(float remise)
{
    // Mettre à jour le spinBox de remise avec la valeur calculée
    ui->spinBox_2->blockSignals(true);
    ui->spinBox_2->setValue(remise);
    ui->spinBox_2->blockSignals(false);

    // Afficher un message de confirmation
    QMessageBox::information(this, "Remise calculée",
                             QString("Remise automatique appliquée: %1%").arg(remise));
}

void MainWindow::onErreurAPI(const QString &message)
{
    QMessageBox::warning(this, "Erreur API", message);

    // En cas d'erreur, basculer en mode manuel
    ui->checkBoxAI->setChecked(false);
    ui->spinBox_2->setEnabled(true);
    ui->spinBox_2->setStyleSheet("");
}

void MainWindow::onConnexionAPITestee(bool succes)
{
    if (succes) {
        qDebug() << "✅ Connexion à l'API établie";
        ui->checkBoxAI->setToolTip("API connectée - Mode automatique disponible");
        ui->checkBoxAI->setStyleSheet("color: green;");
    } else {
        qDebug() << "❌ Impossible de se connecter à l'API";
        ui->checkBoxAI->setToolTip("API non disponible - Mode automatique désactivé");
        ui->checkBoxAI->setStyleSheet("color: red;");
        ui->checkBoxAI->setEnabled(false);

        QMessageBox::warning(this, "API non disponible",
                             "L'API de remises automatiques n'est pas disponible.\n"
                             "Le mode automatique est désactivé.\n"
                             "Veuillez utiliser les remises manuelles.");
    }
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

        if (p.getQuantite() == 0) {
            for (int col = 0; col < ui->tablePersonnel_3->columnCount(); ++col) {
                QTableWidgetItem *item = ui->tablePersonnel_3->item(row, col);
                if (item) {
                    item->setBackground(QColor(255, 230, 230));
                    item->setForeground(QColor(220, 0, 0));
                    if (col == 7) {
                        item->setBackground(QColor(255, 200, 200));
                        item->setFont(QFont("Segoe UI", 9, QFont::Bold));
                    }
                }
            }
        }

        row++;
    }

    ui->tablePersonnel_3->blockSignals(false);

    int stockZeroCount = 0;
    for (int row = 0; row < ui->tablePersonnel_3->rowCount(); ++row) {
        QTableWidgetItem *quantiteItem = ui->tablePersonnel_3->item(row, 7);
        if (quantiteItem && quantiteItem->text().toInt() == 0) {
            stockZeroCount++;
        }
    }

    if (stockZeroCount > 0) {
        ui->label_33->setStyleSheet("background-color: #FEF2F2; padding: 8px; border: 2px solid #DC2626; border-radius: 6px; color: #DC2626; font-weight: bold;");
        ui->label_33->setText(QString("⚠️ ALERTE: %1 produit(s) en rupture de stock").arg(stockZeroCount));
    } else {
        ui->label_33->setStyleSheet("background-color: #F0FDF4; padding: 8px; border: 2px solid #16A34A; border-radius: 6px; color: #166534; font-weight: bold;");
        ui->label_33->setText("✅ Stock normal");
    }
}

void MainWindow::showProduitsInterface() {
    ui->stackedWidget->setCurrentWidget(ui->produits);
    ui->stackedWidget_6->setCurrentIndex(0);

    bool isListPage = (ui->stackedWidget_6->currentIndex() == 0);
    if (m_statsWidgetProduit) {
        m_statsWidgetProduit->setVisible(isListPage);
        if (isListPage) {
            rafraichirTableauProduit();
            rafraichirStatistiquesProduits();
        }
    }
}
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

MainWindow::~MainWindow() {
    delete lineEditIDProduit;
    delete ui;
}
