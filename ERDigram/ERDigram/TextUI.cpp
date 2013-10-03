#include "TextUI.h"

TextUI::TextUI(ERModel* erModel)
{
	this->_erModel = erModel;
	_isDisplayComponentsTable = true;
	_isDisplayConnectionsTable = true;
}

TextUI::~TextUI()
{
	delete(_erModel);
}

void TextUI::displayMenu()
{
	cout << TEXT_MENU;
	_isDisplayComponentsTable = true;
	_isDisplayConnectionsTable = true;
	processCommand();
}

void TextUI::processCommand()
{
	string choice;

	cin >> choice;
	switch(atoi(choice.c_str()))
	{
	case Load:
		cout << "Load" << endl;
		displayMenu();
		break;
	case Save:
		saveERDiagram();
		displayMenu();
		break;
	case Add:
		addNewNode();
		displayComponentTable();
		displayMenu();
		break;
	case Connect:
		addConnection();
		displayConnectionTable();
		displayMenu();
		break;
	case GetTable:
		displayComponentTable();
		displayConnectionTable();
		displayMenu();
		break;
	case SetPK:
		setPrimaryKey();
		displayMenu();
		break;
	case GetERTable:
		displayERDiagramTable();
		displayMenu();
		break;
	case Exit:
		exitERDiagram();
		break;
	default:
		cout << TEXT_MENU_ERRORCHOICE;
		displayMenu();
		break;
	}
}

void TextUI::addNewNode()
{
	string type;
	string text;

	cout << TEXT_ADDNEWNODE_TYPE;
	cin >> type;

	while ( !(type == PARAMETER_ATTRIBUTE || type == PARAMETER_ENTITY || type == PARAMETER_RELATIONSHIP) )
	{
		cout << TEXT_ADDNEWNODE_ERRORTYPE;
		cin >> type;
	}

	cout << TEXT_ADDNEWNODE_NAME;
	cin >> text;

	_erModel->addNode(type,text);
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
	if(_erModel->getCheckConnectionStateMessage(firstComponentID,secondComponentID) != TEXT_CONNECTION_FINISH)
	{
		cout << _erModel->getCheckConnectionStateMessage(firstComponentID,secondComponentID) << endl;
		_isDisplayConnectionsTable = false;
	}
	else if(_erModel->checkSetCardinality(firstComponentID, secondComponentID))
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
		_erModel->addConnection(firstComponentID, secondComponentID, cardinalityOption);
	}
	else
		_erModel->addConnection(firstComponentID, secondComponentID, PARAMETER_SPACE);
}

void TextUI::displayComponentTable()
{
	if (_isDisplayComponentsTable)
	{
		// ComponentTable format
		cout << TEXT_ADDNEWNODE_TITLE << endl;
		cout << TEXT_DEMARCATION_COMPONENTTABLE << endl;
		cout << TEXT_COMPONENT_TABLEFORMAT << endl;
		cout << TEXT_DEMARCATIONTWO_CONPONENTTABLE << endl;

		// ComponentTable contents string
		cout << _erModel->getComponentsTable(PARAMETER_ALL);

		// ComponentTable End
		cout << TEXT_DEMARCATION_COMPONENTTABLE << endl << endl;
	}
}

void TextUI::displayConnectionTable()
{
	if (_isDisplayConnectionsTable)
	{
		// ConnectiontTable format
		cout << TEXT_CONNECTION_TITLE << endl;
		cout << TEXT_DEMARCATION_CONNECTIONTABLE << endl;
		cout << TEXT_CONNECTION_TABLEFORMAT << endl;
		cout << TEXT_DEMARCATIONTWO_CONNECTIONTABLE << endl;

		// ConnectiontTable contents string
		cout << _erModel->getConnectionTable();

		// ConnectiontTable End
		cout << TEXT_DEMARCATION_CONNECTIONTABLE << endl << endl;
	}
}

string TextUI::searchComponent( string searchType )
{
	string searchID;

	cin >> searchID;
	while(!(_erModel->searchComponentExist(searchID, searchType))){
		if (searchType == PARAMETER_ALL)
			cout << TEXT_CONNECTION_ERRORNODE;
		cin >> searchID;
	}
	return searchID;
}


void TextUI::setPrimaryKey()
{
	string entityNodeID;
	string attributeNodeIDSet;
	vector<int> primaryKeys;

	displayEntityTable();

	cout << TEXT_SETPRIMARYKEY_ENTERNODEID;
	entityNodeID = searchEntity(PARAMETER_ENTITY);

	cout << TEXT_SETPRIMARYKEY_ATTRIBUTEOFENTITY << entityNodeID << TEXT_SETPRIMARYKEY_ENDTEXT << endl;
	displayAttributeTable(atoi(entityNodeID.c_str()));
	cout << TEXT_SETPRIMARYKEY_ENTERTWOATTRIBUTE;
	
	primaryKeys = searchAttribute(entityNodeID);
	_erModel->setPrimaryKey(atoi(entityNodeID.c_str()), primaryKeys);
	
	// The text of pk.
	for (int i = 0; i < primaryKeys.size(); i++)
		attributeNodeIDSet += Toolkit::integerToString(primaryKeys[i]) + SPLITTERBYCOMMA;
	attributeNodeIDSet = attributeNodeIDSet.substr(0, 2*primaryKeys.size()-1);

	cout << TEXT_NODENUMBEGIN << entityNodeID << TEXT_SETPRIMARYKEY_SETPKFINISH_ONE << attributeNodeIDSet << TEXT_SETPRIMARYKEY_SETPKFINISH_TWO << endl;
}

