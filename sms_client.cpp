
#include "SMS_client.h"

SMS_client::SMS_client(QWidget *parent, QString phoneNumber, QString clientName)
    : QDialog(parent)
    , m_phoneNumber(phoneNumber)
    , m_clientName(clientName)
    , m_networkManager(new QNetworkAccessManager(this))
{
    setWindowTitle("Envoyer SMS - " + clientName);
    setFixedSize(500, 400);
    setStyleSheet("QDialog { background-color: #f8f9fa; font-family: Arial, sans-serif; }");

    // Création des widgets
    lblClientInfo = new QLabel(this);
    lblClientInfo->setText("📱 Envoyer SMS à : " + clientName + " | Tél: " + phoneNumber);
    lblClientInfo->setStyleSheet(
        "font-weight: bold; color: #2d224c; padding: 12px; "
        "background-color: #e9ecef; border-radius: 8px; "
        "border-left: 4px solid #6c5ce7; font-size: 14px;"
        );
    lblClientInfo->setWordWrap(true);

    lblMessage = new QLabel("Message SMS:", this);
    lblMessage->setStyleSheet("font-weight: bold; color: #2d3436; font-size: 13px; margin-top: 10px;");

    textEditMessage = new QTextEdit(this);
    textEditMessage->setPlaceholderText("Tapez votre message SMS ici...\n\nExemple: Bonjour " + clientName.split(" ").first() + ", ...");
    textEditMessage->setStyleSheet(
        "QTextEdit {"
        "    border: 2px solid #dfe6e9;"
        "    border-radius: 8px;"
        "    padding: 12px;"
        "    font-size: 14px;"
        "    background-color: white;"
        "    min-height: 150px;"
        "}"
        "QTextEdit:focus {"
        "    border: 2px solid #6c5ce7;"
        "}"
        );

    lblCaracteres = new QLabel("0/480 caractères", this);
    lblCaracteres->setStyleSheet("color: #636e72; font-size: 12px; padding: 5px;");
    lblCaracteres->setAlignment(Qt::AlignRight);

    btnAnnuler = new QPushButton("Annuler", this);
    btnAnnuler->setMinimumSize(100, 35);
    btnAnnuler->setStyleSheet(
        "QPushButton {"
        "    background-color: #636e72;"
        "    color: white;"
        "    font-weight: bold;"
        "    border-radius: 8px;"
        "    padding: 8px 16px;"
        "    font-size: 14px;"
        "    border: none;"
        "}"
        "QPushButton:hover {"
        "    background-color: #2d3436;"
        "}"
        );

    btnEnvoyer = new QPushButton("Envoyer SMS", this);
    btnEnvoyer->setMinimumSize(120, 35);
    btnEnvoyer->setStyleSheet(
        "QPushButton {"
        "    background-color: #00b894;"
        "    color: white;"
        "    font-weight: bold;"
        "    border-radius: 8px;"
        "    padding: 8px 16px;"
        "    font-size: 14px;"
        "    border: none;"
        "}"
        "QPushButton:hover {"
        "    background-color: #00a085;"
        "}"
        );

    // Création des layouts
    mainLayout = new QVBoxLayout(this);
    buttonLayout = new QHBoxLayout();

    // Organisation des widgets
    mainLayout->addWidget(lblClientInfo);
    mainLayout->addWidget(lblMessage);
    mainLayout->addWidget(textEditMessage);
    mainLayout->addWidget(lblCaracteres);

    buttonLayout->addStretch();
    buttonLayout->addWidget(btnAnnuler);
    buttonLayout->addWidget(btnEnvoyer);

    mainLayout->addLayout(buttonLayout);

    // Connexions
    connect(btnEnvoyer, &QPushButton::clicked, this, &SMS_client::onEnvoyerClicked);
    connect(btnAnnuler, &QPushButton::clicked, this, &SMS_client::onAnnulerClicked);
    connect(textEditMessage, &QTextEdit::textChanged, this, &SMS_client::updateCaracteresCount);
    connect(m_networkManager, &QNetworkAccessManager::finished, this, &SMS_client::onTwilioReplyFinished);

    updateCaracteresCount();
}

SMS_client::~SMS_client()
{
}

QString SMS_client::formatPhoneNumber(const QString &numero)
{
    // Si commence par +, garder tel quel
    if (numero.startsWith("+")) {
        return numero;
    }

    // Sinon ajouter +216 pour la Tunisie
    QString clean = numero.trimmed();
    clean.remove(QRegularExpression("[^0-9]"));  // ← Corrigé pour Qt6

    if (clean.length() == 8) {
        return "+216" + clean;
    }

    return numero;
}

