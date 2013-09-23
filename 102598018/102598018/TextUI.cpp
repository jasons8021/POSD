#include <sstream>
#include "TextUI.h"

TextUI::TextUI(ERModel* erModel)
{
	this->erModel = erModel;
	isDisplayComponentsTable = true;
	isDisplayConnectionsTable = true;
	displayMenu();
}

TextUI::~TextUI()
{
}

void TextUI::displayMenu()
{
	cout << TEXT_MENU;
	isDisplayComponentsTable = true;
	isDisplayConnectionsTable = true;
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
		displayComponentTable();
		break;
	case Connect:
		addConnection();
		displayConnectionTable();
		break;
	case GetTable:
		displayComponentTable();
		displayConnectionTable();
		break;
	case SetPK:
		setPrimaryKey();
		break;
	case GetERTable:
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
}

void TextUI::addConnection()
{
	int firstComponentID;
	int secondComponentID;
	string cardinalityOption;

	// First Node
	cout << TEXT_CONNECTION_FIRSTNODE;
	firstComponentID = atoi(searchComponent(PARAMETER_ALL).c_str());

	// Second Node
	cout << TEXT_CONNECTION_SECONDNODE;
	secondComponentID = atoi(searchComponent(PARAMETER_ALL).c_str());

	// if connection is failed, erModel->addConnection() return an error message.
	if(erModel->getCheckConnectionStateMessage(firstComponentID,secondComponentID) != TEXT_CONNECTION_FINISH)
	{
		cout << erModel->getCheckConnectionStateMessage(firstComponentID,secondComponentID) << endl;
		isDisplayConnectionsTable = false;
	}
	else if(erModel->checkSetCardinality(firstComponentID, secondComponentID))
	{
		cout << TEXT_CONNECTION_CARDINALITY << endl;
		cout << TEXT_CONNECTION_CARDINALITYOPTION;
		cin >> cardinalityOption;
		switch(atoi(cardinalityOption.c_str()))
		{
		case CardinalityOptionOne:
			cardinalityOption = PARAMETER_CARDINALITYOPTION_ONE;
			break;
		case CardinalityOptionTwo:
			cardinalityOption = PARAMETER_CARDINALITYOPTION_TWO;
			break;
		default:
			break;
		}
		erModel->addConnection(firstComponentID, secondComponentID, cardinalityOption);
	}
	else
		erModel->addConnection(firstComponentID, secondComponentID, PARAMETER_SPACE);
}

void TextUI::displayComponentTable()
{
	if (isDisplayComponentsTable)
	{
		// ComponentTable format
		cout << TEXT_ADDNEWNODE_TITLE << endl;
		cout << TEXT_DEMARCATION_COMPONENTTABLE << endl;
		cout << TEXT_COMPONENT_TABLEFORMAT << endl;
		cout << TEXT_DEMARCATIONTWO_CONPONENTTABLE << endl;

		// ComponentTable contents string
		cout << erModel->getComponentsTable(PARAMETER_ALL);

		// ComponentTable End
		cout << TEXT_DEMARCATION_COMPONENTTABLE << endl << endl;
	}
}

void TextUI::displayConnectionTable()
{
	if (isDisplayConnectionsTable)
	{
		// ConnectiontTable format
		cout << TEXT_CONNECTION_TITLE << endl;
		cout << TEXT_DEMARCATION_CONNECTIONTABLE << endl;
		cout << TEXT_CONNECTION_TABLEFORMAT << endl;
		cout << TEXT_DEMARCATIONTWO_CONNECTIONTABLE << endl;

		// ConnectiontTable contents string
		cout << erModel->getConnectionTable();

		// ConnectiontTable End
		cout << TEXT_DEMARCATION_CONNECTIONTABLE << endl << endl;
	}
	
}

string TextUI::searchComponent( string searchType )
{
	string searchID;

	cin >> searchID;
	while(!(erModel->searchComponentExist(searchID, searchType))){
		if (searchType == PARAMETER_ALL)
			cout << TEXT_CONNECTION_ERRORNODE;
		cin >> searchID;
	}
	return searchID;
}


void TextUI::setPrimaryKey()
{
	string entityNodeID;
	string AttributeNodeID;

	displayEntityTable();

	cout << TEXT_SETPRIMARYKEY_ENTERNODEID;
	entityNodeID = searchEntity(PARAMETER_ENTITY);

	cout << TEXT_SETPRIMARYKEY_ATTRIBUTEOFENTITY << entityNodeID << TEXT_SETPRIMARYKEY_ENDTEXT;
	displayAttributeTable(atoi(entityNodeID.c_str()));
	cout << TEXT_SETPRIMARYKEY_ENTERTWOATTRIBUTE;
	cin >> AttributeNodeID;

}

string TextUI::searchEntity( string searchType )
{
	string searchID;

	cin >> searchID;
	while(true){
		if (!erModel->searchComponentExist(searchID, PARAMETER_ALL))					// The component is not exist.
			cout << TEXT_CONNECTION_ERRORNODE;
		else if (erModel->searchComponentExist(searchID, PARAMETER_ENTITY))				// Entity is found.
			break;
		else																			// Component is exist, but its type isn't entity.
			cout << TEXT_NODENUMBEGIN << searchID << TEXT_SETPRIMARYKEY_ERRORMESSAGE;
		cin >> searchID;
	}
	return searchID;
}

void TextUI::displayEntityTable()
{
	// EntityTable format
	cout << TEXT_SETPRIMARYKEY_ENTITYTITLE << endl;
	cout << TEXT_DEMARCATION_COMPONENTTABLE << endl;
	cout << TEXT_COMPONENT_TABLEFORMAT << endl;
	cout << TEXT_DEMARCATIONTWO_CONPONENTTABLE << endl;

	// EntityTable format
	cout << erModel->getComponentsTable(PARAMETER_ENTITY);

	// ComponentTable End
	cout << TEXT_DEMARCATION_COMPONENTTABLE << endl << endl;
	
}

void TextUI::displayAttributeTable( int entityID)
{
	// AttributeTable format
	cout << TEXT_SETPRIMARYKEY_ENTITYTITLE << endl;
	cout << TEXT_DEMARCATION_COMPONENTTABLE << endl;
	cout << TEXT_COMPONENT_TABLEFORMAT << endl;
	cout << TEXT_DEMARCATIONTWO_CONPONENTTABLE << endl;

	//EntityTable format
	cout << erModel->searchAttributeOfEntity(entityID);

	// ComponentTable End
	cout << TEXT_DEMARCATION_COMPONENTTABLE << endl << endl;
}
