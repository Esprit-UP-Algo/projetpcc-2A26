#include "StatisticsWidget.h"
#include <QPainter>
#include <QSqlQuery>
#include <cmath>
#include <QDate>
#include "connection.h"

StatisticsWidget::StatisticsWidget(QWidget *parent)
    : QWidget(parent)
{
    // Taille pour accommoder les deux graphiques
    setFixedSize(351, 720); // Hauteur augmentée pour les deux graphiques
    rafraichirStatistiques();
}

void StatisticsWidget::rafraichirStatistiques()
{
    // Charger les données pour le camembert (Hommes/Femmes)
    m_data.clear();
    m_data["Hommes"] = 0;
    m_data["Femmes"] = 0;

    Connection c;
    if (c.createconnect()) {
        QSqlQuery query;
        query.prepare("SELECT SEXE, COUNT(*) FROM CLIENT GROUP BY SEXE");

        if (query.exec()) {
            while (query.next()) {
                QString sexe = query.value(0).toString();
                int count = query.value(1).toInt();

                if (sexe == "H") {
                    m_data["Hommes"] += count;
                } else if (sexe == "F") {
                    m_data["Femmes"] += count;
                }
            }
        }
    }

    // Charger les données pour le diagramme en barres
    loadBarChartData();

    update();
}

void StatisticsWidget::loadBarChartData()
{
    m_barData.clear();

    Connection c;
    if (c.createconnect()) {
        QSqlQuery query;
        query.prepare("SELECT DATE_DE_NAISSANCE FROM CLIENT");

        if (query.exec()) {
            QDate currentDate = QDate::currentDate();
            int currentYear = currentDate.year();

            while (query.next()) {
                QDate birthDate = query.value(0).toDate();
                if (birthDate.isValid()) {
                    int age = currentYear - birthDate.year();
                    // Ajuster l'âge si l'anniversaire n'est pas encore arrivé cette année
                    if (currentDate.month() < birthDate.month() ||
                        (currentDate.month() == birthDate.month() && currentDate.day() < birthDate.day())) {
                        age--;
                    }

                    int ageGroup = getAgeGroup(age);
                    int birthYear = birthDate.year();

                    // Initialiser l'année si nécessaire
                    if (!m_barData.contains(birthYear)) {
                        QMap<QString, int> yearData;
                        yearData["-20"] = 0;
                        yearData["20-50"] = 0;
                        yearData["50+"] = 0;
                        m_barData[birthYear] = yearData;
                    }

                    // Incrémenter le compteur pour la tranche d'âge
                    switch(ageGroup) {
                    case 0: m_barData[birthYear]["-20"]++; break;
                    case 1: m_barData[birthYear]["20-50"]++; break;
                    case 2: m_barData[birthYear]["50+"]++; break;
                    }
                }
            }
        }
    }
}

int StatisticsWidget::getAgeGroup(int age)
{
    if (age < 20) return 0;      // -20
    else if (age <= 50) return 1; // 20-50
    else return 2;               // 50+
}

void StatisticsWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Fond
    painter.fillRect(rect(), QColor(255, 255, 255));

    // ==================== PREMIER GRAPHIQUE - CAMEMBERT ====================
    // Titre
    painter.setPen(QColor(45, 34, 76));
    painter.setFont(QFont("Arial", 12, QFont::Bold));
    painter.drawText(QRect(0, 10, width(), 30), Qt::AlignCenter, "Hommes/Femmes");

    // Camembert
    QRect pieRect(50, 50, width() - 100, height() - 550);
    drawPieChart(painter, pieRect);

    // Légende du camembert
    QRect legendRect(0, height() - 480, width(), 80);
    drawLegend(painter, legendRect);

    // ==================== DEUXIÈME GRAPHIQUE - DIAGRAMME EN BARRES ====================
    // Titre du diagramme en barres
    painter.setPen(QColor(45, 34, 76));
    painter.setFont(QFont("Arial", 12, QFont::Bold));
    painter.drawText(QRect(0, 280, width(), 30), Qt::AlignCenter, "Clients par tranche d'âge");

    // Diagramme en barres
    QRect barRect(10, 310, width() - 20, 380);
    drawBarChart(painter, barRect);
}

