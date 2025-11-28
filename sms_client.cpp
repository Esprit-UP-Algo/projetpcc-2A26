#include "SMS_client.h"

SMS_client::SMS_client(QWidget *parent, QString phoneNumber, QString clientName)
    : QDialog(parent)
    , m_phoneNumber(phoneNumber)
    , m_clientName(clientName)
{
    setWindowTitle("Envoyer SMS - " + clientName);
    setFixedSize(500, 400);
    setStyleSheet("QDialog { background-color: #f8f9fa; font-family: Arial, sans-serif; }");

    // Création des widgets
    lblClientInfo = new QLabel(this);
    lblClientInfo->setText("📱 Envoyer SMS à: " + clientName + " | Tél: " + phoneNumber);
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

    // Organisation des widgets dans les layouts
    mainLayout->addWidget(lblClientInfo);
    mainLayout->addWidget(lblMessage);
    mainLayout->addWidget(textEditMessage);
    mainLayout->addWidget(lblCaracteres);

    buttonLayout->addStretch();
    buttonLayout->addWidget(btnAnnuler);
    buttonLayout->addWidget(btnEnvoyer);

    mainLayout->addLayout(buttonLayout);

    // Connexions des signaux/slots
    connect(btnEnvoyer, &QPushButton::clicked, this, &SMS_client::onEnvoyerClicked);
    connect(btnAnnuler, &QPushButton::clicked, this, &SMS_client::onAnnulerClicked);
    connect(textEditMessage, &QTextEdit::textChanged, this, &SMS_client::updateCaracteresCount);

    // Initialiser le compteur
    updateCaracteresCount();
}

SMS_client::~SMS_client()
{
    // Les widgets seront détruits automatiquement car this est leur parent
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

    // Simulation d'envoi
    qDebug() << "=== SIMULATION ENVOI SMS ===";
    qDebug() << "Destinataire:" << m_clientName;
    qDebug() << "Téléphone:" << m_phoneNumber;
    qDebug() << "Message:" << message;
    qDebug() << "Longueur:" << message.length() << "caractères";
    qDebug() << "=============================";

    // Message de confirmation
    QMessageBox::information(this, "SMS envoyé",
                             "✅ SMS envoyé avec succès !\n\n"
                             "👤 Client: " + m_clientName + "\n"
                                                  "📞 Téléphone: " + m_phoneNumber + "\n"
                                                   "💬 Message (" + QString::number(message.length()) + " caractères):\n" +
                                 "\"" + message.left(100) + (message.length() > 100 ? "...\"" : "\""));

    this->accept();
}

void SMS_client::onAnnulerClicked()
{
    this->reject();
}

void SMS_client::updateCaracteresCount()
{
    int length = textEditMessage->toPlainText().length();
    lblCaracteres->setText(QString("%1/480 caractères").arg(length));

    // Changer la couleur si approche de la limite
    if (length > 450) {
        lblCaracteres->setStyleSheet("color: #e74c3c; font-size: 12px; padding: 5px; font-weight: bold;");
    } else if (length > 400) {
        lblCaracteres->setStyleSheet("color: #e67e22; font-size: 12px; padding: 5px;");
    } else {
        lblCaracteres->setStyleSheet("color: #636e72; font-size: 12px; padding: 5px;");
    }
}
