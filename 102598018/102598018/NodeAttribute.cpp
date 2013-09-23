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

bool NodeAttribute::canConnectTo( Component* targetNode )
{
	if (targetNode->getType() == PARAMETER_ENTITY && !(connectedEntity))
		return true;
	else
		return false;
}
