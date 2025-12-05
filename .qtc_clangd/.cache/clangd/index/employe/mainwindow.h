#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
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
    void on_btnAjouterClient_7_clicked();

    void on_btnConfirmer_4_clicked();

    void on_btnAnnuler_4_clicked();

    void on_btnListeClients_6_clicked();
    void on_btnAjouterClient_6_clicked();

    void on_btnListeClients_7_clicked();

    void on_delete_2_clicked();

    void on_btnRechercher_4_clicked();


    void on_comboProfession_4_currentTextChanged(const QString &arg1);

    void on_btnStatistiques_clicked();
    void on_btnExporter_4_clicked();

    void on_btnModifier_2_clicked();

    void on_Modifier_clicked();
    void envoyerSMS(const QString &destinataire, const QString &message);

    void on_Send_mail_clicked();

private:
    void remplirTableFournisseurs();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
