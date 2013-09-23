#ifndef NODEATTRIBUTE
#define NODEATTRIBUTE

#define TEXT_NODENUMBEGIN "The node '"
#define TEXT_CONNECTION_NOTCONNECTION "' cannot be connected by the node '"
#define TEXT_CONNECTION_ITSELFCONNECTION "' cannot be connected to itself."
#define TEXT_CONNECTION_ALREADYCONNECTION "' has already been connected to component '"
#define TEXT_ENDTEXT "'."
#define TEXT_CONNECTION_FINISH "CONNECTOK"

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
	virtual string canConnectTo(Component*);
private:
	bool connectedEntity;
};

#endif