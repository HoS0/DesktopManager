#ifndef AMQPMANAGER_H
#define AMQPMANAGER_H

#include <QWidget>
#include <QCoreApplication>
#include <QTimer>
#include <QDebug>
#include <QWidget>
#include <QObject>
#include <QJsonArray>
#include "qamqpclient.h"
#include "qamqpexchange.h"
#include "qamqpqueue.h"
#include "QUuid"
#include <QJsonDocument>
#include <QJsonObject>
#include <chrono>
#include <thread>
#include "hosrequest.h"

class AmqpManager : public QObject
{
	Q_OBJECT

public:
	AmqpManager();
	~AmqpManager();

	void sendMessage(QString to, HoSRequest *req);

	bool authenticateUser(QString username, QString password);

public slots:
	void start();

private slots:

	void clientConnected();
	void queueDeclaredRecieve();
	void queueDeclaredSend();

	void messageReceived();


private:
	QAmqpClient m_client;

	QAmqpQueue *m_queue;

	QString m_serviceName;

	QList<HoSRequest*> requests;

	QString id;
};

#endif