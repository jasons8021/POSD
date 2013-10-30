#include <iostream>
#include <QApplication>
#include <qdebug>

#include "ERModel.h"
#include "TextUI.h"
#include "PresentationModel.h"
#include "GUI.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

using namespace std;

int main(int argc, char *argv[])
{
	ERModel* erModel = new ERModel();
	PresentationModel* presentationModel = new PresentationModel(erModel);

	if (true)
	{
		QApplication app(argc, argv);
		GUI* graphicalUI = new GUI(presentationModel);

		graphicalUI->setMaximumSize(WINDOW_WIDTH,WINDOW_HEIGHT);
		graphicalUI->setMinimumSize(WINDOW_WIDTH,WINDOW_HEIGHT);
		graphicalUI->setWindowTitle("ER Model GUI");
		graphicalUI->show();
		return app.exec();
	}
	else
	{
		TextUI* textUI= new TextUI(presentationModel);

		textUI->displayMenu();

		delete textUI;
		delete presentationModel;
		delete erModel;

		return 0;
	}
}
