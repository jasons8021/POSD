#include <QtCore/QCoreApplication>
#include <QDebug>
#include "ERModel.h"
#include "TextUI.h"

using namespace std;

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	ERModel* erModel;
	TextUI textUI(erModel);

	return a.exec();
}
