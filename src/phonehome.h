#ifndef PHONEHOME_H
#define PHONEHOME_H
#include "src/pulseview/pv/devices/device.hpp"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTextCodec>

namespace adiscope {
class PhoneHome: public QObject
{
	Q_OBJECT
private:
	PhoneHome() {}
	QString m_lastRequestContent;
	static QString m_scopyVersion;
	static QString m_m2kVersion;
	static PhoneHome* instance;

public:
	static void versionsRequest();
	static QString getScopyVersion() { return m_scopyVersion; }
	static QString getM2kVersion() { return m_m2kVersion; }
	static PhoneHome* getInstance();

Q_SIGNALS:
	void scopyVersionChanged();
	void m2kVersionChanged();

public Q_SLOTS:
	void onVersionsRequestFinished(QNetworkReply*);
};
}
#endif // PHONEHOME_H
