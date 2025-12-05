
void MainWindow::on_btnStatistiques_clicked()
{
    // Statistics implementation
    QSqlQuery query;
    query.exec("SELECT CATEGORIE, COUNT(*) FROM FOURNISSEUR GROUP BY CATEGORIE");

    QPieSeries *series = new QPieSeries();
    while (query.next()) {
        QString category = query.value(0).toString();
        int count = query.value(1).toInt();
        series->append(category, count);
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

void MainWindow::on_btnPDF_clicked()
{
    QString fileName = "fournisseurs.pdf";
    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setPageMargins(QMarginsF(30, 30, 30, 30));

    QPainter painter(&pdfWriter);
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 12));

    // Title
    painter.setFont(QFont("Arial", 16, QFont::Bold));
    painter.drawText(3000, 1000, "Liste des Fournisseurs");

    // Table Header
    painter.setFont(QFont("Arial", 10, QFont::Bold));
    int y = 2000;
    painter.drawText(100, y, "ID");
    painter.drawText(1500, y, "Nom");
    painter.drawText(3500, y, "Email");
    painter.drawText(6000, y, "Téléphone");
    painter.drawText(8000, y, "Catégorie");

    // Table Content
    painter.setFont(QFont("Arial", 10));
    y += 500;

    QSqlQuery query("SELECT ID, NOM, EMAIL, TEL, CATEGORIE FROM FOURNISSEUR");
    while (query.next()) {
        painter.drawText(100, y, query.value(0).toString());
        painter.drawText(1500, y, query.value(1).toString());
        painter.drawText(3500, y, query.value(2).toString());
        painter.drawText(6000, y, query.value(3).toString());
        painter.drawText(8000, y, query.value(4).toString());
        y += 500;
    }

    painter.end();

    QMessageBox::information(this, "Export PDF", "Le fichier PDF a été généré avec succès.");
    QDesktopServices::openUrl(QUrl::fromLocalFile(fileName));
}
