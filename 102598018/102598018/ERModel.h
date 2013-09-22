#ifndef ERMODEL
#define ERMODEL

#define TEXT_CONNECTION_TEXTBEGIN "The node '"
#define TEXT_CONNECTION_CONNECTFINISH "' has been connected to the node '"
#define TEXT_CONNECTION_NOTCONNECTION "' cannot be connected by the node '"
#define TEXT_CONNECTION_ITSELFCONNECTION "' cannot be connected to itself."
#define TEXT_CONNECTION_ALREADYCONNECTION "' has already been connected to component '"
#define TEXT_CONNECTION_TEXTEND "'."
#define TEXT_CONNECTION_FINISH "CONNECTOK"

#define PARAMETER_SPACE ""
#define PARAMETER_CONNECTOR "C"


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
	void getTable();
	bool searchComponentExist(string);
	bool connectedItself(Component*, Component*);
	bool connectedTypeCheck(Component*, Component*);
	bool connectedAlready(Component*, Component*);
	string addConnection(int, int);
	string integerToString(int);
	Component* searchComponent(int);
	vector<Component*> getComponents();
	vector<Connector*> getConnections();
private:
	int componentID;
	vector<Component*> components;
	vector<Connector*> connections;
};

#endif