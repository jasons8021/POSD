#include "TextUI.h"

TextUI::TextUI(ERModel* erModel)
{
	this->_erModel = erModel;
}

TextUI::~TextUI()
{
	delete(_erModel);
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
	case Load:
		loadERDiagram();
		displayMenu();
		break;
	case Save:
		saveERDiagram();
		displayMenu();
		break;
	case Add:
		addNewNode();
		displayMenu();
		break;
	case Connect:
		addConnection();
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
	case Delete:
		deleteComponent();
		displayMenu();
		break;
	case Undo:
		undoCmd();
		displayMenu();
		break;
	case Redo:
		redoCmd();
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

	_erModel->addNodeCmd(type,text);

	displayComponentTable();
}

void TextUI::addConnection()
{
	int firstComponentID;
	int secondComponentID;

	if (_erModel->getComponentTableSize() > PARAMETER_ZEROCOMPONENT)
	{
		// �Ĥ@��Component
		cout << TEXT_CONNECTION_FIRSTNODE;
		firstComponentID = atoi(searchComponent(PARAMETER_ALL).c_str());

		// �ĤG��Component
		cout << TEXT_CONNECTION_SECONDNODE;
		secondComponentID = atoi(searchComponent(PARAMETER_ALL).c_str());

		// �p�G�nconnection�����Component�����D�A�h�^�ǰ��D�r��
		if(_erModel->getCheckConnectionStateMessage(firstComponentID,secondComponentID) != TEXT_CONNECTION_CANCONNECT)
			cout << _erModel->getCheckConnectionStateMessage(firstComponentID,secondComponentID) << endl;
		else if(_erModel->checkSetCardinality(firstComponentID, secondComponentID))
			_erModel->addConnectionCmd(firstComponentID, secondComponentID, chooseCardinality());
		else
			_erModel->addConnectionCmd(firstComponentID, secondComponentID, PARAMETER_NULL);

		displayConnectionTable();
	}
	else
		cout << TEXT_CONNECTION_NOCOMPONENT << endl;
	
}

