#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gestion_fournisseur.h"
#include <QMessageBox>
#include <QtCharts>
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QUrl>
#include <QCoreApplication>
#include <QFileDialog>
#include <QDir>
#include <QDateTime>
#include <QRegularExpression>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    remplirTableFournisseurs();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnAjouterClient_7_clicked()
{
    QString id = ui->id->text();
    QString nom = ui->nom_entreprise->text();
    QString email = ui->email_entreprise->text();
    QString tel = ui->tel->text();
    QString categorie = ui->comboCategorie->currentText(); // ✔ CORRECTION
    QString adresse = ui->adresse->text();

    Gestion_Fournisseur fournisseur(id, nom, email, tel, categorie, adresse);
    if (fournisseur.ajouter_fournisseurs())
    {
                QMessageBox::information(this, "success", "ajout effectue avec success");

        ui->id->clear();
        ui->nom_entreprise->clear();
        ui->email_entreprise->clear();
        ui->tel->clear();
      //  ui->categorie->clear();
        ui->adresse->clear();
    }   
    else
    {
        QMessageBox::critical(this, "Erreur", "Erreur lors de l'ajout du fournisseur.");
    }   
    
}


void MainWindow::on_btnConfirmer_4_clicked()
{
    QString id = ui->id->text().trimmed();
    QString nom = ui->nom_entreprise->text().trimmed();
    QString email = ui->email_entreprise->text().trimmed();
    QString tel = ui->tel->text().trimmed();
    QString categorie = ui->comboCategorie->currentText(); // ✔ CORRECTION
    QString adresse = ui->adresse->text().trimmed();

    // ========== VALIDATION DES CHAMPS ==========
    
    // 1. Vérifier que tous les champs sont remplis
    if (id.isEmpty()) {
        QMessageBox::warning(this, "Champ obligatoire", "Le champ ID est obligatoire !");
        ui->id->setFocus();
        return;
    }
    
    if (nom.isEmpty()) {
        QMessageBox::warning(this, "Champ obligatoire", "Le champ Nom est obligatoire !");
        ui->nom_entreprise->setFocus();
        return;
    }
    
    if (email.isEmpty()) {
        QMessageBox::warning(this, "Champ obligatoire", "Le champ Email est obligatoire !");
        ui->email_entreprise->setFocus();
        return;
    }
    
    if (tel.isEmpty()) {
        QMessageBox::warning(this, "Champ obligatoire", "Le champ Téléphone est obligatoire !");
        ui->tel->setFocus();
        return;
    }
    
    if (adresse.isEmpty()) {
        QMessageBox::warning(this, "Champ obligatoire", "Le champ Adresse est obligatoire !");
        ui->adresse->setFocus();
        return;
    }
    
    // 2. Vérifier que le nom a au moins 3 caractères
    if (nom.length() < 3) {
        QMessageBox::warning(this, "Validation", "Le nom doit contenir au moins 3 caractères !");
        ui->nom_entreprise->setFocus();
        return;
    }
    
    // 3. Vérifier que l'adresse a au moins 3 caractères
    if (adresse.length() < 3) {
        QMessageBox::warning(this, "Validation", "L'adresse doit contenir au moins 3 caractères !");
        ui->adresse->setFocus();
        return;
    }
    
    // 4. Vérifier que le téléphone contient exactement 8 chiffres
    QRegularExpression telRegex("^\\d{8}$");
    if (!telRegex.match(tel).hasMatch()) {
        QMessageBox::warning(this, "Validation", "Le téléphone doit contenir exactement 8 chiffres !");
        ui->tel->setFocus();
        return;
    }
    
    // 5. Vérifier que l'email est au format valide
    QRegularExpression emailRegex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    if (!emailRegex.match(email).hasMatch()) {
        QMessageBox::warning(this, "Validation", "L'email doit être au format valide (exemple@domaine.com) !");
        ui->email_entreprise->setFocus();
        return;
    }
    
    // ========== FIN VALIDATION ==========

    Gestion_Fournisseur fournisseur(id, nom, email, tel, categorie, adresse);
    if (fournisseur.ajouter_fournisseurs())
    {
        QMessageBox::information(this, "Succès", "Fournisseur ajouté avec succès !");

        ui->id->clear();
        ui->nom_entreprise->clear();
        ui->email_entreprise->clear();
        ui->tel->clear();
        //  ui->categorie->clear();
        ui->adresse->clear();
        
        // Retourner à la liste (page_11)
        ui->stackedWidget_5->setCurrentWidget(ui->page_11);
        QString contenu = "Nouvel enregistrement fournisseur confirmé.\n"
                          "Entreprise: " + nom + "\n"
                                  "ID: " + id + "\n"
                                 "Catégorie: " + categorie + ".";
       //THIS IS SENDING MESSAGES METIER
        envoyerSMS("+21658156718", contenu);
         // Rafraîchir la liste si nécessaire
        remplirTableFournisseurs();
    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Erreur lors de l'ajout du fournisseur.");
    }
}


