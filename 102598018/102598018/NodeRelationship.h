#ifndef NODERELATIONAL
#define NODERELATIONAL

#define PARAMETER_ATTRIBUTE "A"
#define PARAMETER_ENTITY "E"
#define PARAMETER_RELATIONSHOP "R"

#include <vector>
#include "Node.h"

using namespace std;

class NodeRelationship : public Node
{
public:
	NodeRelationship();
	NodeRelationship(int, string);
	~NodeRelationship();
	virtual void connectTo(Component*);
	virtual bool canConnectTo(Component*);
};

#endif