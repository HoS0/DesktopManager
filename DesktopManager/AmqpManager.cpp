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
	QAmqpQueue *queue = m_client.createQueue("hello");
	connect(queue, SIGNAL(declared()), this, SLOT(queueDeclaredRecieve()));
	queue->declare();
}


void AmqpManager::messageReceived() {
	QAmqpQueue *queue = dynamic_cast <QAmqpQueue*>(sender());

	if (!queue)
		return;

	queueDeclaredSend();

	QAmqpMessage message = queue->dequeue();

	/*QLabel * label = ui.this->findChild<QLabel*>("label");
	label->setText(message.payload());*/
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