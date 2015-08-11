#include "loginpage.h"

LoginPage::LoginPage(QWidget *parent, AmqpManager* amqpManager, QJsonView* jsonView)
	: QWidget(parent)
{
	ui.setupUi(this);

	if (parent != 0)
	{
		setFixedWidth(parent->width());
		setFixedHeight(parent->height());
	}

	m_amqpManager = amqpManager;

	m_backgroungR = 100;
	m_backgroungG = 100;
	m_backgroungB = 200;

	m_jsonView = jsonView;

	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateBackground()));
	timer->start(300);

	m_color = new QColor(m_backgroungR, m_backgroungG, m_backgroungB);
	this->setAutoFillBackground(true);

	QHBoxLayout *layout1 = new QHBoxLayout;
	QVBoxLayout *layout = new QVBoxLayout;
	QWidget* tWidget = new QWidget;
	tWidget->setFixedWidth(this->width() / 4);
	tWidget->setFixedHeight(this->height() / 2);

	QPushButton *button1 = new QPushButton("login");
	button1->setFixedWidth(this->width() / 15);
	button1->setFixedHeight(this->height() / 25);
	button1->setStyleSheet("background-color: rgb(255,255,255);	border: 1pt solid; border-color: blue; border-radius: 10px; font-size: 14pt;font-family: Tahoma, Geneva, sans-serif; ");
	button1->setDefault(true);
	button1->setAutoDefault(true);
	connect(button1, SIGNAL(clicked()), this, SLOT(loginClicked()));

	QPushButton *button2 = new QPushButton("button2");
	button2->setFixedWidth(this->width() / 10);
	button2->setFixedHeight(this->height() / 25);
	button2->setStyleSheet("background-color: rgb(255,255,255);	border: 2px solid; border-color: blue; border-radius: 10px;");


	usernameEditor = new QLineEdit();
	usernameEditor->setFixedWidth(this->width() / 7);
	usernameEditor->setFixedHeight(this->height() / 25);
	usernameEditor->setStyleSheet("background-color: rgb(255,255,255);	border: 1pt solid; border-radius: 10px; border-color: blue; font-size: 14pt;font-family: Tahoma, Geneva, sans-serif; ");
	usernameEditor->setPlaceholderText("username");


	passwordEditor = new QLineEdit();
	passwordEditor->setFixedWidth(this->width() / 7);
	passwordEditor->setFixedHeight(this->height() / 25);
	passwordEditor->setEchoMode(QLineEdit::Password);
	passwordEditor->setStyleSheet("background-color: rgb(255,255,255);	border: 1pt solid; border-color: blue; border-radius: 10px; font-size: 14pt;font-family: Tahoma, Geneva, sans-serif; ");
	passwordEditor->setPlaceholderText("password");

	profilePic = new QLabel();
	profilePic->setFixedWidth(std::min(profilePic->width(), profilePic->height()));
	profilePic->setFixedHeight(std::min(profilePic->width(), profilePic->height()));
	profilePic->setStyleSheet(" background-image: url('c:/1.png'); 	background-position: center;	background-repeat: no-repeat; background-attachment: fixed; border: 5px solid; border-color: white; border-radius: " + QString::number(profilePic->width() / 2) + "px; font-size: 14pt;font-family: Tahoma, Geneva, sans-serif; ");
	QPalette *palette = new QPalette;
	profilePic->setAutoFillBackground(true);

	messageLabel = new QLabel();
	messageLabel->setStyleSheet("color: red;font-size: 10pt;font-family: Tahoma, Geneva, sans-serif; ");

	layout->addWidget(profilePic, 0, Qt::AlignCenter);
	layout->addWidget(messageLabel, 100, Qt::AlignCenter);
	layout->addWidget(usernameEditor, 100, Qt::AlignCenter);
	layout->addWidget(passwordEditor, 100, Qt::AlignCenter);
	layout->addWidget(button1, 100, Qt::AlignCenter);

	tWidget->setStyleSheet("background-color: rgba(0,0,0,0);");

	tWidget->setLayout(layout);

	layout1->addWidget(tWidget);


	m_effect = new QGraphicsOpacityEffect;
	m_effect->setOpacity(.8);
	this->setGraphicsEffect(m_effect);

	this->setLayout(layout1);
	updateBackground();
}

LoginPage::~LoginPage()
{
}

void LoginPage::loginClicked()
{
	checkCredentials();
}

void LoginPage::disapear()
{
	static float a = .8;
	a -= .05;
	m_effect->setOpacity(a);
}

void LoginPage::updateBackground()
{
	static bool desending = false;

	if (m_backgroungB > 220)
		desending = true;
	else if (m_backgroungB < 140)
		desending = false;

	if (!desending)
		m_backgroungB+=4;
	else
		m_backgroungB-=4;

	QPalette Pal(palette());

	m_color->setRgb(m_backgroungR, m_backgroungG, m_backgroungB);

	Pal.setColor(QPalette::Background, *m_color);
	this->setPalette(Pal);
}

void LoginPage::keyPressEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
	{
		checkCredentials();
	}

	return QWidget::keyPressEvent(event);
}

Q_PROPERTY(QColor color READ color WRITE setColor)

void LoginPage::setColor(const QColor &value) {
	QPalette palette;
	palette.setBrush(QPalette::WindowText, value);
	setPalette(palette);
}

QColor LoginPage::color() 
{
	return palette().color(QPalette::Normal, QPalette::Window);
}

void LoginPage::checkCredentials()
{
	QString json;
	HoSRequest* req = m_amqpManager->authenticateUser(usernameEditor->text().trimmed(), passwordEditor->text(), json);
	if (req->authenticateResponce)
	{
		emit loginAccepted();
	}

	messageLabel->setText(req->failMessage);

	emit m_jsonView->setJsonValue(json);
}