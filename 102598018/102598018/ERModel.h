#ifndef ERMODEL
#define ERMODEL

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

#define SPLITERCHAR ","

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
	void setPrimaryKey(int, string);
	bool searchComponentExist(string, string);
	bool connectedItself(Component*, Component*);
	bool connectedTypeCheck(Component*, Component*);
	bool connectedAlready(Component*, Component*);
	bool checkSetCardinality(int, int);
	string checkConnectionState(Component*, Component*);
	string getCheckConnectionStateMessage(int, int);
	string getComponentsTable(string);
	string getComponentDataList(string, vector<Component*>);
	string getConnectionTable();
	string searchAttributeOfEntity(int);
	string integerToString(int);
	Component* searchComponent(int);
	vector<int> splitPrimaryKey(string);
private:
	int componentID;
	vector<Component*> components;
	vector<Connector*> connections;
};

#endif