void SMS_client::envoyerSMSTwilio(const QString &numero, const QString &message)
{
    // ========================================
    // ⚠️ REMPLACE CES 3 VALEURS PAR TES CREDENTIALS TWILIO
    // ========================================
    QString ACCOUNT_SID = "AC7af75dbbd6e6b12ce370a914d3305896";  // ← TON ACCOUNT SID
    QString AUTH_TOKEN = "ae205d98162f319cb0a9d89032606a2b";                   // ← TON AUTH TOKEN
    QString TWILIO_NUMBER = "+15342486760";                      // ← TON NUMÉRO TWILIO

    // Vérification
    if (ACCOUNT_SID.startsWith("ACX") || AUTH_TOKEN == "ton_auth_token_ici") {
        QMessageBox::critical(this, "Configuration manquante",
                              "⚠️ Tu dois d'abord configurer tes credentials Twilio dans le code !\n\n"
                              "Ouvre sms_client.cpp et remplace :\n"
                              "- ACCOUNT_SID\n"
                              "- AUTH_TOKEN\n"
                              "- TWILIO_NUMBER");
        btnEnvoyer->setEnabled(true);
        btnEnvoyer->setText("Envoyer SMS");
        return;
    }

    QString numeroFormate = formatPhoneNumber(numero);

    // URL de l'API Twilio
    QString urlString = QString("https://api.twilio.com/2010-04-01/Accounts/%1/Messages.json")
                            .arg(ACCOUNT_SID);

    QNetworkRequest request;  // ← Corrigé : enlever les parenthèses
    request.setUrl(QUrl(urlString));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    // Authentification Basic
    QString credentials = ACCOUNT_SID + ":" + AUTH_TOKEN;
    QByteArray credentialsBase64 = credentials.toUtf8().toBase64();
    request.setRawHeader("Authorization", "Basic " + credentialsBase64);

    // Données POST
    QUrlQuery postData;
    postData.addQueryItem("From", TWILIO_NUMBER);
    postData.addQueryItem("To", numeroFormate);
    postData.addQueryItem("Body", message);

    QByteArray postDataEncoded = postData.toString(QUrl::FullyEncoded).toUtf8();

    qDebug() << "📤 Envoi SMS Twilio...";
    qDebug() << "   De:" << TWILIO_NUMBER;
    qDebug() << "   À:" << numeroFormate;
    qDebug() << "   Message:" << message.left(50) + (message.length() > 50 ? "..." : "");

    // Envoyer
    m_networkManager->post(request, postDataEncoded);
}

void SMS_client::onEnvoyerClicked()
{
    QString message = textEditMessage->toPlainText().trimmed();

    if (message.isEmpty()) {
        QMessageBox::warning(this, "Message vide", "Veuillez écrire un message avant d'envoyer.");
        return;
    }

    if (message.length() > 480) {
        QMessageBox::warning(this, "Message trop long",
                             "Le message est trop long pour un SMS (maximum 480 caractères).\n\n"
                             "Votre message fait " + QString::number(message.length()) + " caractères.");
        return;
    }

    // Désactiver le bouton pendant l'envoi
    btnEnvoyer->setEnabled(false);
    btnEnvoyer->setText("Envoi en cours...");

    // Envoyer le SMS via Twilio
    envoyerSMSTwilio(m_phoneNumber, message);
}

void SMS_client::onTwilioReplyFinished(QNetworkReply *reply)
{
    btnEnvoyer->setEnabled(true);
    btnEnvoyer->setText("Envoyer SMS");

    if (reply->error() == QNetworkReply::NoError) {
        // Succès !
        QByteArray response = reply->readAll();
        qDebug() << "✅ Réponse Twilio:" << response;

        QString message = textEditMessage->toPlainText().trimmed();
        QMessageBox::information(this, "SMS envoyé",
                                 "✅ SMS envoyé avec succès !\n\n"
                                 "👤 Client: " + m_clientName + "\n"
                                                      "📞 Téléphone: +216" + m_phoneNumber + "\n"
                                                       "💬 Message (" + QString::number(message.length()) + " caractères):\n" +
                                     "\"" + message.left(100) + (message.length() > 100 ? "...\"" : "\""));

        this->accept();
    } else {
        // Erreur
        QString erreur = reply->errorString();
        QByteArray errorDetails = reply->readAll();

        qDebug() << "❌ Erreur Twilio:" << erreur;
        qDebug() << "   Détails:" << errorDetails;

        QString messageErreur = "Erreur lors de l'envoi du SMS:\n" + erreur;

        // Analyser les erreurs courantes
        if (errorDetails.contains("21211")) {
            messageErreur = "❌ Numéro de téléphone invalide !\n\nVérifiez que le numéro est correct.";
        } else if (errorDetails.contains("21608")) {
            messageErreur = "❌ Numéro non vérifié !\n\nAvec un compte Twilio gratuit, vous devez d'abord vérifier le numéro du destinataire dans votre console Twilio.\n\nAllez sur console.twilio.com pour vérifier ce numéro.";
        } else if (errorDetails.contains("20003")) {
            messageErreur = "❌ Authentification refusée !\n\nVérifiez votre Account SID et Auth Token dans le code.";
        }

        QMessageBox::critical(this, "Erreur d'envoi", messageErreur);
    }

    reply->deleteLater();
}

void SMS_client::onAnnulerClicked()
{
    this->reject();
}

void SMS_client::updateCaracteresCount()
{
    int length = textEditMessage->toPlainText().length();
    lblCaracteres->setText(QString("%1/480 caractères").arg(length));

    if (length > 450) {
        lblCaracteres->setStyleSheet("color: #e74c3c; font-size: 12px; padding: 5px; font-weight: bold;");
    } else if (length > 400) {
        lblCaracteres->setStyleSheet("color: #e67e22; font-size: 12px; padding: 5px;");
    } else {
        lblCaracteres->setStyleSheet("color: #636e72; font-size: 12px; padding: 5px;");
    }
}

