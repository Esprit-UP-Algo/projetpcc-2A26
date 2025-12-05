#include "StatisticsWidgetProduit.h"
#include <QPainter>
#include <QSqlQuery>
#include <cmath>
#include "connection.h"

StatisticsWidgetProduit::StatisticsWidgetProduit(QWidget *parent)
    : QWidget(parent)
    , m_animationProgress(0.0)
{
    setFixedSize(320, 550); // Hauteur totale pour les deux parties

    m_animationTimer = new QTimer(this);
    connect(m_animationTimer, &QTimer::timeout, this, &StatisticsWidgetProduit::onAnimationTimer);
    m_animationTimer->start(16);

    rafraichirStatistiques();
}

void StatisticsWidgetProduit::rafraichirStatistiques()
{
    // Charger les données de genre
    m_data.clear();
    m_data["Homme"] = 0;
    m_data["Femme"] = 0;
    m_data["Unisexe"] = 0;

    Connection c;
    if (c.createconnect()) {
        QSqlQuery query;
        query.prepare("SELECT GENRE, COUNT(*) FROM PRODUIT GROUP BY GENRE");

        if (query.exec()) {
            while (query.next()) {
                QString genre = query.value(0).toString();
                int count = query.value(1).toInt();
                m_data[genre] += count;
            }
        }
    }

    // Charger les données de prix
    loadPrixData();
    m_animationProgress = 0.0;
    update();
}

void StatisticsWidgetProduit::loadPrixData()
{
    m_prixData.clear();
    m_prixData["0-50"] = 0;
    m_prixData["50-100"] = 0;
    m_prixData["100-200"] = 0;
    m_prixData["200+"] = 0;

    Connection c;
    if (c.createconnect()) {
        QSqlQuery query;
        query.prepare("SELECT PRIX FROM PRODUIT");

        if (query.exec()) {
            while (query.next()) {
                float prix = query.value(0).toFloat();
                QString groupe = getPrixGroup(prix);
                m_prixData[groupe]++;
            }
        }
    }
}

QString StatisticsWidgetProduit::getPrixGroup(float prix)
{
    if (prix < 50) return "0-50";
    else if (prix < 100) return "50-100";
    else if (prix < 200) return "100-200";
    else return "200+";
}

void StatisticsWidgetProduit::onAnimationTimer()
{
    if (m_animationProgress < 1.0) {
        m_animationProgress += 0.02;
        if (m_animationProgress > 1.0) m_animationProgress = 1.0;
        update();
    }
}

void StatisticsWidgetProduit::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Fond général
    QLinearGradient gradient(0, 0, width(), height());
    gradient.setColorAt(0, QColor(248, 250, 252));
    gradient.setColorAt(1, QColor(241, 245, 249));
    painter.fillRect(rect(), gradient);

    // ==================== PREMIÈRE PARTIE : STATISTIQUES PRODUITS ====================

    // Titre première partie
    painter.setPen(QColor(30, 41, 59));
    painter.setFont(QFont("Segoe UI", 12, QFont::Bold));
    painter.drawText(QRect(0, 10, width(), 25), Qt::AlignCenter, "Statistiques Produits");

    // Graphique circulaire pour les genres
    QRect pieRect(70, 35, width() - 140, 120);
    drawPieChart(painter, pieRect);

    // Légende pour les genres
    QRect legendRect(20, 165, width() - 40, 80);
    drawLegend(painter, legendRect);

    // ==================== DEUXIÈME PARTIE : RÉPARTITION PAR PRIX ====================

    // Ligne de séparation
    painter.setPen(QPen(QColor(200, 200, 200), 1));
    painter.drawLine(20, 260, width() - 20, 260);

    // Titre deuxième partie - PLACÉ EN DESSOUS
    painter.setPen(QColor(30, 41, 59));
    painter.setFont(QFont("Segoe UI", 12, QFont::Bold));
    painter.drawText(QRect(0, 275, width(), 25), Qt::AlignCenter, "Répartition par Prix");

    // Graphique en barres pour les prix - PLACÉ EN DESSOUS
    QRect barRect(40, 300, width() - 80, 200);
    drawBarChart(painter, barRect);
}

void StatisticsWidgetProduit::drawPieChart(QPainter &painter, const QRect &rect)
{
    int total = m_data["Homme"] + m_data["Femme"] + m_data["Unisexe"];
    if (total == 0) {
        painter.setPen(QColor(100, 116, 139));
        painter.setFont(QFont("Segoe UI", 10));
        painter.drawText(rect, Qt::AlignCenter, "Aucun produit");
        return;
    }

    QColor colors[3] = {
        QColor(59, 130, 246),  // Bleu pour Homme
        QColor(236, 72, 153),  // Rose pour Femme
        QColor(16, 185, 129)   // Vert pour Unisexe
    };

    QString labels[3] = {"Homme", "Femme", "Unisexe"};
    int values[3] = {m_data["Homme"], m_data["Femme"], m_data["Unisexe"]};

    int startAngle = 0;
    painter.setPen(Qt::NoPen);

    for (int i = 0; i < 3; i++) {
        if (values[i] > 0) {
            double animatedValue = values[i] * m_animationProgress;
            int spanAngle = (animatedValue * 360 * 16) / total;

            QRadialGradient gradient(rect.center(), rect.width()/2);
            gradient.setColorAt(0, colors[i].lighter(120));
            gradient.setColorAt(1, colors[i]);
            painter.setBrush(gradient);

            painter.drawPie(rect, startAngle, spanAngle);
            startAngle += spanAngle;
        }
    }

    painter.setBrush(Qt::NoBrush);
    painter.setPen(QColor(148, 163, 184));
    painter.drawEllipse(rect);
}

