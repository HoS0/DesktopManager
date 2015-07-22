#include "AmqpManager.h"


AmqpManager::AmqpManager()
{
	id = QUuid::createUuid().toString().replace("{", "").replace("}", "");
	m_serviceName = "desktopmanager." + id;
	start();
}


AmqpManager::~AmqpManager()
{
	m_client.disconnectFromHost();
}



void AmqpManager::start()
{
	connect(&m_client, SIGNAL(connected()), this, SLOT(clientConnected()));
	//connect(&m_client, SIGNAL(disconnected()), this, SLOT(retryConnection()));
	//m_client.setAutoReconnect(true);
	m_client.connectToHost();
}

void AmqpManager::clientConnected()
{
	QAmqpExchange* defaultExchange = m_client.createExchange("desktopmanager");
	defaultExchange->declare(QAmqpExchange::Direct, QAmqpExchange::AutoDelete);
	m_queue = m_client.createQueue(m_serviceName);
	m_queue->bind(defaultExchange, id);

	connect(m_queue, SIGNAL(declared()), this, SLOT(queueDeclaredRecieve()));
	m_queue->declare();

}


void AmqpManager::messageReceived() {
	QAmqpQueue *queue = dynamic_cast <QAmqpQueue*>(sender());

	if (!queue)
		return;

	queueDeclaredSend();

	QAmqpMessage message = queue->dequeue();
	QString ali =  message.payload();
	QJsonDocument d = QJsonDocument::fromJson(ali.toUtf8());
	QJsonObject sett2 = d.object();
	QJsonValue value = sett2.value(QString("id"));
	QString tt = value.toString();

	HoSRequest* foundedRequest = 0;
	foreach(HoSRequest* h, requests)
	{
		if (h->id == value.toString())
		{
			foundedRequest = h;
			QJsonValue payloadValue = sett2.value(QString("payload"));
			QJsonObject payloadObject = payloadValue.toObject();
			QJsonValue authValue = payloadObject.value("authorized");

			h->authenticateResponce = authValue.toBool();
			if (h->authenticateResponce)
			{
				emit requests.at(0)->replyRecieved();
			}
		}
	}

	if (foundedRequest != 0)
	{
		requests.removeAll(foundedRequest);
		delete foundedRequest;
	}
}

void AmqpManager::queueDeclaredRecieve()
{
	QAmqpQueue *queue = dynamic_cast<QAmqpQueue*>(sender());
	if (!queue)
		return;
	
	connect(queue, SIGNAL(messageReceived()), this, SLOT(messageReceived()));
	queue->consume(QAmqpQueue::coNoAck);
}

void AmqpManager::queueDeclaredSend()
{
	static int count = 0;
	QAmqpQueue *queue = dynamic_cast<QAmqpQueue*>(sender());
	if (!queue)
		return;
	QAmqpExchange *defaultExchange = m_client.createExchange();
	defaultExchange->publish("Hello World!" + QString::number(++count), "hello");
}

bool AmqpManager::authenticateUser(QString username, QString password)
{
		HoSRequest *req = new HoSRequest(this, "", m_serviceName);
		req->args.append(username);
		req->args.append(password);

		req->setAction(retrieve);
		req->setType(user);
		req->setResponseNeeded(true);

		requests.clear();
		requests.append(req);
		sendMessage("datamanager", req);

		return req->authenticateResponce;
}

void AmqpManager::sendMessage(QString to, HoSRequest *req)
{
	QAmqpExchange* defaultExchange = m_client.createExchange(to);
	defaultExchange->declare(QAmqpExchange::Direct, QAmqpExchange::AutoDelete | QAmqpExchange::NoWait); 

	QAmqpMessage::PropertyHash properties;
	properties.insert(QAmqpMessage::ContentType, "application/json");

	QEventLoop wait_loop;
	defaultExchange->publish(req->msgToSend, "", properties);
	connect(req, SIGNAL(replyRecieved()), &wait_loop, SLOT(quit()));

	if (req->responseNeeded)
		wait_loop.exec();

	return;
}