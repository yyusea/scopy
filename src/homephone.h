#ifndef HOMEPHONE_H
#define HOMEPHONE_H
#include "src/pulseview/pv/devices/device.hpp"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTextCodec>

namespace adiscope {
class HomePhone: public QObject
{
	Q_OBJECT
private:
	QString m_lastRequestContent;
	static QString m_scopyVersion;
	static QString m_m2kVersion;

public:
	void scopyVersionRequest();
	void m2kVersionRequest();
	QString getScopyVersion() { return m_scopyVersion; }
	QString getM2kVersion() { return m_m2kVersion; }

Q_SIGNALS:
	void scopyVersionChanged();
	void m2kVersionChanged();

public Q_SLOTS:
	void onScopyRequestFinished(QNetworkReply*);
	void onM2kRequestFinished(QNetworkReply*);
};
}
#endif // HOMEPHONE_H