string TextUI::chooseCardinality()
{
	string cardinalityOption;

	cout << TEXT_CONNECTION_CARDINALITY << endl;
	cout << TEXT_CONNECTION_CARDINALITYOPTION;
	cin >> cardinalityOption;

	switch(atoi(cardinalityOption.c_str()))
	{
	case CardinalityOptionOne:
		return PARAMETER_CARDINALITYOPTION_ONE;
	case CardinalityOptionTwo:
		return PARAMETER_CARDINALITYOPTION_TWO;
	default:
		break;
	}
	return PARAMETER_NULL;
}
void TextUI::displayComponentTable()
{
	if (_erModel->getComponentTableSize() > PARAMETER_ZEROCOMPONENT)
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
	if (_erModel->getConnectionTableSize() > PARAMETER_ZEROCOMPONENT)
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

void TextUI::setPrimaryKey()
{
	string entityNodeID;
	string attributeNodeIDSet;
	vector<int> primaryKeys;

	displayEntityTable();

	// ��JEntity
	cout << TEXT_SETPRIMARYKEY_ENTERNODEID;
	entityNodeID = searchEntity(PARAMETER_ENTITY);

	// ��ܸ�Entity�֦���Attribute Component
	cout << TEXT_SETPRIMARYKEY_ATTRIBUTEOFENTITY << entityNodeID << TEXT_SETPRIMARYKEY_ENDTEXT << endl;
	displayAttributeTable(atoi(entityNodeID.c_str()));
	cout << TEXT_SETPRIMARYKEY_ENTERTWOATTRIBUTE;
	
	// ��Jprimary keys ���ˬd���T
	primaryKeys = searchAttribute(entityNodeID);
	_erModel->setPrimaryKey(atoi(entityNodeID.c_str()), primaryKeys);
	
	// ��ܿ�J��PK�w�g�[�J����
	for (int i = 0; i < primaryKeys.size(); i++)
		attributeNodeIDSet += Toolkit::integerToString(primaryKeys[i]) + COMMA;
	attributeNodeIDSet = attributeNodeIDSet.substr(0, PARAMETER_ADJUSTPKSHOWSTRINGDOUBLESIZE * primaryKeys.size() + PARAMETER_ADJUSTPKSHOWSTRINGSUBLAST);

	cout << TEXT_NODENUMBEGIN << entityNodeID << TEXT_SETPRIMARYKEY_SETPKFINISH_ONE << attributeNodeIDSet << TEXT_SETPRIMARYKEY_SETPKFINISH_TWO << endl;
}

vector<int> TextUI::splitPrimaryKey( string primaryKeys )
{
	vector<string> splitText;
	vector<int> primaryKeySet;

	splitText = Toolkit::splitFunction(primaryKeys,COMMA);
	
	for (int i = 0; i < splitText.size(); i++)
		primaryKeySet.push_back(atoi(splitText[i].c_str()));

	return primaryKeySet;
}

void TextUI::displayEntityTable()
{
	// EntityTable����˦�
	cout << TEXT_SETPRIMARYKEY_ENTITYTITLE << endl;
	cout << TEXT_DEMARCATION_COMPONENTTABLE << endl;
	cout << TEXT_COMPONENT_TABLEFORMAT << endl;
	cout << TEXT_DEMARCATIONTWO_CONPONENTTABLE << endl;

	// EntityTable���e
	cout << _erModel->getComponentsTable(PARAMETER_ENTITY);

	// ComponentTable����
	cout << TEXT_DEMARCATION_COMPONENTTABLE << endl << endl;
	
}

void TextUI::displayAttributeTable( int entityID )
{
	// AttributeTable����˦�
	cout << TEXT_DEMARCATION_COMPONENTTABLE << endl;
	cout << TEXT_COMPONENT_TABLEFORMAT << endl;
	cout << TEXT_DEMARCATIONTWO_CONPONENTTABLE << endl;

	//EntityTable���e
	cout << _erModel->searchAttributeOfEntity(entityID);

	// ComponentTable����
	cout << TEXT_DEMARCATION_COMPONENTTABLE << endl << endl;
}

void TextUI::displayERDiagramTable()
{
	if(_erModel->checkOneToOne())
	{
		// ERDiagramTable ����˦�
		cout << TEXT_DEMARCATION_ERDIAGRAMTABLE << endl;
		cout << TEXT_ERDIAGRAM_TITLE << endl;
		cout << TEXT_DEMARCATIONTWO_ERDIAGRAMTABLE << endl;

		//ERDiagramTable���e
		cout << _erModel->getERDiagramTable();

		// ComponentTable ����
		cout << TEXT_DEMARCATION_ERDIAGRAMTABLE << endl << endl;
	}
	else
		cout << TEXT_ERDIAGRAM_NOTABLE << endl << endl;
}

void TextUI::exitERDiagram()
{
	string choice;

	if (_erModel->getIsModify())
	{
		cout << TEXT_LOADSVAE_EXITPROGRAM << endl;
		cout << TEXT_LOADSVAE_SAVEORNOT << endl;
		cout << GETINPUT;
		cin >> choice;
		switch(atoi(choice.c_str()))
		{
		case PARAMETER_SAVEEXIT:
			saveERDiagram();
			cout << TEXT_GOODBYE;
			break;
		case PARAMETER_NOSAVEEXIT:
			cout << TEXT_GOODBYE;
			break;
		}
	}
	else
		cout << TEXT_GOODBYE;
}

void TextUI::saveERDiagram()
{
	string fileName;
	cout << TEXT_LOADSAVE_FILENAME;
	cin >> fileName;

	_erModel->saveERDiagram(fileName);
}

void TextUI::loadERDiagram()
{
	string fileName;
	cout << TEXT_LOADSAVE_FILENAME;
	cin >> fileName;

	cout << _erModel->loadERDiagram(fileName);
	displayComponentTable();
	displayConnectionTable();
}

void TextUI::deleteComponent()
{
	string delComponentID;
	cout << TEXT_DELETE_ENTERNODE;
	delComponentID = searchComponent(PARAMETER_ALL);
	_erModel->deleteCmd(atoi(delComponentID.c_str()));
	
	cout << TEXT_DELETE_DELETEFINISH_ONE << delComponentID << TEXT_DELETE_DELETEFINISH_TWO << endl;

	displayComponentTable();
	displayConnectionTable();
}

void TextUI::undoCmd()
{
	if (_erModel->undoCmd())
	{
		cout << TEXT_UNDO_SUCCESS << endl;
		displayComponentTable();
		displayConnectionTable();
	}
	else
		cout << TEXT_UNDO_FAILED << endl;
	
}

void TextUI::redoCmd()
{
	if(_erModel->redoCmd())
	{
		cout << TEXT_REDO_SUCCESS << endl;
		displayComponentTable();
		displayConnectionTable();
	}
	else
		cout << TEXT_REDO_FAILED << endl;
}

//////////////////////////////////////////////////////////////////////////
//					�ˬd��J���`�IID�O�_���T��Function					//
//////////////////////////////////////////////////////////////////////////

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

string TextUI::searchEntity( string searchType )
{
	string searchID;

	cin >> searchID;
	while(true){
		if (!_erModel->searchComponentExist(searchID, PARAMETER_ALL))					// ��JID���s�b
			cout << TEXT_CONNECTION_ERRORNODE;
		else if (_erModel->searchComponentExist(searchID, PARAMETER_ENTITY))			// ����J��Entity
			break;
		else																			// ��J��ID���OEntity
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
		//	errorMessage�ΨӦ^��Primary Key�����X�O�_�����D
		errorMessage = PARAMETER_NULL;
		for (int i = 0; i < primaryKeys.size(); i++)
		{
			if (!_erModel->searchComponentExist(Toolkit::integerToString(primaryKeys[i]), PARAMETER_ALL))						//	��J��ID���s�b.
				errorMessage += TEXT_CONNECTION_ERRORNODE;
			else if (!_erModel->searchEntityConnection(atoi(entityNodeID.c_str()), primaryKeys[i], PARAMETER_ATTRIBUTE))		//	��J��ID�ëD�b��EntityNode��
				errorMessage += TEXT_NODENUMBEGIN + Toolkit::integerToString(primaryKeys[i]) + TEXT_SETPRIMARYKEY_ERRORATTRIBUTEID_ONE + entityNodeID + TEXT_SETPRIMARYKEY_ERRORATTRIBUTEID_TWO;
		}
		if (errorMessage != PARAMETER_NULL)
			cout << errorMessage;
		else								//	��J��Primary Key�����X���T�A���X�^�ǵ��G
			break;

		//	���s��J�s��Primary Key
		primaryKeys.clear();
		cin >> attributeNodeID;
		primaryKeys = splitPrimaryKey(attributeNodeID);
	}

	return primaryKeys;
}