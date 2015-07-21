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


class LoginPage : public QWidget
{
	Q_OBJECT

public:
	LoginPage(QWidget *parent = 0);
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

	void updateBackground();
	void disapear();

	void loginClicked();
	//void startFadeOutAnimation();
	void checkCredentials();

signals:
	void loginAccepted();

private:
	QAmqpClient m_client;
	QColor *m_color;

public:
	void setColor(const QColor &value);
	QColor color();

	QLabel* label;

protected:

	void keyPressEvent(QKeyEvent * event);

};

#endif // LOGINPAGE_H
