#include <QtCore/QCoreApplication>
#include <QCoreApplication>
#include <QFile>
#include <QString>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QSslConfiguration>
#include <QList>
#include <QSslCertificate>
#include <QSslError>
#include <QDebug>
#include <QTimer>
#include <QUrl>
#include <QDateTime>
#include "listerrs.h"

#define SERVER_URL "https://www.twitter.com/"
#define NETWORK_ERROR "Network Error"
#define NO_RESPONSE "no response"

QString networkRequest(QString path) {

    QNetworkAccessManager m_Manager;
    QEventLoop eventLoop;
    ListErrs listErrs;
    QNetworkRequest request(QUrl(QString(SERVER_URL) + path));
    QList<QSslCertificate> certList;

    qDebug() << "license server url: " << SERVER_URL;

    // Verisign G5 root cert from:
    // http://www.verisign.com/repository/roots/root-certificates/PCA-3G5.pem
    QFile certFile1(":/twitter.txt"); 
    qDebug() << "opening Verisign cert: " << certFile1.open(QIODevice::ReadOnly);
    QSslCertificate cert1(&certFile1, QSsl::Pem);
    qDebug() << "Is Verisign valid? " << cert1.isValid();
    qDebug() << "Verisign org name? " << cert1.issuerInfo(QSslCertificate::Organization);
    QByteArray dig = cert1.digest();
    qDebug() << "Verisign digest? " << (int)dig[0] << (int)dig[1] << (int)dig[2] << (int)dig[3] << (int)dig[4] << (int)dig[5];
    qDebug() << "Verisign serial number? " << cert1.serialNumber();
    qDebug() << "Verisign expires? " << cert1.expiryDate();
    qDebug() << "Verisign effective? " << cert1.effectiveDate();
    qDebug() << "version == 10.5 " << (QSysInfo::MacintoshVersion == QSysInfo::MV_10_5);
      certList.append(cert1);

    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    QSslConfiguration sslConfig(request.sslConfiguration());
    sslConfig.setCaCertificates(certList);
    request.setSslConfiguration(sslConfig);

    QNetworkReply *reply = m_Manager.get(request);
    QObject::connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    QObject::connect(&m_Manager, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)), &listErrs, SLOT(go(QNetworkReply*,QList<QSslError>)));
    // Quit after 15 seconds in any event
    QTimer::singleShot(15000, &eventLoop, SLOT(quit()));
    eventLoop.exec();
    QString result = reply->readAll();
    if (reply->error() != QNetworkReply::NoError)
    {
        result = QString(NETWORK_ERROR) + " - "  + reply->errorString();
    }
    qDebug() << result;
    return result;
}

int main(int argc, char *argv[])
{
    QCoreApplication instance(argc, argv);
    qDebug() << networkRequest("");

    return 0;
}
