#ifndef NODEATTRIBUTE
#define NODEATTRIBUTE

#include <QtCore/QCoreApplication>
#include <vector>
#include "Node.h"

class NodeAttribute : public Node
{
public:
	NodeAttribute();
	NodeAttribute(int,string);
	~NodeAttribute();
	void connectTo(Component*);
	bool canConnectTo(Component*);
private:
	vector<Node> connections;
};

#endif