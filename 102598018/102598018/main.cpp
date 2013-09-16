#include <QtCore/QCoreApplication>
#include <QDebug>
#include "ERModel.h"
#include "TextUI.h"

using namespace std;

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	TextUI* textUI;
	textUI = new TextUI(new ERModel());

	return a.exec();
}
