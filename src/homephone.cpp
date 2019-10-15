#include "homephone.h"

using namespace adiscope;

QString HomePhone::m_scopyVersion;
QString HomePhone::m_m2kVersion;

void HomePhone::scopyVersionRequest()
{
	QNetworkAccessManager* manager = new QNetworkAccessManager();
	connect(manager, &QNetworkAccessManager::finished, this, &HomePhone::onScopyRequestFinished);
	connect(manager, SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));

	manager->get(QNetworkRequest(QUrl(QString::fromUtf8("http://analog-applications-versions.herokuapp.com/scopy"))));
}

void HomePhone::onScopyRequestFinished(QNetworkReply* reply)
{
	if (reply->error() == QNetworkReply::NoError) {
		HomePhone::m_scopyVersion = reply->readAll();
		Q_EMIT this->scopyVersionChanged();
	} else {
		qDebug() << "Wasn't able to get the latest Scopy version!\n";
	}
}

void HomePhone::m2kVersionRequest()
{
	QNetworkAccessManager* manager = new QNetworkAccessManager();
	connect(manager, &QNetworkAccessManager::finished, this, &HomePhone::onM2kRequestFinished);
	connect(manager, SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));

	manager->get(QNetworkRequest(QUrl(QString::fromUtf8("http://analog-applications-versions.herokuapp.com/m2k-fw"))));
}

void HomePhone::onM2kRequestFinished(QNetworkReply* reply)
{
	if (reply->error() == QNetworkReply::NoError) {
		HomePhone::m_m2kVersion = reply->readAll();
		Q_EMIT m2kVersionChanged();
	} else {
		qDebug() << "Wasn't able to get the latest M2k-fw version!\n";
	}
}

