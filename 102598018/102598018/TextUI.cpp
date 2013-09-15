#include "TextUI.h"

TextUI::TextUI(ERModel* erModel)
{
	displayMenu();
	processCommand(*erModel);
}

TextUI::~TextUI()
{
}

void TextUI::displayMenu()
{
	qDebug() << "hello TextUI";
}

void TextUI::processCommand(ERModel& erModel)
{
	string type,text;
	cout << "please enter A,E,R\n";
	cin >> type;
	cout << "please enter name\n";
	cin >> text;

	erModel.addNode(type,text);
	cout << "Add new node!";
}