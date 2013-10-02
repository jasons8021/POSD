#ifndef ERMODEL_H_
#define ERMODEL_H_

#define TEXT_GETERDIAGRAM_ENDKEY ")"
#define TEXT_GETERDIAGRAM_PK "PK("
#define TEXT_GETERDIAGRAM_SPLITER ", "
#define TEXT_GETERDIAGRAM_FK ", FK("

#define TEXT_ONESPACE " "
#define TEXT_TWOSPACE "  "
#define TEXT_FIVESPACE "     "
#define TEXT_SPACELINE "   |"
#define TEXT_LINESPACE "|  "
#define TEXT_COMMASPACE ", "
#define TEXT_ENDLINE "\n"

#define PARAMETER_SPACE ""
#define PARAMETER_ATTRIBUTE "A"
#define PARAMETER_ENTITY "E"
#define PARAMETER_RELATIONSHIP "R"
#define PARAMETER_CONNECTOR "C"
#define PARAMETER_ALL "ALLTYPE"
#define PARAMETER_RELATIONSHIPLOWERBOUND 2
#define SPLITERCHAR ","


#include <iostream>
#include <fstream>
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
	virtual ~ERModel();
	void addNode(string, string);
	void addConnection(int, int, string);
	void setCardinality(Component*, Component*, string);
	void setPrimaryKey(vector<int>);
	void setForeignKey();
	void saveERDiagram(string);
	bool searchComponentExist(string, string);
	bool connectedItself(Component*, Component*);
	bool connectedTypeCheck(Component*, Component*);
	bool connectedAlready(Component*, Component*);
	bool checkSetCardinality(int, int);
	bool searchComponentConnection(int, string, vector<Component*>);
	bool searchEntityConnection(int, int, string);
	bool checkOneToOne();
	string checkConnectionState(Component*, Component*);
	string getCheckConnectionStateMessage(int, int);
	string getComponentsTable(string);
	string getComponentDataList(string, vector<Component*>);
	string getConnectionTable();
	string getERDiagramTable();
	string searchAttributeOfEntity(int);
	string integerToString(int);
	string getAttributeContents(vector<Component*>);
	string searchForeignKey(int);
	Component* searchComponent(int);
	vector<int> oneToOne(NodeRelationship*);
	vector<Component*> getSpecificTypeComponentSet(string, vector<Component*>);
private:
	int _componentID;
	vector<Component*> _components;
	vector<Connector*> _connections;
};

#endif