void StatisticsWidget::drawPieChart(QPainter &painter, const QRect &rect)
{
    if (m_data.isEmpty()) {
        painter.setPen(QColor(100, 100, 100));
        painter.setFont(QFont("Arial", 12));
        painter.drawText(rect, Qt::AlignCenter, "Aucune donnée");
        return;
    }

    int total = m_data["Hommes"] + m_data["Femmes"];
    if (total == 0) {
        painter.setPen(QColor(100, 100, 100));
        painter.setFont(QFont("Arial", 12));
        painter.drawText(rect, Qt::AlignCenter, "Aucun client");
        return;
    }

    // Calcul des angles en degrés (pas en 1/16e)
    double angleHommes = (m_data["Hommes"] * 360.0) / total;
    double angleFemmes = (m_data["Femmes"] * 360.0) / total;

    int startAngle = 0;

    // Hommes
    if (m_data["Hommes"] > 0) {
        int spanAngle = angleHommes * 16; // Conversion en 1/16e de degré
        painter.setBrush(QColor(65, 105, 225));
        painter.setPen(QColor(50, 50, 50));
        painter.drawPie(rect, startAngle, spanAngle);

        // Pourcentage - position améliorée
        if (angleHommes >= 10.0) { // Au moins 10% pour afficher le texte
            double midAngle = startAngle / 16.0 + angleHommes / 2.0;
            double rad = qDegreesToRadians(midAngle);

            // Position à 60% du rayon pour être bien dans la portion
            double radiusFactor = 0.6;
            int labelX = rect.center().x() + (rect.width() * radiusFactor) * cos(rad);
            int labelY = rect.center().y() + (rect.height() * radiusFactor) * sin(rad);

            double percentage = (m_data["Hommes"] * 100.0) / total;

            // Fond pour le texte
            painter.setBrush(QColor(0, 0, 0, 150));
            painter.setPen(Qt::NoPen);
            painter.drawRoundedRect(labelX - 18, labelY - 7, 36, 14, 4, 4);

            // Texte
            painter.setPen(QColor(255, 255, 255));
            painter.setFont(QFont("Arial", 8, QFont::Bold));
            painter.drawText(QRect(labelX - 18, labelY - 7, 36, 14), Qt::AlignCenter,
                             QString::number(percentage, 'f', 0) + "%");
        }

        startAngle += spanAngle;
    }

    // Femmes
    if (m_data["Femmes"] > 0) {
        int spanAngle = angleFemmes * 16; // Conversion en 1/16e de degré
        painter.setBrush(QColor(255, 105, 180));
        painter.setPen(QColor(50, 50, 50));
        painter.drawPie(rect, startAngle, spanAngle);

        // Pourcentage - position améliorée
        if (angleFemmes >= 10.0) { // Au moins 10% pour afficher le texte
            double midAngle = startAngle / 16.0 + angleFemmes / 2.0;
            double rad = qDegreesToRadians(midAngle);

            // Position à 60% du rayon pour être bien dans la portion
            double radiusFactor = 0.6;
            int labelX = rect.center().x() + (rect.width() * radiusFactor) * cos(rad);
            int labelY = rect.center().y() + (rect.height() * radiusFactor) * sin(rad);

            double percentage = (m_data["Femmes"] * 100.0) / total;

            // Fond pour le texte
            painter.setBrush(QColor(0, 0, 0, 150));
            painter.setPen(Qt::NoPen);
            painter.drawRoundedRect(labelX - 18, labelY - 7, 36, 14, 4, 4);

            // Texte
            painter.setPen(QColor(255, 255, 255));
            painter.setFont(QFont("Arial", 8, QFont::Bold));
            painter.drawText(QRect(labelX - 18, labelY - 7, 36, 14), Qt::AlignCenter,
                             QString::number(percentage, 'f', 0) + "%");
        }
    }

    // Cercle extérieur
    painter.setBrush(Qt::NoBrush);
    painter.setPen(QColor(100, 100, 100));
    painter.drawEllipse(rect);
}