string TextUI::searchEntity( string searchType )
{
	string searchID;

	cin >> searchID;
	while(true){
		if (!_erModel->searchComponentExist(searchID, PARAMETER_ALL))					// The component is not exist.
			cout << TEXT_CONNECTION_ERRORNODE;
		else if (_erModel->searchComponentExist(searchID, PARAMETER_ENTITY))			// Entity is found.
			break;
		else																			// Component is exist, but its type isn't entity.
			cout << TEXT_NODENUMBEGIN << searchID << TEXT_SETPRIMARYKEY_ERRORMESSAGE;
		cin >> searchID;
	}
	return searchID;
}

vector<int> TextUI::searchAttribute( string entityNodeID )
{
	string attributeNodeID;
	string errorMessage = PARAMETER_INITIALSEARCH;
	vector<int> primaryKeys;

	cin >> attributeNodeID;
	primaryKeys = splitPrimaryKey(attributeNodeID);

	
	while(true)
	{
		// The errorMessage use to check the pk set(attributeNode) is in the EntityNode.
		errorMessage = PARAMETER_SPACE;
		for (int i = 0; i < primaryKeys.size(); i++)
		{
			if (!_erModel->searchComponentExist(Toolkit::integerToString(primaryKeys[i]), PARAMETER_ALL))												// The component is not exist.
				errorMessage += TEXT_CONNECTION_ERRORNODE;
			else if (!_erModel->searchEntityConnection(atoi(entityNodeID.c_str()), primaryKeys[i], PARAMETER_ATTRIBUTE))		// The component type is not attribute.
				errorMessage += TEXT_NODENUMBEGIN + Toolkit::integerToString(primaryKeys[i]) + TEXT_SETPRIMARYKEY_ERRORATTRIBUTEID_ONE + entityNodeID + TEXT_SETPRIMARYKEY_ERRORATTRIBUTEID_TWO;
		}
		if (errorMessage != PARAMETER_SPACE)
			cout << errorMessage;
		else								// The pk set is no problem.
			break;

		// Restart and initialize.
		primaryKeys.clear();
		cin >> attributeNodeID;
		primaryKeys = splitPrimaryKey(attributeNodeID);
	}
	
	return primaryKeys;
}

vector<int> TextUI::splitPrimaryKey( string primaryKeys )
{
	vector<string> splitText;
	vector<int> primaryKeySet;

	splitText = Toolkit::splitFunction(primaryKeys,SPLITTERBYCOMMA);
	
	for (int i = 0; i < splitText.size(); i++)
	{
		primaryKeySet.push_back(atoi(splitText[i].c_str()));
	}

	return primaryKeySet;
}

void TextUI::displayEntityTable()
{
	// EntityTable format
	cout << TEXT_SETPRIMARYKEY_ENTITYTITLE << endl;
	cout << TEXT_DEMARCATION_COMPONENTTABLE << endl;
	cout << TEXT_COMPONENT_TABLEFORMAT << endl;
	cout << TEXT_DEMARCATIONTWO_CONPONENTTABLE << endl;

	// EntityTable format
	cout << _erModel->getComponentsTable(PARAMETER_ENTITY);

	// ComponentTable End
	cout << TEXT_DEMARCATION_COMPONENTTABLE << endl << endl;
	
}

void TextUI::displayAttributeTable( int entityID )
{
	// AttributeTable format
	cout << TEXT_DEMARCATION_COMPONENTTABLE << endl;
	cout << TEXT_COMPONENT_TABLEFORMAT << endl;
	cout << TEXT_DEMARCATIONTWO_CONPONENTTABLE << endl;

	//EntityTable format
	cout << _erModel->searchAttributeOfEntity(entityID);

	// ComponentTable End
	cout << TEXT_DEMARCATION_COMPONENTTABLE << endl << endl;
}

void TextUI::displayERDiagramTable()
{
	if(_erModel->checkOneToOne())
	{
		// ERDiagramTable format
		cout << TEXT_DEMARCATION_ERDIAGRAMTABLE << endl;
		cout << TEXT_ERDIAGRAM_TITLE << endl;
		cout << TEXT_DEMARCATIONTWO_ERDIAGRAMTABLE << endl;

		//ERDiagramTable format
		cout << _erModel->getERDiagramTable();

		// ComponentTable End
		cout << TEXT_DEMARCATION_ERDIAGRAMTABLE << endl << endl;
	}
	else
		cout << TEXT_ERDIAGRAM_NOTABLE << endl << endl;
}

void TextUI::exitERDiagram()
{
	cout << TEXT_GOODBYE;
	//exit(1);
}

void TextUI::saveERDiagram()
{
	string fileName;
	cout << TEXT_SAVE_FILENAME;
	cin >> fileName;

	_erModel->saveERDiagram(fileName);
}
