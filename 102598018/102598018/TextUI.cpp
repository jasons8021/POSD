#include "TextUI.h"
#define TEXT_MENU "1. Add a node\n2. Connect two nodes\n3. Display the current diagram\n4. Set a primary key\n5. Display the table\n6. Exit\n"
#define TEXT_ADDNEWNODE "What kind of node do you want to add?\n[A]Attribute [E]Entity [R]Relation"


TextUI::TextUI(ERModel* erModel)
{
	this->erModel = erModel;

	displayMenu();
}

TextUI::~TextUI()
{
}

void TextUI::displayMenu()
{
	cout << TEXT_MENU << endl;
	processCommand();
}

void TextUI::processCommand()
{
	string type;
	string text;

	cout << "please enter A,E,R" << endl;
	cin >> type;
	cout << "please enter name" << endl;
	cin >> text;

	erModel->addNode(type,text);

	cout << "Add new node!" << endl;
}