void StatisticsWidget::drawBarChart(QPainter &painter, const QRect &rect)
{
    // Calculer les totaux par tranche d'âge pour l'année actuelle
    int countMoins20 = 0;
    int count20a50 = 0;
    int countPlus50 = 0;

    // Agréger les données de toutes les années pour avoir les totaux par tranche d'âge
    for (int year : m_barData.keys()) {
        countMoins20 += m_barData[year]["-20"];
        count20a50 += m_barData[year]["20-50"];
        countPlus50 += m_barData[year]["50+"];
    }

    int counts[3] = {countMoins20, count20a50, countPlus50};
    QString ageGroups[3] = {"-20", "20-50", "50+"};
    QColor colors[3] = {
        QColor(100, 200, 255),  // -20 : Bleu clair
        QColor(255, 200, 100),  // 20-50 : Orange
        QColor(255, 100, 100)   // 50+ : Rouge
    };

    // Échelle fixe : 0, 5, 10, 15
    int maxCount = 15;

    if (countMoins20 == 0 && count20a50 == 0 && countPlus50 == 0) {
        painter.setPen(QColor(100, 100, 100));
        painter.setFont(QFont("Arial", 10));
        painter.drawText(rect, Qt::AlignCenter, "Aucune donnée d'âge");
        return;
    }

    // Dimensions
    int barWidth = 60;
    int barSpacing = 30;
    int chartBottom = rect.bottom() - 40;
    int chartHeight = rect.height() - 80;
    int chartLeft = rect.left() + 50;

    // Dessiner les axes
    painter.setPen(QColor(100, 100, 100));
    painter.drawLine(chartLeft, rect.top() + 20, chartLeft, chartBottom); // Axe Y
    painter.drawLine(chartLeft, chartBottom, rect.right(), chartBottom);  // Axe X

    // Titre de l'année
    int currentYear = QDate::currentDate().year();
    painter.setPen(QColor(45, 34, 76));
    painter.setFont(QFont("Arial", 10, QFont::Bold));
    painter.drawText(QRect(rect.left(), rect.top(), rect.width(), 20),
                     Qt::AlignCenter, QString("Année: %1").arg(currentYear));

    // Échelle fixe sur l'axe Y : 0, 5, 10, 15
    painter.setPen(QColor(100, 100, 100));
    painter.setFont(QFont("Arial", 8));

    // Valeurs fixes pour l'échelle
    int yValues[4] = {0, 5, 10, 15};

    for (int i = 0; i < 4; i++) {
        int value = yValues[i];
        int y = chartBottom - (value * chartHeight) / maxCount;
        painter.drawText(QRect(rect.left(), y - 10, 40, 20),
                         Qt::AlignRight | Qt::AlignVCenter, QString::number(value));
        painter.setPen(QColor(200, 200, 200));
        painter.drawLine(chartLeft, y, rect.right(), y);
        painter.setPen(QColor(100, 100, 100));
    }

    // Dessiner les barres
    int x = chartLeft + barSpacing;
    for (int i = 0; i < 3; i++) {
        int barHeight = (counts[i] * chartHeight) / maxCount;
        int barY = chartBottom - barHeight;

        // Dessiner la barre
        painter.setBrush(colors[i]);
        painter.setPen(QColor(50, 50, 50));
        painter.drawRect(x, barY, barWidth, barHeight);

        // Afficher le nombre au-dessus de la barre
        painter.setPen(QColor(0, 0, 0));
        painter.setFont(QFont("Arial", 9, QFont::Bold));
        painter.drawText(QRect(x, barY - 20, barWidth, 20),
                         Qt::AlignCenter, QString::number(counts[i]));

        // Afficher la tranche d'âge en bas
        painter.setPen(QColor(80, 80, 80));
        painter.setFont(QFont("Arial", 9));
        painter.drawText(QRect(x, chartBottom + 5, barWidth, 20),
                         Qt::AlignCenter, ageGroups[i]);

        x += (barWidth + barSpacing);
    }

    // Légende pour les tranches d'âge
    int legendY = chartBottom + 30;
    int legendX = chartLeft;
    painter.setFont(QFont("Arial", 9));
    painter.setPen(QColor(50, 50, 50));
    painter.drawText(QRect(legendX, legendY, rect.width(), 20),
                     Qt::AlignCenter, "Tranches d'âge (années)");
}

void StatisticsWidget::drawLegend(QPainter &painter, const QRect &rect)
{
    painter.setPen(QColor(50, 50, 50));
    painter.setFont(QFont("Arial", 10));

    int x = rect.left() + 20;
    int y = rect.top() + 10;
    int itemHeight = 22;
    int colorSize = 15;

    int total = m_data["Hommes"] + m_data["Femmes"];
    double percentageHommes = total > 0 ? (m_data["Hommes"] * 100.0) / total : 0;
    double percentageFemmes = total > 0 ? (m_data["Femmes"] * 100.0) / total : 0;

    // Hommes
    painter.setBrush(QColor(65, 105, 225));
    painter.setPen(QColor(100, 100, 100));
    painter.drawRect(x, y, colorSize, colorSize);

    painter.setPen(QColor(50, 50, 50));
    QString legendHommes = QString("Hommes: %1 (%2%)")
                               .arg(m_data["Hommes"])
                               .arg(percentageHommes, 0, 'f', 1);
    painter.drawText(x + colorSize + 10, y + colorSize - 3, legendHommes);

    // Femmes
    y += itemHeight;
    painter.setBrush(QColor(255, 105, 180));
    painter.setPen(QColor(100, 100, 100));
    painter.drawRect(x, y, colorSize, colorSize);

    painter.setPen(QColor(50, 50, 50));
    QString legendFemmes = QString("Femmes: %1 (%2%)")
                               .arg(m_data["Femmes"])
                               .arg(percentageFemmes, 0, 'f', 1);
    painter.drawText(x + colorSize + 10, y + colorSize - 3, legendFemmes);

    // Total
    y += itemHeight + 5;
    painter.setPen(QColor(45, 34, 76));
    painter.setFont(QFont("Arial", 11, QFont::Bold));
    painter.drawText(QRect(rect.left(), y, rect.width(), 25),
                     Qt::AlignCenter,
                     QString("Total: %1 clients").arg(total));
}
