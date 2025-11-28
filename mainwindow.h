#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "gestion_client.h"
#include "apiremises.h"
#include "gestion_personnel.h"
#include "gestion_locaux.h"
#include "gestion_fournisseur.h"
#include "gestion_produit.h"
#include "StatisticsWidget.h"
#include "StatisticsWidgetProduit.h"
#include <QTableWidgetItem>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onTestAPIClicked();

    void onRemiseCalculee(float remise);
    void onErreurAPI(const QString &message);
    void onConnexionAPITestee(bool succes);
    
    void ajusterPositionStatistiques();
    void on_searchLineEdit_4_textChanged(const QString &text);
    void on_btnExporter_4_clicked();
    void on_tableClients_2_doubleClicked(const QModelIndex &index);
    void chargerEtAfficherFournisseur(int id);
    void onFiltresFournisseurChanged();
    void showClientInterface();
    void showPersonnelInterface();
    void showLocauxInterface();
    void showFournisseurInterface();
    void showProduitsInterface();

    void on_btnConfirmer_3_clicked();
    void on_btnAnnuler_3_clicked();
    void on_btnConfirmerPersonnel_clicked();
    void on_btnAnnulerPersonnel_clicked();
    void on_btnConfirmerLocal_clicked();
    void on_btnAnnulerLocal_clicked();
    void on_btnConfirmerFournisseur_clicked();
    void on_btnAnnulerFournisseur_clicked();
    void on_btnConfirmerProduit_clicked();
    void on_btnAnnulerProduit_clicked();

    void validerIDFournisseur(const QString &text);
    void validerNomFournisseur(const QString &text);
    void validerTelephoneFournisseur(const QString &text);
    void validerMailFournisseur(const QString &text);

    void validerID(const QString &text);
    void validerNom(const QString &text);
    void validerPrenom(const QString &text);
    void validerTelephone(const QString &text);

    void onTableItemChanged(QTableWidgetItem *item);
    void onTablePersonnelItemChanged(QTableWidgetItem *item);
    void onTableLocauxItemChanged(QTableWidgetItem *item);
    void onTableFournisseurItemChanged(QTableWidgetItem *item);
    void onTableProduitItemChanged(QTableWidgetItem *item);

    void on_searchLineEdit_3_textChanged(const QString &text);
    void on_btnExporter_3_clicked();
    void on_tableClients_doubleClicked(const QModelIndex &index);
    void chargerEtAfficherClient(int id);
    void onFiltresChanged();

    void rafraichirStatistiquesClients();
    void onPageChanged();
    void on_btnUploadPhoto_clicked();
    void on_btnUploadOrdonnance_clicked();

    void on_searchLineEdit_5_textChanged(const QString &text);
    void on_btnExporter_5_clicked();
    void onFiltresProduitChanged();
    void rafraichirStatistiquesProduits();
    void verifierStockFaible();

private:
    Ui::MainWindow *ui;
    StatisticsWidget *m_statsWidget;
    StatisticsWidgetProduit *m_statsWidgetProduit;
    QLineEdit *lineEditIDProduit;
    QString photoPath;
    QString ordonnancePath;
    ApiRemises *m_apiRemises;

    void initialiserAPI();
    void gererRemiseAutomatique();
    void gererRemiseManuelle();
    void onCheckBoxAIClicked(bool checked);
    void onQuantiteChanged(int quantite);
    void onRemiseManuelleChanged(double remise);

    void viderFormulaireClient();
    void viderFormulairePersonnel();
    void viderFormulaireLocal();
    void viderFormulaireFournisseur();
    void viderFormulaireProduit();

    void rafraichirTableauClients();
    void rafraichirTableauPersonnel();
    void rafraichirTableauLocaux();
    void rafraichirTableauFournisseur();
    void rafraichirTableauProduit();
    bool modifierClientExistant(int id, const QString &nom, const QString &prenom,
                                int telephone, const QDate &dateNaissance,
                                const QString &statut, const QString &sexe,
                                const QString &ordonnance, const QString &photo,
                                QString &erreurMessage);
    bool ligneCorrespondFiltre(int row, const QString &filtre);
    void appliquerFiltre(const QString &filtre);
    void reinitialiserFiltres();
    void decrementerQuantiteProduit(int idProduit);
    QString genererNomCourt(const QString &cheminOriginal, const QString &prefixe);
    QString copierFichierVersDossierApp(const QString &sourcePath, const QString &dossier, const QString &prefixe);
    bool ligneProduitCorrespondFiltre(int row, const QString &filtre);
    void appliquerFiltreProduit(const QString &filtre);
    void reinitialiserFiltresProduit();
    void trierTableauProduit(const QString &critere);

    bool modifierFournisseurExistant(int id, const QString &nomEntreprise,
                                     const QString &personneContact, const QString &adresse,
                                     int telephone, const QString &mail,
                                     const QString &categorie, const QString &details,
                                     float noteFiabilite, QString &erreurMessage);
    bool ligneFournisseurCorrespondFiltre(int row, const QString &filtre);
    void appliquerFiltreFournisseur(const QString &filtre);
    void reinitialiserFiltresFournisseur();
    void trierTableauFournisseur(const QString &critere);
    void highlightLowStockProducts();
    void showStockAlert();
};

#endif
