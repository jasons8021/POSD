#ifndef NODEATTRIBUTE
#define NODEATTRIBUTE

#define PARAMETER_ATTRIBUTE "A"
#define PARAMETER_ENTITY "E"
#define PARAMETER_RELATIONSHOP "R"

#include <vector>
#include "Node.h"

using namespace std;

class NodeAttribute : public Node
{
public:
	NodeAttribute();
	NodeAttribute(int, string);
	~NodeAttribute();
	virtual void connectTo(Component*);
	virtual bool canConnectTo(Component*);
};

#endif