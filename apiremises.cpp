#include "apiremises.h"
#include <QNetworkRequest>
#include <QUrl>
#include <QDebug>
#include <QMessageBox>
#include <QRegularExpression>

ApiRemises::ApiRemises(QObject *parent)
    : QObject(parent)
    , m_manager(new QNetworkAccessManager(this))
    , m_apiKey("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")
    , m_modeSimulation(false)
{
    connect(m_manager, &QNetworkAccessManager::finished, this, &ApiRemises::onReponseAPI);
    qDebug() << "🔧 API Remises initialisée - Clé API Groq configurée";
}

void ApiRemises::setModeSimulation(bool active)
{
    m_modeSimulation = active;
    qDebug() << (active ? "🔧 Mode simulation ACTIVÉ" : "🌐 Mode API Groq ACTIVÉ");
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

    // Utiliser l'API Groq pour un calcul intelligent
    QUrl url("https://api.groq.com/openai/v1/chat/completions");
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", QString("Bearer %1").arg(m_apiKey).toUtf8());

    // Créer le prompt pour l'IA
    QJsonObject messageObj;
    messageObj["role"] = "user";
    messageObj["content"] = QString(
                                "En tant qu'expert en stratégie de prix OPTIMATECH, calcule le pourcentage de remise optimal "
                                "pour une commande de %1 unités de produits optiques. "
                                "Considérations importantes :\n"
                                "- Nous sommes une entreprise spécialisée en optique (lunettes, lentilles, etc.)\n"
                                "- Marge standard : 40-60%\n"
                                "- Clientèle : particuliers et professionnels\n"
                                "- Politique de remise : progressive selon le volume\n\n"
                                "Règles métier OPTIMATECH :\n"
                                "• 1-9 unités : 0%% de remise (vente unitaire standard)\n"
                                "• 10-19 unités : 5%% de remise (petit volume)\n"
                                "• 20-49 unités : 10%% de remise (volume moyen)\n"
                                "• 50-99 unités : 15%% de remise (gros volume)\n"
                                "• 100+ unités : 25%% de remise (très gros volume)\n\n"
                                "Pour %1 unités, réponds UNIQUEMENT par le chiffre du pourcentage sans aucun texte, symbole ou explication. "
                                "Exemple de réponse attendue : '10'"
                                ).arg(quantite);

    QJsonArray messagesArray;
    messagesArray.append(messageObj);

    QJsonObject data;
    data["messages"] = messagesArray;
    data["model"] = "llama-3.1-8b-instant";
    data["temperature"] = 0.1;
    data["max_tokens"] = 5;
    data["stream"] = false;

    QJsonDocument doc(data);
    QByteArray postData = doc.toJson();

    qDebug() << "🌐 Envoi requête à l'API Groq...";
    qDebug() << "📦 Quantité analysée:" << quantite;

    QNetworkReply *reply = m_manager->post(request, postData);
    reply->setProperty("idProduit", idProduit);
    reply->setProperty("quantite", quantite);
    reply->setProperty("type", "calculRemise");
}

float ApiRemises::calculerRemiseSimulation(int quantite)
{
    // Logique de remise simulée - identique aux règles métier
    if (quantite >= 100) return 25.0f;
    else if (quantite >= 50) return 15.0f;
    else if (quantite >= 20) return 10.0f;
    else if (quantite >= 10) return 5.0f;
    else return 0.0f;
}

void ApiRemises::simulerReponseAPI(int idProduit, int quantite)
{
    Q_UNUSED(idProduit);

    float remise = calculerRemiseSimulation(quantite);
    qDebug() << "🔧 Simulation - Quantité:" << quantite << "→ Remise:" << remise << "%";

    // Simuler un délai réseau
    QTimer::singleShot(800, this, [this, remise]() {
        emit remiseCalculee(remise);
    });
}

void ApiRemises::appliquerRemiseManuelle(int idProduit, float remise)
{
    Q_UNUSED(idProduit);

    // Pour les remises manuelles, on émet directement le signal
    qDebug() << "🔧 Remise manuelle appliquée:" << remise << "%";
    emit remiseCalculee(remise);
}

void ApiRemises::testerConnexionAPI()
{
    if (m_modeSimulation) {
        qDebug() << "🔧 Test connexion - Mode simulation actif";
        emit connexionTestee(true);
        return;
    }

    QUrl url("https://api.groq.com/openai/v1/models");
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", QString("Bearer %1").arg(m_apiKey).toUtf8());

    QNetworkReply *reply = m_manager->get(request);
    reply->setProperty("type", "testConnexion");
}

void ApiRemises::onReponseAPI(QNetworkReply *reply)
{
    QString type = reply->property("type").toString();
    int quantite = reply->property("quantite").toInt();

    if (reply->error() != QNetworkReply::NoError) {
        QString errorMsg = QString("Erreur API Groq: %1").arg(reply->errorString());
        qDebug() << "❌" << errorMsg;

        // En cas d'erreur, basculer en mode simulation
        if (!m_modeSimulation) {
            m_modeSimulation = true;
            qDebug() << "🔧 Basculement automatique en mode simulation";

            if (type == "calculRemise") {
                float remise = calculerRemiseSimulation(quantite);
                emit erreurAPI(errorMsg + " - Mode simulation activé");
                emit remiseCalculee(remise);
            }
        } else {
            emit erreurAPI(errorMsg);
        }

        reply->deleteLater();
        return;
    }

    QByteArray responseData = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(responseData);

    if (doc.isNull()) {
        emit erreurAPI("Réponse API Groq invalide - JSON corrompu");
        reply->deleteLater();
        return;
    }

    QJsonObject json = doc.object();

    if (type == "testConnexion") {
        bool succes = json.contains("data"); // L'API Groq retourne un objet avec "data"
        qDebug() << (succes ? "✅ Connexion API Groq réussie" : "❌ Réponse API Groq anormale");
        emit connexionTestee(succes);
    }
    else if (type == "calculRemise") {
        // Extraire la réponse de l'IA
        QString remiseText = "0";

        if (json.contains("choices") && json["choices"].isArray()) {
            QJsonArray choices = json["choices"].toArray();
            if (!choices.isEmpty()) {
                QJsonObject firstChoice = choices[0].toObject();
                if (firstChoice.contains("message") && firstChoice["message"].isObject()) {
                    QJsonObject message = firstChoice["message"].toObject();
                    if (message.contains("content")) {
                        remiseText = message["content"].toString().trimmed();
                        qDebug() << "🤖 Réponse IA brute:" << remiseText;
                    }
                }
            }
        }

        // Utiliser QRegularExpression pour nettoyer la réponse
        QRegularExpression regex("[^0-9.]");
        remiseText.remove(regex);

        bool ok;
        float remise = remiseText.toFloat(&ok);

        if (!ok || remise < 0 || remise > 100) {
            qDebug() << "⚠️ Réponse IA invalide, utilisation du mode simulation";
            remise = calculerRemiseSimulation(quantite);
            emit erreurAPI("Réponse IA invalide - Utilisation des règles métier");
        } else {
            qDebug() << "✅ Remise calculée par IA:" << remise << "%";
        }

        emit remiseCalculee(remise);
    }

    reply->deleteLater();
}
