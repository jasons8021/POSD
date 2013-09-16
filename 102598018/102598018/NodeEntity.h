#ifndef NODEENTITY
#define NODEENTITY

#include <QtCore/QCoreApplication>
#include <vector>
#include "Node.h"

using namespace std;

class NodeEntity : public Node
{
public:
	NodeEntity();
	NodeEntity(int, string);
	~NodeEntity();
	void connectTo(Component*);
	bool canConnectTo(Component*);
private:
	vector<Node> connections;
};

#endif