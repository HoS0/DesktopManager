#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QWidget>
#include "ui_loginpage.h"

#include <QCoreApplication>
#include <QTimer>
#include <QDebug>
#include <QLabel>
#include <QPainter>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QKeyEvent>
#include <QGraphicsBlurEffect>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QPalette>
#include <QColor>
#include <QWidget>
#include "qamqpclient.h"
#include "qamqpexchange.h"
#include "qamqpqueue.h"
#include "AmqpManager.h"
#include "qjsonview.h"


class LoginPage : public QWidget
{
	Q_OBJECT

public:
	LoginPage(QWidget *parent = 0, AmqpManager* amqpManager = 0, QJsonView* jsonView = 0);
	~LoginPage();

private:
	Ui_LoginPage ui;

	QGraphicsOpacityEffect* m_effect;

	int m_backgroungR;
	int m_backgroungG;
	int m_backgroungB;
	QTimer *m_disapearTimer;
	QLineEdit *usernameEditor;
	QLineEdit *passwordEditor;

public slots:
	void updateBackground();
	void disapear();

	void loginClicked();
	//void startFadeOutAnimation();
	void checkCredentials();

signals:
	void loginAccepted();

private:
	QColor *m_color;
	AmqpManager* m_amqpManager;

public:
	void setColor(const QColor &value);
	QColor color();

	QLabel* profilePic;
	QLabel* messageLabel;

	QJsonView* m_jsonView;

protected:

	void keyPressEvent(QKeyEvent * event);

};

#endif // LOGINPAGE_H