void MainWindow::on_btnAnnuler_4_clicked()
{
    ui->id->clear();
    ui->nom_entreprise->clear();
    ui->email_entreprise->clear();
    ui->tel->clear();
    //  ui->categorie->clear();
    ui->adresse->clear();
    
    // Retourner à la liste (page_11)
    ui->stackedWidget_5->setCurrentWidget(ui->page_11);
}



void MainWindow::on_btnListeClients_6_clicked()
{
    Gestion_Fournisseur f; // ou utiliser l'objet déjà existant si tu en as un
    QSqlQueryModel *model = f.afficher();

    // Effacer l'ancien contenu
    ui->tableClients_2->clear();
    ui->tableClients_2->setRowCount(model->rowCount());
    ui->tableClients_2->setColumnCount(model->columnCount());

    // Définir les en-têtes
    for(int c = 0; c < model->columnCount(); ++c) {
        ui->tableClients_2->setHorizontalHeaderItem(c, new QTableWidgetItem(model->headerData(c, Qt::Horizontal).toString()));
    }

    // Remplir les données
    for(int r = 0; r < model->rowCount(); ++r) {
        for(int c = 0; c < model->columnCount(); ++c) {
            QString data = model->data(model->index(r, c)).toString();
            ui->tableClients_2->setItem(r, c, new QTableWidgetItem(data));
        }
    }

    // Ajuster automatiquement la largeur des colonnes au contenu
    ui->tableClients_2->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    delete model; // libérer la mémoire
}
void MainWindow::remplirTableFournisseurs()
{
    Gestion_Fournisseur f; // objet pour gérer les fournisseurs
    QSqlQueryModel *model = f.afficher();

    // Effacer l'ancien contenu
    ui->tableClients_2->clear();
    ui->tableClients_2->setRowCount(model->rowCount());
    ui->tableClients_2->setColumnCount(model->columnCount());

    // Définir les en-têtes
    for(int c = 0; c < model->columnCount(); ++c) {
        ui->tableClients_2->setHorizontalHeaderItem(c, new QTableWidgetItem(model->headerData(c, Qt::Horizontal).toString()));
    }

    // Remplir les données
    for(int r = 0; r < model->rowCount(); ++r) {
        for(int c = 0; c < model->columnCount(); ++c) {
            QString data = model->data(model->index(r, c)).toString();
            ui->tableClients_2->setItem(r, c, new QTableWidgetItem(data));
        }
    }

    // Ajuster automatiquement la largeur des colonnes au contenu
    ui->tableClients_2->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    delete model;
}



void MainWindow::on_btnAjouterClient_6_clicked()
{
    // Naviguer vers la page 13 du QStackedWidget
    ui->stackedWidget_5->setCurrentWidget(ui->page_13);
}


void MainWindow::on_btnListeClients_7_clicked()
{

    // Naviguer vers la page 11 du QStackedWidget
    ui->stackedWidget_5->setCurrentWidget(ui->page_11);
    remplirTableFournisseurs();

}



void MainWindow::on_delete_2_clicked()
{
    // Récupérer l'ID depuis le QLineEdit
    QString id = ui->searchLineEdit_4->text().trimmed();

    if (id.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID à supprimer !");
        return;
    }

    Gestion_Fournisseur f;

    // Appeler la fonction de suppression
    if (f.supprimer_fournisseurs(id)) {
        // Rafraîchir le tableau après suppression
        remplirTableFournisseurs();

        // Vider le QLineEdit
        ui->searchLineEdit_4->clear();
    }
}

void MainWindow::on_btnRechercher_4_clicked()
{
    QString id = ui->searchLineEdit_4->text().trimmed();

    if (id.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID pour la recherche !");
        return;
    }

    Gestion_Fournisseur f;
    QSqlQueryModel *model = f.rechercher_fournisseur(id);

    // Effacer l'ancien contenu du tableau
    ui->tableClients_2->clear();
    ui->tableClients_2->setRowCount(model->rowCount());
    ui->tableClients_2->setColumnCount(model->columnCount());

    // Définir les en-têtes
    for(int c = 0; c < model->columnCount(); ++c) {
        ui->tableClients_2->setHorizontalHeaderItem(c, new QTableWidgetItem(model->headerData(c, Qt::Horizontal).toString()));
    }

    // Remplir les données
    for(int r = 0; r < model->rowCount(); ++r) {
        for(int c = 0; c < model->columnCount(); ++c) {
            QString data = model->data(model->index(r, c)).toString();
            ui->tableClients_2->setItem(r, c, new QTableWidgetItem(data));
        }
    }

    delete model;
}




