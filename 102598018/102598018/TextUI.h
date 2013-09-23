#ifndef TEXTUI
#define TEXTUI

// Menu text set.
#define TEXT_MENU "1. Add a node\n2. Connect two nodes\n3. Display the current diagram\n4. Set a primary key\n5. Display the table\n6. Exit\n> "
#define TEXT_MENU_ERRORCHOICE "You entered a invalid number. Please enter a valid number again.\n> "

// General text set
#define TEXT_NODENUMBEGIN "The node '"
#define TEXT_ENDTEXT "'."
#define TEXT_COMPONENT_TABLEFORMAT " TYPE |  ID  |  NAME"
#define TEXT_CONNECTION_TABLEFORMAT "Connection | node | node |"

// Choice 1. Add new node text set. They make use of onShow.
#define TEXT_ADDNEWNODE_TYPE "What kind of node do you want to add?\n[A]Attribute [E]Entity [R]Relation\n> "
#define TEXT_ADDNEWNODE_ERRORTYPE "You entered an invalid node. Please enter a valid one again.\n> "
#define TEXT_ADDNEWNODE_NAME "Enter the name of this node:\n> "
#define TEXT_ADDNEWNODE_TITLE "Components:"

// Choice 2. Add connection between two node text set.
#define TEXT_CONNECTION_FIRSTNODE "Please enter the first node ID\n> "
#define TEXT_CONNECTION_SECONDNODE "Please enter the second node ID\n> "
#define TEXT_CONNECTION_ERRORNODE "The node ID you entered does not exist. Please enter a valid one again.\n> "
#define TEXT_CONNECTION_CONNECTFINISH "' has been connected to the node '"
#define TEXT_CONNECTION_NOTCONNECTION "' cannot be connected by the node '"
#define TEXT_CONNECTION_ITSELFCONNECTION "' cannot be connected to itself."
#define TEXT_CONNECTION_ALREADYCONNECTION "' has already been connected to component '"
#define TEXT_CONNECTION_CARDINALITY "Enter the type of the cardinality:"
#define TEXT_CONNECTION_CARDINALITYOPTION "[0]1 [1]N\n> "
#define TEXT_CONNECTION_CARDINALITYRELATIONSHIP "Its cardinality of the relationship is '"
#define TEXT_CONNECTION_FINISH "CONNECTOK"
#define TEXT_CONNECTION_TITLE "Connections:"

// Choice 4. SetPrimaryKey text set
#define TEXT_SETPRIMARYKEY_ERRORMESSAGE "' is not an entity. Please enter a valid one again.\n> "
#define TEXT_SETPRIMARYKEY_ENTITYTITLE "Entities:"
#define TEXT_SETPRIMARYKEY_ATTRIBUTETITLE "Attributes of the entity '"
#define TEXT_SETPRIMARYKEY_ENDTEXT "'"
#define TEXT_SETPRIMARYKEY_ENTERNODEID "Enter the ID of the entity:\n> "
#define TEXT_SETPRIMARYKEY_ATTRIBUTEOFENTITY "Attributes of the entity '"
#define TEXT_SETPRIMARYKEY_ENTERTWOATTRIBUTE "Enter the IDs of the attributes (use a comma to separate two attributes):\n> "


// Demarcation text set. They make use of onShow.
#define TEXT_DEMARCATION_COMPONENTTABLE "------------------------------------"
#define TEXT_DEMARCATION_CONNECTIONTABLE "--------------------------"
#define TEXT_DEMARCATIONTWO_CONPONENTTABLE "------+------+----------------------"
#define TEXT_DEMARCATIONTWO_CONNECTIONTABLE "-----------+------+------|"
#define TEXT_TWOSPACE "  "
#define TEXT_FIVESPACE "     "
#define TEXT_SPACELINE "   |"

// Parameter text set. They are parameters in some method.
#define PARAMETER_ATTRIBUTE "A"
#define PARAMETER_ENTITY "E"
#define PARAMETER_RELATIONSHOP "R"
#define PARAMETER_ALL "ALLTYPE"
#define PARAMETER_CARDINALITYOPTION_ONE "1"
#define PARAMETER_CARDINALITYOPTION_TWO "N"

#define SPLITERCHAR ","

#include <iostream>
#include <string>
#include "ERModel.h"
#include "Component.h"
#include "Connector.h"

using namespace std;

enum Option{Add = 1, Connect, GetTable, SetPK, GetERTable, Exit};
enum Cardinality{CardinalityOptionOne, CardinalityOptionTwo};

class TextUI
{
public:
	TextUI(ERModel*);
	~TextUI();
	void addNewNode();
	void addConnection();
	void setPrimaryKey();
	void displayComponentTable();
	void displayConnectionTable();
	void displayMenu();
	void displayEntityTable();
	void displayAttributeTable(int);
	void processCommand();
	string searchComponent(string);
	string searchEntity(string);
private:
	ERModel* erModel;
	bool isDisplayComponentsTable;
	bool isDisplayConnectionsTable;
};

#endif