#ifndef NODE
#define NODE

#define PARAMETER_SPACE ""

#include <vector>
#include "Component.h"

using namespace std;

class Node : public Component{
public:
	Node();
	Node(int, string, string);
	~Node();
	virtual void connectTo(Component*);
	virtual string canConnectTo(Component*);
};

#endif