#include "hosrequest.h"

HoSRequest::HoSRequest(QObject *parent, QString msg, QString sender)
	: QObject(parent)
{
	id = QUuid::createUuid().toString().replace("{", "").replace("}", "");

	msgToSend = msg;
	responseNeeded = true;
	m_serviceName = sender;
	authenticateResponce = false;
}

HoSRequest::~HoSRequest()
{

}

void HoSRequest::setResponseNeeded(bool value)
{
	responseNeeded = value;
	CreateMessageBody();
}

void HoSRequest::CreateMessageBody()
{
	msgToSend = "";
	msgToSend += "{";
	msgToSend += "\"action\": \"" + ConvertActiontoString(action) + "\", ";
	msgToSend += "\"type\": \"" + ConvertTypetoString(type) + "\", ";
	msgToSend += CreatePayloadBody();
	msgToSend += "\"sender\": \"" + m_serviceName + "\" ,";
	msgToSend += "\"responceNeeded\": " + (responseNeeded ? QString("true") : QString("false")) + QString(" , ");
	msgToSend += "\"id\": \"" + id + "\" ";
	msgToSend += "} ";
}

QString HoSRequest::CreatePayloadBody()
{
	QString ret = "\"payload\": { ";
	
	switch (type)
	{
	case user:
		ret += "\"username\": \"" + args.at(0) + "\", ";
		ret += "\"password\": \"" + args.at(1) + "\" ";
		break;
	default:
		break;
	}

	ret += "}, ";

	return ret;
}

QString HoSRequest::ConvertActiontoString(Action action)
{
	switch (action)
	{
	case retrieve:
		return "retrieve";
	case create:
		return "create";
	default:
		break;
	}

	return "";
}

QString HoSRequest::ConvertTypetoString(PayloadType type)
{
	switch (type)
	{
	case user:
		return "user";
	default:
		return "";
	}
}