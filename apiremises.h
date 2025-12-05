#ifndef APIREMISES_H
#define APIREMISES_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTimer>
#include <QRegularExpression>

class ApiRemises : public QObject
{
    Q_OBJECT

public:
    explicit ApiRemises(QObject *parent = nullptr);

    // Méthode pour calculer la remise automatique basée sur la quantité
    void calculerRemiseAutomatique(int idProduit, int quantite);

    // Méthode pour appliquer une remise manuelle
    void appliquerRemiseManuelle(int idProduit, float remise);

    // Vérifier si l'API est disponible
    void testerConnexionAPI();

    // Activer/désactiver le mode simulation
    void setModeSimulation(bool active);

signals:
    void remiseCalculee(float remise);
    void erreurAPI(const QString &message);
    void connexionTestee(bool succes);

private slots:
    void onReponseAPI(QNetworkReply *reply);

private:
    QNetworkAccessManager *m_manager;
    QString m_apiKey;
    bool m_modeSimulation;

    // Méthodes de simulation
    float calculerRemiseSimulation(int quantite);
    void simulerReponseAPI(int idProduit, int quantite);
};

#endif // APIREMISES_H
