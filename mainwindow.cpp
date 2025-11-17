#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include "gestion_client.h"
#include "gestion_fournisseur.h"
#include "gestion_locaux.h"
#include "gestion_produit.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QFileDialog>
#include <QPrinter>
#include <QTextDocument>
#include <QTextTable>
#include <QTextCursor>
#include <QTextTableFormat>
#include <QDate>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

//===================== TABLE LOCAUX ITEM CHANGED =====================
void MainWindow::onTableLocauxItemChanged(QTableWidgetItem *item)
{
    if (!item || item->column() == 0 || item->column() == 7) return;

    int row = item->row();
    int col = item->column();
    int id = ui->locaux->item(row, 0)->text().toInt();
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

//===================== TABLE FOURNISSEUR ITEM CHANGED =====================
void MainWindow::onTableFournisseurItemChanged(QTableWidgetItem *item)
{
    if (!item || item->column() == 0 || item->column() == 8) return;

    int row = item->row();
    int col = item->column();
    int id = ui->fournisseur->item(row, 0)->text().toInt();
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

//===================== TABLE PRODUIT ITEM CHANGED =====================
void MainWindow::onTableProduitItemChanged(QTableWidgetItem *item)
{
    if (!item || item->column() == 0 || item->column() == 10) return;

    int row = item->row();
    int col = item->column();
    int id = ui->produit->item(row, 0)->text().toInt();
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

//===================== TABLE CLIENTS SEARCH =====================
void MainWindow::on_searchLineEdit_3_textChanged(const QString &text)
{
    QString filter = text.trimmed();
    QString filtreActif = ui->comboProfession_3->currentText();

    for (int i = 0; i < ui->clients->rowCount(); ++i) {
        bool show = true;
        if (filtreActif != "Tous les filtres") show = ligneCorrespondFiltre(i, filtreActif);

        if (show && !filter.isEmpty()) {
            QString id = ui->clients->item(i, 0)->text();
            QString nom = ui->clients->item(i, 1)->text();
            QString prenom = ui->clients->item(i, 2)->text();
            show = id.contains(filter, Qt::CaseInsensitive) ||
                   nom.contains(filter, Qt::CaseInsensitive) ||
                   prenom.contains(filter, Qt::CaseInsensitive);
        }

        ui->clients->setRowHidden(i, !show);
    }
}

//===================== PDF EXPORT =====================
void MainWindow::on_btnExporter_3_clicked()
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
    for (int i = 0; i < ui->clients->rowCount(); ++i)
        if (!ui->clients->isRowHidden(i)) visibleRows++;

    QTextTableFormat tableFormat;
    tableFormat.setBorder(1);
    tableFormat.setCellPadding(5);
    tableFormat.setAlignment(Qt::AlignCenter);
    tableFormat.setWidth(QTextLength(QTextLength::PercentageLength, 100));

    QTextTable *table = cursor.insertTable(visibleRows + 1, 7, tableFormat);
    QStringList headers = {"ID", "Nom", "Prénom", "Âge", "Statut", "Téléphone", "Sexe"};
    QTextCharFormat headerFmt; headerFmt.setFontWeight(QFont::Bold); headerFmt.setBackground(Qt::lightGray);

    for (int col = 0; col < 7; ++col) table->cellAt(0, col).firstCursorPosition().insertText(headers[col], headerFmt);

    int pdfRow = 1;
    for (int row = 0; row < ui->clients->rowCount(); ++row) {
        if (ui->clients->isRowHidden(row)) continue;
        for (int col = 0; col < 7; ++col) {
            QString text = ui->clients->item(row, col) ? ui->clients->item(row, col)->text() : "";
            table->cellAt(pdfRow, col).firstCursorPosition().insertText(text);
        }
        pdfRow++;
    }

    doc.print(&printer);
    QMessageBox::information(this, "Succès", "PDF exporté avec succès !");
}

//===================== CLIENT DOUBLE CLICK =====================
void MainWindow::on_tableClients_doubleClicked(const QModelIndex &index)
{
    int row = index.row();
    int col = index.column();
    if (col != 0) return;

    int clientId = ui->clients->item(row, 0)->text().toInt();
    chargerEtAfficherClient(clientId);
}

void MainWindow::chargerEtAfficherClient(int id)
{
    bool clientTrouve = false;
    gestion_client client;

    for (int row = 0; row < ui->clients->rowCount(); ++row) {
        QTableWidgetItem *idItem = ui->clients->item(row, 0);
        if (idItem && idItem->text().toInt() == id) {
            clientTrouve = true;
            client.setId(id);
            client.setNom(ui->clients->item(row, 1)->text());
            client.setPrenom(ui->clients->item(row, 2)->text());
            client.setTelephone(ui->clients->item(row, 5)->text().toInt());
            client.setStatut(ui->clients->item(row, 4)->text());
            client.setSexe(ui->clients->item(row, 6)->text());
            break;
        }
    }

    if (!clientTrouve) {
        QMessageBox::warning(this, "Erreur", "Client non trouvé dans le tableau !");
        return;
    }

    ui->stackedWidget_4->setCurrentIndex(2);
    ui->lineEditID_3->setText(QString::number(client.getId()));
    ui->lineEditNom_4->setText(client.getNom());
    ui->lineEditPrenom_3->setText(client.getPrenom());
    ui->lineEditPhone_3->setText(QString::number(client.getTelephone()));

    if (client.getSexe() == "H") ui->comboSexe_2->setCurrentText("Homme");
    else ui->comboSexe_2->setCurrentText("Femme");

    QString statut = client.getStatut();
    ui->checkNew_2->setChecked(statut == "Nouveau");
    ui->checkOld_2->setChecked(statut == "Ancien");
    ui->checkVIP_2->setChecked(statut == "VIP");

    ui->lineEditID_3->setEnabled(false);
    ui->btnConfirmer_3->setText("Modifier le client");
}

//===================== VALIDATION =====================
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
    bool valid = text.toInt(&ok) && text.length() == 8;
    ui->lineEditPhone_3->setStyleSheet(valid ? "border: 2px solid green;" : "border: 2px solid red; background-color: #FFE6E6;");
}

MainWindow::~MainWindow() {
    delete ui;
}
