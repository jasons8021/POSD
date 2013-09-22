#ifndef TEXTUI
#define TEXTUI

// Menu text set.
#define TEXT_MENU "1. Add a node\n2. Connect two nodes\n3. Display the current diagram\n4. Set a primary key\n5. Display the table\n6. Exit\n>"
#define TEXT_MENU_ERRORCHOICE "You entered a invalid number. Please enter a valid number again.\n>"

// Choice 1. Add new node text set. They make use of onShow.
#define TEXT_ADDNEWNODE_TYPE "What kind of node do you want to add?\n[A]Attribute [E]Entity [R]Relation\n>"
#define TEXT_ADDNEWNODE_ERRORTYPE "You entered an invalid node. Please enter a valid one again.\n>"
#define TEXT_ADDNEWNODE_NAME "Enter the name of this node:\n>"
#define TEXT_ADDNEWNODE_CONTAINSCOMPONENTS "Components:"
#define TEXT_ADDNEWNODE_TABLEFORMAT " TYPE |  ID  |  NAME"

//Choice 2. Add connection between two node text set.
#define TEXT_CONNECTION_FIRSTNODE "Please enter the first node ID\n>"
#define TEXT_CONNECTION_SECONDNODE "Please enter the second node ID\n>"
#define TEXT_CONNECTION_ERRORNODE "The node ID you entered does not exist. Please enter a valid one again.\n>"
// TEXT_CONNECTION_CONNECTFINISH and TEXT_CONNECTION_NOTCONNECTION are composed of TEXTBEGIN, CONNECTFINISH (or NOTCONNECTION) and TEXTEND
// TEXT_CONNECTION_CONNECTFINISH is showed when connection finish.
// TEXT_CONNECTION_NOTCONNECTION is showed when connection failed.
// TEXT_CONNECTION_ALREADYCONNECTION is showed when connection already have it.
#define TEXT_CONNECTION_TEXTBEGIN "The node '"
#define TEXT_CONNECTION_CONNECTFINISH "' has been connected to the node '"
#define TEXT_CONNECTION_NOTCONNECTION "' cannot be connected by the node '"
#define TEXT_CONNECTION_ITSELFCONNECTION "' cannot be connected to itself."
#define TEXT_CONNECTION_ALREADYCONNECTION "' has already been connected to component '"
#define TEXT_CONNECTION_TEXTEND "'."
#define TEXT_CONNECTION_CARDINALITY "Enter the type of the cardinality:"
#define TEXT_CONNECTION_CARDINALITYOPTION "[0]1 [1]N\n>"
#define TEXT_CONNECTION_CARDINALITYRELATIONSHIP "Its cardinality of the relationship is '"
#define TEXT_CONNECTION_FINISH "CONNECTOK"

// Demarcation text set. They make use of onShow.
#define TEXT_DEMARCATION "------------------------------------"
#define TEXT_DEMARCATIONTWO "------+------+----------------------"
#define TEXT_SPACE "  "
#define TEXT_SPACELINE "   |"

// Parameter text set. They are parameters in some method.
#define PARAMETER_ATTRIBUTE "A"
#define PARAMETER_ENTITY "E"
#define PARAMETER_RELATIONSHOP "R"

#include <iostream>
#include <string>
#include "ERModel.h"
#include "Component.h"
#include "Connector.h"

using namespace std;

enum Option{Add = 1, Connect, GetClassDiagram, SetPrimaryKey, GetTable, Exit};

class TextUI
{
public:
	TextUI(ERModel*);
	~TextUI();
	void addNewNode();
	void addConnection();
	void displayComponentTable();
	void displayConnectionTable();
	void displayMenu();
	void processCommand();
	string searchComponent();
private:
	ERModel* erModel;
	vector<Component*> erModelComponents;
	vector<Connector*> erModelConnections;
};

#endif