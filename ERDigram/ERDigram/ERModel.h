#ifndef ERMODEL_H_
#define ERMODEL_H_

#define TEXT_CONNECTION_CANCONNECT "CANCONNECT"

#define TEXT_GETERDIAGRAM_ENDKEY ")"
#define TEXT_GETERDIAGRAM_PK "PK("
#define TEXT_GETERDIAGRAM_FK ", FK("

#define TEXT_ONESPACE " "
#define TEXT_TWOSPACE "  "
#define TEXT_FIVESPACE "     "
#define TEXT_SPACELINE "   |"
#define TEXT_LINESPACE "|  "
#define TEXT_COMMASPACE ", "
#define TEXT_ENDLINE "\n"
#define COMMA ","

#define PARAMETER_NULL ""
#define PARAMETER_ATTRIBUTE "A"
#define PARAMETER_ENTITY "E"
#define PARAMETER_RELATIONSHIP "R"
#define PARAMETER_CONNECTOR "C"
#define PARAMETER_ALL "ALLTYPE"
#define PARAMETER_RELATIONSHIPLOWERBOUND 2
#define PARAMETER_COMPONENTSTABLE 0
#define PARAMETER_CONNECTIONSTABLE 1

#define SPLITTERBYBACKSLASH "\\"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <direct.h>
#include "Component.h"
#include "ComponentFactory.h"
#include "Toolkit.h"

using namespace std;

class ERModel
{
public:
	ERModel();
	virtual ~ERModel();
	int recoveryConnection(vector<string>, int, string);
	void addNode(string, string);
	void addConnection(int, int, string);
	void setCardinality(Component*, Component*, string);
	void setPrimaryKey(int, vector<int>);
	void setForeignKey();
	void loadERDiagram(string);
	void saveERDiagram(string);
	void creatFilePath(string);
	void recoveryFile(vector<vector<string>>);
	void recoveryAllComponent(vector<string>, vector<string>);
	void recoveryPrimaryKey(vector<string>);
	void deleteFunction(int);
	void deleteComponent(Component*);
	void deleteTableSet(int, vector<Component*>, int);
	void deleteConnection(Component*);
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
	string getAttributeContents(vector<Component*>);
	string searchForeignKey(int);
	string saveComponentTable();
	string saveConnectionTable();
	string savePrimaryKeyTable();
	Component* searchComponent(int);
	vector<int> oneToOne(NodeRelationship*);
	vector<Component*> searchSpecificTypeComponentSet(string, vector<Component*>);
	vector<Component*> searchConnection(int);
	vector<Component*> searchRelatedComponent(int);
	vector<vector<string>> classifyInputFile(string);
	pair<string,vector<string>> splitter(string);
private:
	int _componentID;
	vector<Component*> _components;
	vector<Component*> _connections;
};

#endif