void MainWindow::on_comboProfession_4_currentTextChanged(const QString &arg1)
{
    Gestion_Fournisseur f;
    QSqlQueryModel *model = f.trier_fournisseurs(arg1);

    // Effacer l'ancien contenu du tableau
    ui->tableClients_2->clear();
    ui->tableClients_2->setRowCount(model->rowCount());
    ui->tableClients_2->setColumnCount(model->columnCount());

    // Définir les en-têtes
    for(int c = 0; c < model->columnCount(); ++c) {
        ui->tableClients_2->setHorizontalHeaderItem(c, new QTableWidgetItem(model->headerData(c, Qt::Horizontal).toString()));
    }

    // Remplir les données
    for(int r = 0; r < model->rowCount(); ++r) {
        for(int c = 0; c < model->columnCount(); ++c) {
            QString data = model->data(model->index(r, c)).toString();
            ui->tableClients_2->setItem(r, c, new QTableWidgetItem(data));
        }
    }

    delete model;
}

void MainWindow::on_btnStatistiques_clicked()
{
    // Statistics implementation
    QSqlQuery query;
    if (!query.exec("SELECT CATEGORIE, COUNT(*) FROM FOURNISSEUR GROUP BY CATEGORIE")) {
        QMessageBox::critical(this, "Erreur de requête", query.lastError().text());
        return;
    }

    QPieSeries *series = new QPieSeries();
    bool hasData = false;
    while (query.next()) {
        hasData = true;
        QString category = query.value(0).toString();
        int count = query.value(1).toInt();
        if (category.isEmpty()) category = "Inconnu";
        series->append(category, count);
    }

    if (!hasData) {
        QMessageBox::warning(this, "Données", "Aucune donnée trouvée pour les statistiques.");
        return;
    }

    // Add percentages to labels
    for (QPieSlice *slice : series->slices()) {
        slice->setLabel(QString("%1 : %2%").arg(slice->label()).arg(100 * slice->percentage(), 0, 'f', 1));
        slice->setLabelVisible();
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques des Fournisseurs par Catégorie");
    chart->setAnimationOptions(QChart::AllAnimations);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    
    QDialog *chartDialog = new QDialog(this);
    chartDialog->setWindowTitle("Statistiques");
    chartDialog->resize(800, 600);
    
    QVBoxLayout *layout = new QVBoxLayout(chartDialog);
    layout->addWidget(chartView);
    chartDialog->setLayout(layout);
    
    chartDialog->exec();
}

void MainWindow::on_btnExporter_4_clicked()
{
    // Demander à l'utilisateur où sauvegarder le fichier
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Enregistrer le PDF",
        QDir::homePath() + "/fournisseurs.pdf",
        "Fichiers PDF (*.pdf)"
    );
    
    // Si l'utilisateur annule
    if (fileName.isEmpty()) {
        return;
    }
    
    // S'assurer que le fichier a l'extension .pdf
    if (!fileName.endsWith(".pdf", Qt::CaseInsensitive)) {
        fileName += ".pdf";
    }
    
    // Créer le PDF Writer
    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setPageMargins(QMarginsF(15, 15, 15, 15), QPageLayout::Millimeter);
    
    QPainter painter(&pdfWriter);
    if (!painter.isActive()) {
        QMessageBox::critical(this, "Erreur PDF", "Impossible d'initialiser le fichier PDF. Vérifiez les permissions.");
        return;
    }
    
    // Configuration des dimensions (en unités de périphérique)
    int pageWidth = pdfWriter.width();
    int pageHeight = pdfWriter.height();
    int margin = 500;
    
    // Titre principal
    painter.setFont(QFont("Arial", 20, QFont::Bold));
    painter.setPen(QColor(45, 34, 76)); // Couleur #2d224c
    QRect titleRect(margin, margin, pageWidth - 2*margin, 800);
    painter.drawText(titleRect, Qt::AlignCenter, "Liste des Fournisseurs");
    
    // Ligne de séparation sous le titre
    painter.setPen(QPen(QColor(165, 94, 234), 3)); // Couleur #a55eea
    painter.drawLine(margin, margin + 900, pageWidth - margin, margin + 900);
    
    // Définir les positions des colonnes
    int startY = margin + 1200;
    int rowHeight = 400;
    
    // Calculer la largeur disponible pour le tableau
    int availableWidth = pageWidth - 2 * margin;
    
    // Définir les largeurs proportionnelles (en pourcentage de la largeur disponible)
    // ID: 8%, Nom: 15%, Email: 22%, Téléphone: 15%, Catégorie: 15%, Adresse: 25%
    int colWidths[] = {
        (int)(availableWidth * 0.08),  // ID
        (int)(availableWidth * 0.15),  // Nom
        (int)(availableWidth * 0.35),  // Email
        (int)(availableWidth * 0.15),  // Téléphone
        (int)(availableWidth * 0.15),  // Catégorie
        (int)(availableWidth * 0.25)   // Adresse
    };
    
    int colPositions[7];
    colPositions[0] = margin;
    for (int i = 1; i < 7; i++) {
        colPositions[i] = colPositions[i-1] + colWidths[i-1];
    }
    
    // En-tête du tableau
    painter.setFont(QFont("Arial", 11, QFont::Bold));
    painter.setPen(Qt::white);
    painter.setBrush(QColor(45, 34, 76)); // Fond de l'en-tête
    painter.drawRect(margin, startY, pageWidth - 2*margin, rowHeight);
    
    // Texte de l'en-tête
    QStringList headers = {"ID", "Nom", "Email", "Téléphone", "Catégorie", "Adresse"};
    for (int i = 0; i < headers.size(); i++) {
        QRect headerRect(colPositions[i] + 50, startY, colWidths[i] - 100, rowHeight);
        painter.drawText(headerRect, Qt::AlignLeft | Qt::AlignVCenter, headers[i]);
    }
    
    // Récupérer les données
    QSqlQuery query("SELECT ID, NOM, EMAIL, TEL, CATEGORIE, ADRESSE FROM FOURNISSEUR");
    int count = 0;
    int currentY = startY + rowHeight;
    
    painter.setFont(QFont("Arial", 10));
    
    while (query.next()) {
        count++;
        
        // Alterner les couleurs de fond
        if (count % 2 == 0) {
            painter.setBrush(QColor(245, 246, 250)); // #f5f6fa
        } else {
            painter.setBrush(Qt::white);
        }
        
        painter.setPen(QColor(223, 230, 233)); // Bordure légère
        painter.drawRect(margin, currentY, pageWidth - 2*margin, rowHeight);
        
        // Dessiner le texte
        painter.setPen(Qt::black);
        for (int i = 0; i < 6; i++) {
            QString text = query.value(i).toString();
            QRect cellRect(colPositions[i] + 50, currentY, colWidths[i] - 100, rowHeight);
            
            // Tronquer le texte s'il est trop long
            QFontMetrics fm(painter.font());
            text = fm.elidedText(text, Qt::ElideRight, colWidths[i] - 100);
            
            painter.drawText(cellRect, Qt::AlignLeft | Qt::AlignVCenter, text);
        }
        
        currentY += rowHeight;
        
        // Vérifier si on doit créer une nouvelle page
        if (currentY > pageHeight - margin - 500) {
            pdfWriter.newPage();
            currentY = margin;
            
            // Redessiner l'en-tête sur la nouvelle page
            painter.setBrush(QColor(45, 34, 76));
            painter.setPen(Qt::white);
            painter.drawRect(margin, currentY, pageWidth - 2*margin, rowHeight);
            
            for (int i = 0; i < headers.size(); i++) {
                QRect headerRect(colPositions[i] + 50, currentY, colWidths[i] - 100, rowHeight);
                painter.drawText(headerRect, Qt::AlignLeft | Qt::AlignVCenter, headers[i]);
            }
            
            currentY += rowHeight;
            painter.setFont(QFont("Arial", 10));
        }
    }
    
    // Pied de page
    QFont footerFont("Arial", 9);
    footerFont.setItalic(true);
    painter.setFont(footerFont);
    painter.setPen(QColor(100, 100, 100));
    QString footer = QString("Total: %1 fournisseur(s) - Généré le %2")
        .arg(count)
        .arg(QDateTime::currentDateTime().toString("dd/MM/yyyy à hh:mm"));
    QRect footerRect(margin, currentY + 300, pageWidth - 2*margin, 400);
    painter.drawText(footerRect, Qt::AlignCenter, footer);
    
    painter.end();
    
    // Messages de confirmation
    if (count == 0) {
        QMessageBox::information(this, "Export PDF", "Le fichier PDF a été généré mais aucune donnée n'a été trouvée dans la base.");
    } else {
        QMessageBox::information(this, "Export PDF", 
            QString("Le fichier PDF a été généré avec succès.\n\nNombre de fournisseurs: %1\nChemin: %2")
            .arg(count).arg(fileName));
    }
    
    // Ouvrir le PDF
    if (!QDesktopServices::openUrl(QUrl::fromLocalFile(fileName))) {
        QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir le fichier PDF automatiquement.");
    }
}

