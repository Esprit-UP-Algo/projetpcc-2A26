
#ifndef STATISTICSWIDGET_H
#define STATISTICSWIDGET_H

#include <QWidget>
#include <QMap>

class StatisticsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StatisticsWidget(QWidget *parent = nullptr);
    void rafraichirStatistiques();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QMap<QString, int> m_data;
    QMap<int, QMap<QString, int>> m_barData;

    void drawPieChart(QPainter &painter, const QRect &rect);
    void drawBarChart(QPainter &painter, const QRect &rect);
    void drawLegend(QPainter &painter, const QRect &rect);

    void loadBarChartData();
    int getAgeGroup(int age);
};

#endif // STATISTICSWIDGET_H
