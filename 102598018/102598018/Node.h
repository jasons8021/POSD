#ifndef NODE
#define NODE

#include <vector>
#include "Component.h"

using namespace std;

class Node : public Component{
public:
	Node();
	Node(int, string, string);
	~Node();
	virtual void connectTo(Component*);
	virtual bool canConnectTo(Component*);
};

#endif