void MainWindow::on_btnModifier_2_clicked()
{
    // Vérifier qu'une ligne est sélectionnée
    QList<QTableWidgetItem*> selectedItems = ui->tableClients_2->selectedItems();
    
    if (selectedItems.isEmpty()) {
        QMessageBox::warning(this, "Aucune sélection", "Veuillez sélectionner un fournisseur à modifier.");
        return;
    }
    
    // Récupérer la ligne sélectionnée
    int selectedRow = ui->tableClients_2->currentRow();
    
    // Récupérer les données de la ligne sélectionnée
    QString id = ui->tableClients_2->item(selectedRow, 0)->text();
    QString nom = ui->tableClients_2->item(selectedRow, 1)->text();
    QString email = ui->tableClients_2->item(selectedRow, 2)->text();
    QString tel = ui->tableClients_2->item(selectedRow, 3)->text();
    QString categorie = ui->tableClients_2->item(selectedRow, 4)->text();
    QString adresse = ui->tableClients_2->item(selectedRow, 5)->text();
    
    // Créer un dialogue pour la modification
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Modifier Fournisseur");
    dialog->setMinimumSize(600, 500);
    dialog->setStyleSheet("QDialog { background-color: #f5f6fa; }");
    
    // Créer le layout principal
    QVBoxLayout *mainLayout = new QVBoxLayout(dialog);
    
    // Titre
    QLabel *titleLabel = new QLabel("Modifier les informations du fournisseur", dialog);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #2d224c; margin: 10px;");
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);
    
    // Formulaire
    QFormLayout *formLayout = new QFormLayout();
    formLayout->setSpacing(15);
    
    // Champs de saisie
    QLineEdit *idEdit = new QLineEdit(id, dialog);
    idEdit->setReadOnly(true); // L'ID ne peut pas être modifié
    idEdit->setStyleSheet("background-color: #e0e0e0; padding: 8px; border-radius: 5px;");
    
    QLineEdit *nomEdit = new QLineEdit(nom, dialog);
    nomEdit->setStyleSheet("padding: 8px; border-radius: 5px; border: 1px solid #dfe6e9;");
    
    QLineEdit *emailEdit = new QLineEdit(email, dialog);
    emailEdit->setStyleSheet("padding: 8px; border-radius: 5px; border: 1px solid #dfe6e9;");
    
    QLineEdit *telEdit = new QLineEdit(tel, dialog);
    telEdit->setStyleSheet("padding: 8px; border-radius: 5px; border: 1px solid #dfe6e9;");
    
    QComboBox *categorieCombo = new QComboBox(dialog);
    categorieCombo->addItems({"Lunettes", "Lentilles", "Services", "Accessoires"});
    categorieCombo->setCurrentText(categorie);
    categorieCombo->setStyleSheet("padding: 8px; border-radius: 5px; border: 1px solid #dfe6e9;");
    
    QLineEdit *adresseEdit = new QLineEdit(adresse, dialog);
    adresseEdit->setStyleSheet("padding: 8px; border-radius: 5px; border: 1px solid #dfe6e9;");
    
    // Ajouter les champs au formulaire
    formLayout->addRow("ID:", idEdit);
    formLayout->addRow("Nom:", nomEdit);
    formLayout->addRow("Email:", emailEdit);
    formLayout->addRow("Téléphone:", telEdit);
    formLayout->addRow("Catégorie:", categorieCombo);
    formLayout->addRow("Adresse:", adresseEdit);
    
    mainLayout->addLayout(formLayout);
    
    // Boutons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    
    QPushButton *btnConfirmer = new QPushButton("Confirmer", dialog);
    btnConfirmer->setStyleSheet("background-color:#2980b9;color:white;font-weight:bold;border-radius:10px;padding:10px 20px;font-size:14px;");
    
    QPushButton *btnAnnuler = new QPushButton("Annuler", dialog);
    btnAnnuler->setStyleSheet("background-color:#636e72;color:white;font-weight:bold;border-radius:10px;padding:10px 20px;font-size:14px;");
    
    buttonLayout->addWidget(btnConfirmer);
    buttonLayout->addWidget(btnAnnuler);
    mainLayout->addLayout(buttonLayout);
    
    // Connexion des boutons
    connect(btnAnnuler, &QPushButton::clicked, dialog, &QDialog::reject);
    
    connect(btnConfirmer, &QPushButton::clicked, [=]() {
        // Récupérer les nouvelles valeurs
        QString newNom = nomEdit->text().trimmed();
        QString newEmail = emailEdit->text().trimmed();
        QString newTel = telEdit->text().trimmed();
        QString newCategorie = categorieCombo->currentText();
        QString newAdresse = adresseEdit->text().trimmed();
        
        // ========== VALIDATION DES CHAMPS ==========
        
        if (newNom.isEmpty()) {
            QMessageBox::warning(dialog, "Champ obligatoire", "Le champ Nom est obligatoire !");
            nomEdit->setFocus();
            return;
        }
        
        if (newEmail.isEmpty()) {
            QMessageBox::warning(dialog, "Champ obligatoire", "Le champ Email est obligatoire !");
            emailEdit->setFocus();
            return;
        }
        
        if (newTel.isEmpty()) {
            QMessageBox::warning(dialog, "Champ obligatoire", "Le champ Téléphone est obligatoire !");
            telEdit->setFocus();
            return;
        }
        
        if (newAdresse.isEmpty()) {
            QMessageBox::warning(dialog, "Champ obligatoire", "Le champ Adresse est obligatoire !");
            adresseEdit->setFocus();
            return;
        }
        
        // Vérifier que le nom a au moins 3 caractères
        if (newNom.length() < 3) {
            QMessageBox::warning(dialog, "Validation", "Le nom doit contenir au moins 3 caractères !");
            nomEdit->setFocus();
            return;
        }
        
        // Vérifier que l'adresse a au moins 3 caractères
        if (newAdresse.length() < 3) {
            QMessageBox::warning(dialog, "Validation", "L'adresse doit contenir au moins 3 caractères !");
            adresseEdit->setFocus();
            return;
        }
        
        // Vérifier que le téléphone contient exactement 8 chiffres
        QRegularExpression telRegex("^\\d{8}$");
        if (!telRegex.match(newTel).hasMatch()) {
            QMessageBox::warning(dialog, "Validation", "Le téléphone doit contenir exactement 8 chiffres !");
            telEdit->setFocus();
            return;
        }
        
        // Vérifier que l'email est au format valide
        QRegularExpression emailRegex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
        if (!emailRegex.match(newEmail).hasMatch()) {
            QMessageBox::warning(dialog, "Validation", "L'email doit être au format valide (exemple@domaine.com) !");
            emailEdit->setFocus();
            return;
        }
        
        // ========== FIN VALIDATION ==========
        
        // Créer un objet Gestion_Fournisseur avec les nouvelles données
        Gestion_Fournisseur fournisseur(id, newNom, newEmail, newTel, newCategorie, newAdresse);
        
        // Appeler la fonction de modification
        if (fournisseur.modifier_fournisseurs()) {
            // Rafraîchir la table
            remplirTableFournisseurs();
            dialog->accept();
        }
    });
    
    // Afficher le dialogue
    dialog->exec();
    delete dialog;
}



