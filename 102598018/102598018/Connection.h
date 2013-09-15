#ifndef CONNECTION
#define CONNECTION

#include <QtCore/QCoreApplication>
#include <vector>
#include "Component.h"
#include "Node.h"

class Connection : Component
{
public:
	Connection();
	~Connection();
	void connectTo(Component*);
	bool canConnectTo(Component*);
private:
	vector<Node> connections;
};

#endif