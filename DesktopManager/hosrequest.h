#ifndef HOSREQUEST_H
#define HOSREQUEST_H

#include <QObject>
#include <QUuid>

enum PayloadType
{
	user
};

enum Action
{
	retrieve,
	create
};

class HoSRequest : public QObject
{
	Q_OBJECT

public:
	HoSRequest(QObject *parent, QString msg = "", QString sender = "");
	~HoSRequest();

	void CreateMessageBody();
	QString CreatePayloadBody();
	
	void setResponseNeeded(bool value);

	Action action;
	PayloadType type;
	QList<QString> args;
	bool authenticateResponce;

	bool responseNeeded;

signals:
	void replyRecieved();

private:
	
	QString m_serviceName;
	QString m_payload;

	QString HoSRequest::ConvertActiontoString(Action action);
	QString HoSRequest::ConvertTypetoString(PayloadType type);

public:
	QString id;
	QString msgToSend;

};

#endif // HOSREQUEST_H
