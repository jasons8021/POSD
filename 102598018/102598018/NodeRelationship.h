#ifndef NODERELATIONAL
#define NODERELATIONAL

#include <QtCore/QCoreApplication>
#include <vector>
#include "Node.h"

using namespace std;

class NodeRelationship : public Node
{
public:
	NodeRelationship();
	NodeRelationship(int, string);
	~NodeRelationship();
	void connectTo(Component*);
	bool canConnectTo(Component*);
private:
	vector<Node> connections;
};

#endif