void MainWindow::on_Modifier_clicked()
{
    // Vérifier qu'une ligne est sélectionnée
    QList<QTableWidgetItem*> selectedItems = ui->tableClients_2->selectedItems();

    if (selectedItems.isEmpty()) {
        QMessageBox::warning(this, "Aucune sélection", "Veuillez sélectionner un fournisseur à modifier.");
        return;
    }

    // Récupérer la ligne sélectionnée
    int selectedRow = ui->tableClients_2->currentRow();

    // Récupérer les données de la ligne sélectionnée
    QString id = ui->tableClients_2->item(selectedRow, 0)->text();
    QString nom = ui->tableClients_2->item(selectedRow, 1)->text();
    QString email = ui->tableClients_2->item(selectedRow, 2)->text();
    QString tel = ui->tableClients_2->item(selectedRow, 3)->text();
    QString categorie = ui->tableClients_2->item(selectedRow, 4)->text();
    QString adresse = ui->tableClients_2->item(selectedRow, 5)->text();

    // Créer un dialogue pour la modification
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Modifier Fournisseur");
    dialog->setMinimumSize(600, 500);
    dialog->setStyleSheet("QDialog { background-color: #f5f6fa; }");

    // Créer le layout principal
    QVBoxLayout *mainLayout = new QVBoxLayout(dialog);

    // Titre
    QLabel *titleLabel = new QLabel("Modifier les informations du fournisseur", dialog);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #2d224c; margin: 10px;");
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    // Formulaire
    QFormLayout *formLayout = new QFormLayout();
    formLayout->setSpacing(15);

    // Champs de saisie
    QLineEdit *idEdit = new QLineEdit(id, dialog);
    idEdit->setReadOnly(true); // L'ID ne peut pas être modifié
    idEdit->setStyleSheet("background-color: #e0e0e0; padding: 8px; border-radius: 5px;");

    QLineEdit *nomEdit = new QLineEdit(nom, dialog);
    nomEdit->setStyleSheet("padding: 8px; border-radius: 5px; border: 1px solid #dfe6e9;");

    QLineEdit *emailEdit = new QLineEdit(email, dialog);
    emailEdit->setStyleSheet("padding: 8px; border-radius: 5px; border: 1px solid #dfe6e9;");

    QLineEdit *telEdit = new QLineEdit(tel, dialog);
    telEdit->setStyleSheet("padding: 8px; border-radius: 5px; border: 1px solid #dfe6e9;");

    QComboBox *categorieCombo = new QComboBox(dialog);
    categorieCombo->addItems({"Lunettes", "Lentilles", "Services", "Accessoires"});
    categorieCombo->setCurrentText(categorie);
    categorieCombo->setStyleSheet("padding: 8px; border-radius: 5px; border: 1px solid #dfe6e9;");

    QLineEdit *adresseEdit = new QLineEdit(adresse, dialog);
    adresseEdit->setStyleSheet("padding: 8px; border-radius: 5px; border: 1px solid #dfe6e9;");

    // Ajouter les champs au formulaire
    formLayout->addRow("ID:", idEdit);
    formLayout->addRow("Nom:", nomEdit);
    formLayout->addRow("Email:", emailEdit);
    formLayout->addRow("Téléphone:", telEdit);
    formLayout->addRow("Catégorie:", categorieCombo);
    formLayout->addRow("Adresse:", adresseEdit);

    mainLayout->addLayout(formLayout);

    // Boutons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();

    QPushButton *btnConfirmer = new QPushButton("Confirmer", dialog);
    btnConfirmer->setStyleSheet("background-color:#2980b9;color:white;font-weight:bold;border-radius:10px;padding:10px 20px;font-size:14px;");

    QPushButton *btnAnnuler = new QPushButton("Annuler", dialog);
    btnAnnuler->setStyleSheet("background-color:#636e72;color:white;font-weight:bold;border-radius:10px;padding:10px 20px;font-size:14px;");

    buttonLayout->addWidget(btnConfirmer);
    buttonLayout->addWidget(btnAnnuler);
    mainLayout->addLayout(buttonLayout);

    // Connexion des boutons
    connect(btnAnnuler, &QPushButton::clicked, dialog, &QDialog::reject);

    connect(btnConfirmer, &QPushButton::clicked, [=]() {
        // Récupérer les nouvelles valeurs
        QString newNom = nomEdit->text().trimmed();
        QString newEmail = emailEdit->text().trimmed();
        QString newTel = telEdit->text().trimmed();
        QString newCategorie = categorieCombo->currentText();
        QString newAdresse = adresseEdit->text().trimmed();

        // ========== VALIDATION DES CHAMPS ==========

        if (newNom.isEmpty()) {
            QMessageBox::warning(dialog, "Champ obligatoire", "Le champ Nom est obligatoire !");
            nomEdit->setFocus();
            return;
        }

        if (newEmail.isEmpty()) {
            QMessageBox::warning(dialog, "Champ obligatoire", "Le champ Email est obligatoire !");
            emailEdit->setFocus();
            return;
        }

        if (newTel.isEmpty()) {
            QMessageBox::warning(dialog, "Champ obligatoire", "Le champ Téléphone est obligatoire !");
            telEdit->setFocus();
            return;
        }

        if (newAdresse.isEmpty()) {
            QMessageBox::warning(dialog, "Champ obligatoire", "Le champ Adresse est obligatoire !");
            adresseEdit->setFocus();
            return;
        }

        // Vérifier que le nom a au moins 3 caractères
        if (newNom.length() < 3) {
            QMessageBox::warning(dialog, "Validation", "Le nom doit contenir au moins 3 caractères !");
            nomEdit->setFocus();
            return;
        }

        // Vérifier que l'adresse a au moins 3 caractères
        if (newAdresse.length() < 3) {
            QMessageBox::warning(dialog, "Validation", "L'adresse doit contenir au moins 3 caractères !");
            adresseEdit->setFocus();
            return;
        }

        // Vérifier que le téléphone contient exactement 8 chiffres
        QRegularExpression telRegex("^\\d{8}$");
        if (!telRegex.match(newTel).hasMatch()) {
            QMessageBox::warning(dialog, "Validation", "Le téléphone doit contenir exactement 8 chiffres !");
            telEdit->setFocus();
            return;
        }

        // Vérifier que l'email est au format valide
        QRegularExpression emailRegex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
        if (!emailRegex.match(newEmail).hasMatch()) {
            QMessageBox::warning(dialog, "Validation", "L'email doit être au format valide (exemple@domaine.com) !");
            emailEdit->setFocus();
            return;
        }

        // ========== FIN VALIDATION ==========

        // Créer un objet Gestion_Fournisseur avec les nouvelles données
        Gestion_Fournisseur fournisseur(id, newNom, newEmail, newTel, newCategorie, newAdresse);

        // Appeler la fonction de modification
        if (fournisseur.modifier_fournisseurs()) {
            // Rafraîchir la table
            remplirTableFournisseurs();
            dialog->accept();
        }
    });

    // Afficher le dialogue
    dialog->exec();
    delete dialog;
}


