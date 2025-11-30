#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gestion_client.h"
#include "gestion_personnel.h"
#include "gestion_locaux.h"
#include "gestion_fournisseur.h"
#include "gestion_produit.h"
#include "StatisticsWidget.h"
#include <QTableWidgetItem>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>


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


private:
    Ui::MainWindow *ui;

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
    StatisticsWidget *m_statsWidget;
    QLineEdit *lineEditIDProduit;
    QString photoPath;
    QString ordonnancePath;
    QString genererNomCourt(const QString &cheminOriginal, const QString &prefixe);
    QString copierFichierVersDossierApp(const QString &sourcePath, const QString &dossier, const QString &prefixe);
    void afficherPhotoPleinCadre(const QString &cheminPhoto);
    bool validerVisageHumain(const QString &cheminPhoto, QString &erreurMessage);
    void verifierInstallationOpenCV();

    void appliquerFiltreAvecSQL(const QString &filtre, const QString &recherche);
};

#endif // MAINWINDOW_H
