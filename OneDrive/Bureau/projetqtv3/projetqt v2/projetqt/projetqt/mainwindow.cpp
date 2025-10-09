#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableWidget>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTableWidgetItem>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(0);

    connect(ui->btnAjouterClient_8, &QPushButton::clicked, [=]() {
        ui->stackedWidget->setCurrentIndex(2);
    });

    connect(ui->btnListeClients_8, &QPushButton::clicked, [=]() {
        ui->stackedWidget->setCurrentIndex(0);
    });

    connect(ui->btnAjouterPersonnel_5, &QPushButton::clicked, [=]() {
        ui->stackedWidget->setCurrentIndex(2);
    });

    connect(ui->btnListePersonnel_5, &QPushButton::clicked, [=]() {
        ui->stackedWidget->setCurrentIndex(0);
    });

    QTableWidget *table = ui->tablePersonnel_3;

    table->setRowCount(8);

    QStringList marques = {"Ray-Ban", "Oakley", "Gucci", "Prada"};
    QStringList modeles = {"Aviator", "Frogskins", "GG", "Linea Rossa"};
    QStringList types = {"Solaire", "Vue", "Mixte", "Lentille"};
    QStringList couleurs = {"Noir", "Argent", "Or", "Brun"};

    for (int row = 0; row < 4; ++row) {
        table->setItem(row, 0, new QTableWidgetItem(QString::number(1000 + row)));
        table->setItem(row, 1, new QTableWidgetItem(marques[row]));
        table->setItem(row, 2, new QTableWidgetItem(modeles[row]));
        table->setItem(row, 3, new QTableWidgetItem(types[row]));
        table->setItem(row, 4, new QTableWidgetItem(couleurs[row]));
        table->setItem(row, 5, new QTableWidgetItem("150.00"));
        table->setItem(row, 6, new QTableWidgetItem("25"));
        table->setItem(row, 7, new QTableWidgetItem("2024-01-15"));
    }

    table->setColumnWidth(8, 180);

    for (int row = 0; row < table->rowCount(); ++row) {
        QWidget *widget = new QWidget();
        QHBoxLayout *layout = new QHBoxLayout(widget);

        QPushButton *btnModif = new QPushButton("MOD️");
        QPushButton *btnSupp = new QPushButton("SUP️");

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

        layout->addWidget(btnModif);
        layout->addWidget(btnSupp);
        layout->setContentsMargins(5, 2, 5, 2);
        layout->setSpacing(10);

        table->setCellWidget(row, 10, widget);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnImporterOrdonnance_clicked()
{
}
