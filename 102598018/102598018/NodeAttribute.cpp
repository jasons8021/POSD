#include "NodeAttribute.h"

NodeAttribute::NodeAttribute()
{
}

NodeAttribute::NodeAttribute( int id, string text ) : Node( id, PARAMETER_ATTRIBUTE, text)
{
}

NodeAttribute::~NodeAttribute()
{
}

void NodeAttribute::connectTo( Component* targetNode )
{

}

bool NodeAttribute::canConnectTo( Component* targetNode )
{
	if (targetNode->getType() == PARAMETER_ENTITY)
		return true;
	else
		return false;
}
