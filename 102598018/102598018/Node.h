#ifndef NODE
#define NODE

#include <QtCore/QCoreApplication>
#include <vector>
#include "Component.h"

using namespace std;

class Node : public Component{
public:
	Node();
	Node(int, string, string);
	~Node();
	void connectTo(Component*);
	bool canConnectTo(Component*);
private:
	vector<Node> connections;
};

#endif