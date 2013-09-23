#include "NodeAttribute.h"

NodeAttribute::NodeAttribute()
{
	connectedEntity = false;
}

NodeAttribute::NodeAttribute( int id, string text ) : Node( id, PARAMETER_ATTRIBUTE, text)
{
	connectedEntity = false;
}

NodeAttribute::~NodeAttribute()
{
}

void NodeAttribute::connectTo( Component* targetNode )
{
	Component::connectTo(targetNode);
	connectedEntity = true;
}

string NodeAttribute::canConnectTo( Component* targetNode )
{
	string checkMessage = Component::canConnectTo(targetNode);

	if (targetNode->getType() == PARAMETER_ENTITY && !(connectedEntity))
	{
		if (checkMessage == TEXT_CONNECTION_FINISH)		// TargetNode can be connected.
			return TEXT_CONNECTION_FINISH;
		else											// Already connected or connected itself
			return checkMessage;
	}
	else												// Type error
		return TEXT_NODENUMBEGIN + targetNode->getIDString() + TEXT_CONNECTION_NOTCONNECTION + this->getIDString() + TEXT_ENDTEXT;
}
