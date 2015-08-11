#ifndef WIDGETTEST_H
#define WIDGETTEST_H

#include <QtWidgets/QMainWindow>
#include "ui_widgettest.h"

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

#include "qamqpclient.h"
#include "qamqpexchange.h"
#include "qamqpqueue.h"

#include "loginpage.h"
#include "AmqpManager.h"

#include "qjsonview.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	Ui::widgetTestClass ui;

	void startFadeOutAnimation();

	LoginPage* loginPage;
	AmqpManager* m_amqpManger;

	QJsonView* m_jsonView;

public slots:
	void removeLoginPage();

protected:
	void keyPressEvent(QKeyEvent* event);



};

#endif // WIDGETTEST_H
