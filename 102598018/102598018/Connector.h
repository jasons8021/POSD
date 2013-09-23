#ifndef CONNECTOR
#define CONNECTOR

#define PARAMETER_CONNECTOR "C"
#define PARAMETER_SPACE ""

#include <vector>
#include "Component.h"

class Connector : public Component
{
public:
	Connector();
	Connector(int, string);
	~Connector();
	int getSourceNodeID();
	int getDestinationNodeID();
	void setConnectedNode(Component*,Component*);
	void setSourceNode(Component*);
	void setDestinationNode(Component*);
	string getSourceNodeType();
	string getDestinationNodeType();
	string getSourceNodeText();
	string getDestinationNodeText();
	Component* getSourceNode();
	Component* getDestinationNode();
	virtual void connectTo(Component*);
	virtual string canConnectTo(Component*);
private:
	Component* sourceNode;
	Component* destinationNode;
};

#endif