void MainWindow::envoyerSMS(const QString &destinataire, const QString &message)
{
    // SID et auth token de Twilio
    QString sid = "ACe59ad4c288d393194c07aebcb0c8abf6";
    QString authToken = "432ac1950a67de748e7467dd41fcb08e";

    // Construire l'URL de l'API Twilio
    QString url = "https://api.twilio.com/2010-04-01/Accounts/" + sid + "/Messages.json";

    // Créer le gestionnaire de réseau
    QNetworkAccessManager *networkAccessManager = new QNetworkAccessManager(this);
     connect(networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

    // Construire les données de la requête
    QByteArray postData;
    postData.append("To=" + destinataire.toUtf8());
    postData.append("&From=+16812466585");
    postData.append("&Body=" + message.toUtf8());

    // Créer la requête HTTP
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setRawHeader("Authorization", "Basic " + QByteArray(QString("%1:%2").arg(sid).arg(authToken).toUtf8()).toBase64());


    // Envoyer la requête
    networkAccessManager->post(request, postData);

    // Afficher un message de succès
    QMessageBox::information(this, "Envoi SMS", "Le SMS a été envoyé avec succès.");
}

void MainWindow::on_Send_mail_clicked()
{
    QString host = "smtp.gmail.com";
    int port = 587;

    QString sender = "kennabouline@gmail.com";
    QString recipient = ui->dest->text();
    QString contenu = ui->contenu->text();

    // Validation email
    if (recipient.isEmpty()) {
        QMessageBox::warning(this, "Destinataire vide", "Veuillez saisir une adresse email.");
        return;
    }

    if (contenu.isEmpty()) {
        QMessageBox::warning(this, "Contenu vide", "Veuillez saisir votre message.");
        return;
    }



    QString subject = " [ IMPORTANT ] : Cher notre fournisseur ";
    QString body = contenu;

    QSslSocket socket;
    socket.connectToHost(host, port);

    if (!socket.waitForConnected()) {
        qDebug() << "Failed to connect:" << socket.errorString();
        return;
    }

    socket.waitForReadyRead();
    qDebug() << socket.readAll();

    socket.write("EHLO localhost\r\n");
    socket.waitForBytesWritten();
    socket.waitForReadyRead();
    qDebug() << socket.readAll();

    socket.write("STARTTLS\r\n");
    socket.waitForBytesWritten();
    socket.waitForReadyRead();
    qDebug() << socket.readAll();

    socket.startClientEncryption();
    if (!socket.waitForEncrypted()) {
        qDebug() << "Encryption failed:" << socket.errorString();
        return;
    }

    socket.write("AUTH LOGIN\r\n");
    socket.waitForReadyRead();
    qDebug() << socket.readAll();

    socket.write(QByteArray(sender.toUtf8()).toBase64() + "\r\n");
    socket.waitForReadyRead();
    qDebug() << socket.readAll();

    socket.write(QByteArray("yobf dbfa qtti yngq").toBase64() + "\r\n");
    socket.waitForReadyRead();
    qDebug() << socket.readAll();

    socket.write("MAIL FROM:<" + sender.toUtf8() + ">\r\n");
    socket.waitForReadyRead();
    qDebug() << socket.readAll();

    socket.write("RCPT TO:<" + recipient.toUtf8() + ">\r\n");
    socket.waitForReadyRead();
    qDebug() << socket.readAll();

    socket.write("DATA\r\n");
    socket.waitForReadyRead();
    qDebug() << socket.readAll();

    socket.write("From: " + sender.toUtf8() + "\r\n");
    socket.write("To: " + recipient.toUtf8() + "\r\n");
    socket.write("Subject: " + subject.toUtf8() + "\r\n\r\n");
    socket.write(body.toUtf8() + "\r\n.\r\n");

    socket.waitForReadyRead();
    qDebug() << socket.readAll();

    socket.write("QUIT\r\n");

    QMessageBox::information(this, "Succès", "Email envoyé.");
    ui->contenu->clear();
    ui->dest->clear();
}

