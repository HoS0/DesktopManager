#include "AmqpManager.h"


AmqpManager::AmqpManager()
{
	start();
}


AmqpManager::~AmqpManager()
{
	m_client.disconnectFromHost();
}



void AmqpManager::start()
{
	connect(&m_client, SIGNAL(connected()), this, SLOT(clientConnected()));
	connect(&m_client, SIGNAL(disconnected()), qApp, SLOT(quit()));
	m_client.connectToHost();
}

void AmqpManager::clientConnected()
{
	QAmqpExchange* defaultExchange = m_client.createExchange("desktopmanager");
	defaultExchange->declare(QAmqpExchange::Direct, QAmqpExchange::AutoDelete);
	QString id = QUuid::createUuid().toString().replace("{", "").replace("}", "");
	m_serviceName = "desktopmanager." + id;
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

	/*QLabel * label = ui.this->findChild<QLabel*>("label");*/
	QString ali =  message.payload();

	QJsonDocument d = QJsonDocument::fromJson(ali.toUtf8());

	QJsonObject sett2 = d.object();

	QJsonValue value = sett2.value(QString("authorized"));

	if (value.toBool() == true)
	{
		ali = "yay";
	}

	ali += "asd";
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

void AmqpManager::sendMessage(QString to, QString message)
{
	QString mes;
	mes += "{";
	mes += "\"action\": \"retrieve\", ";
	mes += "\"type\": \"user\", ";
	mes += "\"payload\": { ";
	mes += "\"username\": \"ali\", ";
	mes += "\"password\": \"alikh\" ";
	mes += "}, ";
	mes += "\"sender\": \"" + m_serviceName + "\" ,";
	mes += "\"responceNeeded\": true , ";
	mes += "\"id\": \"" + QUuid::createUuid().toString().replace("{", "").replace("}", "") + "\" ";
	mes += "} ";

	QAmqpExchange* defaultExchange = m_client.createExchange(to);
	QAmqpMessage::PropertyHash properties;
	properties.insert(QAmqpMessage::ContentType, "application/json");

	defaultExchange->publish(mes, "", properties);
}