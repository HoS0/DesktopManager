#include "MainWindow.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
	QApplication::setDesktopSettingsAware(true);
	QApplication a(argc, argv);

	MainWindow w;
	w.show();

	//Sender sender;
	//sender.start();

	return a.exec();
}
