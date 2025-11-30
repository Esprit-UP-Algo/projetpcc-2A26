
#ifndef SMS_CLIENT_H
#define SMS_CLIENT_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QDebug>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QRegularExpression>

class SMS_client : public QDialog
{
    Q_OBJECT

public:
    explicit SMS_client(QWidget *parent = nullptr,
                        QString phoneNumber = "",
                        QString clientName = "");
    ~SMS_client();

private slots:
    void onEnvoyerClicked();
    void onAnnulerClicked();
    void updateCaracteresCount();
    void onTwilioReplyFinished(QNetworkReply *reply);

private:
    QString m_phoneNumber;
    QString m_clientName;
    QNetworkAccessManager *m_networkManager;

    // Widgets
    QLabel *lblClientInfo;
    QLabel *lblMessage;
    QTextEdit *textEditMessage;
    QLabel *lblCaracteres;
    QPushButton *btnAnnuler;
    QPushButton *btnEnvoyer;

    // Layouts
    QVBoxLayout *mainLayout;
    QHBoxLayout *buttonLayout;

    // Méthodes privées pour Twilio
    QString formatPhoneNumber(const QString &numero);
    void envoyerSMSTwilio(const QString &numero, const QString &message);
};

#endif // SMS_CLIENT_H
