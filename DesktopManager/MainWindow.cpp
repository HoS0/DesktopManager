#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	m_amqpManger = new AmqpManager;

	setWindowState(this->windowState() ^ Qt::WindowFullScreen);

	QGraphicsBlurEffect* blur = new QGraphicsBlurEffect;
	blur->setBlurRadius(30);

	QWidget* temp = new QWidget(this);
	temp->setFixedWidth(this->width());
	temp->setFixedHeight(this->height());
	//temp->setGraphicsEffect(blur);
	temp->setStyleSheet("background-image: url('c:/2.jpg'); background-repeat: no-repeat; background-position: center;");
	QHBoxLayout *layout3 = new QHBoxLayout;
	temp->setLayout(layout3);

	QVBoxLayout *layout1 = new QVBoxLayout();
	loginPage = new LoginPage(this, m_amqpManger);
	connect(loginPage, SIGNAL(loginAccepted()), this, SLOT(removeLoginPage()));

	//centralWidget()->setStyleSheet("background-image: url('c:/1.png'); 	background-position: center;");
}

void MainWindow::startFadeOutAnimation() 
{
	QPropertyAnimation *animation = new QPropertyAnimation(loginPage, "geometry",this);
	animation->setDuration(1500);
	animation->setStartValue(QRect(0, 0, 0, 0));
	animation->setEndValue(QRect(0, - loginPage->height(), 0, 0));
	animation->setEasingCurve(QEasingCurve::OutCirc);
	animation->start(QAbstractAnimation::DeleteWhenStopped);
}

MainWindow::~MainWindow()
{
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
	{
		//startFadeOutAnimation();
	}
}

void MainWindow::removeLoginPage()
{
	startFadeOutAnimation();
}