void StatisticsWidgetProduit::drawBarChart(QPainter &painter, const QRect &rect)
{
    QString groupes[4] = {"0-50", "50-100", "100-200", "200+"};
    QColor colors[4] = {
        QColor(96, 165, 250),   // Bleu
        QColor(139, 92, 246),   // Violet
        QColor(245, 158, 11),   // Orange
        QColor(239, 68, 68)     // Rouge
    };

    int maxCount = 0;
    for (const QString &groupe : groupes) {
        if (m_prixData[groupe] > maxCount)
            maxCount = m_prixData[groupe];
    }
    if (maxCount == 0) maxCount = 10;

    int chartBottom = rect.bottom() - 30;
    int chartHeight = rect.height() - 50;
    int chartLeft = rect.left() + 40;

    // Axes
    painter.setPen(QColor(148, 163, 184));
    painter.drawLine(chartLeft, rect.top() + 15, chartLeft, chartBottom);
    painter.drawLine(chartLeft, chartBottom, rect.right(), chartBottom);

    int barWidth = 35;
    int barSpacing = 20;
    int x = chartLeft + barSpacing;

    for (int i = 0; i < 4; i++) {
        double animatedCount = m_prixData[groupes[i]] * m_animationProgress;
        int barHeight = (animatedCount * chartHeight) / maxCount;
        int barY = chartBottom - barHeight;

        // Barre avec dégradé
        QLinearGradient gradient(x, barY, x + barWidth, chartBottom);
        gradient.setColorAt(0, colors[i].lighter(120));
        gradient.setColorAt(1, colors[i]);
        painter.setBrush(gradient);
        painter.setPen(QPen(colors[i].darker(120), 1));
        painter.drawRect(x, barY, barWidth, barHeight);

        // Valeur au-dessus de la barre
        painter.setPen(QColor(30, 41, 59));
        painter.setFont(QFont("Segoe UI", 9, QFont::Bold));
        painter.drawText(QRect(x, barY - 20, barWidth, 20), Qt::AlignCenter, QString::number(m_prixData[groupes[i]]));

        // Libellé en dessous
        painter.setPen(QColor(71, 85, 105));
        painter.setFont(QFont("Segoe UI", 8));
        painter.drawText(QRect(x, chartBottom + 3, barWidth, 20), Qt::AlignCenter, groupes[i] + " DT");

        x += (barWidth + barSpacing);
    }
}

void StatisticsWidgetProduit::drawLegend(QPainter &painter, const QRect &rect)
{
    painter.setPen(QColor(30, 41, 59));
    painter.setFont(QFont("Segoe UI", 9));

    int x = rect.left() + 20;
    int y = rect.top() + 10;
    int itemHeight = 20;
    int colorSize = 12;

    QColor colors[3] = {
        QColor(59, 130, 246),
        QColor(236, 72, 153),
        QColor(16, 185, 129)
    };

    QString labels[3] = {"Homme", "Femme", "Unisexe"};
    int total = m_data["Homme"] + m_data["Femme"] + m_data["Unisexe"];

    for (int i = 0; i < 3; i++) {
        painter.setBrush(colors[i]);
        painter.setPen(QColor(148, 163, 184));
        painter.drawRect(x, y, colorSize, colorSize);

        painter.setPen(QColor(30, 41, 59));
        double percentage = total > 0 ? (m_data[labels[i]] * 100.0) / total : 0;
        QString legend = QString("%1: %2 (%3%)").arg(labels[i]).arg(m_data[labels[i]]).arg(percentage, 0, 'f', 1);
        painter.drawText(x + colorSize + 8, y + colorSize - 2, legend);
        y += itemHeight;
    }

    y += 5;
    painter.setPen(QColor(30, 41, 59));
    painter.setFont(QFont("Segoe UI", 10, QFont::Bold));
    painter.drawText(QRect(rect.left(), y, rect.width(), 20), Qt::AlignCenter, QString("Total: %1 produits").arg(total));
}

// Méthodes de positionnement existantes
void StatisticsWidgetProduit::deplacerVersDroite(int decalage)
{
    QRect currentGeometry = geometry();
    setGeometry(currentGeometry.x() + decalage, currentGeometry.y(),
                currentGeometry.width(), currentGeometry.height());
}

void StatisticsWidgetProduit::deplacerVersBas(int decalage)
{
    QRect currentGeometry = geometry();
    setGeometry(currentGeometry.x(), currentGeometry.y() + decalage,
                currentGeometry.width(), currentGeometry.height());
}

void StatisticsWidgetProduit::deplacerManuellement(int x, int y)
{
    QRect currentGeometry = geometry();
    setGeometry(x, y, currentGeometry.width(), currentGeometry.height());
}

void StatisticsWidgetProduit::redimensionnerManuellement(int largeur, int hauteur)
{
    QRect currentGeometry = geometry();
    setGeometry(currentGeometry.x(), currentGeometry.y(), largeur, hauteur);
}

void StatisticsWidgetProduit::deplacerEtRedimensionner(int x, int y, int largeur, int hauteur)
{
    setGeometry(x, y, largeur, hauteur);
}
