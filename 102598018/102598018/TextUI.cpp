#include <sstream>
#include "TextUI.h"

TextUI::TextUI(ERModel* erModel)
{
	this->erModel = erModel;

	displayMenu();
}

TextUI::~TextUI()
{
	erModelComponents.clear();
}

void TextUI::displayMenu()
{
	cout << TEXT_MENU;
	processCommand();
}

void TextUI::processCommand()
{
	string choice;

	cin >> choice;
	switch(atoi(choice.c_str()))
	{
	case Add:
		addNewNode();
		break;
	case Connect:
		addConnection();
		break;
	case GetClassDiagram:
		cout << "GetClassDiagram";
		break;
	case SetPrimaryKey:
		cout << "SetPrimaryKey";
		break;
	case GetTable:
		cout << "GetTable";
		break;
	default:
		cout << TEXT_MENU_ERRORCHOICE;
		break;
	}

	displayMenu();
}

void TextUI::addNewNode()
{
	string type;
	string text;

	cout << TEXT_ADDNEWNODE_TYPE;
	cin >> type;

	while ( !(type == PARAMETER_ATTRIBUTE || type == PARAMETER_ENTITY || type == PARAMETER_RELATIONSHOP) )
	{
		cout << TEXT_ADDNEWNODE_ERRORTYPE;
		cin >> type;
	}

	cout << TEXT_ADDNEWNODE_NAME;
	cin >> text;

	erModel->addNode(type,text);
	displayComponentTable();
}

void TextUI::displayComponentTable()
{
	erModelComponents = erModel->getComponents();

	if (erModelComponents.size() != 0)
	{
		cout << TEXT_ADDNEWNODE_CONTAINSCOMPONENTS << endl;
		cout << TEXT_DEMARCATION << endl;
		cout << TEXT_ADDNEWNODE_TABLEFORMAT << endl;
		cout << TEXT_DEMARCATIONTWO << endl;

		for (vector<Component*>::iterator contents = erModelComponents.begin(); contents != erModelComponents.end(); ++contents) {
			cout << TEXT_SPACE << ((Component*)*contents)->getType() << TEXT_SPACELINE;
			cout << TEXT_SPACE << ((Component*)*contents)->getID() << TEXT_SPACELINE;
			cout << TEXT_SPACE << ((Component*)*contents)->getText() << endl;
		}
		cout << TEXT_DEMARCATION << endl << endl;
	}
}

void TextUI::addConnection()
{
	int firstComponentID;
	int secondComponentID;

	// First Node
	cout << TEXT_CONNECTION_FIRSTNODE;
	firstComponentID = atoi(searchComponent().c_str());

	// Second Node
	cout << TEXT_CONNECTION_SECONDNODE;
	secondComponentID = atoi(searchComponent().c_str());

	// if connection is failed, erModel->addConnection() return an error message.
	if(erModel->addConnection(firstComponentID,secondComponentID) != TEXT_CONNECTION_FINISH)
		cout << erModel->addConnection(firstComponentID,secondComponentID) << endl;
	else
		displayConnectionTable();
}

string TextUI::searchComponent()
{
	string searchID;

	cin >> searchID;
	while(!(erModel->searchComponentExist(searchID))){
		cout << TEXT_CONNECTION_ERRORNODE;
		cin >> searchID;
	}
	return searchID;
}

void TextUI::displayConnectionTable()
{
}
