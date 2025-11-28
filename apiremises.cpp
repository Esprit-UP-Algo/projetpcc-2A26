#include "apiremises.h"
#include <QNetworkRequest>
#include <QUrl>
#include <QDebug>
#include <QMessageBox>

ApiRemises::ApiRemises(QObject *parent)
    : QObject(parent)
    , m_manager(new QNetworkAccessManager(this))
    , m_baseUrl("http://localhost:3000")
    , m_modeSimulation(true)  // ← FORCER le mode simulation
{
    qDebug() << "🔧 Mode simulation FORCÉ - API désactivée";
}
void ApiRemises::setModeSimulation(bool active)
{
    m_modeSimulation = active;
    qDebug() << (active ? "🔧 Mode simulation ACTIVÉ" : "🌐 Mode réseau ACTIVÉ");
}
void ApiRemises::calculerRemiseAutomatique(int idProduit, int quantite)
{
    qDebug() << "🔍 DEBUG - calculerRemiseAutomatique appelé avec:";
    qDebug() << "   ID Produit:" << idProduit;
    qDebug() << "   Quantité:" << quantite;

    if (idProduit <= 0) {
        qDebug() << "❌ ID produit invalide:" << idProduit;
        emit erreurAPI("ID produit invalide");
        return;
    }

    if (quantite < 0) {
        qDebug() << "❌ Quantité invalide:" << quantite;
        emit erreurAPI("Quantité invalide");
        return;
    }

    // Si mode simulation, utiliser la logique locale
    if (m_modeSimulation) {
        qDebug() << "🔧 Mode simulation - Calcul local";
        simulerReponseAPI(idProduit, quantite);
        return;
    }

    QUrl url(m_baseUrl + "/api/produits/" + QString::number(idProduit) + "/quantite");
    qDebug() << "🌐 URL appelée:" << url.toString();

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["quantite"] = quantite;

    QJsonDocument doc(json);
    QByteArray data = doc.toJson();

    qDebug() << "📦 Données envoyées:" << data;

    QNetworkReply *reply = m_manager->put(request, data);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        onReponseRemise(reply);
    });
}
float ApiRemises::calculerRemiseSimulation(int quantite)
{
    // Même logique que l'API
    if (quantite >= 100) return 25;
    else if (quantite >= 50) return 15;
    else if (quantite >= 20) return 10;
    else if (quantite >= 10) return 5;
    else return 0;
}
void ApiRemises::simulerReponseAPI(int idProduit, int quantite)
{
    Q_UNUSED(idProduit);

    float remise = calculerRemiseSimulation(quantite);
    qDebug() << "🔧 Simulation - Quantité:" << quantite << "→ Remise:" << remise << "%";

    // Simuler un délai réseau
    QTimer::singleShot(500, this, [this, remise]() {
        emit remiseCalculee(remise);
    });
}
void ApiRemises::appliquerRemiseManuelle(int idProduit, float remise)
{
    if (idProduit <= 0) {
        emit erreurAPI("ID produit invalide");
        return;
    }

    QUrl url(m_baseUrl + "/api/produits/" + QString::number(idProduit) + "/remise");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["remise"] = remise;

    QJsonDocument doc(json);
    QByteArray data = doc.toJson();

    QNetworkReply *reply = m_manager->put(request, data);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() { onReponseRemise(reply); });
}

void ApiRemises::testerConnexionAPI()
{
    QUrl url(m_baseUrl);
    QNetworkRequest request(url);

    QNetworkReply *reply = m_manager->get(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() { onTestConnexion(reply); });
}

void ApiRemises::onReponseRemise(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        qDebug() << "✅ Réponse API:" << response;

        QJsonDocument doc = QJsonDocument::fromJson(response);
        if (doc.isNull()) {
            emit erreurAPI("Réponse API invalide (JSON corrompu)");
            reply->deleteLater();
            return;
        }

        QJsonObject obj = doc.object();

        if (obj["success"].toBool()) {
            QJsonObject data = obj["data"].toObject();
            float remise = data["REMISE"].toDouble();
            qDebug() << "🎯 Remise calculée:" << remise << "%";
            emit remiseCalculee(remise);
        } else {
            QString erreur = obj["error"].toString();
            if (erreur.isEmpty()) erreur = "Erreur inconnue de l'API";
            emit erreurAPI("Erreur API: " + erreur);
        }
    } else {
        QString erreurReseau = reply->errorString();
        qDebug() << "❌ Erreur réseau:" << erreurReseau;

        if (reply->error() == QNetworkReply::ConnectionRefusedError) {
            emit erreurAPI("API non disponible - Vérifiez que le serveur Node.js est démarré");
        } else if (reply->error() == QNetworkReply::HostNotFoundError) {
            emit erreurAPI("Serveur introuvable - Vérifiez l'URL de l'API");
        } else if (reply->error() == QNetworkReply::TimeoutError) {
            emit erreurAPI("Timeout - L'API ne répond pas");
        } else {
            emit erreurAPI("Erreur réseau: " + erreurReseau);
        }
    }

    reply->deleteLater();
}

void ApiRemises::onTestConnexion(QNetworkReply *reply)
{
    bool succes = (reply->error() == QNetworkReply::NoError);
    qDebug() << (succes ? "✅ API connectée" : "❌ API non disponible");
    emit connexionTestee(succes);
    reply->deleteLater();
}
