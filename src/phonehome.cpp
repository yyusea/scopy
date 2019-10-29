#include "phonehome.h"

#include <QJsonDocument>
#include <QJsonObject>

using namespace adiscope;

PHONEHOME_H

QString PhoneHome::m_scopyVersion;
QString PhoneHome::m_m2kVersion;
PhoneHome* PhoneHome::instance = nullptr;

PhoneHome* PhoneHome::getInstance()
{
	if (PhoneHome::instance == nullptr) {
		PhoneHome::instance = new PhoneHome();
	}

	return instance;
}

void PhoneHome::versionsRequest()
{
	QNetworkAccessManager* manager = new QNetworkAccessManager();
	connect(manager, &QNetworkAccessManager::finished, PhoneHome::getInstance(), &PhoneHome::onVersionsRequestFinished);
	connect(manager, SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));

	manager->get(QNetworkRequest(QUrl(QString::fromUtf8("http://analog-applications-versions.herokuapp.com/all"))));
}

void PhoneHome::onVersionsRequestFinished(QNetworkReply* reply)
{
	if (reply->error() == QNetworkReply::NoError) {
		auto content = QJsonDocument::fromJson(reply->readAll()).object().toVariantMap();
		PhoneHome::m_scopyVersion = content["scopy"].toMap()["version"].toString();
		PhoneHome::m_m2kVersion = content["m2k-fw"].toMap()["version"].toString();
		Q_EMIT scopyVersionChanged();
		Q_EMIT m2kVersionChanged();
	} else {
		qDebug() << "Wasn't able to access versions database!\n";
	}
}

