#ifndef STATISTICSWIDGET_PRODUIT_H
#define STATISTICSWIDGET_PRODUIT_H

#include <QWidget>
#include <QMap>
#include <QTimer>

class StatisticsWidgetProduit : public QWidget
{
    Q_OBJECT

public:
    void deplacerVersBas(int decalage);
    void deplacerManuellement(int x, int y);
    void redimensionnerManuellement(int largeur, int hauteur);
    void deplacerEtRedimensionner(int x, int y, int largeur, int hauteur);
    void deplacerVersDroite(int decalage);
    explicit StatisticsWidgetProduit(QWidget *parent = nullptr);
    void rafraichirStatistiques();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void onAnimationTimer();

private:
    QMap<QString, int> m_data;
    QMap<QString, int> m_prixData;
    QTimer *m_animationTimer;
    double m_animationProgress;

    void drawPieChart(QPainter &painter, const QRect &rect);
    void drawBarChart(QPainter &painter, const QRect &rect);
    void drawLegend(QPainter &painter, const QRect &rect);
    void loadPrixData();
    QString getPrixGroup(float prix);
};

#endif
