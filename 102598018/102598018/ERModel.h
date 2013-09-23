#ifndef ERMODEL
#define ERMODEL

#define TEXT_ERROR_MESSAGEBEGIN "The node '"
#define TEXT_CONNECTION_CONNECTFINISH "' has been connected to the node '"
#define TEXT_CONNECTION_NOTCONNECTION "' cannot be connected by the node '"
#define TEXT_CONNECTION_ITSELFCONNECTION "' cannot be connected to itself."
#define TEXT_CONNECTION_ALREADYCONNECTION "' has already been connected to component '"
#define TEXT_CONNECTION_TEXTEND "'."
#define TEXT_CONNECTION_FINISH "CONNECTOK"

#define TEXT_TWOSPACE "  "
#define TEXT_FIVESPACE "     "
#define TEXT_SPACELINE "   |"
#define TEXT_ENDLINE "\n"

#define PARAMETER_SPACE ""
#define PARAMETER_ATTRIBUTE "A"
#define PARAMETER_ENTITY "E"
#define PARAMETER_RELATIONSHOP "R"
#define PARAMETER_CONNECTOR "C"
#define PARAMETER_ALL "ALLTYPE"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Component.h"
#include "ComponentFactory.h"

using namespace std;

class ERModel
{
public:
	ERModel();
	~ERModel();
	void addNode(string, string);
	void addConnection(int, int, string);
	void setPrimaryKeyEntity(int);
	void setPrimaryKeyAttribute(string);
	bool searchComponentExist(string, string);
	bool connectedItself(Component*, Component*);
	bool connectedTypeCheck(Component*, Component*);
	bool connectedAlready(Component*, Component*);
	bool checkSetCardinality(int, int);
	string checkConnectionState(Component*, Component*);
	string getCheckConnectionStateMessage(int, int);
	string getComponentsTable(string);
	string getConnectionTable();
	string integerToString(int);
	Component* searchComponent(int);
private:
	int componentID;
	vector<Component*> components;
	vector<Connector*> connections;
};

#endif