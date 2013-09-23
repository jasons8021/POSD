#ifndef NODEENTITY
#define NODEENTITY

#define PARAMETER_ATTRIBUTE "A"
#define PARAMETER_ENTITY "E"
#define PARAMETER_RELATIONSHOP "R"

#include <vector>
#include "Node.h"

using namespace std;

class NodeEntity : public Node
{
public:
	NodeEntity();
	NodeEntity(int, string);
	~NodeEntity();
	virtual void connectTo(Component*);
	virtual bool canConnectTo(Component*);
};

#endif